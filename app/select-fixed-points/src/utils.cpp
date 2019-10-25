#include "select-fixed-points/utils.h"

namespace SelectFixedPoints
{
    namespace Utils
    {
        std::vector<SCell> filterBoundaryLinels(cv::Mat& img, std::vector<cv::Point>& fixedPoints)
        {
            using namespace DGtal::Z2i;

            Domain domain( Point(0,0),Point(img.cols,img.rows) - Point(1,1) );
            DigitalSet ds(domain);
            DIPaCUS::Representation::CVMatToDigitalSet(ds,img);

            std::vector<SCell> fixedLinels;

            int maxY = (ds.domain().upperBound() - ds.domain().lowerBound() + Point(1,1) )[1];

            Curve curve;
            DIPaCUS::Misc::computeBoundaryCurve(curve,ds);
            KSpace kspace;
            kspace.init(ds.domain().lowerBound(),ds.domain().upperBound(),true);
            for(auto l:curve)
            {
                auto pixels = kspace.sUpperIncident(l);
                bool found=false;
                for(auto p:pixels)
                {
                    Point pc = kspace.sCoords(p);
                    for(auto fp:fixedPoints)
                    {

                        if( pc==Point(fp.x,maxY-1-fp.y))
                        {
                            fixedLinels.push_back( l );
                            found=true;
                            break;
                        }
                    }
                    if(found) break;
                }
            }

            return fixedLinels;
        }

        void writeFixedLinels(std::ostream& os, std::vector<SCell>& fixedLinels)
        {
            for(auto p:fixedLinels)
            {
                auto c = p.preCell().coordinates;
                int x = c[0];
                int y = c[1];

                os << (x<0?"":"+") << (x<0?-x:x) << " "
                   << (y<0?"":"+") << (y<0?-y:y) << " "
                   << p.preCell().positive << " ";
            }
        }
    }

}