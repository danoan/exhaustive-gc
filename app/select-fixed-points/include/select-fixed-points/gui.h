#ifndef EXHAUSTIVE_GC_SELECTFIXEDPOINTS_GUI_H
#define EXHAUSTIVE_GC_SELECTFIXEDPOINTS_GUI_H

#include <opencv2/highgui.hpp>
#include <DGtal/helpers/StdDefs.h>

#include "GUIControl.h"
#include "events.h"
#include "utils.h"

namespace SelectFixedPixels
{
    void gui(cv::Mat& img, std::ostream& os);
}

#endif //EXHAUSTIVE_GC_GUI_H
