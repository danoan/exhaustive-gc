#ifndef EXHAUSTIVE_GC_SEPARATEINNERANDOUTER_H
#define EXHAUSTIVE_GC_SEPARATEINNERANDOUTER_H

#include <DGtal/helpers/StdDefs.h>
#include <exhaustive-gc/core/model/GCInitData.h>
#include "gcurve/GluedCurveRange.h"

namespace ExhaustiveGC
{

    class SeparateInnerAndOuter
    {
    public:
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef GCurve::GluedCurveRange GluedCurveRange;
        typedef GluedCurveRange::GluedCurveSeedIterator GluedCurveSeedIterator;
        typedef GluedCurveRange::GluedCurveLinkIterator GluedCurveLinkIterator;

        typedef std::vector<GCInitData> SeedVector;

    public:
        SeparateInnerAndOuter(const KSpace& KImage,
                              const Curve& innerCurve,
                              const Curve& outerCurve):KImage(KImage),
                                                 innerCurve(innerCurve),
                                                 outerCurve(outerCurve){}

        void operator()(SeedVector& fromInnerSeeds,
                        SeedVector& fromOuterSeeds);

    private:
        void innerAndOuterList(SeedVector& fromInnerSCells,
                               SeedVector& fromOuterSCells,
                               GluedCurveSeedIterator begin,
                               GluedCurveSeedIterator end,
                               GluedCurveLinkIterator beginLink);

    public:
        const KSpace& KImage;
        const DGtal::Z2i::Curve& innerCurve;
        const DGtal::Z2i::Curve& outerCurve;
    };
}

#endif //EXHAUSTIVE_GC_SEPARATEINNERANDOUTER_H
