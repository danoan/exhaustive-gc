#ifndef EXHAUSTIVE_GC_API_H
#define EXHAUSTIVE_GC_API_H

#include <DGtal/kernel/PointVector.h>
#include <DGtal/io/boards/Board2D.h>

#include "DIPaCUS/base/Shapes.h"

#include <exhaustive-gc/dev/control/CurveCandidatesGenerator.h>
#include <exhaustive-gc/dev/checker/GluedIntersectionChecker.h>
#include <exhaustive-gc/dev/checker/MinimumDistanceChecker.h>

#include <exhaustive-gc/api/utils/FilterSeedPairs.h>
#include <exhaustive-gc/api/utils/InitImage.h>
#include <exhaustive-gc/api/utils/ImageFromCurve.h>
#include <exhaustive-gc/api/model/SearchParameters.h>
#include "exhaustive-gc/api/utils/GenerateSeedPairs.h"

namespace ExhaustiveGC
{
    namespace API
    {
        typedef DGtal::Z2i::DigitalSet DigitalSet;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Curve Curve;
        typedef ExhaustiveGC::EnergyType EnergyType;

        template<typename TSearchParameters>
        void findOptimalOneExpansion(Curve& optimalCurve,
                                     const TSearchParameters& sp,
                                     const KSpace& KImage,
                                     const Curve& innerCurve,
                                     const Curve& outerCurve);


        template<typename TSearchParameters>
        void optimalOneExpansionSequence(const DigitalSet& dsInput,
                                         const TSearchParameters& sp,
                                         int iterations,
                                         std::string outputFolder);


    }
}

#include "api.hpp"

#endif //EXHAUSTIVE_GC_API_H