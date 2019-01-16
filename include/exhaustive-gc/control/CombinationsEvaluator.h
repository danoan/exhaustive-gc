#ifndef EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
#define EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H

#include <boost/filesystem/operations.hpp>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"

#include "DIPaCUS/components/Transform.h"
#include "geoc/api/api.h"
#include "gcurve/GluedCurveRange.h"

#include <lazy-comb/interface/IMarkedMapChecker.h>
#include "lazy-comb/LazyCombinations.h"

#include <exhaustive-gc/check-elem/CheckableSeedPair.h>





namespace ExhaustiveGC
{
    template<int maxPairs>
    class CombinationsEvaluator
    {
    protected:
        typedef DGtal::Z2i::Curve::ConstIterator SCellIterator;
        typedef DGtal::Circulator<SCellIterator> SCellCirculator;

        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef std::vector<CheckableSeedPair> CheckableSeedList;
        typedef LazyCombinator::LazyCombinations <CheckableSeedList, maxPairs> MyLazyCombinations;

        typedef GCurve::GluedCurveRange GluedCurveRange;

        typedef LazyCombinator::IMarkedMapChecker<CheckableSeedPair> Checker;

    public:
        CombinationsEvaluator(){}
        ~CombinationsEvaluator(){ for(auto itc=checkers.begin();itc!=checkers.end();++itc) delete *itc; }
        CombinationsEvaluator(const CombinationsEvaluator<maxPairs>&){ throw std::runtime_error("Operation not allowed!");}
        CombinationsEvaluator& operator=(const CombinationsEvaluator<maxPairs>&){ throw std::runtime_error("Operation not allowed!");}

        void addChecker(Checker* c)
        {
            checkers.push_back( c );
        }

        void operator()(Curve& minCurve,
                        CheckableSeedPair bestSeedCombination[maxPairs],
                        std::vector<CheckableSeedPair> &pairList,
                        KSpace &KImage,
                        int maxSimultaneousPairs,
                        std::string outputFolder="",
                        double currLength=0)
        {
            bool saveEPS = outputFolder!="";

            double minEnergyValue = 100;
            double currentEnergyValue;

            MyLazyCombinations myCombinations(pairList);
            for(auto itc=checkers.begin();itc!=checkers.end();++itc) {
                for (auto it = pairList.begin(); it != pairList.end(); ++it) {
                    (*itc)->unmark(*it);
                }
                myCombinations.addConsistencyChecker(*itc);
            }

            int n = 0;

            Board2D board;
            if(saveEPS)
            {
                outputFolder += std::to_string(maxPairs);
                boost::filesystem::create_directories(outputFolder);
            }


            CheckableSeedPair seedCombination[maxPairs];
            double nlength;
            double f = 1;
            while (myCombinations.next(seedCombination)) {
                Curve curve;
                std::map<KSpace::SCell, double> weightMap;

                createCurve(curve, seedCombination, maxPairs);
                DIPaCUS::Transform::eliminateLoops(curve, KImage, curve);

                GEOC::API::GridCurve::Curvature::symmetricClosed(KImage,
                                                                 curve.begin(),
                                                                 curve.end(),
                                                                 weightMap);

                if(currLength!=0)
                {
                    std::vector<double> localLengthEstimations;

                    //TODO::Better use a global estimator
                    GEOC::API::GridCurve::Length::lmdssClosed(KImage,curve.begin(),curve.end(),localLengthEstimations,1.0);

                    nlength=0;
                    for(int i=0;i<localLengthEstimations.size();++i)
                    {
                        nlength+=localLengthEstimations[i];
                    }

                    f = currLength/nlength;
                }

                currentEnergyValue = energyValue(curve, weightMap)*f;
                if (currentEnergyValue < minEnergyValue) {
                    std::cout << "Updated min energy value: " << minEnergyValue << " -> " << currentEnergyValue
                              << std::endl;
                    minEnergyValue = currentEnergyValue;

                    minCurve = curve;
                    bestSeedCombination[0] = seedCombination[0];

                    if(saveEPS)
                    {
                        board.clear();
                        board << curve;
                        board.saveEPS((outputFolder + "/" + std::to_string(n) + ".eps").c_str());
                    }
                }

                ++n;
            }
            std::cout << maxPairs << "-Combination: " << n << std::endl;
            std::cout << "Min energy value: " << minEnergyValue << std::endl;

            CombinationsEvaluator<maxPairs - 1> next;
            next(pairList, KImage, maxSimultaneousPairs);
        }


