#include "exhaustive-gc/dev/control/CurveFromJoints.h"

using namespace ExhaustiveGC;

CurveFromJoints::CurveFromJoints(Curve &curve,
                                 CheckableSeedPair *seedPairs,
                                 int totalPairs)
{
    typedef KSpace::SCell SCell;
    std::vector<SCell> scells;

    CheckableSeedPair* currentPair;
    CheckableSeedPair* nextPair;
    for(int i=0;i<totalPairs;++i)
    {
        if(i==(totalPairs-1))
        {
            currentPair = &seedPairs[totalPairs-1];
            nextPair = &seedPairs[0];
        }else
        {
            currentPair = &seedPairs[i];
            nextPair = &seedPairs[i+1];
        }

        addSeedPairSCells(scells,*currentPair,*nextPair);
    }

    curve.initFromSCellsVector(scells);
}

void CurveFromJoints::addIntervalSCells(std::vector<KSpace::SCell>& vectorOfSCells,
                                        SCellCirculator begin,
                                        SCellCirculator end)
{
    SCellCirculator it = begin;
    while (it != end)
    {
        vectorOfSCells.push_back(*it);
        ++it;
    }
    vectorOfSCells.push_back(*it);
}

void CurveFromJoints::addSeedPairSCells(std::vector<KSpace::SCell>& vectorOfSCells,
                                        CheckableSeedPair& currentPair,
                                        CheckableSeedPair& nextPair)
{
    GluedCurveSeed inToExtSeed = currentPair.data().first.seed;
    GCInitData::LinkLinelType cinConnector = currentPair.data().first.connectors[0];

    GluedCurveSeed extToIntSeed = currentPair.data().second.seed;
    GCInitData::LinkLinelType cextConnector = currentPair.data().second.connectors[0];

    if( inToExtSeed.linkType != GCurve::GluedCurve::LinkType::INTERN_TO_EXTERN)
    {
        std::cout << "ERROR" << std::endl;
    }

    if( extToIntSeed.linkType != GCurve::GluedCurve::LinkType::EXTERN_TO_INTERN)
    {
        std::cout << "ERROR" << std::endl;
    }


    vectorOfSCells.push_back(cinConnector);
    addIntervalSCells(vectorOfSCells,inToExtSeed.c2It,extToIntSeed.c1It);

    GluedCurveSeed nextIntToExtSeed = nextPair.data().first.seed;
    vectorOfSCells.push_back(cextConnector);
    addIntervalSCells(vectorOfSCells,extToIntSeed.c2It,nextIntToExtSeed.c1It);
    
}