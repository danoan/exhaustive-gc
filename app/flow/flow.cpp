#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"
#include "exhaustive-gc/energy/EnergyInput.h"

#include "InputReader.h"
#include "InputData.h"
#include "utils.h"

using namespace ExhaustiveGC;

void writeInputData(const InputData& id, const std::string& outputFile)
{
    std::string inputDataFile = outputFile;
    std::ofstream ofs(inputDataFile);
    ofs << id;
    ofs.flush();
    ofs.close();
}

int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);

    DIPaCUS::Shapes::DigitalSet square = APP::Utils::resolveShape(id.shape,id.gridStep);

    Energy::EnergyInput energyInput( id.energyType, id.estimator, id.gridStep, id.radius, id.lengthPenalization );

    API::Curve optimalCurve;
    API::SearchParameters sp(id.strategy,id.joints,id.minGCLength,id.maxGCLength,energyInput);

    boost::filesystem::create_directories(id.outputFolder);


    writeInputData(id,id.outputFolder + "/inputData.txt");

    std::ofstream ofs(id.outputFolder + "/energy.txt");



    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,id.iterations,id.outputFolder,ofs);
    ofs << "\n\n";
    Utils::Timer::end(ofs);

    ofs.flush();
    ofs.close();

    return 0;
}