#ifndef EXHAUSTIVE_GC_SELECTFIXEDPOINTS_GUICONTROL_H
#define EXHAUSTIVE_GC_SELECTFIXEDPOINTS_GUICONTROL_H

namespace SelectFixedPoints
{
    struct GUIControl
    {
        GUIControl(const cv::Mat& loadedImg, cv::Mat& displayedImg):loadedImg(loadedImg),displayedImg(displayedImg){}

        void addPointsInRect(const cv::Point& lb, const cv::Point& ub)
        {
            cv::Point diff = ub - lb;

            for(auto x=0;x<=diff.x;++x)
            {
                for(auto y=0;y<=diff.y;++y)
                {
                    fixedPoints.push_back(cv::Point(lb+cv::Point(x,y)));
                }
            }

        }

        const cv::Mat& loadedImg;
        cv::Mat& displayedImg;

        std::vector<cv::Point> fixedPoints;
    };
}

#endif //EXHAUSTIVE_GC_GUICONTROL_H
