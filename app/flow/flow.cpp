#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"

#include "InputReader.h"
#include "InputData.h"
#include "utils.h"


int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);

    DIPaCUS::Shapes::DigitalSet square = resolveShape(id.shape,0.5);

    API::Curve optimalCurve;
    API::SearchParameters sp(id.strategy,id.joints,id.minGCLength,id.maxGCLength,API::EnergyType::IntSquaredCurvature);

    boost::filesystem::create_directories(id.outputFolder);

    Utils::Timer::start();
    API::optimalOneExpansionAlternateSequence(square,sp,id.iterations,id.outputFolder);
    Utils::Timer::end(std::cout);
    return 0;
}