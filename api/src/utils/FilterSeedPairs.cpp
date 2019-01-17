#include "exhaustive-gc/api/utils/FilterSeedPairs.h"

using namespace ExhaustiveGC::API;

FilterSeedPairs::FilterSeedPairs(SeedPairsList &spl,
                                 int minDistance,
                                 int maxDistance)
{
    typedef std::vector< CheckableSeedPair > CheckableSeedList;
    CheckableSeedList filteredPairList;

    if(maxDistance==-1) maxDistance = spl.size();

    SeedPairsList::const_iterator it = spl.begin();
    while(it!=spl.end())
    {
        DGtal::PointVector<2,int> coordInt = it->first.connectors[0].preCell().coordinates;
        DGtal::PointVector<2,int> coordExt = it->second.connectors[0].preCell().coordinates;
        DGtal::PointVector<2,int> diff = coordExt - coordInt;
        int connectorsDistance = (abs(diff[0])+abs(diff[1]) )/2;

        //Internal Connector must be different from External Connector
        if(coordInt==coordExt)
        {
            it = spl.erase(it);
        }
        //Internal and External Connector must cover between 10 and at most 20 external linels
        else if( connectorsDistance < minDistance || connectorsDistance > maxDistance)
        {
            it = spl.erase(it);
        }
        else
        {
            ++it;
        }
    }

}