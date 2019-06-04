#include "CurveCandidatesGenerator.h"

using namespace ExhaustiveGC;

template<int maxPairs>
void CurveCandidatesGenerator<maxPairs>::initCheckers(MyLazyCombinations& myCombinations,
                                                      const CheckableSeedVector &csVector)
{
    for(auto itc=checkers.begin();itc!=checkers.end();++itc) {
        for (auto it = csVector.begin(); it != csVector.end(); ++it) {
            (*itc)->unmark(*it);
        }
        myCombinations.addConsistencyChecker(*itc);
    }
}

template<int maxPairs>
void CurveCandidatesGenerator<maxPairs>::squaredCurvature(const KSpace& KImage,
                                                          Curve::ConstIterator begin,
                                                          Curve::ConstIterator end,
                                                          WeightMap& weightMap)
{
    using namespace GEOC::API::GridCurve::Curvature;

    EstimationsVector ev;
    symmetricClosed<EstimationAlgorithms::ALG_MDCA> (KImage,
                                                     begin,
                                                     end,
                                                     ev);


    auto it = begin;
    int i=0;
    do
    {
        weightMap[*it]= pow(ev[i],2);
        ++it;
        ++i;
    }while(i<ev.size());
}

template<int maxPairs>
void CurveCandidatesGenerator<maxPairs>::intSquaredCurvature(const KSpace& KImage,
                                                             Curve::ConstIterator begin,
                                                             Curve::ConstIterator end,
                                                             WeightMap& weightMap)
{
    using namespace GEOC::API::GridCurve;

    Curvature::EstimationsVector evCurv;
    Curvature::symmetricClosed<Curvature::EstimationAlgorithms::ALG_MDCA> (KImage,
                                                                           begin,
                                                                           end,
                                                                           evCurv);

    Length::EstimationsVector evLength;
    Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED >(KImage,begin,end,evLength);


    auto it = begin;
    int i=0;
    do
    {
        weightMap[*it]= pow(evCurv[i],2)*evLength[i];
        ++it;
        ++i;
    }while(i<evCurv.size());
}

template<int maxPairs>
void CurveCandidatesGenerator<maxPairs>::computeWeightMap(const KSpace& KImage,
                                                          Curve::ConstIterator begin,
                                                          Curve::ConstIterator end,
                                                          EnergyType energy,
                                                          WeightMap& weightMap)
{
    switch(energy)
    {
        case EnergyType::SquaredCurvature:
        {
            squaredCurvature(KImage,begin,end,weightMap);
            break;
        }
        case EnergyType::IntSquaredCurvature:
        {
            intSquaredCurvature(KImage,begin, end, weightMap);
            break;
        }
    }

}


template<int maxPairs>
void CurveCandidatesGenerator<maxPairs>::operator()(Curve& minCurve,
                                                    const CheckableSeedVector &csVector,
                                                    const EnergyType energy,
                                                    const KSpace &KImage)
{
    double minEnergyValue = 100;
    double currentEnergyValue;

    MyLazyCombinations myCombinations(csVector);
    initCheckers(myCombinations,csVector);

    CheckableSeedPair seedCombination[maxPairs];

    int n=0;
    while (myCombinations.next(seedCombination)) {
        Curve curve;
        std::map<KSpace::SCell, double> weightMap;

        CurveFromJoints(curve, seedCombination, maxPairs);
        DIPaCUS::Transform::eliminateLoops(curve, KImage, curve);

        computeWeightMap(KImage,
                         curve.begin(),
                         curve.end(),
                         energy,
                         weightMap);

        currentEnergyValue = energyValue(curve, weightMap);
        if (currentEnergyValue < minEnergyValue) {
            std::cout << "Updated min energy value: " << minEnergyValue << " -> " << currentEnergyValue
                      << std::endl;

            minEnergyValue = currentEnergyValue;
            minCurve = curve;
        }

        ++n;
    }
    std::cout << maxPairs << "-Combination: " << n << std::endl;
    std::cout << "Min energy value: " << minEnergyValue << std::endl;
}


template<int maxPairs>
double CurveCandidatesGenerator<maxPairs>::energyValue(Curve& curve, std::map<KSpace::SCell,double>& weightMap)
{
    auto it = curve.begin();
    double v=0;
    do
    {
        v+=weightMap[*it];
        ++it;
    }while(it!=curve.end());

    return v;
}