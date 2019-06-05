#ifndef EXHAUSTIVE_GC_SEARCHPARAMETERS_H
#define EXHAUSTIVE_GC_SEARCHPARAMETERS_H

#include "exhaustive-gc/energy/EnergyType.h"
#include "exhaustive-gc/core/model/Types.h"

namespace ExhaustiveGC
{
    namespace API
    {
        struct SearchParameters
        {
            typedef ExhaustiveGC::Energy::EnergyType EnergyType;
            typedef ExhaustiveGC::Core::Strategy Strategy;

            SearchParameters(Strategy strategy,
                             unsigned int maxPairs,
                             int minGCLength,
                             int maxGCLength,
                             EnergyType et):strategy(strategy),
                                            jointPairs(maxPairs),
                                            minGCLength(minGCLength),
                                            maxGCLength(maxGCLength),
                                            energyType(et){}

            Strategy strategy;
            unsigned int jointPairs;
            int minGCLength;
            int maxGCLength;
            
            EnergyType energyType;
            
        };
    }
}

#endif //EXHAUSTIVE_GC_SEARCHPARAMETERS_H
