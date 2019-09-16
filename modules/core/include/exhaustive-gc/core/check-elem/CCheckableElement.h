#ifndef EXHAUSTIVE_GC_CCHECKABLEELEMENT_H
#define EXHAUSTIVE_GC_CCHECKABLEELEMENT_H

#include <boost/concept/assert.hpp>

namespace ExhaustiveGC
{
    template<typename T>
    class CCheckableElement
    {
        typedef typename T::CheckedType CheckedType;
        typedef typename T::MarkedType MarkedType;
        typedef typename T::ComparisonClass ComparisonClass;
    };
}


#endif //EXHAUSTIVE_GC_CCHECKABLEELEMENT_H
