#ifndef EXHAUSTIVE_GC_CONTAINERCOMBINATOR_H
#define EXHAUSTIVE_GC_CONTAINERCOMBINATOR_H

#include <utility>
#include <vector>

template<typename TContainer, typename IteratorT1, typename IteratorT2>
class ContainerCombinator
{
public:
    typedef typename IteratorT1::value_type T1;
    typedef typename IteratorT2::value_type T2;


    typedef std::pair<T1,T2> PairType;
    typedef std::back_insert_iterator< TContainer > OutputIterator;

public:
    ContainerCombinator(IteratorT1 b1,
                        IteratorT1 e1,
                        IteratorT2 b2,
                        IteratorT2 e2,
                        OutputIterator oit)
    {
        for(IteratorT1 it1=b1;it1!=e1;++it1)
        {
            for(IteratorT2 it2=b2;it2!=e2;++it2)
            {
                auto next = it1->inCirculatorEnd;
                ++next;
                if( next == it2->outCirculatorBegin )
                {
                    oit = PairType(*it1,*it2);
                }
            }
        }
    }
};


#endif //EXHAUSTIVE_GC_CONTAINERCOMBINATOR_H
