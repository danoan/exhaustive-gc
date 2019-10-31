#ifndef EXHAUSTIVE_GC_SELECTFIXEDPOINTS_UTILS_H
#define EXHAUSTIVE_GC_SELECTFIXEDPOINTS_UTILS_H

#include <vector>

#include <DGtal/helpers/StdDefs.h>
#include <opencv2/core/types.hpp>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>

namespace SelectFixedPixels
{
    namespace Utils
    {
        typedef DGtal::Z2i::SCell SCell;
        typedef DGtal::Z2i::Point Point;

        void writeFixedPixels(std::ostream& os, const std::vector<cv::Point>& fixedPixels);
    }
}


#endif //EXHAUSTIVE_GC_SELECTFIXEDPOINTS_UTILS_H
