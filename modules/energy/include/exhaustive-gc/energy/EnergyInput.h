#ifndef EXHAUSTIVE_GC_ENERGYINPUT_H
#define EXHAUSTIVE_GC_ENERGYINPUT_H

#include <set>
#include <DGtal/helpers/StdDefs.h>
#include "EnergyType.h"

namespace ExhaustiveGC
{
    namespace Energy
    {
        struct EnergyInput
        {
            enum AlgorithmEstimator{MDCA,II};
            typedef DGtal::Z2i::SCell SCell;
            typedef std::set<SCell> LinelSet;

            EnergyInput(EnergyType type,
                        AlgorithmEstimator estimator,
                        double gridStep,
                        double radius,
                        double lengthPenalization,
                        const LinelSet& fixedLinels):type(type),
                                                   estimator(estimator),
                                                   gridStep(gridStep),
                                                   radius(radius),
                                                   lengthPenalization(lengthPenalization),
                                                   fixedLinels(fixedLinels){}

            EnergyType type;
            AlgorithmEstimator estimator;
            double gridStep;
            double radius;
            double lengthPenalization;

            LinelSet fixedLinels;
        };
    }
}


#endif //EXHAUSTIVE_GC_ENERGYINPUT_H
