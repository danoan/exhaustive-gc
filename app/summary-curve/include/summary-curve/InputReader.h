#ifndef EXHAUSTIVE_GC_SUMMARY_CURVE_INPUTREADER_H
#define EXHAUSTIVE_GC_SUMMARY_CURVE_INPUTREADER_H

#include <unistd.h>
#include <iostream>
#include <string>
#include <boost/filesystem/operations.hpp>

#include "InputData.h"

namespace SummaryCurve
{
    namespace InputReader
    {
        void usage(int argc,char* argv[]);
        InputData readInput(int argc,char* argv[]);
    }
}

#endif //EXHAUSTIVE_GC_INPUTREADER_H
