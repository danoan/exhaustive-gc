#ifndef EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
#define EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H

#include <boost/filesystem/operations.hpp>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"

#include "DIPaCUS/components/Transform.h"
#include "geoc/api/api.h"

#include <lazy-comb/interface/IMarkedMapChecker.h>
#include "lazy-comb/LazyCombinations.h"

#include <exhaustive-gc/core/check-elem/CheckableSeedPair.h>
#include <exhaustive-gc/core/model/EnergyType.h>
#include "CurveFromJoints.h"


namespace ExhaustiveGC
{
    template<int maxPairs>
    class CurveCandidatesGenerator
    {
    public:
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef LazyCombinator::IMarkedMapChecker<CheckableSeedPair> Checker;
        typedef std::vector<CheckableSeedPair> CheckableSeedVector;

    private:
        typedef std::map<KSpace::SCell, double> WeightMap;
        typedef LazyCombinator::LazyCombinations <CheckableSeedVector, maxPairs> MyLazyCombinations;

    private:
        void initCheckers(MyLazyCombinations& myCombinations,
                          const CheckableSeedVector &csVector);


        void squaredCurvature(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              WeightMap& weightMap);

        void intSquaredCurvature(const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end,
                                 WeightMap& weightMap);

        void computeWeightMap(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              EnergyType energy,
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
                        const CheckableSeedVector &csVector,
                        const EnergyType energy,
                        const KSpace &KImage);


    private:
        double energyValue(Curve& curve, std::map<KSpace::SCell,double>& weightMap);

    private:
        std::vector< Checker* > checkers;
    };
}

#include "CurveCandidatesGenerator.hpp"


#endif //EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
