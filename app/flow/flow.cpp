#include <boost/filesystem.hpp>

#include <exhaustive-gc/api/api.h>
#include <exhaustive-gc/utils/timer.h>
#include <exhaustive-gc/energy/EnergyInput.h>

#include "InputReader.h"
#include "InputData.h"
#include "utils.h"

using namespace ExhaustiveGC;

int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);

    DIPaCUS::Shapes::DigitalSet square = APP::Utils::resolveShape(id.shape,id.gridStep);

    Energy::EnergyInput::LinelSet ls;
    if(id.selectFixedLinels)
         ls = APP::Utils::selectLinels(square);
    else
         ls = APP::Utils::convertToDGtalPoints(square.domain(),id.fixedLinels);

    Energy::EnergyInput energyInput( id.energyType, id.estimator, id.gridStep, id.radius, id.lengthPenalization,ls );

    API::Curve optimalCurve;
    API::SearchParameters sp(id.strategy,id.joints,id.minGCLength,id.maxGCLength,energyInput,id.nThreads,id.threadSize);

    boost::filesystem::create_directories(id.outputFolder);


    APP::Utils::writeInputData(id,ls,id.outputFolder + "/inputData.txt");

    std::ofstream ofs(id.outputFolder + "/energy.txt");



    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,id.iterations,id.outputFolder,ofs);
    ofs << "\n\n#";
    Utils::Timer::end(ofs);

    ofs.flush();
    ofs.close();

    return 0;
}