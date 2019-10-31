#ifndef EXHAUSTIVE_GC_SELECTFIXEDPOINTS_GUICONTROL_H
#define EXHAUSTIVE_GC_SELECTFIXEDPOINTS_GUICONTROL_H

namespace SelectFixedPixels
{
    struct GUIControl
    {
        GUIControl(const cv::Mat& loadedImg, cv::Mat& displayedImg):loadedImg(loadedImg),displayedImg(displayedImg){}

        void addPointsInRect(const cv::Point& lb, const cv::Point& ub,int maxY)
        {
            cv::Point diff = ub - lb;

            for(auto x=0;x<=diff.x;++x)
            {
                for(auto y=0;y<=diff.y;++y)
                {
                    cv::Point p = (lb+cv::Point(x,y));
                    p.y=maxY-p.y;
                    fixedPixels.push_back(p);
                }
            }

        }

        const cv::Mat& loadedImg;
        cv::Mat& displayedImg;

        std::vector<cv::Point> fixedPixels;
    };
}

#endif //EXHAUSTIVE_GC_GUICONTROL_H
