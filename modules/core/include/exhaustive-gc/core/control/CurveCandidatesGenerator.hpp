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

double CurveCandidatesGenerator::computeEnergyValue(const DigitalSet& ds,
                                             const Curve& curve,
                                             const KSpace& KImage,
                                             const Energy::EnergyInput& energyInput)
{
    std::vector< std::set<Point> > components;

    DigitalSet startingPS = ds;

    auto outerPixelsRange = curve.getOuterPointsRange();
    for(auto it=outerPixelsRange.begin();it!=outerPixelsRange.end();++it)
    {
        startingPS.erase( *it );
    }

    double value=0;
    std::vector< DIPaCUS::Misc::ConnectedComponent > vcc;
    DIPaCUS::Misc::getConnectedComponents(vcc,startingPS);

    DigitalSet compDS(ds.domain());
    value = Energy::energyValue(curve, KImage, energyInput);
    if(vcc.size()!=1)
    {
        int s=0;
        for(auto it=vcc.begin();it!=vcc.end();++it)
        {
            if(it->size()>10) ++s;
            if(s==2)
            {
                value=1e20;
                break;
            }
        }
    }

    return value;

}


bool CurveCandidatesGenerator::operator()(Curve& minCurve,
                                          const DigitalSet& ds,
                                          const double energyValue,
                                          const CheckableSeedVector &csVector,
                                          const Energy::EnergyInput& energyInput,
                                          const KSpace &KImage)
{
    bool considerMultipleConnectedComponents = true;

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

        if(considerMultipleConnectedComponents)
            currentEnergyValue = computeEnergyValue(ds,curve,KImage,energyInput);
        else
            currentEnergyValue = Energy::energyValue(curve,KImage,energyInput);

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


