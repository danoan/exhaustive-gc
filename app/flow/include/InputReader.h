#ifndef EXHAUSTIVE_GC_INPUTREADER_H
#define EXHAUSTIVE_GC_INPUTREADER_H

#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>

#include "InputData.h"

namespace InputReader
{
    void usage(char* argv[]);
    InputData readInput(int argc, char* argv[]);
}


#endif //EXHAUSTIVE_GC_INPUTREADER_H

