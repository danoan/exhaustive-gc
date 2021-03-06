#ifndef EXHAUSTIVE_GC_SEARCHPARAMETERS_H
#define EXHAUSTIVE_GC_SEARCHPARAMETERS_H

#include "exhaustive-gc/energy/EnergyInput.h"
#include "exhaustive-gc/core/model/Types.h"

namespace ExhaustiveGC
{
    namespace API
    {
        struct SearchParameters
        {
            typedef ExhaustiveGC::Energy::EnergyInput EnergyInput;
            typedef ExhaustiveGC::Core::Strategy Strategy;

            SearchParameters(Strategy strategy,
                             unsigned int maxPairs,
                             int minGCLength,
                             int maxGCLength,
                             bool automaticGCLength,
                             uint nCurveSegs,
                             uint nDilatedSets,
                             uint nErodedSets,
                             const EnergyInput& energyInput,
                             int nThreads,
                             int threadSize):strategy(strategy),
                                             jointPairs(maxPairs),
                                             minGCLength(minGCLength),
                                             maxGCLength(maxGCLength),
                                             nCurveSegs(nCurveSegs),
                                             nDilatedSets(nDilatedSets),
                                             nErodedSets(nErodedSets),
                                             automaticGCLength(automaticGCLength),
                                             energyInput(energyInput),
                                             nThreads(nThreads),
                                             threadSize(threadSize){}

            Strategy strategy;
            unsigned int jointPairs;

            int minGCLength;
            int maxGCLength;
            bool automaticGCLength;

            int nCurveSegs;
            int nDilatedSets;
            int nErodedSets;

            int nThreads;
            int threadSize;
            
            EnergyInput energyInput;
            
        };
    }
}

#endif //EXHAUSTIVE_GC_SEARCHPARAMETERS_H
