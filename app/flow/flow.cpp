#include <random>

#include "boost/filesystem.hpp"

#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"
#include "exhaustive-gc/energy/EnergyInput.h"

#include "InputReader.h"
#include "InputData.h"
#include "utils.h"

using namespace ExhaustiveGC;

void writeInputData(const InputData& id, const Energy::EnergyInput::LinelSet& fixedLinels, const std::string& outputFile)
{
    std::string inputDataFile = outputFile;
    std::ofstream ofs(inputDataFile);
    ofs << id;

    ofs << "Fixed Linels: ";
    for(auto l:fixedLinels)
    {
        auto c = l.preCell().coordinates;
        ofs << (c[0]>0?"+":"") << (c[0]>0?c[0]:-c[0]) << " "
        << (c[1]>0?"+":"") << (c[1]>0?c[1]:-c[1]) << " "
        << l.preCell().positive << " ";
    }
    ofs << "\n";

    ofs.flush();
    ofs.close();
}

Energy::EnergyInput::LinelSet randomLinels(const DGtal::Z2i::DigitalSet& ds,int nLinels)
{
    Energy::EnergyInput::LinelSet ls;
    API::Curve shapeBoundary;
    DIPaCUS::Misc::computeBoundaryCurve(shapeBoundary,ds);

    std::random_device rd;
    std::knuth_b prg(rd());

    std::uniform_int_distribution<int> ud(0,shapeBoundary.size()-1);

    for(int i=0;i<nLinels;++i)
    {
        int g = ud.operator()(prg);
        auto l = *( shapeBoundary.begin()+g );
        if( ls.find(l)!=ls.end()) continue;

        ls.insert( l );
    }

    return ls;
}

Energy::EnergyInput::LinelSet convertToDGtalPoints(const DGtal::Z2i::Domain& domain, InputData::MyCoordsCollection& inputCoords)
{
    Energy::EnergyInput::LinelSet ls;
    DGtal::Z2i::KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    for(auto c:inputCoords) ls.insert( kspace.sCell( DGtal::Z2i::Point(c.x,c.y),c.sign) );
    return ls;
}

int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);

    DIPaCUS::Shapes::DigitalSet square = APP::Utils::resolveShape(id.shape,id.gridStep);

    Energy::EnergyInput::LinelSet ls;
    if(id.randomFixedLinels)
         ls = randomLinels(square,id.numFixedLinels);
    else
         ls = convertToDGtalPoints(square.domain(),id.fixedLinels);

    Energy::EnergyInput energyInput( id.energyType, id.estimator, id.gridStep, id.radius, id.lengthPenalization,ls );

    API::Curve optimalCurve;
    API::SearchParameters sp(id.strategy,id.joints,id.minGCLength,id.maxGCLength,energyInput,id.nThreads,id.threadSize);

    boost::filesystem::create_directories(id.outputFolder);


    writeInputData(id,ls,id.outputFolder + "/inputData.txt");

    std::ofstream ofs(id.outputFolder + "/energy.txt");



    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,id.iterations,id.outputFolder,ofs);
    ofs << "\n\n#";
    Utils::Timer::end(ofs);

    ofs.flush();
    ofs.close();

    return 0;
}