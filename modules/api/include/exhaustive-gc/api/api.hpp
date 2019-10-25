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

    int threadSize = sp.threadSize;
    if(sp.threadSize==0) threadSize = (int) (spl.size()/sp.nThreads);



    CheckableSeedPairVector cspv;
    std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp) mutable {cspv.push_back( CheckableSeedPair(sp) );});


    typedef ExhaustiveGC::Core::CCGData CCGData;

    CCGData ccgData(sp.jointPairs,
                    sp.strategy,
                    false,
                    ds,
                    cspv,
                    sp.energyInput,
                    kspace);

    if(sp.jointPairs>1)
    {
        ccgData.registerChecker( new GluedIntersectionChecker() );
    }


    return ExhaustiveGC::Core::FindCandidate::findCandidate(optimalCurve,
                                                            currentEnergyValue,
                                                            ccgData,
                                                            sp.nThreads,
                                                            threadSize);




}

void exportImageFromDigitalSet(const std::string& imageOutputPath, const DigitalSet& ds, const std::set<DGtal::Z2i::Point>& fixedPixels)
{
    typedef DIPaCUS::Representation::Image2D Image2D;

    Image2D img(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(img,ds);
    for(auto p:fixedPixels) img.setValue(p,128);
    DGtal::GenericWriter<Image2D>::exportFile(imageOutputPath,img);
}

template<typename TSearchParameters>
void optimalOneExpansionSequence(const DigitalSet& dsInput,
                                 const TSearchParameters& sp,
                                 int iterations,
                                 std::string outputFolder,
                                 std::ostream& os)
{
    os << "#It\tEnergyValue\n";

    Point lb,ub;
    dsInput.computeBoundingBox(lb,ub);

    DGtal::Z2i::Domain domain( lb - Point(40,40),ub + Point(40,40));
    DigitalSet workingSet(domain);
    workingSet.insert(dsInput.begin(),dsInput.end());

    DGtal::Z2i::KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);
    std::set<DGtal::Z2i::Point> fixedPixels;
    for(auto l:sp.energyInput.fixedLinels)
    {
        for(auto p:kspace.sUpperIncident(l)) fixedPixels.insert( kspace.sCoords(p) );
    }

    double lastEnergyValue = Energy::energyValue(workingSet,sp.energyInput);

    exportImageFromDigitalSet(outputFolder + "/" + nDigitsString(0,4) + ".pgm",workingSet,fixedPixels);
    for(int i=1;i<=iterations;++i)
    {
        writeEnergy(os,i,lastEnergyValue);

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


            exportImageFromDigitalSet(outputFolder + "/" + nDigitsString(i,4) + ".pgm",workingSet,fixedPixels);

            lastEnergyValue = Energy::energyValue(workingSet,sp.energyInput);
        }else
        {
            break;
        }


    }
}
