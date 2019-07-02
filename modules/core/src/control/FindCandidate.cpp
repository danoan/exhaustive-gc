#include "exhaustive-gc/core/control/FindCandidate.h"

namespace ExhaustiveGC
{
    namespace Core
    {
        namespace FindCandidate
        {
            void initCheckers(MyLazyCombinations& myCombinations,
                              const CCGData& ccgData)
            {
                for(auto itc=ccgData.checkers.begin();itc!=ccgData.checkers.end();++itc) {
                    for (auto it = ccgData.csVector.begin(); it != ccgData.csVector.end(); ++it) {
                        (*itc)->unmark(*it);
                    }
                    myCombinations.addConsistencyChecker(*itc);
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


                MyLazyCombinations myCombinations(ccgData.csVector,ccgData.maxPairs);
                initCheckers(myCombinations,ccgData);

                MyMultiThreadLC multithreadLC(nThreads,threadSize);
                multithreadLC.start(myCombinations,&exhaustCombinator,combinatorCallback,ccgData);

                for(auto it=multithreadLC.threadInputVector.begin();it!=multithreadLC.threadInputVector.end();++it)
                {
                    if( it->data.energyValue < minEnergyValue )
                    {
                        std::cout << "Updated min energy value: " << minEnergyValue << " -> " << it->data.energyValue
                                  << std::endl;
                        minEnergyValue = it->data.energyValue;
                        minCurve = it->data.curve;
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

            void* exhaustCombinator( void* params)
            {
                MyThreadInput* ti = (MyThreadInput*) params;
                if(!ti->data.initialized)
                {
                    ti->data.energyValue=1e20;
                    ti->data.initialized=true;
                }

                ti->data.foundCandidate=false;

                std::vector<ContainerValueType> element(ti->params.maxPairs);
                int c=0;
                while( ti->combPointer->next(element.data()) && c<ti->elems )
                {
                    ti->callback(element.data(),ti);
                    if(ti->params.strategy==Core::Strategy::First) break;
                    ++c;
                }

            }

            void combinatorCallback(ContainerValueType* seedCombination, MyThreadInput* ti)
            {
                const Params& params = ti->params;

                Curve curve;
                std::map<KSpace::SCell, double> weightMap;

                CurveFromJoints(curve, seedCombination, params.maxPairs);


                double currentEnergyValue;
                if(params.preserveConnectedeness)
                    currentEnergyValue = computeEnergyValue(params.ds,curve,params.KImage,params.energyInput);
                else
                    currentEnergyValue = Energy::energyValue(curve,params.KImage,params.energyInput);

                if (currentEnergyValue < ti->data.energyValue)
                {
                    ti->data.energyValue = currentEnergyValue;
                    ti->data.curve = curve;
                    ti->data.foundCandidate = true;
                }
            }
        }

    }
}



