#include <iostream>
#include <opencv2/highgui.hpp>

#include <DGtal/helpers/StdDefs.h>
#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>

using namespace DGtal::Z2i;

struct GUIControl
{
    GUIControl(const cv::Mat& loadedImg, cv::Mat& displayedImg):loadedImg(loadedImg),displayedImg(displayedImg){}

    void addPointsInRect(const cv::Point& lb, const cv::Point& ub)
    {
        cv::Point diff = ub - lb;

        for(auto x=0;x<=diff.x;++x)
        {
            for(auto y=0;y<=diff.y;++y)
            {
                fixedPoints.push_back(cv::Point(lb+cv::Point(x,y)));
            }
        }

    }

    const cv::Mat& loadedImg;
    cv::Mat& displayedImg;

    std::vector<cv::Point> fixedPoints;
};

void callbackFn(int event,
                int x,
                int y,
                int flags,
                void *param)

{
    GUIControl* me = (GUIControl*) param;
    cv::Mat tempImg = me->displayedImg.clone();
    switch(event)
    {
        case cv::EVENT_LBUTTONDOWN:
        {
            cv::Point p1(x-1,y-1);
            cv::Point p2(x+1,y+1);
            me->addPointsInRect(p1,p2);
            cv::rectangle( me->displayedImg, p1,p2, 64,-1);
            break;
        }
        case cv::EVENT_MOUSEMOVE:
        {
            cv::Point p1(x-1,y-1);
            cv::Point p2(x+1,y+1);
            cv::rectangle( tempImg, p1,p2, 128,-1);

            cv::imshow("fixed-points-selection", tempImg);

            break;
        }
        case cv::EVENT_LBUTTONUP:
        {
            break;
        }
    }
}

std::vector<SCell> filterBoundaryLinels(const DigitalSet& ds, const Point& translation, std::vector<cv::Point>& fixedPoints)
{
    std::vector<SCell> fixedLinels;

    int maxY = (ds.domain().upperBound() - ds.domain().lowerBound() + Point(1,1) )[1];

    Curve curve;
    DIPaCUS::Misc::computeBoundaryCurve(curve,ds);
    KSpace kspace;
    kspace.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);
    for(auto l:curve)
    {
        auto pixels = kspace.sUpperIncident(l);
        for(auto p:pixels)
        {
            Point pc = kspace.sCoords(p);
            for(auto fp:fixedPoints)
            {

                if( pc==Point(fp.x,maxY-fp.y)-translation )
                {
                    fixedLinels.push_back( l );
                }
            }
        }
    }

    return fixedLinels;
}

void writeFixedLinels(std::ostream& os, std::vector<SCell>& fixedLinels)
{
    for(auto p:fixedLinels)
    {
        auto c = p.preCell().coordinates;
        int x = c[0];
        int y = c[1];

        os << (x<0?"":"+") << (x<0?-x:x) << " "
        << (y<0?"":"+") << (y<0?-y:y) << " "
        << p.preCell().positive << " ";
    }
}

int main(int argc, char* argv[])
{
    std::string wn = "fixed-points-selection";
    cv::namedWindow(wn);

    DigitalSet square = DIPaCUS::Shapes::square();
    Point squareSize = square.domain().upperBound() - square.domain().lowerBound() + Point(1,1);

    Point translation = Point(0,0) - square.domain().lowerBound();

    cv::Mat cvImg = cv::Mat::zeros(squareSize[1],squareSize[0],DIPaCUS::Representation::GRAYSCALE_IMG_TYPE);
    cv::imwrite("test.pgm",cvImg);
    DIPaCUS::Representation::digitalSetToCVMat(cvImg,square);

    cv::Mat displayedImg = cvImg.clone();

    GUIControl me(cvImg,displayedImg);
    cv::setMouseCallback(wn,callbackFn,&me);

    std::ostream& os = std::cout;
    cv::imshow(wn,cvImg);

    bool onExecution=true;
    while(onExecution)
    {
        int key=cv::waitKey(10);
        switch(key)
        {
            case 'r':
            {
                cv::imshow(wn,cvImg);
                me.fixedPoints.clear();
                break;
            }
            case 's':
            {
                auto fixedLinels = filterBoundaryLinels(square,translation,me.fixedPoints);
                writeFixedLinels(os, fixedLinels );
                cv::imshow(wn,cvImg);
                me.fixedPoints.clear();
                onExecution=false;
                break;
            }
        }
    }

    os.flush();
    cv::destroyWindow(wn);

    return 0;
}