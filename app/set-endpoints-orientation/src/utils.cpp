#include "set-endpoints-orientation/utils.h"

namespace SetEndpointsOrientation
{
    namespace Utils
    {
        void closedPolygonFrom4Points(cv::Point* pts, int thickness,cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4)
        {
            pts[0] = p1;
            pts[1] = p2;
            pts[2] = p3;
            pts[3] = p4;

            int maxY=pts[0].y;
            int maxX=pts[0].x;
            int lowY=pts[0].y;
            int lowX=pts[0].x;
            for(int i=0;i<4;++i)
            {
                if( pts[i].y > maxY ) maxY = pts[i].y;
                if( pts[i].y < lowY ) lowY = pts[i].y;
                if( pts[i].x > maxX ) maxX = pts[i].x;
                if( pts[i].x < lowX ) lowX = pts[i].x;
            }


            pts[4] = cv::Point(maxX+thickness,lowY-thickness);

            pts[5] = cv::Point(lowX-thickness,pts[4].y);
            pts[6] = cv::Point(lowX-thickness,maxY);
            pts[7] = pts[0];
        }

        void drawPolygon(cv::Mat& img, const cv::Vec3b& polyColor, int thickness,cv::Point p1, cv::Point p2, cv::Point p3, cv::Point p4,bool fill)
        {
            int npt[] = {8};
            cv::Point pts[8];
            Utils::closedPolygonFrom4Points(pts,thickness,p1,p2,p3,p4);
            const cv::Point* ppt[1] = { pts };

            if(fill)
                cv::fillPoly(img,ppt,npt,1,polyColor);
            else
                cv::polylines(img,ppt,npt,1,true,polyColor);
        }

        void fixPoints(std::vector<cv::Point>& cvPoints, cv::Mat& img)
        {
            for(int r=0;r<img.rows;++r)
            {
                for(int c=0;c<img.cols;++c)
                {
                    if( img.at<cv::Vec3b>(r,c)==cv::Vec3b(255,255,255) )
                    {
                        cvPoints.push_back(cv::Point(c,img.rows-1-r));
                    }
                }
            }
        }
    }
}
