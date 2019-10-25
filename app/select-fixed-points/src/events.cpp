#include "select-fixed-points/events.h"

namespace SelectFixedPoints
{
    namespace Events
    {
        void mouseCallback(int event,
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

    }
       
}