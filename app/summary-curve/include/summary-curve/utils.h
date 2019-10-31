#ifndef EXHAUSTIVE_GC_SUMMARY_CURVE_UTILS_H
#define EXHAUSTIVE_GC_SUMMARY_CURVE_UTILS_H

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/derivates/Misc.h>

#include <DGtal/helpers/StdDefs.h>
#include "types.h"

namespace SummaryCurve
{
    namespace Utils
    {
        using namespace DGtal::Z2i;

        typedef std::set<SCell> LinelSet;
        typedef std::set<Point> PixelSet;

        LinelSet selectLinels(const DigitalSet& ds);
        PixelSet incidentPixels(const Domain& domain, const LinelSet& ls);
        DigitalSet eliminatePixels(const DigitalSet& ds, const PixelSet& ps);
        DigitalSet eliminatePixels(const DigitalSet&ds, const LinelSet& ls);
    }

}

#endif //EXHAUSTIVE_GC_SUMMARY_CURVE_UTILS_H
