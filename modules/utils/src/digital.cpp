#include "exhaustive-gc/utils/digital.h"

namespace ExhaustiveGC
{
    namespace Utils
    {
        namespace Digital
        {
            DigitalSet digitalSetFromCurve(const Curve& curve)
            {
                DIPaCUS::Properties::BoundingBox bb;
                DIPaCUS::Properties::curveBoundingBox(bb,curve.begin(),curve.end());

                DigitalSet tempDS( DGtal::Z2i::Domain(bb.lb-DGtal::Z2i::Point(1,1),bb.ub+DGtal::Z2i::Point(1,1) ) );
                DIPaCUS::Misc::compactSetFromClosedCurve<Curve::ConstIterator>(tempDS,curve.begin(),curve.end());

                return tempDS;
            }

        }
    }
}