#ifndef EXHAUSTIVE_GC_INITIMAGE_H
#define EXHAUSTIVE_GC_INITIMAGE_H

#include <DIPaCUS/derivates/Misc.h>
#include <DIPaCUS/base/Representation.h>

namespace ExhaustiveGC
{
    namespace API
    {
        namespace InitImage
        {
            typedef DIPaCUS::Representation::Image2D Image2D;
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::KSpace KSpace;

            typedef DIPaCUS::Representation::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;
            
            enum Mode{OriginalBoundary,DilatedBoundary};

            KSpace eval(Mode mode,
                        Curve& innerCurve,
                        Curve& outerCurve,
                        const DigitalSet& ds);
        }
    }
}

#endif //EXHAUSTIVE_GC_INITIMAGE_H
