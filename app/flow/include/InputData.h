#ifndef EXHAUSTIVE_GC_INPUTDATA_H
#define EXHAUSTIVE_GC_INPUTDATA_H

#include <string>

#include "Shape.h"
#include "exhaustive-gc/core/model/Types.h"
#include "exhaustive-gc/energy/EnergyType.h"
#include "exhaustive-gc/energy/EnergyInput.h"

struct InputData
{
    typedef unsigned long int uint;
    typedef ExhaustiveGC::Core::Strategy  Strategy;
    typedef ExhaustiveGC::Energy::EnergyType  EnergyType;
    typedef ExhaustiveGC::Energy::EnergyInput::AlgorithmEstimator  AlgorithmEstimator;
    
    enum InitializationMode{None,FixedPixels,InteractiveFixedPixels,InteractiveEndpoints};

    InputData()
    {
        minGCLength = 4;
        maxGCLength = 10;
        automaticGCLength = true;

        joints = 2;
        iterations = 10;

        shape = Shape( ShapeType::Square );
        strategy = Strategy::First;

        energyType = EnergyType::Elastica;
        lengthPenalization = 0.005;

        gridStep = 1.0;
        radius = 3.0;
        estimator = AlgorithmEstimator::MDCA;

        nThreads = 4;
        threadSize = 0;

        fixedPixelsMask="";
        initMode = None;

        outputFolder="";
    }

    uint minGCLength;
    uint maxGCLength;
    uint joints;
    uint iterations;

    bool automaticGCLength;

    Shape shape;
    Strategy  strategy;


    EnergyType energyType;
    double lengthPenalization;

    double gridStep;
    double radius;
    AlgorithmEstimator estimator;

    int nThreads;
    int threadSize;

    std::string fixedPixelsMask;
    InitializationMode initMode;


    std::string outputFolder;


    friend std::ostream& operator<<(std::ostream& os,const InputData::AlgorithmEstimator& estimator);
    friend std::ostream& operator<<(std::ostream& os,const InputData::Strategy& strategy);
    friend std::ostream& operator<<(std::ostream& os,const InputData& id);

};

#endif //EXHAUSTIVE_GC_INPUTDATA_H
