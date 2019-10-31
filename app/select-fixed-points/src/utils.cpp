#include "select-fixed-points/utils.h"

namespace SelectFixedPixels
{
    namespace Utils
    {
        void writeFixedPixels(std::ostream& os, const std::vector<cv::Point>& fixedPixels)
        {
            for(auto p:fixedPixels)
            {
                int x = p.x;
                int y = p.y;

                os << (x<0?"":"+") << (x<0?-x:x) << " "
                   << (y<0?"":"+") << (y<0?-y:y) << " ";
            }
        }
    }

}