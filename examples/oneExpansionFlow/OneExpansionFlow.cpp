#include <DIPaCUS/base/Shapes.h>
#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"
#include "exhaustive-gc/energy/EnergyInput.h"

using namespace ExhaustiveGC;

int main()
{
    std::string projectDir = std::string(PROJECT_DIR);
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    Energy::EnergyInput energyInput(Energy::EnergyType::SquaredCurvature,0.005);

    API::Curve optimalCurve;
    API::SearchParameters sp(Core::Strategy::First,1,4,13,energyInput);

    std::string outputFolder= projectDir + "/output";
    boost::filesystem::create_directories(outputFolder);

    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,50,outputFolder);
    Utils::Timer::end(std::cout);
}