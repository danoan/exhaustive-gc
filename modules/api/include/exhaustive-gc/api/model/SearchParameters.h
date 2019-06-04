#ifndef EXHAUSTIVE_GC_SEARCHPARAMETERS_H
#define EXHAUSTIVE_GC_SEARCHPARAMETERS_H

#include <exhaustive-gc/core/model/EnergyType.h>

namespace ExhaustiveGC
{
    namespace API
    {
        template<int maxPairs>
        struct SearchParameters
        {
            typedef ExhaustiveGC::EnergyType EnergyType;

            SearchParameters(int minGCLength,
                             int maxGCLength,
                             EnergyType et):minGCLength(minGCLength),
                                            maxGCLength(maxGCLength),
                                            energyType(et){}

            constexpr static int jointPairs = maxPairs;
            int minGCLength;
            int maxGCLength;
            
            EnergyType energyType;
            
        };
    }
}

#endif //EXHAUSTIVE_GC_SEARCHPARAMETERS_H
