#ifndef EXHAUSTIVE_GC_IMARKEDMAPCHECKER_H
#define EXHAUSTIVE_GC_IMARKEDMAPCHECKER_H

#include <unordered_map>
#include "exhaustive-gc/core/check-elem/CCheckableElement.h"

namespace ExhaustiveGC
{
    template<typename CheckableElement>
    class IMarkedMapChecker
    {
    public:
        BOOST_CONCEPT_ASSERT( (CCheckableElement<CheckableElement>) );

        typedef typename CheckableElement::CheckedType CheckedType;
        typedef typename CheckableElement::MarkedType MarkedType;
        typedef typename CheckableElement::ComparisonClass ComparisonClass;

    public:
        virtual bool operator()(const CheckableElement& e)const=0;
        virtual void mark(const CheckableElement& e)=0;
        virtual void unmark(const CheckableElement& e)=0;

        virtual IMarkedMapChecker<CheckableElement>* reproduce()=0;
        virtual ~IMarkedMapChecker(){};

    protected:
        std::unordered_map<MarkedType,
                bool,
                std::hash<MarkedType>,
                ComparisonClass> _markMap;
    };
}

#endif //EXHAUSTIVE_GC_IMARKEDMAPCHECKER_H
