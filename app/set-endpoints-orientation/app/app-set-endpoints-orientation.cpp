#include <boost/filesystem/operations.hpp>
#include "set-endpoints-orientation/gui.h"

int main(int argc,char* argv[])
{
    if(argc<2)
    {
        std::cerr << "Usage: OutputFilePath" << std::endl;
        exit(1);
    }

    std::string outputFilePath = argv[1];
    boost::filesystem::path p(outputFilePath);
    boost::filesystem::create_directories(p.remove_filename());

    SetEndpointsOrientation::gui(outputFilePath,std::cout);


}