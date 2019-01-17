#ifndef EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
#define EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H

#include <boost/filesystem/operations.hpp>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"

#include "DIPaCUS/components/Transform.h"
#include "geoc/api/api.h"

#include <lazy-comb/interface/IMarkedMapChecker.h>
#include "lazy-comb/LazyCombinations.h"

#include <exhaustive-gc/check-elem/CheckableSeedPair.h>
#include "exhaustive-gc/control/CurveFromJoints.h"


namespace ExhaustiveGC
{
    template<int maxPairs>
    class CurveCandidatesGenerator
    {
    protected:
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef std::map<KSpace::SCell, double> WeightMap;

        typedef std::vector<CheckableSeedPair> CheckableSeedVector;
        typedef LazyCombinator::LazyCombinations <CheckableSeedVector, maxPairs> MyLazyCombinations;

        typedef LazyCombinator::IMarkedMapChecker<CheckableSeedPair> Checker;

    private:
        void initCheckers(MyLazyCombinations& myCombinations,
                          const CheckableSeedVector &csVector);

        double lengthFactor(double currLength,
                            const KSpace& KImage,
                            Curve::ConstIterator begin,
                            Curve::ConstIterator end);

        void computeWeightMap(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              WeightMap& weightMap);

    public:
        CurveCandidatesGenerator(){}
        ~CurveCandidatesGenerator(){ for(auto itc=checkers.begin();itc!=checkers.end();++itc) delete *itc; }
        CurveCandidatesGenerator(const CurveCandidatesGenerator<maxPairs>&){ throw std::runtime_error("Operation not allowed!");}
        CurveCandidatesGenerator& operator=(const CurveCandidatesGenerator<maxPairs>&){ throw std::runtime_error("Operation not allowed!");}

        void registerChecker(Checker* c)
        {
            checkers.push_back( c );
        }

        void operator()(Curve& minCurve,
                        CheckableSeedVector &csVector,
                        KSpace &KImage,
                        CheckableSeedPair bestCombination[maxPairs],
                        std::string outputFolder="",
                        double currLength=0);


    private:
        double energyValue(Curve& curve, std::map<KSpace::SCell,double>& weightMap);

    private:
        std::vector< Checker* > checkers;
    };
}

#include "CurveCandidatesGenerator.hpp"


#endif //EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
