#include "exhaustive-gc/utils/timer.h"

namespace ExhaustiveGC
{
    namespace Utils
    {
        namespace Timer
        {
            void start()
            {
                startTime = boost::posix_time::microsec_clock::local_time();
            }

            void end(std::ostream& os)
            {
                endTime = boost::posix_time::microsec_clock::local_time();

                boost::posix_time::time_duration diff = endTime - startTime;
                os << diff.total_seconds() << "s " << diff.total_milliseconds() << "ms " << diff.total_microseconds() << "us \n";
            }
        }
    }
}