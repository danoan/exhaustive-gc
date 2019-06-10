#ifndef EXHAUSTIVE_GC_GENERATESEEDPAIRS_H
#define EXHAUSTIVE_GC_GENERATESEEDPAIRS_H

#include <gcurve/Seed.h>
#include <gcurve/Range.h>

#include "exhaustive-gc/core/model/ContainerCombinator.h"
#include "exhaustive-gc/core/check-elem/CheckableSeedPair.h"

namespace ExhaustiveGC
{
    namespace API
    {
        class GenerateSeedPairs
        {
        private:
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::Curve Curve;

            typedef std::vector<GCurve::Seed> SeedVector;

        public:
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef std::pair<GCurve::Seed,GCurve::Seed> SeedPair;
            typedef std::list< SeedPair > SeedPairsList;

        public:
            GenerateSeedPairs(SeedPairsList& seedPairList,
                              const GCurve::Range& gcRange);
        };
    }
}

#endif //EXHAUSTIVE_GC_GENERATESEEDPAIRS_H
