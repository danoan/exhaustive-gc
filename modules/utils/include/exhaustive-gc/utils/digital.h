#ifndef EXHAUSTIVE_GC_DIGITAL_H
#define EXHAUSTIVE_GC_DIGITAL_H

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/components/Properties.h>
#include <DIPaCUS/derivates/Misc.h>

namespace ExhaustiveGC
{
    namespace Utils
    {
        namespace Digital
        {
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Curve Curve;

            DigitalSet digitalSetFromCurve(const Curve& curve);
        }
    }
}

#endif //EXHAUSTIVE_GC_DIGITAL_H
