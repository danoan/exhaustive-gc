#include <boost/filesystem.hpp>
#include <DGtal/io/boards/Board2D.h>

#include <DIPaCUS/base/Shapes.h>

#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"

using namespace ExhaustiveGC;

int main()
{
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    Energy::EnergyInput energyInput(API::EnergyType::SquaredCurvature,
                                    Energy::EnergyInput::AlgorithmEstimator::MDCA,
                                    1.0,
                                    3.0,
                                    0.01);

    API::Curve optimalCurve;
    API::SearchParameters sp(Core::Strategy::Best,2,4,13,false,energyInput,4,1000);

    Utils::Timer::start();
    double energyValue = Energy::energyValue(square,energyInput);
    API::findOptimalOneExpansion(optimalCurve, energyValue, sp,square);
    Utils::Timer::end(std::cout);

    std::string outputFolder= std::string(PROJECT_DIR) + "/output";
    boost::filesystem::create_directories(outputFolder);

    DGtal::Board2D board;
    board << optimalCurve;
    board.saveSVG( (outputFolder+"/optimalCurve.svg").c_str() );

    return 0;
}