#include "CurveCandidatesGenerator.h"

using namespace ExhaustiveGC;

void CurveCandidatesGenerator::initCheckers(MyLazyCombinations& myCombinations,
                                                      const CheckableSeedVector &csVector)
{
    for(auto itc=checkers.begin();itc!=checkers.end();++itc) {
        for (auto it = csVector.begin(); it != csVector.end(); ++it) {
            (*itc)->unmark(*it);
        }
        myCombinations.addConsistencyChecker(*itc);
    }
}




bool CurveCandidatesGenerator::operator()(Curve& minCurve,
                                          const double energyValue,
                                          const CheckableSeedVector &csVector,
                                          const Energy::EnergyInput energyInput,
                                          const KSpace &KImage)
{
    double minEnergyValue = energyValue;
    double currentEnergyValue;
    bool candidateFound=false;

    MyLazyCombinations myCombinations(csVector,maxPairs);
    initCheckers(myCombinations,csVector);

    CheckableSeedPair seedCombination[maxPairs];

    int n=0;
    while (myCombinations.next(seedCombination)) {
        Curve curve;
        std::map<KSpace::SCell, double> weightMap;

        CurveFromJoints(curve, seedCombination, maxPairs);
        //DIPaCUS::Transform::eliminateLoops(curve, KImage, curve);

        currentEnergyValue = Energy::energyValue(curve, KImage, energyInput);
        if (currentEnergyValue < minEnergyValue) {
            std::cout << "Updated min energy value: " << minEnergyValue << " -> " << currentEnergyValue
                      << std::endl;

            minEnergyValue = currentEnergyValue;
            minCurve = curve;

            if(strategy==Strategy::First) return true;
            candidateFound=true;
        }

        ++n;
    }
    std::cout << maxPairs << "-Combination: " << n << std::endl;
    std::cout << "Min energy value: " << minEnergyValue << std::endl;

    return candidateFound;
}


