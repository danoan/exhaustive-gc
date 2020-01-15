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

    GenerateSeedPairs::SeedPairsList spl;

    std::vector<GCurve::Range*> ranges;
    if(sp.automaticGCLength)
    {
        int step=sp.maxGCLength/3;
        for(int i=0;i<3;++i)
        {
            ranges.push_back( new GCurve::Range(ds,step*(i+1)) );
            GenerateSeedPairs(spl,*(ranges[i]) );
        }
    } else
    {
        int k=0;
        for(int i=sp.minGCLength;i<=sp.maxGCLength;++i,++k)
        {
            ranges.push_back( new GCurve::Range(ds,i) );
            GenerateSeedPairs(spl,*(ranges[k]) );
        }

    }


    FilterSeedPairs(spl,sp.energyInput.fixedLinels);
    std::cout << spl.size() << " qualified seeds\n";

    int threadSize = sp.threadSize;
    if(sp.threadSize==0) threadSize = (int) (spl.size()/sp.nThreads);



    CheckableSeedPairVector cspv;
    std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp) mutable {cspv.push_back( CheckableSeedPair(sp) );});


    typedef ExhaustiveGC::Core::CCGData CCGData;

    CCGData ccgData(sp.jointPairs,
                    sp.strategy,
                    ds,
                    cspv,
                    sp.energyInput,
                    kspace);

    if(sp.jointPairs>1)
    {
        ccgData.registerChecker( new GluedIntersectionChecker() );
    }


    bool flag = ExhaustiveGC::Core::FindCandidate::findCandidate(optimalCurve,
                                                                 currentEnergyValue,
                                                                 ccgData,
                                                                 sp.nThreads,
                                                                 threadSize);

    for(auto p:ranges) delete(p);

    return flag;

}

void exportImageFromDigitalSet(const std::string& imageOutputPath, const DigitalSet& ds, const std::set<DGtal::Z2i::Point>& fixedPixels)
{
    typedef DIPaCUS::Representation::Image2D Image2D;

    Image2D img(ds.domain());
    DIPaCUS::Representation::digitalSetToImage(img,ds);
    for(auto p:fixedPixels) img.setValue(p,128);
    DGtal::GenericWriter<Image2D>::exportFile(imageOutputPath,img);
}

void exportPixelMask(const std::string& imageOutputPath, const DGtal::Z2i::Domain& domain, const std::set<DGtal::Z2i::Point>& fixedPixels)
{
    typedef DIPaCUS::Representation::Image2D Image2D;

    Image2D img(domain);
    for(auto p:fixedPixels) img.setValue(p,128);
    DGtal::GenericWriter<Image2D>::exportFile(imageOutputPath,img);
}

template<typename TSearchParameters>
struct IterationState
{
    typedef TSearchParameters SearchParameters;

    enum sUpdate{UPDATED,KEPT};


    IterationState(const DigitalSet& dsInput,SearchParameters sp, int maxIt):sp(sp),maxIt(maxIt),currIt(0)
    {
        Curve curve;
        DIPaCUS::Misc::computeBoundaryCurve(curve,dsInput);
        this->sp.maxGCLength = curve.size()/2;
        sMaxGCLength = UPDATED;
    }

    bool valid()
    {
        return currIt < maxIt;
    }

    void update(const Curve& curveIt, bool found)
    {
        if(found)
        {
            currIt+=1;
            sMaxGCLength=KEPT;
        } else{
            if(sMaxGCLength==UPDATED) sp.maxGCLength/=2;
            else sp.maxGCLength = curveIt.size()/2;

            std::cout << "***Updated N to: "<<  sp.maxGCLength << std::endl;

            if(sp.maxGCLength<10) currIt=maxIt;
            sMaxGCLength=UPDATED;
        }
    }

    SearchParameters sp;

    int maxIt;
    int currIt;

    sUpdate sMaxGCLength;
};

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

    exportPixelMask(outputFolder + "/pixelMask.pgm", domain,fixedPixels);

    IterationState<TSearchParameters> itState(workingSet,sp,iterations);
    double lastEnergyValue = Energy::energyValue(workingSet,itState.sp.energyInput);

    exportImageFromDigitalSet(outputFolder + "/" + nDigitsString(0,4) + ".pgm",workingSet,fixedPixels);
    while(itState.valid())
    {
        writeEnergy(os,itState.currIt,lastEnergyValue);

        Curve minCurve;
        DIPaCUS::Misc::computeBoundaryCurve(minCurve,workingSet);

        bool foundBetter = findOptimalOneExpansion(minCurve,
                                                   lastEnergyValue,
                                                   itState.sp,
                                                   workingSet);

        if(foundBetter)
        {
            DigitalSet tempDS = Utils::Digital::digitalSetFromCurve(minCurve);
            workingSet.clear();
            workingSet.insert(tempDS.begin(),tempDS.end());


            exportImageFromDigitalSet(outputFolder + "/" + nDigitsString(itState.currIt,4) + ".pgm",workingSet,fixedPixels);
            lastEnergyValue = Energy::energyValue(workingSet,itState.sp.energyInput);

        }


        itState.update(minCurve,foundBetter);

    }
}
