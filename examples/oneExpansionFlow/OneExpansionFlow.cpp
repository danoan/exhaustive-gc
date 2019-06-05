#include <DIPaCUS/base/Shapes.h>
#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"

using namespace ExhaustiveGC;

int main()
{
    std::string projectDir = std::string(PROJECT_DIR);
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    API::Curve optimalCurve;
    API::SearchParameters sp(Core::Strategy::First,1,4,13,API::EnergyType::IntSquaredCurvature);

    std::string outputFolder= projectDir + "/output";
    boost::filesystem::create_directories(outputFolder);

    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,API::InitImage::DilatedBoundary,50,outputFolder);
    Utils::Timer::end(std::cout);
}