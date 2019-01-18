#include "exhaustive-gc/control/CurveCandidatesGenerator.h"

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
double CurveCandidatesGenerator<maxPairs>::lengthFactor(double currLength,
                                                        const KSpace& KImage,
                                                        Curve::ConstIterator begin,
                                                        Curve::ConstIterator end)
{
    double f=1;
    if(currLength!=0)
    {
        std::vector<double> localLengthEstimations;

        //TODO::Better use a global estimator
        {
            using namespace GEOC::API::GridCurve::Length;
            mdssClosed<EstimationAlgorithms::ALG_PROJECTED>(KImage,begin,end,localLengthEstimations,1.0);
        }

        double nlength=0;
        for(int i=0;i<localLengthEstimations.size();++i)
        {
            nlength+=localLengthEstimations[i];
        }

        f=currLength/nlength;
    }

    return f;
}

template<int maxPairs>
void CurveCandidatesGenerator<maxPairs>::computeWeightMap(const KSpace& KImage,
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
void CurveCandidatesGenerator<maxPairs>::operator()(Curve& minCurve,
                                                    CheckableSeedVector &csVector,
                                                    KSpace &KImage,
                                                    CheckableSeedPair bestCombination[maxPairs],
                                                    std::string outputFolder)
{
    bool saveEPS = outputFolder!="";

    double minEnergyValue = 6.20158;
    double currentEnergyValue;

    MyLazyCombinations myCombinations(csVector);
    initCheckers(myCombinations,csVector);

    DGtal::Board2D board;
    if(saveEPS)
    {
        outputFolder += std::to_string(maxPairs);
        boost::filesystem::create_directories(outputFolder);
    }


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
                         weightMap);

        currentEnergyValue = energyValue(curve, weightMap);
        if (currentEnergyValue < minEnergyValue) {
            std::cout << "Updated min energy value: " << minEnergyValue << " -> " << currentEnergyValue
                      << std::endl;
            minEnergyValue = currentEnergyValue;

            minCurve = curve;

            for(int i=0;i<maxPairs;++i) bestCombination[i] = seedCombination[i];

            if(saveEPS)
            {
                board.clear();
                board << curve;
                board.saveEPS((outputFolder + "/" + std::to_string(n) + ".eps").c_str());
            }
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