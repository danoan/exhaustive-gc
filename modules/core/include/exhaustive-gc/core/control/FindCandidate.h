#ifndef EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
#define EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H

#include <DGtal/helpers/StdDefs.h>

#include "magLac/core/base/Range.hpp"
#include "magLac/core/single/Combinator.hpp"

#include "magLac/core/multithread/Trigger.h"
#include "magLac/core/multithread/ThreadInput.h"
#include "magLac/core/multithread/ThreadControl.h"

#include "exhaustive-gc/core/model/CCGData.h"
#include "exhaustive-gc/core/control/CurveFromJoints.h"



namespace ExhaustiveGC
{
    namespace Core
    {
        namespace FindCandidate
        {
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            typedef CCGData::CheckableSeedVector CheckableSeedVector;
            typedef CheckableSeedVector::value_type ContainerValueType;

            struct Data
            {
                Data(){restart();}

                void restart()
                {
                    energyValue=1e20;
                    foundCandidate=false;
                }

                double energyValue;
                bool foundCandidate;
                Curve curve;
            };

            template<class TCombinator>
            using ThreadInput = magLac::Core::MultiThread::ThreadInput<TCombinator,Data,CCGData>;

            template<class TThreadInput>
            using ThreadTrigger = magLac::Core::MultiThread::Trigger< TThreadInput >;

            typedef magLac::Core::MultiThread::ThreadControl ThreadControl;

            typedef std::map<KSpace::SCell, double> WeightMap;


            void initCheckers(const CCGData& ccgData);

            bool findCandidate(DGtal::Z2i::Curve& minCurve,
                               const double energyValue,
                               const CCGData& ccgData,
                               int nThread,
                               int threadSize);

            double computeEnergyValue(const DigitalSet& ds,
                                      const Curve& curve,
                                      const KSpace& KImage,
                                      const Energy::EnergyInput& energyInput);



        }

    }
}


#endif //EXHAUSTIVE_GC_COMBINATIONSEVALUATOR_H
