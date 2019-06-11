#ifndef EXHAUSTIVE_GC_ENERGYINPUT_H
#define EXHAUSTIVE_GC_ENERGYINPUT_H

#include "EnergyType.h"

namespace ExhaustiveGC
{
    namespace Energy
    {
        struct EnergyInput
        {
            EnergyInput(EnergyType type,double lengthPenalization):type(type),
                                                                   lengthPenalization(lengthPenalization){}

            EnergyType type;
            double lengthPenalization;
        };
    }
}


#endif //EXHAUSTIVE_GC_ENERGYINPUT_H
