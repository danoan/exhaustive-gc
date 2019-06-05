#include "exhaustive-gc/api/utils/InitImage.h"

using namespace ExhaustiveGC::API;

InitImage::KSpace InitImage::eval(Mode mode,
                                  Curve& innerCurve,
                                  Curve& outerCurve,
                                  const DigitalSet& ds)
{
    KSpace KImage;

    if(mode==Mode::DilatedBoundary)
    {
        DIPaCUS::Misc::computeBoundaryCurve(innerCurve,ds);

        Domain dilatedDomain( ds.domain().lowerBound() - DGtal::Z2i::Point(1,1), ds.domain().upperBound() + DGtal::Z2i::Point(1,1) );
        DigitalSet dilatedDS( dilatedDomain );

        {
            using namespace DIPaCUS::Morphology;
            dilate(dilatedDS,ds,StructuringElement(StructuringElement::RECT,1),1);
        }

        DIPaCUS::Misc::computeBoundaryCurve(outerCurve,dilatedDS);


        KImage.init(dilatedDomain.lowerBound(),dilatedDomain.upperBound(),true);
    }else
    {
        DIPaCUS::Misc::computeBoundaryCurve(outerCurve,ds);

        Domain erodedDomain( ds.domain().lowerBound() - DGtal::Z2i::Point(1,1), ds.domain().upperBound() + DGtal::Z2i::Point(1,1) );
        DigitalSet erodedDS( erodedDomain );

        {
            using namespace DIPaCUS::Morphology;
            erode(erodedDS,ds,StructuringElement(StructuringElement::RECT,1),1);
        }

        DIPaCUS::Misc::computeBoundaryCurve(innerCurve,erodedDS);


        KImage.init(erodedDomain.lowerBound(),erodedDomain.upperBound(),true);
    }

    return KImage;
}