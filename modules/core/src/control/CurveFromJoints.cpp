#include "exhaustive-gc/core/control/CurveFromJoints.h"

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
    GluedCurveSeed mainToAuxiliarSeed = currentPair.data().first;
    GluedCurveSeed auxiliarToMainSeed = currentPair.data().second;


    //Notice that all linels between the end of current glued curve and the next are
    //included. One may ask how to guarantee that the joint pairs come in order. In
    //other words, why should I expect that the third evaluated pair is not between
    //the first two?
    //There are two reasons that explains it. First reason is that I have a Intersection
    //checker that forbids two pairs in the same combination sequence to have any element
    //in common; the second is in the way the combinations are constructed. For elements
    //{1,2,3,4} the 2 combination sequence will be:
    //(1,2) (1,3) (1,4) (2,3) (2,4) (3,4)
    //We generate all combinations for the first joints pair, then all remaining combinations
    //for the second pair, and so on. The next element in the sequence does not intersect the
    //previous and it is higher in the order adopted for the curve linels.


    vectorOfSCells.insert(vectorOfSCells.end(),mainToAuxiliarSeed.linkLinels.begin(),mainToAuxiliarSeed.linkLinels.end());
    addIntervalSCells(vectorOfSCells,mainToAuxiliarSeed.inCirculatorBegin, auxiliarToMainSeed.outCirculatorEnd);

    GluedCurveSeed nextIntToExtSeed = nextPair.data().first;
    vectorOfSCells.insert(vectorOfSCells.end(),auxiliarToMainSeed.linkLinels.begin(),auxiliarToMainSeed.linkLinels.end());
    addIntervalSCells(vectorOfSCells,auxiliarToMainSeed.inCirculatorBegin, nextIntToExtSeed.outCirculatorEnd);
    
}