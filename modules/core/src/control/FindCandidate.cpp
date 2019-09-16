#include "exhaustive-gc/core/control/FindCandidate.h"

namespace ExhaustiveGC
{
    namespace Core
    {
        namespace FindCandidate
        {
            void initCheckers(const CCGData& ccgData)
            {
                for(auto itc=ccgData.checkers.begin();itc!=ccgData.checkers.end();++itc) {
                    for (auto it = ccgData.csVector.begin(); it != ccgData.csVector.end(); ++it) {
                        (*itc)->unmark(*it);
                    }
                }
            }

            bool findCandidate(Curve& minCurve,
                               const double energyValue,
                               const CCGData& ccgData,
                               int nThreads,
                               int threadSize)
            {
                double minEnergyValue = energyValue;
                bool candidateFound=false;


                auto range = magLac::Core::addRange(ccgData.csVector.begin(),ccgData.csVector.end(),ccgData.maxPairs);
                auto mrc = magLac::Core::Single::createCombinator(range);
                typedef decltype(mrc) MyCombinator;
                typedef MyCombinator::MyResolver MyResolver;
                typedef ThreadInput<MyCombinator> MyThreadInput;
                typedef ThreadTrigger<MyThreadInput> MyThreadTrigger;

                initCheckers(ccgData);

                MyThreadTrigger::CallbackFunction cbf = [](MyResolver& resolver,MyThreadInput& ti, ThreadControl& tc) mutable
                {
                    const MyThreadInput::Params& params = ti.params;
                    std::vector<ContainerValueType> seedCombination(params.maxPairs);
                    resolver >> seedCombination;

                    bool validCombination=true;
                    for(auto it=ti.params.checkers.begin();it!=ti.params.checkers.end();++it)
                    {
                        for(auto itSeedPair=seedCombination.begin();itSeedPair!=seedCombination.end();++itSeedPair)
                        {
                            if( (*it)->operator()(*itSeedPair) )
                            {
                                (*it)->mark(*itSeedPair);
                            }
                            else
                            {
                                validCombination=false;
                                break;
                            }
                        }
                        if(!validCombination) break;
                    }

                    for(auto it=ti.params.checkers.begin();it!=ti.params.checkers.end();++it)
                    {
                        for(auto itSeedPair=seedCombination.begin();itSeedPair!=seedCombination.end();++itSeedPair)
                        {
                            (*it)->unmark(*itSeedPair);
                        }
                    }



                    if(validCombination)
                    {
                        Curve curve;
                        CurveFromJoints(curve, seedCombination.data(), params.maxPairs);


                        double currentEnergyValue;
                        if(params.preserveConnectedeness)
                            currentEnergyValue = computeEnergyValue(params.ds,curve,params.KImage,params.energyInput);
                        else
                            currentEnergyValue = Energy::energyValue(curve,params.KImage,params.energyInput);

                        if (currentEnergyValue < ti.vars.energyValue)
                        {
                            ti.vars.energyValue = currentEnergyValue;
                            ti.vars.curve = curve;
                            ti.vars.foundCandidate = true;


                            if(ti.params.strategy==Core::Strategy::First) tc.stop();
                        }
                    }
                };


                MyThreadTrigger mtTrigger(nThreads,threadSize,cbf);
                mtTrigger.start(mrc,ccgData);

                for(auto it=mtTrigger.threadInputVector.begin();it!=mtTrigger.threadInputVector.end();++it)
                {
                    if( it->vars.energyValue < minEnergyValue )
                    {
                        std::cout << "Updated min energy value: " << minEnergyValue << " -> " << it->vars.energyValue
                                  << std::endl;
                        minEnergyValue = it->vars.energyValue;
                        minCurve = it->vars.curve;
                        candidateFound = true;
                    }
                }

                std::cout << "Min energy value: " << minEnergyValue << std::endl;

                return candidateFound;
            }

            double computeEnergyValue(const DigitalSet& ds,
                                      const Curve& curve,
                                      const KSpace& KImage,
                                      const Energy::EnergyInput& energyInput)
            {
                std::vector< std::set<Point> > components;

                DigitalSet startingPS = ds;

                auto outerPixelsRange = curve.getOuterPointsRange();
                for(auto it=outerPixelsRange.begin();it!=outerPixelsRange.end();++it)
                {
                    startingPS.erase( *it );
                }

                double value=0;
                std::vector< DIPaCUS::Misc::ConnectedComponent > vcc;
                DIPaCUS::Misc::getConnectedComponents(vcc,startingPS);

                DigitalSet compDS(ds.domain());
                value = Energy::energyValue(curve, KImage, energyInput);
                if(vcc.size()!=1)
                {
                    int s=0;
                    for(auto it=vcc.begin();it!=vcc.end();++it)
                    {
                        if(it->size()>10) ++s;
                        if(s==2)
                        {
                            value=1e20;
                            break;
                        }
                    }
                }

                return value;

            }

        }

    }
}



