#ifndef EXHAUSTIVE_GC_IMAGEFROMCURVE_H
#define EXHAUSTIVE_GC_IMAGEFROMCURVE_H

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>

namespace ExhaustiveGC
{
    namespace API
    {
        class ImageFromCurve
        {
        public:
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Curve Curve;

            typedef DGtal::ImageContainerBySTLVector<DGtal::Z2i::Domain, unsigned char> Image2D;

        private:
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

        public:
            ImageFromCurve(Image2D& image,
                           const Domain& domain,
                           const Curve& curve);
        };
    }
}

#endif //EXHAUSTIVE_GC_IMAGEFROMCURVE_H
