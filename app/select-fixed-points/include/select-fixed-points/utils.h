#ifndef EXHAUSTIVE_GC_SELECTFIXEDPOINTS_UTILS_H
#define EXHAUSTIVE_GC_SELECTFIXEDPOINTS_UTILS_H

#include <vector>

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core/types.hpp>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>

namespace SelectFixedPoints
{
    namespace Utils
    {
        typedef DGtal::Z2i::SCell SCell;
        typedef DGtal::Z2i::Point Point;

        std::vector<SCell> filterBoundaryLinels(cv::Mat& img, std::vector<cv::Point>& fixedPoints);
        void writeFixedLinels(std::ostream& os, std::vector<SCell>& fixedLinels);
    }
}


#endif //EXHAUSTIVE_GC_SELECTFIXEDPOINTS_UTILS_H
