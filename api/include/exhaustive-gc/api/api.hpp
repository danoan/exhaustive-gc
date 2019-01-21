#include "exhaustive-gc/api/api.h"

using namespace ExhaustiveGC;

template<typename TSearchParameters>
void API::findOptimalOneExpansion(Curve& optimalCurve,
                                  const TSearchParameters& sp,
                                  const KSpace& KImage,
                                  const Curve& innerCurve,
                                  const Curve& outerCurve)
{
    typedef GenerateSeedPairs::SeedPair SeedPair;
    typedef std::vector< CheckableSeedPair > CheckableSeedPairVector;

    GenerateSeedPairs::SeedPairsList spl;
    GenerateSeedPairs(spl,KImage,innerCurve,outerCurve);


    FilterSeedPairs(spl,sp.minGCLength,sp.maxGCLength);
    std::cout << spl.size() << " qualified seeds\n";


    CheckableSeedPairVector cspv;
    std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp) mutable {cspv.push_back( CheckableSeedPair(sp) );});


    CurveCandidatesGenerator<sp.jointPairs> CE;
    CE.registerChecker( new GluedIntersectionChecker() );
    CE.registerChecker( new MinimumDistanceChecker(KImage) );


    CheckableSeedPair bestCombination[1];

    CE(optimalCurve,
       cspv,
       sp.energyType,
       KImage);

}

template<typename TSearchParameters>
void API::optimalOneExpansionSequence(const DigitalSet& dsInput,
                                      const TSearchParameters& sp,
                                      int iterations,
                                      std::string outputFolder)
{
    DigitalSet ds = dsInput;
    DGtal::Board2D board;

    for(int i=0;i<iterations;++i)
    {
        Curve minCurve;

        Curve innerCurve,outerCurve;
        KSpace KImage = InitImage::eval(innerCurve,outerCurve,ds);

        findOptimalOneExpansion(minCurve,
                                sp,
                                KImage,
                                innerCurve,
                                outerCurve);

        ds.clear();
        DIPaCUS::Misc::CompactSetFromClosedCurve<Curve::ConstIterator>(ds,minCurve.begin(),minCurve.end());

        board << ds;
        board.saveEPS( (outputFolder + "/" + std::to_string(i) + ".eps").c_str() );
    }
}

