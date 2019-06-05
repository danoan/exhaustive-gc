#include <DIPaCUS/base/Shapes.h>
#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"

using namespace ExhaustiveGC;

int main()
{
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    API::Curve optimalCurve;
    API::SearchParameters sp(Core::Strategy::First,4,10,11,API::EnergyType::SquaredCurvature);

    API::Curve innerCurve,outerCurve;
    API::InitImage::KSpace KImage = API::InitImage::eval(API::InitImage::Mode::OriginalBoundary,innerCurve,outerCurve,square);

    Utils::Timer::start();
    double energyValue = Energy::energyValue(innerCurve,KImage,Energy::IntSquaredCurvature);
    API::findOptimalOneExpansion(optimalCurve, energyValue, sp,KImage,innerCurve,outerCurve);
    Utils::Timer::end(std::cout);

    std::string outputFolder= std::string(PROJECT_DIR) + "/output";
    boost::filesystem::create_directories(outputFolder);

    DGtal::Board2D board;
    board << optimalCurve;
    board.saveSVG( (outputFolder+"/optimalCurve.svg").c_str() );

    return 0;
}