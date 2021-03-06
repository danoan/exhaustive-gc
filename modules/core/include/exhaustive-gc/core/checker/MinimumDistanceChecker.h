#ifndef EXHAUSTIVE_GC_MINIMUMDISTANCECHECKER_H
#define EXHAUSTIVE_GC_MINIMUMDISTANCECHECKER_H

#include "exhaustive-gc/core/checker/IMarkedMapChecker.h"
#include "exhaustive-gc/core/check-elem/CheckableSeedPair.h"

namespace ExhaustiveGC
{
    class MinimumDistanceChecker: public IMarkedMapChecker<CheckableSeedPair>
    {
    public:
        typedef DGtal::Z2i::Curve::ConstIterator SCellIterator;
        typedef DGtal::Circulator<SCellIterator> SCellCirculator;

        typedef DGtal::Z2i::KSpace KSpace;

    private:
        bool validConnector(const KSpace::SCell& c1) const
        {
            KSpace::SCell c1s = KImage.sIndirectIncident(c1,*KImage.sDirs(c1));
            KSpace::SCell c1t = KImage.sDirectIncident(c1,*KImage.sDirs(c1));

            if( this->_markMap.at( c1s ) ) return false;
            if( this->_markMap.at( c1t ) ) return false;

            return true;
        }

        void markConnector(const KSpace::SCell& c1,bool mark)
        {
            KSpace::SCell c1s = KImage.sIndirectIncident(c1,*KImage.sDirs(c1));
            KSpace::SCell c1t = KImage.sDirectIncident(c1,*KImage.sDirs(c1));

            this->_markMap[ c1s ] = mark;
            this->_markMap[ c1t ] = mark;
        }


    public:
        MinimumDistanceChecker(const KSpace& KImage):KImage(KImage){}
        IMarkedMapChecker<CheckableSeedPair>* reproduce()
        {
            return new MinimumDistanceChecker(KImage);
        }

        ~MinimumDistanceChecker(){}

        bool operator()(const CheckableSeedPair& sp) const
        {
            if( !validConnector( sp.data().first.linkLinels.at(0) ) ) return false;
            if( !validConnector( sp.data().second.linkLinels.at(0) ) ) return false;

            return true;
        }

        void mark(const CheckableSeedPair& sp)
        {
            markConnector( sp.data().first.linkLinels.at(0),true);
            markConnector( sp.data().second.linkLinels.at(0),true);
        }

        void unmark(const CheckableSeedPair& sp)
        {
            markConnector( sp.data().first.linkLinels.at(0),false);
            markConnector( sp.data().second.linkLinels.at(0),false);
        }

        const KSpace& KImage;

    };
}

#endif //EXHAUSTIVE_GC_MINIMUMDISTANCECHECKER_H
