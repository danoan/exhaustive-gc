#ifndef EXHAUSTIVE_GC_GENERATESEEDPAIRS_H
#define EXHAUSTIVE_GC_GENERATESEEDPAIRS_H

#include <exhaustive-gc/dev/model/ContainerCombinator.h>
#include "exhaustive-gc/dev/utils/SeparateInnerAndOuter.h"
#include "exhaustive-gc/dev/check-elem/CheckableSeedPair.h"

namespace ExhaustiveGC
{
    namespace API
    {
        class GenerateSeedPairs
        {
        public:
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::Curve Curve;

            typedef std::pair<GCInitData,GCInitData> SeedPair;
            typedef std::list< SeedPair > SeedPairsList;

        private:
            typedef SeparateInnerAndOuter::SeedVector SeedVector;

        public:
            GenerateSeedPairs(SeedPairsList& seedPairsVector,
                              const KSpace& KImage,
                              const Curve& innerCurve,
                              const Curve& outerCurve);
        };
    }
}

#endif //EXHAUSTIVE_GC_GENERATESEEDPAIRS_H
