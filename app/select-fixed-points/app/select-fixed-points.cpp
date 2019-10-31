#include <iostream>
#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>

#include <select-fixed-points/gui.h>

using namespace DGtal::Z2i;

int main(int argc, char* argv[])
{
    DigitalSet square = DIPaCUS::Shapes::square();
    Point squareSize = square.domain().upperBound() - square.domain().lowerBound() + Point(1,1);

    Point translation = Point(0,0) - square.domain().lowerBound();

    cv::Mat cvImg = cv::Mat::zeros(squareSize[1],squareSize[0],DIPaCUS::Representation::GRAYSCALE_IMG_TYPE);
    cv::imwrite("test.pgm",cvImg);
    DIPaCUS::Representation::digitalSetToCVMat(cvImg,square);

    SelectFixedPixels::gui(cvImg,std::cout);


    return 0;
}