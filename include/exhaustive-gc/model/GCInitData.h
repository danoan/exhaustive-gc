#ifndef EXHAUSTIVE_GC_GCINITDATA_H
#define EXHAUSTIVE_GC_GCINITDATA_H

#include <gcurve/GluedCurveSeed.h>
#include <gcurve/GluedCurveRange.h>

namespace ExhaustiveGC
{
    struct GCInitData
    {
        typedef GCurve::GluedCurveSeed GluedCurveSeed;
        typedef GCurve::GluedCurveRange::LinkLinelType LinkLinelType;

        GluedCurveSeed seed;
        std::vector<LinkLinelType> connectors;
    };
}

#endif //EXHAUSTIVE_GC_GCINITDATA_H
