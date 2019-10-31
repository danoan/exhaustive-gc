#include "select-fixed-points/gui.h"

namespace SelectFixedPixels
{
    void gui(cv::Mat& img, std::ostream& os)
    {
        using namespace DGtal::Z2i;

        std::string wn = "fixed-points-selection";
        cv::namedWindow(wn,cv::WINDOW_GUI_EXPANDED);

        cv::Mat displayedImg = img.clone();

        GUIControl me(img,displayedImg);
        cv::setMouseCallback(wn,Events::mouseCallback,&me);

        cv::imshow(wn,img);

        bool onExecution=true;
        while(onExecution)
        {
            int key=cv::waitKey(10);
            switch(key)
            {
                case 'r':
                {
                    displayedImg = img.clone();
                    cv::imshow(wn,displayedImg);
                    me.fixedPixels.clear();
                    break;
                }
                case 's':
                {
                    Utils::writeFixedPixels(os, me.fixedPixels );
                    cv::imshow(wn,img);
                    me.fixedPixels.clear();
                    onExecution=false;
                    break;
                }
            }
        }

        os.flush();
        cv::destroyWindow(wn);
    }
}