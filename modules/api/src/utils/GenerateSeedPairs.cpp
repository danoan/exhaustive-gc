#include "exhaustive-gc/api/utils/GenerateSeedPairs.h"

using namespace ExhaustiveGC::API;

GenerateSeedPairs::GenerateSeedPairs(SeedPairsList& seedPairList,
                                     const GCurve::Range& gcRange)
{
    std::map<std::string,SeedVector> seedDrawer;
    seedDrawer["mainInner"] = SeedVector();
    seedDrawer["mainOuter"] = SeedVector();
    seedDrawer["innerMain"] = SeedVector();
    seedDrawer["outerMain"] = SeedVector();

    for(auto it=gcRange.begin();it!=gcRange.end();++it)
    {
        switch(it->seed.type)
        {
            case GCurve::Seed::MainInner:
            {
                seedDrawer["mainInner"].push_back(it->seed);
                break;
            }
            case GCurve::Seed::MainOuter:
            {
                seedDrawer["mainOuter"].push_back(it->seed);
                break;
            }
            case GCurve::Seed::InnerMain:
            {
                seedDrawer["innerMain"].push_back(it->seed);
                break;
            }
            case GCurve::Seed::OuterMain:
            {
                seedDrawer["outerMain"].push_back(it->seed);
                break;
            }

        }
    }

    typedef ContainerCombinator<SeedPairsList,
            SeedVector::const_iterator,
            SeedVector::const_iterator> MyContainerCombinator;

    MyContainerCombinator(seedDrawer["mainInner"].begin(),
                          seedDrawer["mainInner"].end(),
                          seedDrawer["innerMain"].begin(),
                          seedDrawer["innerMain"].end(),
                          std::back_inserter(seedPairList));

    MyContainerCombinator(seedDrawer["innerMain"].begin(),
                          seedDrawer["innerMain"].end(),
                          seedDrawer["mainInner"].begin(),
                          seedDrawer["mainInner"].end(),
                          std::back_inserter(seedPairList));

    MyContainerCombinator(seedDrawer["outerMain"].begin(),
                          seedDrawer["outerMain"].end(),
                          seedDrawer["mainOuter"].begin(),
                          seedDrawer["mainOuter"].end(),
                          std::back_inserter(seedPairList));

    MyContainerCombinator(seedDrawer["mainOuter"].begin(),
                          seedDrawer["mainOuter"].end(),
                          seedDrawer["outerMain"].begin(),
                          seedDrawer["outerMain"].end(),
                          std::back_inserter(seedPairList));


}