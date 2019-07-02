#ifndef EXHAUSTIVE_GC_CCGDATA_H
#define EXHAUSTIVE_GC_CCGDATA_H

#include <lazy-comb/interface/IMarkedMapChecker.h>
#include <lazy-comb/LazyCombinations.h>

#include "exhaustive-gc/core/check-elem/CheckableSeedPair.h"
#include "exhaustive-gc/core/model/Types.h"
#include "exhaustive-gc/energy/EnergyInput.h"
#include "exhaustive-gc/energy/energy.h"
#include "exhaustive-gc/core/model/Types.h"

namespace ExhaustiveGC
{
    namespace Core
    {
        class CCGData
        {
        public:
            typedef DGtal::Z2i::Curve Curve;
            typedef DGtal::Z2i::KSpace KSpace;
            typedef DGtal::Z2i::DigitalSet DigitalSet;

            typedef LazyCombinator::IMarkedMapChecker<CheckableSeedPair> Checker;
            typedef std::vector<CheckableSeedPair> CheckableSeedVector;

            typedef LazyCombinator::LazyCombinations <CheckableSeedVector> MyLazyCombinations;

            typedef Core::Strategy Strategy;

        public:
            CCGData(unsigned int maxPairs,
                    Strategy strategy,
                    bool preserveConnectedeness,
                    const DigitalSet& ds,
                    const CheckableSeedVector &csVector,
                    const Energy::EnergyInput& energyInput,
                    const KSpace &KImage):maxPairs(maxPairs),
                                          strategy(strategy),
                                          ds(ds),
                                          csVector(csVector),
                                          energyInput(energyInput),
                                          KImage(KImage),
                                          preserveConnectedeness(preserveConnectedeness){}

            ~CCGData(){ for(auto itc=checkers.begin();itc!=checkers.end();++itc) delete *itc; }

            void registerChecker(Checker* c)
            {
                checkers.push_back( c );
            }
        public:
            DigitalSet ds;
            const Energy::EnergyInput& energyInput;
            const KSpace& KImage;
            const CheckableSeedVector& csVector;

            unsigned int maxPairs;
            bool preserveConnectedeness;

            Strategy strategy;
            std::vector< Checker* > checkers;
        };
    }
}

#endif //EXHAUSTIVE_GC_CCGDATA_H
