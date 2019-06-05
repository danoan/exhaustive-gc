#ifndef EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
#define EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H

#include <boost/filesystem/operations.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>

#include <DIPaCUS/components/Transform.h>
#include <geoc/api/api.h>

#include <lazy-comb/interface/IMarkedMapChecker.h>
#include <lazy-comb/LazyCombinations.h>
#include <exhaustive-gc/core/model/Types.h>

#include "exhaustive-gc/core/check-elem/CheckableSeedPair.h"
#include "exhaustive-gc/core/model/Types.h"
#include "exhaustive-gc/energy/EnergyType.h"
#include "exhaustive-gc/energy/energy.h"

#include "CurveFromJoints.h"


namespace ExhaustiveGC
{
    class CurveCandidatesGenerator
    {
    public:
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef LazyCombinator::IMarkedMapChecker<CheckableSeedPair> Checker;
        typedef std::vector<CheckableSeedPair> CheckableSeedVector;

        typedef Core::Strategy Strategy;

    private:
        typedef std::map<KSpace::SCell, double> WeightMap;
        typedef LazyCombinator::LazyCombinations <CheckableSeedVector> MyLazyCombinations;

    private:
        void initCheckers(MyLazyCombinations& myCombinations,
                          const CheckableSeedVector &csVector);


    public:
        CurveCandidatesGenerator(unsigned int maxPairs, Strategy strategy):maxPairs(maxPairs),strategy(strategy){}
        ~CurveCandidatesGenerator(){ for(auto itc=checkers.begin();itc!=checkers.end();++itc) delete *itc; }
        CurveCandidatesGenerator(const CurveCandidatesGenerator&){ throw std::runtime_error("Operation not allowed!");}
        CurveCandidatesGenerator& operator=(const CurveCandidatesGenerator&){ throw std::runtime_error("Operation not allowed!");}

        void registerChecker(Checker* c)
        {
            checkers.push_back( c );
        }

        bool operator()(Curve& minCurve,
                        const double energyValue,
                        const CheckableSeedVector &csVector,
                        const Energy::EnergyType energy,
                        const KSpace &KImage);


    private:
        unsigned int maxPairs;
        Strategy strategy;
        std::vector< Checker* > checkers;
    };
}

#include "CurveCandidatesGenerator.hpp"


#endif //EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
