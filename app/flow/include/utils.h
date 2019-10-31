#ifndef EXHAUSTIVE_GC_UTILS_H
#define EXHAUSTIVE_GC_UTILS_H

#include <random>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/base/Representation.h>
#include <DIPaCUS/derivates/Misc.h>

#include <select-fixed-points/gui.h>
#include <set-endpoints-orientation/gui.h>

#include "Shape.h"
#include "InputData.h"



namespace ExhaustiveGC
{
    namespace APP
    {
        namespace Utils
        {
            typedef std::set<DGtal::Z2i::SCell> LinelSet;
            typedef DGtal::Z2i::DigitalSet DigitalSet;
            typedef DGtal::Z2i::Domain Domain;
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Curve Curve;

            typedef std::vector<Point> PointVector;

            DIPaCUS::Shapes::DigitalSet resolveShape(Shape shape,double gridStep);

            void writeInputData(const InputData& id, const std::string& outputFile);

            PointVector toPointVector(const DigitalSet& ds, std::ostringstream& oss);

            LinelSet randomLinels(const DigitalSet& ds,int nLinels);
            LinelSet getLinels(const DigitalSet& ds, const std::string& fixedPixelsMask);

            template<class TPointIterator>
            LinelSet getLinels(const DigitalSet& ds, TPointIterator begin, TPointIterator end);

            LinelSet selectLinels(const DigitalSet& ds);
            LinelSet setEndpoints(DigitalSet& ds);

            #include "utils.hpp"
        }

    }
}



#endif //EXHAUSTIVE_GC_UTILS_H
