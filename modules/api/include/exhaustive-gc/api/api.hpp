#include "exhaustive-gc/api/api.h"

using namespace ExhaustiveGC;

template<typename TSearchParameters>
bool API::findOptimalOneExpansion(Curve& optimalCurve,
                                  const double currentEnergyValue,
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


    CurveCandidatesGenerator CE(sp.jointPairs,sp.strategy);
    CE.registerChecker( new GluedIntersectionChecker() );
    CE.registerChecker( new MinimumDistanceChecker(KImage) );


    CheckableSeedPair bestCombination[1];

    return CE(optimalCurve,
              currentEnergyValue,
              cspv,
              sp.energyType,
              KImage);

}

template<typename TSearchParameters>
void API::optimalOneExpansionSequence(const DigitalSet& dsInput,
                                      const TSearchParameters& sp,
                                      const InitImage::Mode mode,
                                      int iterations,
                                      std::string outputFolder)
{
    DGtal::Board2D board;

    Curve innerCurve,outerCurve;
    KSpace KImage = InitImage::eval(mode,innerCurve,outerCurve,dsInput);

    double lastEnergyValue = Energy::energyValue(innerCurve,KImage,sp.energyType);

    for(int i=0;i<iterations;++i)
    {
        Curve minCurve;
        bool foundBetter = findOptimalOneExpansion(minCurve,
                                                   lastEnergyValue,
                                                   sp,
                                                   KImage,
                                                   innerCurve,
                                                   outerCurve);

        if(foundBetter)
        {
            DigitalSet tempDS = Utils::Digital::digitalSetFromCurve(minCurve);

            board.clear();
            board << tempDS;
            board.saveSVG( (outputFolder + "/" + std::to_string(i) + ".svg").c_str() );

            KImage = InitImage::eval(mode,innerCurve,outerCurve,tempDS);
            lastEnergyValue = Energy::energyValue(minCurve,KImage,sp.energyType);
        }else
        {
            break;
        }


    }
}

template<typename TSearchParameters>
void API::optimalOneExpansionAlternateSequence(const DigitalSet& dsInput,
                                               const TSearchParameters& sp,
                                               int iterations,
                                               std::string outputFolder)
{
    DGtal::Board2D board;

    Curve innerCurve,outerCurve;
    InitImage::Mode mode = InitImage::Mode::OriginalBoundary;
    KSpace KImage = InitImage::eval(mode,innerCurve,outerCurve,dsInput);

    double lastEnergyValue = Energy::energyValue(outerCurve,KImage,sp.energyType);

    int i=0;
    while(i<iterations)
    {
        Curve minCurve;
        bool foundBetter = findOptimalOneExpansion(minCurve,
                                                   lastEnergyValue,
                                                   sp,
                                                   KImage,
                                                   innerCurve,
                                                   outerCurve);

        if(foundBetter)
        {
            DigitalSet tempDS = Utils::Digital::digitalSetFromCurve(minCurve);

            if(mode==InitImage::Mode::DilatedBoundary)
            {
                mode = InitImage::Mode::OriginalBoundary;
                std::cerr << "Next mode is OriginalBoundary" << std::endl;
            }

            board.clear();
            board << tempDS;
            board.saveSVG( (outputFolder + "/" + std::to_string(i) + ".svg").c_str() );

            lastEnergyValue = Energy::energyValue(minCurve,KImage,sp.energyType);
            KImage = InitImage::eval(mode,innerCurve,outerCurve,tempDS);

            ++i;
        }else
        {
            if(mode==InitImage::Mode::OriginalBoundary)
            {
                mode = InitImage::Mode::DilatedBoundary;
                std::cerr << "Next mode is DilatedBoundary" << std::endl;


                DigitalSet tempDS = Utils::Digital::digitalSetFromCurve(minCurve);
                KImage = InitImage::eval(mode,innerCurve,outerCurve,tempDS);
            }else
            {
                std::cerr << "End of Flow" << std::endl;
                break;
            }
        }


    }
}

