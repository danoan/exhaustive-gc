#include "utils.h"


namespace ExhaustiveGC
{
    namespace APP
    {
        namespace Utils
        {

            DIPaCUS::Shapes::DigitalSet resolveShape(Shape shape,double gridStep)
            {
                int radius=20;
                if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
                else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
                else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
                else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
                else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
                else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,7.0,2);
                else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
                else if(shape.type==ShapeType::Wave) return DIPaCUS::Shapes::wave(gridStep,1200,radius*3,radius*6,0.01);
                else if(shape.type==ShapeType::Bean) return DIPaCUS::Shapes::bean(gridStep,0,0,0.1);
                else
                {
                    typedef DIPaCUS::Representation::Image2D Image2D;
                    Image2D image = DGtal::GenericReader<Image2D>::import(shape.imagePath);
                    DigitalSet dsOut(image.domain());
                    DIPaCUS::Representation::imageAsDigitalSet(dsOut,image,1);
                    return dsOut;
                }
            }

            void writeInputData(const InputData& id, const std::string& outputFile)
            {
                std::string inputDataFile = outputFile;
                std::ofstream ofs(inputDataFile);
                ofs << id;

                ofs.flush();
                ofs.close();
            }

            LinelSet randomLinels(const DigitalSet& ds,int nLinels)
            {
                LinelSet ls;
                Curve shapeBoundary;
                DIPaCUS::Misc::computeBoundaryCurve(shapeBoundary,ds);

                std::random_device rd;
                std::knuth_b prg(rd());

                std::uniform_int_distribution<int> ud(0,shapeBoundary.size()-1);

                for(int i=0;i<nLinels;++i)
                {
                    int g = ud.operator()(prg);
                    auto l = *( shapeBoundary.begin()+g );
                    if( ls.find(l)!=ls.end()) continue;

                    ls.insert( l );
                }

                return ls;
            }

            LinelSet getLinels(const DigitalSet& ds, const std::string& fixedPixelsMask)
            {
                typedef DIPaCUS::Representation::Image2D Image2D;
                Image2D image = DGtal::GenericReader<Image2D>::import(fixedPixelsMask);
                DigitalSet dsOut(image.domain());
                DIPaCUS::Representation::imageAsDigitalSet(dsOut,image,1);

                return getLinels(ds,dsOut.begin(),dsOut.end());
            }
            
            PointVector toPointVector(const DigitalSet& ds, std::ostringstream& oss)
            {
                PointVector pixels;
                Point translation = ds.domain().lowerBound();

                std::string s = oss.str();
                std::string buffer="";
                int currDim=0;
                Point p;
                for(auto c:s)
                {
                    if(c==' ')
                    {
                        int v = buffer[0]=='+'?std::atoi(buffer.data()+1): -std::atoi(buffer.data());
                        p[currDim++] = v;

                        if(currDim==2)
                        {
                            pixels.push_back( Point(p[0],p[1])+translation );
                            currDim=0;
                        }

                        buffer="";
                    }else
                    {
                        buffer+=c;
                    }
                }
                
                return pixels;
            }

            LinelSet selectLinels(const DigitalSet& ds)
            {
                DGtal::Z2i::Domain domain = ds.domain();
                Point size = domain.upperBound() - domain.lowerBound() + Point(1,1);
                cv::Mat img = cv::Mat::zeros(size[1],size[0],DIPaCUS::Representation::GRAYSCALE_IMG_TYPE);
                
                std::ostringstream oss;
                DIPaCUS::Representation::digitalSetToCVMat(img,ds);
                SelectFixedPixels::gui(img,oss);

                PointVector fixedPixels = toPointVector(ds,oss);
                
                return getLinels(ds,fixedPixels.begin(),fixedPixels.end());

            }

            LinelSet setEndpoints(DigitalSet& ds)
            {
                std::ostringstream oss;
                SetEndpointsOrientation::gui(ds,oss);

                PointVector fixedPixels = toPointVector(ds,oss);

                return getLinels(ds,fixedPixels.begin(),fixedPixels.end());
            }
        }
    }
}