        void operator()(std::vector<CheckableSeedPair> &pairList,
                        KSpace &KImage,
                        int maxSimultaneousPairs,
                        std::string outputFolder="")
        {
            Curve minCurve;
            CheckableSeedPair seedCombination[10];
            this->operator()(minCurve,seedCombination,pairList,KImage,maxSimultaneousPairs,outputFolder);
        }

        void operator()(Curve& minCurve,
                        std::vector<CheckableSeedPair> &pairList,
                        KSpace &KImage,
                        int maxSimultaneousPairs,
                        std::string outputFolder="")
        {
            CheckableSeedPair seedCombination[10];
            this->operator()(minCurve,seedCombination,pairList,KImage,maxSimultaneousPairs,outputFolder);
        }

    private:
        void addIntervalSCells(std::vector<KSpace::SCell>& vectorOfSCells,
                               SCellCirculator begin,
                               SCellCirculator end)
        {
            SCellCirculator it = begin;
            while (it != end)
            {
                vectorOfSCells.push_back(*it);
                ++it;
            }
            vectorOfSCells.push_back(*it);
        }

        void addSeedPairSCells(std::vector<KSpace::SCell>& vectorOfSCells,
                               CheckableSeedPair& currentPair,
                               CheckableSeedPair& nextPair)
        {
            ConnectorSeed inToExtSeed = currentPair.data().first;
            ConnectorSeed extToIntSeed = currentPair.data().second;

            if( currentPair.data().first.cType != ConnectorType::internToExtern)
            {
                std::cout << "ERROR" << std::endl;
            }

            if( currentPair.data().second.cType != ConnectorType::externToIntern)
            {
                std::cout << "ERROR" << std::endl;
            }


            vectorOfSCells.push_back(inToExtSeed.connectors[0]);
            addIntervalSCells(vectorOfSCells,inToExtSeed.secondCirculator,extToIntSeed.firstCirculator);


            ConnectorSeed nextIntToExtSeed = nextPair.data().first;
            vectorOfSCells.push_back(extToIntSeed.connectors[0]);
            addIntervalSCells(vectorOfSCells,extToIntSeed.secondCirculator,nextIntToExtSeed.firstCirculator);
        }

        void createCurve(Curve& curve,
                         CheckableSeedPair* seedPairs,
                         int totalPairs)
        {
            typedef KSpace::SCell SCell;
            std::vector<SCell> scells;

            CheckableSeedPair currentPair;
            CheckableSeedPair nextPair;
            for(int i=0;i<totalPairs;++i)
            {
                if(i==(totalPairs-1))
                {
                    currentPair = seedPairs[totalPairs-1];
                    nextPair = seedPairs[0];
                }else
                {
                    currentPair = seedPairs[i];
                    nextPair = seedPairs[i+1];
                }

                addSeedPairSCells(scells,currentPair,nextPair);
            }

            curve.initFromSCellsVector(scells);
        }

        double energyValue(Curve& curve, std::map<KSpace::SCell,double>& weightMap)
        {
            auto it = curve.begin();
            double v=0;
            do
            {
                v+=weightMap[*it];
                ++it;
            }while(it!=curve.end());

            return v;
        }



    private:
        std::vector< Checker* > checkers;
    };
}


template<>
class CombinationsEvaluator<0>:public CombinationsEvaluator<1>
{
public:
    void operator()(std::vector<CheckableSeedPair> &pairList, KSpace& KImage, int maxSimultaneousPairs)
    {
        return;
    }
};

#endif //EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
