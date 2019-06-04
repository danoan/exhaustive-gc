#include <unistd.h>
#include <string>

#include "exhaustive-gc/api/api.h"
#include "exhaustive-gc/utils/timer.h"

struct InputData
{
    typedef unsigned long int uint;

    InputData()
    {
        minGCLength = 4;
        maxGCLength = 10;
        joints = 2;
        iterations = 10;

        outputFolder="";
    }

    uint minGCLength;
    uint maxGCLength;
    uint joints;
    uint iterations;

    std::string outputFolder;
};

void usage(char* argv[])
{
    std::cerr << "Usage: " << argv[0] << " OutputFolder \n"
            "[-m Minimum glued curve length]\n"
            "[-M Maximum glued curve length]\n"
            "[-j Number of joints to optimize per iteration]\n"
            "[-i Number of iterations]\n";
}

InputData readInput(int argc, char* argv[])
{
    if(argc<2)
    {
        usage(argv);
        exit(1);
    }

    InputData id;
    int opt;
    while( (opt=getopt(argc,argv,"m:M:j:i:"))!=-1 )
    {
        switch(opt)
        {
            case 'm':
            {
                id.minGCLength = std::atoi(optarg);
                break;
            }
            case 'M':
            {
                id.maxGCLength = std::atoi(optarg);
                break;
            }
            case 'j':
            {
                id.joints = std::atoi(optarg);
                break;
            }
            case 'i':
            {
                id.iterations = std::atoi(optarg);
                break;
            }
        }
    }

    id.outputFolder = argv[optind++];
    return id;
}


int main(int argc, char* argv[])
{
    InputData id = readInput(argc,argv);

    DIPaCUS::Shapes::DigitalSet square = DIPaCUS::Shapes::square();

    API::Curve optimalCurve;
    API::SearchParameters<2> sp(id.minGCLength,id.maxGCLength,API::EnergyType::IntSquaredCurvature);

    boost::filesystem::create_directories(id.outputFolder);

    Utils::Timer::start();
    API::optimalOneExpansionSequence(square,sp,id.iterations,id.outputFolder);
    Utils::Timer::end(std::cout);
    return 0;
}