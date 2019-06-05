#include "exhaustive-gc/energy/energy.h"

namespace ExhaustiveGC
{
    namespace Energy
    {
        void squaredCurvature(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              WeightMap& weightMap)
        {
            using namespace GEOC::API::GridCurve::Curvature;

            EstimationsVector ev;
            symmetricClosed<EstimationAlgorithms::ALG_MDCA> (KImage,
                                                             begin,
                                                             end,
                                                             ev);


            auto it = begin;
            int i=0;
            do
            {
                weightMap[*it]= pow(ev[i],2);
                ++it;
                ++i;
            }while(i<ev.size());
        }

        void intSquaredCurvature(const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end,
                                 WeightMap& weightMap)
        {
            using namespace GEOC::API::GridCurve;

            Curvature::EstimationsVector evCurv;
            Curvature::symmetricClosed<Curvature::EstimationAlgorithms::ALG_MDCA> (KImage,
                                                                                   begin,
                                                                                   end,
                                                                                   evCurv);

            Length::EstimationsVector evLength;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED >(KImage,begin,end,evLength);


            auto it = begin;
            int i=0;
            do
            {
                weightMap[*it]= pow(evCurv[i],2)*evLength[i];
                ++it;
                ++i;
            }while(i<evCurv.size());
        }

        void computeWeightMap(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              EnergyType energy,
                              WeightMap& weightMap)
        {
            switch(energy)
            {
                case EnergyType::SquaredCurvature:
                {
                    squaredCurvature(KImage,begin,end,weightMap);
                    break;
                }
                case EnergyType::IntSquaredCurvature:
                {
                    intSquaredCurvature(KImage,begin, end, weightMap);
                    break;
                }
            }

        }

        double energyValue(Curve& curve, std::map<KSpace::SCell,double>& weightMap)
        {
            auto it = curve.begin();
            double v=0;
            do
            {
                v+=weightMap[*it];
                ++it;
            }while(it!=curve.end());

            return v;
        }

        double energyValue(Curve& curve, const KSpace& KImage, EnergyType energy)
        {
            WeightMap weightMap;
            computeWeightMap(KImage,curve.begin(),curve.end(),energy,weightMap);
            auto it = curve.begin();
            double v=0;
            do
            {
                v+=weightMap[*it];
                ++it;
            }while(it!=curve.end());

            return v;
        }
    }
}

