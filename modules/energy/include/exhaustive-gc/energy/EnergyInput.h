#ifndef EXHAUSTIVE_GC_ENERGYINPUT_H
#define EXHAUSTIVE_GC_ENERGYINPUT_H

#include "EnergyType.h"

namespace ExhaustiveGC
{
    namespace Energy
    {
        struct EnergyInput
        {
            enum AlgorithmEstimator{MDCA,II};

            EnergyInput(EnergyType type,
                        AlgorithmEstimator estimator,
                        double gridStep,
                        double radius,
                        double lengthPenalization):type(type),
                                                   estimator(estimator),
                                                   gridStep(gridStep),
                                                   radius(radius),
                                                   lengthPenalization(lengthPenalization){}

            EnergyType type;
            AlgorithmEstimator estimator;
            double gridStep;
            double radius;
            double lengthPenalization;
        };
    }
}


#endif //EXHAUSTIVE_GC_ENERGYINPUT_H
