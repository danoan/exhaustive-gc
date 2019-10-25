#ifndef EXHAUSTIVE_GC_SELECTFIXEDPOINTS_EVENTS_H
#define EXHAUSTIVE_GC_SELECTFIXEDPOINTS_EVENTS_H

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "GUIControl.h"

namespace SelectFixedPoints
{
    namespace Events
    {
        void mouseCallback(int event,
                           int x,
                           int y,
                           int flags,
                           void *param);        
    }

}

#endif //EXHAUSTIVE_GC_SELECTFIXEDPOINTS_EVENTS_H
