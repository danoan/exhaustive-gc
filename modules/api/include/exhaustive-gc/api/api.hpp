#include "exhaustive-gc/api/api.h"

template<typename TSearchParameters>
bool findOptimalOneExpansion(Curve& optimalCurve,
                             const double currentEnergyValue,
                             const TSearchParameters& sp,
                             const DigitalSet& ds)
{
    typedef GenerateSeedPairs::SeedPair SeedPair;
    typedef std::vector< CheckableSeedPair > CheckableSeedPairVector;

    const DGtal::Z2i::Domain& domain = ds.domain();
    KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    GCurve::Range gcRange(ds,5);
    GenerateSeedPairs::SeedPairsList spl;
    GenerateSeedPairs(spl,gcRange);


    FilterSeedPairs(spl,sp.minGCLength,sp.maxGCLength);
    std::cout << spl.size() << " qualified seeds\n";


    CheckableSeedPairVector cspv;
    std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp) mutable {cspv.push_back( CheckableSeedPair(sp) );});


    CurveCandidatesGenerator CE(sp.jointPairs,sp.strategy);
    CE.registerChecker( new GluedIntersectionChecker() );
    CE.registerChecker( new MinimumDistanceChecker(kspace) );


    CheckableSeedPair bestCombination[1];

    return CE(optimalCurve,
              currentEnergyValue,
              cspv,
              sp.energyInput,
              kspace);

}

template<typename TSearchParameters>
void optimalOneExpansionSequence(const DigitalSet& dsInput,
                                 const TSearchParameters& sp,
                                 int iterations,
                                 std::string outputFolder)
{
    DGtal::Board2D board;

    Point lb,ub;
    dsInput.computeBoundingBox(lb,ub);

    DGtal::Z2i::Domain domain( lb - Point(10,10),ub + Point(10,10));
    DigitalSet workingSet(domain);
    workingSet.insert(dsInput.begin(),dsInput.end());

    double lastEnergyValue = Energy::energyValue(workingSet,sp.energyInput);

    for(int i=0;i<iterations;++i)
    {
        Curve minCurve;
        bool foundBetter = findOptimalOneExpansion(minCurve,
                                                   lastEnergyValue,
                                                   sp,
                                                   workingSet);

        if(foundBetter)
        {
            DigitalSet tempDS = Utils::Digital::digitalSetFromCurve(minCurve);
            workingSet.clear();
            workingSet.insert(tempDS.begin(),tempDS.end());

            board.clear();
            board << workingSet;
            board.saveSVG( (outputFolder + "/" + std::to_string(i) + ".svg").c_str() );

            lastEnergyValue = Energy::energyValue(workingSet,sp.energyInput);
        }else
        {
            break;
        }


    }
}
