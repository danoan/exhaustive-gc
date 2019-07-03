#ifndef EXHAUSTIVE_GC_GLUEDINTERSECTIONCHECKER_H
#define EXHAUSTIVE_GC_GLUEDINTERSECTIONCHECKER_H

#include "lazy-comb/interface/IMarkedMapChecker.h"
#include "exhaustive-gc/core/check-elem/CheckableSeedPair.h"

namespace ExhaustiveGC
{
    class GluedIntersectionChecker: public LazyCombinator::IMarkedMapChecker<CheckableSeedPair>
    {
    public:
        typedef DGtal::Z2i::Curve::ConstIterator SCellIterator;
        typedef DGtal::Circulator<SCellIterator> SCellCirculator;

    public:
        IMarkedMapChecker<CheckableSeedPair>* reproduce()
        {
            return new GluedIntersectionChecker();
        }

        ~GluedIntersectionChecker(){}

        bool operator()(const CheckableSeedPair& sp) const
        {
            SCellCirculator extCircBegin = sp.data().first.inCirculatorBegin;; //First -> intToExt
            SCellCirculator extCircEnd = sp.data().second.outCirculatorBegin; //Second -> extToInt

            SCellCirculator it = extCircBegin;
            do
            {
                if( this->_markMap.at(*it) ) return false;
                ++it;
            }while(it!=extCircEnd);

            if( this->_markMap.at(*it) ) return false;
            else return true;
        }

        void mark(const CheckableSeedPair& sp)
        {
            SCellCirculator extCircBegin = sp.data().first.inCirculatorBegin; //First -> intToExt
            SCellCirculator extCircEnd = sp.data().second.outCirculatorBegin; //Second -> extToInt

            SCellCirculator it = extCircBegin;
            do
            {
                this->_markMap[*it] = true;
                ++it;
            }while(it!=extCircEnd);

            this->_markMap[*it] = true;
        }

        void unmark(const CheckableSeedPair& sp)
        {
            SCellCirculator extCircBegin = sp.data().first.inCirculatorBegin; //First -> intToExt
            SCellCirculator extCircEnd = sp.data().second.outCirculatorBegin; //Second -> extToInt

            SCellCirculator it = extCircBegin;
            do
            {
                this->_markMap[*it] = false;
                ++it;
            }while(it!=extCircEnd);

            this->_markMap[*it] = false;
        }

    };
}

#endif //EXHAUSTIVE_GC_GLUEDINTERSECTIONCHECKER_H
