#ifndef EXHAUSTIVE_GC_INPUTDATA_H
#define EXHAUSTIVE_GC_INPUTDATA_H

#include <string>
#include "Shape.h"
#include "exhaustive-gc/core/model/Types.h"

struct InputData
{
    typedef unsigned long int uint;
    typedef ExhaustiveGC::Core::Strategy  Strategy;
    typedef ExhaustiveGC::Energy::EnergyType  EnergyType;
    typedef ExhaustiveGC::Energy::EnergyInput::AlgorithmEstimator  AlgorithmEstimator;

    InputData()
    {
        minGCLength = 4;
        maxGCLength = 10;
        joints = 2;
        iterations = 10;

        shape = Shape( ShapeType::Square );
        strategy = Strategy::First;

        energyType = EnergyType::SquaredCurvature;
        lengthPenalization = 0.005;

        gridStep = 1.0;
        radius = 3.0;
        estimator = AlgorithmEstimator::MDCA;

        outputFolder="";
    }

    uint minGCLength;
    uint maxGCLength;
    uint joints;
    uint iterations;

    Shape shape;
    Strategy  strategy;


    EnergyType energyType;
    double lengthPenalization;

    double gridStep;
    double radius;
    AlgorithmEstimator estimator;


    std::string outputFolder;
};

#endif //EXHAUSTIVE_GC_INPUTDATA_H
