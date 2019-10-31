#ifndef EXHAUSTIVE_GC_FILTERSEEDPAIRS_H
#define EXHAUSTIVE_GC_FILTERSEEDPAIRS_H

#include <DGtal/helpers/StdDefs.h>
#include <gcurve/Seed.h>
#include "exhaustive-gc/core/check-elem/CheckableSeedPair.h"

namespace ExhaustiveGC
{
    namespace API
    {
        class FilterSeedPairs
        {
        public:
            typedef std::pair<GCurve::Seed,GCurve::Seed> SeedPair;
            typedef std::list< SeedPair > SeedPairsList;
            typedef std::set<DGtal::Z2i::SCell> LinelSet;

        public:
            FilterSeedPairs(SeedPairsList& spl, int minDistance=1,int maxDistance=-1);
            FilterSeedPairs(SeedPairsList& spl, const LinelSet& ls);
        };
    }
}

#endif //EXHAUSTIVE_GC_FILTERSEEDPAIRS_H
