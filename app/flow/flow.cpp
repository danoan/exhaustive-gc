#include <boost/filesystem.hpp>

#include <exhaustive-gc/api/api.h>
#include <exhaustive-gc/utils/timer.h>
#include <exhaustive-gc/energy/EnergyInput.h>

#include <set-endpoints-orientation/gui.h>

#include "InputReader.h"
#include "InputData.h"
#include "utils.h"

using namespace ExhaustiveGC;

typedef std::pair<DGtal::Z2i::DigitalSet,Energy::EnergyInput::LinelSet> InitializationPair;
typedef DGtal::Z2i::DigitalSet DigitalSet;
typedef DGtal::Z2i::Domain Domain;
typedef DGtal::Z2i::Point Point;

InitializationPair resolveInitialSet(const InputData& id)
{


    DigitalSet shape= APP::Utils::resolveShape(id.shape,id.gridStep);

    Energy::EnergyInput::LinelSet ls;
    switch(id.initMode)
    {
        case InputData::None:
        {
            return InitializationPair(shape,ls);
        }
        case InputData::FixedPixels:
        {
            ls = APP::Utils::getLinels(shape,id.fixedPixelsMask);
            return InitializationPair(shape,ls);
        }
        case InputData::InteractiveFixedPixels:
        {
            ls = APP::Utils::selectLinels(shape);
            return InitializationPair(shape,ls);
        }
        case InputData::InteractiveEndpoints:
        {
            auto SS = SetEndpointsOrientation::SCREEN_SIZE;
            DigitalSet ds( Domain( Point(0,0),Point(SS.x-1,SS.y-1) ) );
            ls = APP::Utils::setEndpoints(ds);

            return InitializationPair(ds,ls);
        }
        default:
        {
            throw std::runtime_error("Initialization mode not recognized!");
        }
    }



}

int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);
    InitializationPair ip = resolveInitialSet(id);

    const DigitalSet& shape = ip.first;
    const Energy::EnergyInput::LinelSet& ls = ip.second;

    Energy::EnergyInput energyInput( id.energyType, id.estimator, id.gridStep, id.radius, id.lengthPenalization,ls );

    API::Curve optimalCurve;
    API::SearchParameters sp(id.strategy,id.joints,id.minGCLength,id.maxGCLength,id.automaticGCLength,energyInput,id.nThreads,id.threadSize);

    boost::filesystem::create_directories(id.outputFolder);


    APP::Utils::writeInputData(id,id.outputFolder + "/inputData.txt");
    std::ofstream ofs(id.outputFolder + "/energy.txt");



    Utils::Timer::start();
    API::optimalOneExpansionSequence(shape,sp,id.iterations,id.outputFolder,ofs);
    ofs << "\n\n#";
    Utils::Timer::end(ofs);

    ofs << "Initial digital shape size: " << shape.size() << " pixels.";

    ofs.flush();
    ofs.close();

    return 0;
}