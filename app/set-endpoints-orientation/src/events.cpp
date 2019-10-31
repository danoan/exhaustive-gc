#include "set-endpoints-orientation/events.h"

namespace SetEndpointsOrientation
{
    namespace Events
    {
        cv::Vec3b HIGHLIGHT_COLOR(0,0,255);
        cv::Vec3b ARROW_COLOR(0,255,0);

        void mouseCallback(int event, int x, int y, int flags, void* userdata)
        {
            GUIControl* me = (GUIControl*) userdata;
            switch(event)
            {
                case cv::EVENT_LBUTTONDOWN:
                {
                    if(me->state == GUIControl::WaitAction) me->state = GUIControl::SetPoint1;
                    else if(me->state == GUIControl::WaitPoint2) me->state = GUIControl::SetPoint2;
                    else throw std::runtime_error("Unexpected state!");

                    me->setPoint(cv::Point(x,y));

                    break;
                }
                case cv::EVENT_LBUTTONUP:
                {
                    if(me->state == GUIControl::SetPoint1) me->state = GUIControl::WaitPoint2;
                    else if(me->state == GUIControl::SetPoint2)
                    {
                        me->state = GUIControl::WaitAction;

                        *me->displayImg = me->originalImg.clone();
                        Utils::drawPolygon(*me->displayImg,POLY_COLOR,SHAPE_THICKNESS,me->p1,me->p1+me->d1,me->p2,me->p2+me->d2,false);
                        cv::line(*me->displayImg,me->p1+me->d1,me->p2,HIGHLIGHT_COLOR,2,cv::LINE_4);

                        cv::imshow(me->wn,*me->displayImg);
                        break;

                    }
                    else throw std::runtime_error("Unexpected state!");

                    cv::arrowedLine(*me->displayImg,me->p1,me->p1 + me->d1,cv::Vec3b(0,255,0),3, cv::LINE_AA);

                    break;
                }
                case cv::EVENT_MOUSEMOVE:
                {
                    cv::Point poi;
                    if(me->state == GUIControl::SetPoint1) poi = me->p1;
                    else if(me->state == GUIControl::SetPoint2) poi = me->p2;
                    else break;

                    me->setDir( cv::Point(x,y) - poi);

                    *me->bufferImg = me->displayImg->clone();
                    cv::arrowedLine(*me->bufferImg,poi,cv::Point(x,y),ARROW_COLOR,2, cv::LINE_AA);
                    cv::imshow(me->wn,*me->bufferImg);


                    break;
                }
            }
        }
    }
}