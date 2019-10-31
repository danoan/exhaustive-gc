#ifndef EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_GUI_H
#define EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_GUI_H

#include <string>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include <select-fixed-points/utils.h>

#include "GUIControl.h"
#include "events.h"
#include "utils.h"

namespace SetEndpointsOrientation
{
    extern cv::Point SCREEN_SIZE;
    extern cv::Vec3b POLY_COLOR;
    extern int SHAPE_THICKNESS;

    void gui(const std::string& outputFilePath, std::ostream& os);
    void gui(DGtal::Z2i::DigitalSet& ds, std::ostream& os);
}

#endif //EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_GUI_H
