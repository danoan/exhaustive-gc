#ifndef EXHAUSTIVE_GC_ENERGY_H
#define EXHAUSTIVE_GC_ENERGY_H

#include <map>
#include <DGtal/helpers/StdDefs.h>
#include <geoc/api/api.h>

#include "exhaustive-gc/energy/EnergyInput.h"

namespace ExhaustiveGC
{
    namespace Energy
    {
        extern double INF;
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        typedef GEOC::API::GridCurve::Curvature::EstimationsVector CurvatureEstimationsVector;
        typedef GEOC::API::GridCurve::Length::EstimationsVector LengthEstimationsVector;

        typedef std::map<KSpace::SCell, double> WeightMap;

        void curvatureEstimation(CurvatureEstimationsVector& ev,
                                 const EnergyInput& energyInput,
                                 const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end);

        void squaredCurvature(const EnergyInput& energyInput,
                              const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              WeightMap& weightMap);

        void intSquaredCurvature(const EnergyInput& energyInput,
                                 const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end,
                                 WeightMap& weightMap);

        void elastica(const EnergyInput& energyInput,
                      const KSpace& KImage,
                      Curve::ConstIterator begin,
                      Curve::ConstIterator end,
                      WeightMap& weightMap);

        void computeWeightMap(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              const EnergyInput energyInput,
                              WeightMap& weightMap);

        double energyValue(const Curve& curve, const WeightMap& weightMap);
        double energyValue(const Curve& curve, const KSpace& KImage, const EnergyInput energyInput);
        double energyValue(const DigitalSet& ds, const EnergyInput energyInput);
    }
}


#endif //EXHAUSTIVE_GC_ENERGY_H
