#ifndef EXHAUSTIVE_GC_BASEMAP_H
#define EXHAUSTIVE_GC_BASEMAP_H

#include <map>
#include <DGtal/helpers/StdDefs.h>

#include <geoc/api/api.h>
#include <exhaustive-gc/energy/EnergyInput.h>

namespace ExhaustiveGC
{
    namespace Energy
    {
        typedef GEOC::API::GridCurve::Curvature::EstimationsVector CurvatureEstimationsVector;
        typedef GEOC::API::GridCurve::Length::EstimationsVector LengthEstimationsVector;

        extern void curvatureEstimation(CurvatureEstimationsVector& ev,
                                        const EnergyInput& energyInput,
                                        const KSpace& KImage,
                                        Curve::ConstIterator begin,
                                        Curve::ConstIterator end);

        extern void lengthEstimation(LengthEstimationsVector& evLength,
                                     const EnergyInput& energyInput,
                                     const KSpace& KImage,
                                     Curve::ConstIterator begin,
                                     Curve::ConstIterator end);
        class BaseMap
        {
        public:
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::Curve Curve;

            typedef std::map<KSpace::SCell,double> BaseKMap;
            typedef std::map<KSpace::SCell,double> BaseLengthMap;

        private:
            void _BaseMap(const Curve& curve, const EnergyInput& energyInput,int neighborhoodRadius=4);

        public:
            BaseMap(const Curve& curve, const EnergyInput& energyInput,int neighborhoodRadius=4);

            BaseMap(const DigitalSet& ds, const EnergyInput& energyInput,int neighborhoodRadius=4);

            double getK(const KSpace::SCell s) const;
            double getLength(const KSpace::SCell s) const;

        private:
            KSpace kspace;
            BaseKMap kMap;
            BaseLengthMap lMap;

            int neighborhoodRadius;
            Point neighborhood[22]={ Point(0,0),Point(1,1),Point(-1,-1),Point(-1,1),Point(1,-1),Point(2,0),Point(-2,0),Point(0,2),
                                     Point(0,-2),Point(2,2),Point(3,1),Point(1,3),Point(-3,-1),Point(-1,-3),Point(4,0),
                                     Point(2,2),Point(2,-2),Point(-2,2),Point(-2,-2),Point(0,4),Point(-4,0),Point(0,-4)};
        };
    }
};


#endif //EXHAUSTIVE_GC_BASEMAP_H
