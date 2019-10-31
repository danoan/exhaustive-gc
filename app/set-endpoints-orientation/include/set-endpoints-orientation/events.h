#ifndef EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_EVENTS_H
#define EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_EVENTS_H

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "GUIControl.h"
#include "utils.h"

namespace SetEndpointsOrientation
{
    extern cv::Vec3b POLY_COLOR;
    extern int SHAPE_THICKNESS;

    namespace Events
    {
        extern cv::Vec3b HIGHLIGHT_COLOR;
        extern cv::Vec3b ARROW_COLOR;

        void mouseCallback(int event, int x, int y, int flags, void* userdata);
    }
}

#endif //EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_EVENTS_H
