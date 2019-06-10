#ifndef EXHAUSTIVE_GC_UTILS_H
#define EXHAUSTIVE_GC_UTILS_H

#include <DIPaCUS/base/Shapes.h>
#include "Shape.h"

namespace ExhaustiveGC
{
    namespace APP
    {
        namespace Utils
        {
            DIPaCUS::Shapes::DigitalSet resolveShape(Shape shape,double gridStep);
        }

    }
}


#endif //EXHAUSTIVE_GC_UTILS_H