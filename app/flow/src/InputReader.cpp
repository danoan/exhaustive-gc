#include <stdexcept>
#include <exhaustive-gc/energy/EnergyType.h>
#include <exhaustive-gc/energy/EnergyInput.h>
#include "InputReader.h"

namespace InputReader
{
    void usage(char* argv[])
    {
        std::cerr << "Usage: " << argv[0] << " OutputFolder \n"
                "[-m Minimum glued curve length]\n"
                "[-M Maximum glued curve length]\n"
                "[-j Number of joints to optimize per iteration]\n"
                "[-i Number of iterations]\n"
                "[-D Number of dilated sets]\n"
                "[-E Number of eroded sets]\n"
                "[-V Number of curve divisions]\n"
                "[-e Energy (isqc elastica selastica cselastica)]\n"
                "[-a Length penalization ]\n"
                "[-S Shape (triangle square elipse pentagon heptagon ball flower)]\n"
                "[-s Strategy (first best)]\n"
                "[-h Grid step]\n"
                "[-t Estimator (mdca,ii)]\n"
                "[-r II estimation ball radius]\n"
                "[-n Threads number]\n"
                "[-k Thread elements]\n"
                "[-f Interactively select fixed pixels]\n"
                "[-F Fixed pixels mask image path]\n"
                "[-x Set endpoints orientation]\n";
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
        while( (opt=getopt(argc,argv,"m:M:j:i:S:s:e:a:h:t:r:n:k:fF:xD:E:V:"))!=-1 )
        {
            switch(opt)
            {
                case 'm':
                {
                    id.minGCLength = std::atoi(optarg);
                    id.automaticGCLength = false;
                    break;
                }
                case 'M':
                {
                    id.maxGCLength = std::atoi(optarg);
                    id.automaticGCLength = false;
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
                case 'S':
                {
                    if(strcmp(optarg,"triangle")==0) id.shape = Shape( ShapeType::Triangle);
                    else if(strcmp(optarg,"square")==0) id.shape = Shape( ShapeType::Square );
                    else if(strcmp(optarg,"pentagon")==0) id.shape = Shape( ShapeType::Pentagon);
                    else if(strcmp(optarg,"heptagon")==0) id.shape = Shape( ShapeType::Heptagon);
                    else if(strcmp(optarg,"ball")==0) id.shape = Shape( ShapeType::Ball);
                    else if(strcmp(optarg,"ellipse")==0) id.shape = Shape( ShapeType::Ellipse);
                    else if(strcmp(optarg,"flower")==0) id.shape = Shape( ShapeType::Flower);
                    else if(strcmp(optarg,"wave")==0) id.shape = Shape( ShapeType::Wave);
                    else if(strcmp(optarg,"bean")==0) id.shape = Shape( ShapeType::Bean);
                    else id.shape = Shape(ShapeType::UserDefined,optarg);
                    break;
                }
                case 's':
                {
                    if(strcmp(optarg,"first")==0) id.strategy = InputData::Strategy::First;
                    else if(strcmp(optarg,"best")==0) id.strategy = InputData::Strategy::Best;
                    else throw std::runtime_error("Unknown strategy");
                    break;
                }
                case 'e':
                {
                    if(strcmp(optarg,"isqc")==0) id.energyType = InputData::EnergyType::IntSquaredCurvature;
                    else if(strcmp(optarg,"elastica")==0) id.energyType = InputData::EnergyType::Elastica;
                    else if(strcmp(optarg,"selastica")==0) id.energyType = InputData::EnergyType::SimplifiedElastica;
                    else if(strcmp(optarg,"cselastica")==0) id.energyType = InputData::EnergyType::CorrectedSimplifiedElastica;
                    else throw std::runtime_error("Unknown energy");
                    break;
                }
                case 'a':
                {
                    id.lengthPenalization = std::atof(optarg);
                    break;
                }
                case 'h':
                {
                    id.gridStep = std::atof(optarg);
                    break;
                }
                case 't':
                {
                    if(strcmp(optarg,"mdca")==0) id.estimator = InputData::AlgorithmEstimator::MDCA;
                    else if(strcmp(optarg,"ii")==0) id.estimator = InputData::AlgorithmEstimator::II;
                    else throw std::runtime_error("Unknown estimator");
                    break;
                }
                case 'r':
                {
                    id.radius = std::atof(optarg);
                    break;
                }
                case 'n':
                {
                    id.nThreads = std::atoi(optarg);
                    break;
                }
                case 'k':
                {
                    id.threadSize = std::atoi(optarg);
                    break;
                }
                case 'f':
                {
                    id.initMode = InputData::InteractiveFixedPixels;
                    break;
                }
                case 'F':
                {
                    id.fixedPixelsMask = optarg;
                    id.initMode = InputData::FixedPixels;
                    break;
                }
                case 'x':
                {
                    id.initMode = InputData::InteractiveEndpoints;
                    break;
                }
                case 'D':
                {
                    id.nDilatedSets= std::atoi(optarg);
                    break;
                }
                case 'E':
                {
                    id.nErodedSets= std::atoi(optarg);
                    break;
                }
                case 'V':
                {
                    id.nCurveSegs= std::atoi(optarg);
                    break;
                }
                default:
                {
                    usage(argv);
                    exit(1);
                }
            }
        }

        id.outputFolder = argv[optind++];
        return id;
    }

}

std::ostream& operator<<(std::ostream& os,const InputData::AlgorithmEstimator& estimator)
{
    switch(estimator)
    {
        case InputData::AlgorithmEstimator::MDCA:
        {
            os << "MDCA";
            break;
        }
        case InputData::AlgorithmEstimator::II:
        {
            os << "II";
            break;
        }
        default:
        {
            os << "Not Recognized";
            break;
        }
    }

    return os;
}

std::ostream& operator<<(std::ostream& os,const InputData::Strategy& strategy)
{
    switch(strategy)
    {
        case InputData::Strategy::First:
        {
            os << "First";
            break;
        }
        case InputData::Strategy::Best:
        {
            os << "Best";
            break;
        }
        default:
        {
            os << "Not Recognized";
            break;
        }
    }

    return os;

}

std::ostream& operator<<(std::ostream& os,const InputData::InitializationMode & initMode)
{
    switch(initMode)
    {
        case InputData::InitializationMode::InteractiveEndpoints:
        {
            os << "InteractiveEndpoints";
            break;
        }
        case InputData::InitializationMode::FixedPixels:
        {
            os << "FixedPixels";
            break;
        }
        case InputData::InitializationMode::InteractiveFixedPixels:
        {
            os << "InteractiveFixedPixels";
            break;
        }
        default:
        {
            os << "Not Recognized";
            break;
        }
    }

    return os;

}

std::ostream& operator<<(std::ostream& os,const InputData::EnergyType & energyType)
{
    switch(energyType)
    {
        case InputData::EnergyType::Elastica:
        {
            os << "Elastica";
            break;
        }
        case InputData::EnergyType::CorrectedSimplifiedElastica:
        {
            os << "Corrected Simplified Elastica";
            break;
        }
        case InputData::EnergyType::SimplifiedElastica:
        {
            os << "Simplified Elastica";
            break;
        }
        case InputData::EnergyType::IntSquaredCurvature:
        {
            os << "Integrated Squared Curvature";
            break;
        }
        default:
        {
            os << "Not Recognized";
            break;
        }
    }

    return os;

}

std::ostream& operator<<(std::ostream& os,const InputData& id)
{
    os << "Shape: " << id.shape.name << "\n";
    os << "Grid Step: " << id.gridStep<< "\n";
    os << "Radius: " << id.radius<< "\n";
    os << "Iterations: " << id.iterations << "\n";
    os << "Estimator: " << id.estimator << "\n";
    os << "Strategy: " << id.strategy << "\n";
    os << "Min GC Length: " << id.minGCLength << "\n";
    os << "Max GC Length: " << id.maxGCLength << "\n";
    os << "Jonctions: " << id.joints<< "\n";
    os << "Length Penalization: " << id.lengthPenalization<< "\n";
    os << "Number of eroded sets: " << id.nErodedSets<< "\n";
    os << "Number of dilated sets: " << id.nDilatedSets<< "\n";
    os << "Number of curve segments: " << id.nCurveSegs<< "\n";
    os << "Automatic glued curve length: " << id.automaticGCLength<< "\n";
    os << "Initializationo mode: " << id.initMode<< "\n";
    os << "Energy type: " << id.energyType<< "\n";
    os << "Fixed pixel mask: " << id.fixedPixelsMask<< "\n";


    return os;
}
