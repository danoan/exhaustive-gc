#ifndef EXHAUSTIVE_GC_CURVEFROMJOINTS_H
#define EXHAUSTIVE_GC_CURVEFROMJOINTS_H

#include <exhaustive-gc/dev/check-elem/CheckableSeedPair.h>
#include "gcurve/GluedCurveSeed.h"

namespace ExhaustiveGC
{
    class CurveFromJoints
    {
    private:
        typedef DGtal::Z2i::KSpace KSpace;

        typedef DGtal::Z2i::Curve::ConstIterator SCellIterator;
        typedef DGtal::Circulator<SCellIterator> SCellCirculator;

        typedef GCurve::GluedCurveSeed GluedCurveSeed;
    public:
        typedef DGtal::Z2i::Curve Curve;

    private:
        void addIntervalSCells(std::vector<KSpace::SCell>& vectorOfSCells,
                               SCellCirculator begin,
                               SCellCirculator end);

        void addSeedPairSCells(std::vector<KSpace::SCell>& vectorOfSCells,
                               CheckableSeedPair& currentPair,
                               CheckableSeedPair& nextPair);

    public:
        CurveFromJoints(Curve& curve,
                        CheckableSeedPair* seedPairs,
                        int totalPairs);
    };
}

#endif //EXHAUSTIVE_GC_CURVEFROMJOINTS_H
