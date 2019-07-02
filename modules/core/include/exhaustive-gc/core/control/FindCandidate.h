#ifndef EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
#define EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H

#include <DGtal/helpers/StdDefs.h>

#include <lazy-comb/LazyCombinations.h>
#include <lazy-comb/MultiThreadLC.h>
#include <lazy-comb/ThreadInput.h>

#include "exhaustive-gc/core/model/CCGData.h"
#include "exhaustive-gc/core/control/CurveFromJoints.h"



namespace ExhaustiveGC
{
    namespace Core
    {
        namespace FindCandidate
        {
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            typedef CCGData::CheckableSeedVector CheckableSeedVector;
            typedef CheckableSeedVector::value_type ContainerValueType;

            struct Data
            {
                Data():initialized(false){}

                double energyValue;
                bool foundCandidate;
                Curve curve;
                bool initialized;
            };

            typedef LazyCombinator::ThreadInput<CheckableSeedVector,Data,CCGData> MyThreadInput;
            typedef LazyCombinator::MultiThreadLC<MyThreadInput> MyMultiThreadLC;

            typedef MyThreadInput::Params Params;


            typedef std::map<KSpace::SCell, double> WeightMap;
            typedef LazyCombinator::LazyCombinations <CheckableSeedVector> MyLazyCombinations;


            void initCheckers(MyLazyCombinations& myCombinations,
                              const CCGData& ccgData);

            bool findCandidate(DGtal::Z2i::Curve& minCurve,
                               const double energyValue,
                               const CCGData& ccgData,
                               int nThread,
                               int threadSize);

            double computeEnergyValue(const DigitalSet& ds,
                                      const Curve& curve,
                                      const KSpace& KImage,
                                      const Energy::EnergyInput& energyInput);

            void* exhaustCombinator( void* params);
            void combinatorCallback(ContainerValueType* seedCombination, MyThreadInput* ti);


        }

    }
}


#endif //EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
