#include <DIPaCUS/base/Shapes.h>
#include <exhaustive-gc/api/api.h>

int main()
{
    std::string projectDir = std::string(PROJECT_DIR);
    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    //DIPaCUS::Representation::DigitalSet square( DGtal::Z2i::Domain( DGtal::Z2i::Point(0,0), DGtal::Z2i::Point(42,42) ));
    //DIPaCUS::Representation::imageAsDigitalSet( square,projectDir + "/output/examples/one-exp-flow/4.pgm");

    API::Curve optimalCurve;
    API::SearchParameters<1> sp(4,13,API::EnergyType::IntSquaredCurvature);

    std::string outputFolder= projectDir + "/output/examples/one-exp-flow-int";
    boost::filesystem::create_directories(outputFolder);

    API::optimalOneExpansionSequence(square,sp,15,outputFolder);
}