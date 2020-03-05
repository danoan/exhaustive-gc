#ifndef EXHAUSTIVE_GC_STRING_H
#define EXHAUSTIVE_GC_STRING_H

#include <string>
#include <cmath>

namespace ExhaustiveGC
{
    namespace Utils
    {
        namespace String
        {
            std::string nDigitsString(int num, int digits);
            std::string fixedStrLength(int l,double v);
            std::string fixedStrLength(int l,std::string str);
        }
    }
}

#endif //EXHAUSTIVE_GC_STRING_H
