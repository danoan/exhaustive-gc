#include <DIPaCUS/base/Shapes.h>
#include <exhaustive-gc/api/api.h>

using namespace ExhaustiveGC;

int main()
{
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    API::Curve optimalCurve;
    API::SearchParameters<2> sp(7,13,API::EnergyType::SquaredCurvature);

    API::Curve innerCurve,outerCurve;
    API::InitImage::KSpace KImage = API::InitImage::eval(innerCurve,outerCurve,square);

    API::findOptimalOneExpansion(optimalCurve,sp,KImage,innerCurve,outerCurve);

    std::string outputFolder= std::string(PROJECT_DIR) + "/output/examples/two-joint";
    boost::filesystem::create_directories(outputFolder);

    DGtal::Board2D board;
    board << optimalCurve;
    board.saveEPS( (outputFolder+"/optimalCurve.eps").c_str() );

    return 0;
}