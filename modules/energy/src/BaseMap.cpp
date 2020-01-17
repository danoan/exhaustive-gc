#include <exhaustive-gc/energy/BaseMap.h>

namespace ExhaustiveGC
{
    namespace Energy
    {
        void BaseMap::_BaseMap(const Curve& curve, const EnergyInput& energyInput,int neighborhoodRadius)
        {
            this->neighborhoodRadius=neighborhoodRadius;

            DIPaCUS::Properties::BoundingBox bb;
            DIPaCUS::Properties::curveBoundingBox(bb,curve.begin(),curve.end());

            kspace.init(bb.lb - Point(10,10),bb.ub + Point(10,10),true);

            CurvatureEstimationsVector evK;
            curvatureEstimation(evK,energyInput,kspace,curve.begin(),curve.end());

            LengthEstimationsVector evL;
            lengthEstimation(evL,energyInput,kspace,curve.begin(),curve.end());

            int i=0;
            auto it=curve.begin();
            do{
                kMap[*it]=evK[i];
                lMap[*it]=evL[i];

                ++it;
                ++i;
            }while(it!=curve.end());
        }

        BaseMap::BaseMap(const Curve& curve, const EnergyInput& energyInput,int neighborhoodRadius)
        {
            _BaseMap(curve,energyInput,neighborhoodRadius);
        }

        BaseMap::BaseMap(const DigitalSet& ds, const EnergyInput& energyInput,int neighborhoodRadius)
        {
            Curve curve;
            DIPaCUS::Misc::computeBoundaryCurve(curve,ds);

            _BaseMap(curve,energyInput,neighborhoodRadius);
        }

        double BaseMap::getK(const KSpace::SCell s) const
        {
            for(auto n:neighborhood)
            {
                KSpace::SCell sp = kspace.sCell(s.preCell().coordinates + n,s.preCell().positive);
                KSpace::SCell sn = kspace.sCell(s.preCell().coordinates + n,!s.preCell().positive);

                if(kMap.find(sp)!=kMap.end()) return kMap.at(sp);
                if(kMap.find(sn)!=kMap.end()) return kMap.at(sn);
            }

            throw std::runtime_error("K not found!");
        }

        double BaseMap::getLength(const KSpace::SCell s) const
        {
            for(auto n:neighborhood)
            {
                KSpace::SCell sp = kspace.sCell(s.preCell().coordinates + n,s.preCell().positive);
                KSpace::SCell sn = kspace.sCell(s.preCell().coordinates + n,!s.preCell().positive);

                if(lMap.find(sp)!=lMap.end()) return lMap.at(sp);
                if(lMap.find(sn)!=lMap.end()) return lMap.at(sn);
            }

            throw std::runtime_error("Length not found!");
        }
    }
}
