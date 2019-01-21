#include <DIPaCUS/base/Shapes.h>
#include <exhaustive-gc/api/api.h>

int main()
{
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    API::Curve optimalCurve;
    API::SearchParameters<1> sp(4,13,API::EnergyType::SquaredCurvature);

    API::Curve innerCurve,outerCurve;
    API::InitImage::KSpace KImage = API::InitImage::eval(innerCurve,outerCurve,square);

    std::string outputFolder= std::string(PROJECT_DIR) + "/output/examples/one-exp-flow";
    boost::filesystem::create_directories(outputFolder);
    
    API::optimalOneExpansionSequence(square,sp,10,outputFolder);
}