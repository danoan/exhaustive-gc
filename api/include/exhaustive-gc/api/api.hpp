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
    DGtal::Board2D board;

    Curve innerCurve,outerCurve;
    KSpace KImage = InitImage::eval(innerCurve,outerCurve,dsInput);


    for(int i=0;i<iterations;++i)
    {
        Curve minCurve;
        findOptimalOneExpansion(minCurve,
                                sp,
                                KImage,
                                innerCurve,
                                outerCurve);

        board.clear();
        board << innerCurve;
        board.saveEPS( (outputFolder + "/innerCurve.eps").c_str() );

        board.clear();
        board << outerCurve;
        board.saveEPS( (outputFolder + "/outerCurve.eps").c_str() );

        board.clear();
        board << minCurve;
        board.saveEPS( (outputFolder + "/minCurve.eps").c_str() );


        DIPaCUS::Properties::BoundingBox bb;
        DIPaCUS::Properties::curveBoundingBox(bb,minCurve.begin(),minCurve.end());

        DigitalSet tempDS( DGtal::Z2i::Domain(bb.lb-DGtal::Z2i::Point(1,1),bb.ub+DGtal::Z2i::Point(1,1) ) );
        DIPaCUS::Misc::CompactSetFromClosedCurve<Curve::ConstIterator>(tempDS,minCurve.begin(),minCurve.end());

        board.clear();

        board << tempDS;
        board.saveEPS( (outputFolder + "/" + std::to_string(i) + ".eps").c_str() );

        KImage = InitImage::eval(innerCurve,outerCurve,tempDS);
    }
}

