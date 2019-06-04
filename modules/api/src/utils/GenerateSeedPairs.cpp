#include "exhaustive-gc/api/utils/GenerateSeedPairs.h"

using namespace ExhaustiveGC::API;

GenerateSeedPairs::GenerateSeedPairs(SeedPairsList& seedPairList,
                                     const KSpace& KImage,
                                     const Curve& innerCurve,
                                     const Curve& outerCurve)
{
    SeedVector fromInnerSeeds;
    SeedVector fromOuterSeeds;

    {
        SeparateInnerAndOuter _(KImage,innerCurve,outerCurve);
        _(fromInnerSeeds,fromOuterSeeds);
    }

    ContainerCombinator<SeedPairsList,
            SeedVector::const_iterator,
            SeedVector::const_iterator>(fromInnerSeeds.begin(),
                                        fromInnerSeeds.end(),
                                        fromOuterSeeds.begin(),
                                        fromOuterSeeds.end(),
                                        std::back_inserter(seedPairList));
}