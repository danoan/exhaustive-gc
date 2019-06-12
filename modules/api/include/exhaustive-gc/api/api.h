#ifndef EXHAUSTIVE_GC_API_H
#define EXHAUSTIVE_GC_API_H

#include <DGtal/kernel/PointVector.h>
#include <DGtal/io/writers/GenericWriter.h>

#include "DIPaCUS/base/Shapes.h"

#include "exhaustive-gc/core/control/CurveCandidatesGenerator.h"
#include "exhaustive-gc/core/checker/GluedIntersectionChecker.h"
#include "exhaustive-gc/core/checker/MinimumDistanceChecker.h"

#include "exhaustive-gc/utils/digital.h"

#include "exhaustive-gc/api/utils/FilterSeedPairs.h"
#include "exhaustive-gc/api/utils/InitImage.h"
#include "exhaustive-gc/api/model/SearchParameters.h"
#include "exhaustive-gc/api/utils/GenerateSeedPairs.h"


namespace ExhaustiveGC
{
    namespace API
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Curve Curve;
        typedef ExhaustiveGC::Energy::EnergyType EnergyType;

        template<typename TSearchParameters>
        bool findOptimalOneExpansion(Curve& optimalCurve,
                                     const double currentEnergyValue,
                                     const TSearchParameters& sp,
                                     const DigitalSet& ds);


        template<typename TSearchParameters>
        void optimalOneExpansionSequence(const DigitalSet& dsInput,
                                         const TSearchParameters& sp,
                                         int iterations,
                                         std::string outputFolder,
                                         std::ostream& os);

        void writeEnergy(std::ostream& os, int iteration, double energyValue)
        {
            os << iteration << "\t" << energyValue << "\n";
        }

        #include "api.hpp"

    }
}

#endif //EXHAUSTIVE_GC_API_H