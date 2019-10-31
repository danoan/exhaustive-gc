#ifndef EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_GUICONTROL_H
#define EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_GUICONTROL_H

#include <opencv2/highgui.hpp>

namespace SetEndpointsOrientation
{
    struct GUIControl
    {
        enum State{SetPoint1,WaitPoint2,SetPoint2,WaitAction};

        GUIControl(cv::Mat& originalImg,const std::string& wn):originalImg(originalImg),wn(wn),state(WaitAction)
        {
            bufferImg = new cv::Mat(originalImg.rows,originalImg.cols,originalImg.type());
            displayImg = new cv::Mat(originalImg.rows,originalImg.cols,originalImg.type());

            *displayImg = originalImg.clone();
        }

        ~GUIControl(){ delete bufferImg; delete displayImg; }
        GUIControl(const GUIControl& other):originalImg(other.originalImg){throw std::runtime_error("Operation not allowed!");}
        GUIControl& operator=(const GUIControl& other){throw std::runtime_error("Operation not allowed!");}

        void setPoint(const cv::Point& p)
        {
            if(state==SetPoint1) p1 = p;
            else if(state==SetPoint2) p2=p;
            else throw std::runtime_error("Unexpected state!");
        }

        void setDir(const cv::Point& d)
        {
            if(state==SetPoint1) d1 = d;
            else if(state==SetPoint2) d2=d;
            else throw std::runtime_error("Unexpected state!");
        }

        State state;
        cv::Point p1,p2;
        cv::Point d1,d2;

        cv::Mat* bufferImg;
        cv::Mat* displayImg;
        cv::Mat& originalImg;

        const std::string wn;

    };
}

#endif //EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_GUICONTROL_H
