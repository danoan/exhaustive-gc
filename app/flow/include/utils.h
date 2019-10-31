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
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Curve Curve;

            DIPaCUS::Shapes::DigitalSet resolveShape(Shape shape,double gridStep);

            void writeInputData(const InputData& id, const LinelSet& fixedLinels, const std::string& outputFile);

            LinelSet randomLinels(const DGtal::Z2i::DigitalSet& ds,int nLinels);
            LinelSet convertToDGtalPoints(const DGtal::Z2i::Domain& domain, const InputData::MyCoordsCollection& inputCoords);
            LinelSet selectLinels(const DGtal::Z2i::DigitalSet& ds);
            LinelSet setEndpoints(DGtal::Z2i::DigitalSet& ds);
        }

    }
}


#endif //EXHAUSTIVE_GC_UTILS_H
