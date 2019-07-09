#include <boost/filesystem.hpp>

#include <DIPaCUS/base/Shapes.h>
#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"
#include "exhaustive-gc/energy/EnergyInput.h"

using namespace ExhaustiveGC;

int main()
{
    std::string projectDir = std::string(PROJECT_DIR);
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    Energy::EnergyInput energyInput(Energy::EnergyType::SquaredCurvature,
                                    Energy::EnergyInput::AlgorithmEstimator::MDCA,
                                    1.0,
                                    3.0,
                                    0.01);

    API::Curve optimalCurve;
    API::SearchParameters sp(Core::Strategy::Best,1,4,13,energyInput,4,1000);

    std::string outputFolder= projectDir + "/output";
    boost::filesystem::create_directories(outputFolder);

    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,100,outputFolder,std::cout);
    Utils::Timer::end(std::cout);
}