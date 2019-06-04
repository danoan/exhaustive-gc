#ifndef EXHAUSTIVE_GC_TIMER_H
#define EXHAUSTIVE_GC_TIMER_H

#include <boost/date_time.hpp>
#include <ostream>

namespace ExhaustiveGC
{
    namespace Utils
    {
        namespace Timer
        {
            boost::posix_time::ptime startTime;
            boost::posix_time::ptime endTime;

            void start();
            void end(std::ostream& os);
        }
    }
}

#endif //EXHAUSTIVE_GC_TIMER_H
