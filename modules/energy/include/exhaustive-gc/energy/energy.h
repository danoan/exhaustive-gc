#ifndef EXHAUSTIVE_GC_ENERGY_H
#define EXHAUSTIVE_GC_ENERGY_H

#include <map>
#include <DGtal/helpers/StdDefs.h>
#include <geoc/api/api.h>

#include "exhaustive-gc/energy/EnergyType.h"


namespace ExhaustiveGC
{
    namespace Energy
    {
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef std::map<KSpace::SCell, double> WeightMap;

        void squaredCurvature(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              WeightMap& weightMap);

        void intSquaredCurvature(const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end,
                                 WeightMap& weightMap);

        void computeWeightMap(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              EnergyType energy,
                              WeightMap& weightMap);

        double energyValue(Curve& curve, WeightMap& weightMap);
        double energyValue(Curve& curve, const KSpace& KImage, EnergyType energy);
    }
}


#endif //EXHAUSTIVE_GC_ENERGY_H
