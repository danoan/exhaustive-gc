#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/derivates/Misc.h>

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/io/boards/Board2D.h>
#include <boost/filesystem/operations.hpp>

#include "summary-curve/InputData.h"
#include "summary-curve/InputReader.h"

#include "summary-curve/utils.h"
#include "summary-curve/OneImageFlow.h"

using namespace DGtal::Z2i;
using namespace SummaryCurve;

typedef std::set<SCell> LinelSet;

int main(int argc, char* argv[])
{
    InputData id = InputReader::readInput(argc,argv);


    boost::filesystem::path srcImagePath( id.flowImagesFolderPath );
    std::string name = srcImagePath.stem().string();

    SummaryCurve::OneImageFlow oif(srcImagePath.string(),id.outputFilePath,id.pixelMaskPath,id.dirsMaskPath,id.jumpStep,id.iot);

    return 0;
}