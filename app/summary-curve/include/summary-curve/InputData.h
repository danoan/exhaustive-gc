#ifndef EXHAUSTIVE_GC_SUMMARY_CURVE_INPUTDATA_H
#define EXHAUSTIVE_GC_SUMMARY_CURVE_INPUTDATA_H

#include <vector>

#include "types.h"

namespace SummaryCurve
{
    struct InputData
    {
        InputData()
        {
            jumpStep=5;
            pixelMaskPath="";
            dirsMaskPath="";
            flowImagesFolderPath="";
            outputFilePath="";
            iot=ImageOutputType::SVG;
        }

        int jumpStep;
        std::string pixelMaskPath;
        std::string dirsMaskPath;

        ImageOutputType iot;
        std::string flowImagesFolderPath;
        std::string outputFilePath;
    };
}

#endif //EXHAUSTIVE_GC_SUMMARY_CURVE_INPUTDATA_H
