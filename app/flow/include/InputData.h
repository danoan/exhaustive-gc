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

    struct MyCoords
    {
        MyCoords():x(0),y(0),sign(false){}
        MyCoords(int x, int y, bool sign) : x(x), y(y), sign(sign) {}

        int x,y;
        bool sign;
    };
    typedef std::vector<MyCoords> MyCoordsCollection;

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

        nThreads = 4;
        threadSize = 0;

        numFixedLinels=0;
        randomFixedLinels=false;

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

    int nThreads;
    int threadSize;

    int numFixedLinels;
    bool randomFixedLinels;
    MyCoordsCollection fixedLinels;


    std::string outputFolder;


    friend std::ostream& operator<<(std::ostream& os,const InputData::AlgorithmEstimator& estimator);
    friend std::ostream& operator<<(std::ostream& os,const InputData::Strategy& strategy);
    friend std::ostream& operator<<(std::ostream& os,const InputData& id);

};

#endif //EXHAUSTIVE_GC_INPUTDATA_H
