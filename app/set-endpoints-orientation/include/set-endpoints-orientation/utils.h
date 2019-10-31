#ifndef EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_UTILS_H
#define EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_UTILS_H

#include <vector>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

namespace SetEndpointsOrientation
{
    namespace Utils
    {
        void fixPoints(std::vector<cv::Point>& cvPoints, cv::Mat& img);
        void closedPolygonFrom4Points(cv::Point* pts, int thickness,cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4);
        void drawPolygon(cv::Mat& img, const cv::Vec3b& polyColor, int thickness,cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4,bool fill);
    }
}

#endif //EXHAUSTIVE_GC_SETENDPOINTSORIENTATION_UTILS_H
