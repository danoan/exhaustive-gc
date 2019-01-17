#ifndef EXHAUSTIVE_GC_CHECKABLESEEDPAIR_H
#define EXHAUSTIVE_GC_CHECKABLESEEDPAIR_H

#include "lazy-comb/concepts/CCheckableElement.h"
#include "gcurve/GluedCurveRange.h"

#include <DGtal/helpers/StdDefs.h>
#include <exhaustive-gc/model/GCInitData.h>

namespace ExhaustiveGC
    {
    class CheckableSeedPair
    {
    public:
        typedef std::pair<GCInitData,GCInitData> CheckedType;
        typedef SCell MarkedType;

        typedef
        class UnsignedSCellComparison{
        public:
            bool operator()(const MarkedType& s1, const MarkedType& s2) const{
                return s1.preCell().coordinates == s2.preCell().coordinates;
            }
        } ComparisonClass;

    public:
        CheckableSeedPair(){}
        CheckableSeedPair(CheckedType data):_data(data){}

        const CheckedType& data() const  { return _data; }

    private:
        CheckedType _data;
    };
}


namespace std
{
    template<>
    struct hash<ExhaustiveGC::CheckableSeedPair::MarkedType>
    {
        std::size_t operator()(const ExhaustiveGC::CheckableSeedPair::MarkedType& k) const
        {
            return ( ( hash<int>()( k.preCell().coordinates[0] )
                       ^( hash<int>()( k.preCell().coordinates[1] ) << 1 ) >> 1 )
            );
        }
    };
}


#endif //EXHAUSTIVE_GC_CHECKABLESEEDPAIR_H
