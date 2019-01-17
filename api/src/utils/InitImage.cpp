#include "exhaustive-gc/api/utils/InitImage.h"

using namespace ExhaustiveGC::API;

InitImage::KSpace InitImage::eval(Curve& innerCurve,
                                  Curve& outerCurve,
                                  const Image2D& image)
{
    DIPaCUS::Misc::ComputeBoundaryCurve(image,innerCurve,1);

    DigitalSet ds(image.domain());
    DIPaCUS::Representation::imageAsDigitalSet(ds,image);

    Domain dilatedDomain( ds.domain().lowerBound() - DGtal::Z2i::Point(1,1), ds.domain().upperBound() + DGtal::Z2i::Point(1,1) );
    DigitalSet dilatedDS( dilatedDomain );

    {
        using namespace DIPaCUS::Morphology;
        dilate(dilatedDS,ds,StructuringElement(StructuringElement::RECT,1),1);
    }

    Image2D dilatedImage(dilatedDomain);
    DIPaCUS::Representation::digitalSetToImage(dilatedImage,dilatedDS);


    DIPaCUS::Misc::ComputeBoundaryCurve(dilatedImage,outerCurve,1);
}