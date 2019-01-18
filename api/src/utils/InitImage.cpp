#include "exhaustive-gc/api/utils/InitImage.h"

using namespace ExhaustiveGC::API;

InitImage::KSpace InitImage::eval(Curve& innerCurve,
                                  Curve& outerCurve,
                                  const DigitalSet& ds)
{
    DIPaCUS::Misc::ComputeBoundaryCurve(ds,innerCurve);

    Domain dilatedDomain( ds.domain().lowerBound() - DGtal::Z2i::Point(1,1), ds.domain().upperBound() + DGtal::Z2i::Point(1,1) );
    DigitalSet dilatedDS( dilatedDomain );

    {
        using namespace DIPaCUS::Morphology;
        dilate(dilatedDS,ds,StructuringElement(StructuringElement::RECT,1),1);
    }

    DIPaCUS::Misc::ComputeBoundaryCurve(dilatedDS,outerCurve);

    KSpace KImage;
    KImage.init(dilatedDomain.lowerBound(),dilatedDomain.upperBound(),true);

    return KImage;
}