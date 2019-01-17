#ifndef EXHAUSTIVE_GC_GENERATESEEDPAIRS_H
#define EXHAUSTIVE_GC_GENERATESEEDPAIRS_H

#include <exhaustive-gc/model/ContainerCombinator.h>
#include "exhaustive-gc/utils/SeparateInnerAndOuter.h"
#include "exhaustive-gc/check-elem/CheckableSeedPair.h"

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
