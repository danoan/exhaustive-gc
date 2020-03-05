#ifndef EXHAUSTIVE_GC_ENERGYVALUE_H
#define EXHAUSTIVE_GC_ENERGYVALUE_H

#include <DGtal/helpers/StdDefs.h>
#include <exhaustive-gc/energy/EnergyInput.h>
#include <exhaustive-gc/energy/energy.h>

struct EnergyValue
{
    typedef DGtal::Z2i::DigitalSet DigitalSet;
    typedef ExhaustiveGC::Energy::EnergyInput EnergyInput;

    EnergyValue(const DigitalSet& ds, const EnergyInput& ei)
    {
        compute(ds,ei);
    }

    void compute(const DigitalSet& ds, const EnergyInput& ei)
    {
        EnergyInput mdca = ei;
        mdca.estimator = EnergyInput::AlgorithmEstimator::MDCA;
        
        EnergyInput ii = ei;
        ii.estimator = EnergyInput::AlgorithmEstimator::II;
        
        mdcaValue = ExhaustiveGC::Energy::energyValue(ds,mdca);
        iiValue = ExhaustiveGC::Energy::energyValue(ds,ii);
    }
    
    double mdcaValue;
    double iiValue;
};

#endif //EXHAUSTIVE_GC_ENERGYVALUE_H
