#ifndef EXHAUSTIVE_GC_INPUTDATA_H
#define EXHAUSTIVE_GC_INPUTDATA_H

#include <string>
#include "Shape.h"
#include "exhaustive-gc/core/model/Types.h"

struct InputData
{
    typedef unsigned long int uint;
    typedef ExhaustiveGC::Core::Strategy  Strategy;

    InputData()
    {
        minGCLength = 4;
        maxGCLength = 10;
        joints = 2;
        iterations = 10;

        shape = Shape( ShapeType::Square );
        strategy = Strategy::First;

        outputFolder="";
    }

    uint minGCLength;
    uint maxGCLength;
    uint joints;
    uint iterations;

    Shape shape;
    Strategy  strategy;

    std::string outputFolder;
};

#endif //EXHAUSTIVE_GC_INPUTDATA_H
