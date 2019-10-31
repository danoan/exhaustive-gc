#include "utils.h"


namespace ExhaustiveGC
{
    namespace APP
    {
        namespace Utils
        {

            DIPaCUS::Shapes::DigitalSet resolveShape(Shape shape,double gridStep)
            {
                int radius=10;
                if(shape.type==ShapeType::Triangle) return DIPaCUS::Shapes::triangle(gridStep,0,0,radius);
                else if(shape.type==ShapeType::Square) return DIPaCUS::Shapes::square(gridStep,0,0,radius);
                else if(shape.type==ShapeType::Pentagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,5);
                else if(shape.type==ShapeType::Heptagon) return DIPaCUS::Shapes::NGon(gridStep,0,0,radius,7);
                else if(shape.type==ShapeType::Ball) return DIPaCUS::Shapes::ball(gridStep,0,0,radius);
                else if(shape.type==ShapeType::Flower) return DIPaCUS::Shapes::flower(gridStep,0,0,radius,radius/2.0,2);
                else if(shape.type==ShapeType::Ellipse) return DIPaCUS::Shapes::ellipse(gridStep,0,0,radius,radius/2);
                else if(shape.type==ShapeType::Wave) return DIPaCUS::Shapes::wave(gridStep,1200,radius*3,radius*6,0.01);
                else if(shape.type==ShapeType::Bean) return DIPaCUS::Shapes::bean(gridStep,0,0,0.1);
                else
                {
                    typedef DIPaCUS::Representation::Image2D Image2D;
                    Image2D image = DGtal::GenericReader<Image2D>::import(shape.imagePath);
                    DGtal::Z2i::DigitalSet dsOut(image.domain());
                    DIPaCUS::Representation::imageAsDigitalSet(dsOut,image,1);
                    return dsOut;
                }
            }

            void writeInputData(const InputData& id, const LinelSet& fixedLinels, const std::string& outputFile)
            {
                std::string inputDataFile = outputFile;
                std::ofstream ofs(inputDataFile);
                ofs << id;

                ofs << "Fixed Linels: ";
                for(auto l:fixedLinels)
                {
                    auto c = l.preCell().coordinates;
                    ofs << (c[0]>0?"+":"") << (c[0]>0?c[0]:-c[0]) << " "
                        << (c[1]>0?"+":"") << (c[1]>0?c[1]:-c[1]) << " "
                        << l.preCell().positive << " ";
                }
                ofs << "\n";

                ofs.flush();
                ofs.close();
            }

            LinelSet randomLinels(const DGtal::Z2i::DigitalSet& ds,int nLinels)
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

            LinelSet convertToDGtalPoints(const DGtal::Z2i::Domain& domain, const InputData::MyCoordsCollection& inputCoords)
            {
                LinelSet ls;
                DGtal::Z2i::KSpace kspace;
                kspace.init(domain.lowerBound(),domain.upperBound(),true);

                for(auto c:inputCoords) ls.insert( kspace.sCell( DGtal::Z2i::Point(c.x,c.y),c.sign) );
                return ls;
            }

            InputData::MyCoordsCollection toMyCoords(const DGtal::Z2i::DigitalSet& ds, std::ostringstream& oss)
            {
                InputData::MyCoordsCollection coords;

                DGtal::Z2i::Domain domain = ds.domain();
                Point translation = Point(0,0) - domain.lowerBound();
                Point size = domain.upperBound() - domain.lowerBound() + Point(1,1);
                int maxY = size[1];
                
                std::string s = oss.str();
                std::string buffer="";
                int currDim=0;
                Point p;
                for(auto c:s)
                {
                    if(c==' ')
                    {
                        if(currDim<=1)
                        {
                            int v = buffer[0]=='+'?std::atoi(buffer.data()+1): -std::atoi(buffer.data());
                            p[currDim++] = v;
                        }else
                        {
                            bool sign = std::atoi(buffer.data())==1;
                            p-=2*translation;
                            coords.push_back( InputData::MyCoords(p[0],p[1],sign));
                            currDim=0;
                        }
                        buffer="";
                    }else
                    {
                        buffer+=c;
                    }
                }
                
                return coords;
            }

            LinelSet selectLinels(const DGtal::Z2i::DigitalSet& ds)
            {
                DGtal::Z2i::Domain domain = ds.domain();
                Point size = domain.upperBound() - domain.lowerBound() + Point(1,1);
                cv::Mat img = cv::Mat::zeros(size[1],size[0],DIPaCUS::Representation::GRAYSCALE_IMG_TYPE);
                
                std::ostringstream oss;
                DIPaCUS::Representation::digitalSetToCVMat(img,ds);
                SelectFixedPoints::gui(img,oss);

                
                return convertToDGtalPoints(domain,toMyCoords(ds,oss));

            }

            LinelSet setEndpoints(DGtal::Z2i::DigitalSet& ds)
            {
                std::ostringstream oss;
                SetEndpointsOrientation::gui(ds,oss);


                return convertToDGtalPoints(ds.domain(),toMyCoords(ds,oss));                
            }
        }
    }
}
