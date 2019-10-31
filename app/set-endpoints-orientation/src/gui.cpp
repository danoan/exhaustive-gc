#include "set-endpoints-orientation/gui.h"

namespace SetEndpointsOrientation
{
    cv::Point SCREEN_SIZE(600,600);
    cv::Vec3b POLY_COLOR(255,255,255);
    int SHAPE_THICKNESS = 60;

    void gui(const std::string& outputFilePath, std::ostream& os)
    {
        using namespace DGtal::Z2i;
        Domain domain(Point(0,0),Point(SCREEN_SIZE.x-1,SCREEN_SIZE.y-1));
        DigitalSet ds(domain);

        gui(ds,os);
        cv::Mat img = cv::Mat::zeros(SCREEN_SIZE,CV_8U);
        DIPaCUS::Representation::digitalSetToCVMat(img,ds);

        cv::imwrite(outputFilePath,img);
    }

    void gui(DGtal::Z2i::DigitalSet& ds, std::ostream& os)
    {
        typedef DGtal::Z2i::SCell SCell;

        std::string wn = "set-endpoints-orientation";
        cv::namedWindow(wn,cv::WINDOW_NORMAL);

        cv::Mat img = cv::Mat::zeros( SCREEN_SIZE, CV_8UC3);

        SetEndpointsOrientation::GUIControl me(img,wn);
        cv::setMouseCallback(wn,Events::mouseCallback,&me);

        cv::imshow(wn,img);

        bool onExecution=true;
        while(onExecution)
        {
            int key = cv::waitKey(10);
            switch(key)
            {
                case 's':
                {
                    onExecution=false;

                    std::vector<cv::Point> fixedPixels;
                    Utils::fixPoints(fixedPixels,*me.displayImg);

                    cv::Mat gray = cv::Mat::zeros(me.displayImg->rows,me.displayImg->cols,CV_8U);
                    Utils::drawPolygon(gray,POLY_COLOR,SHAPE_THICKNESS,me.p1,me.p1+me.d1,me.p2,me.p2+me.d2,true);

                    SelectFixedPixels::Utils::writeFixedPixels(os,fixedPixels);
                    os.flush();

                    DIPaCUS::Representation::CVMatToDigitalSet(ds,gray);

                    break;
                }
            }
        }

        cv::destroyAllWindows();
    }
}