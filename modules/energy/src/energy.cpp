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


        void elastica(const KSpace& KImage,
                      Curve::ConstIterator begin,
                      Curve::ConstIterator end,
                      WeightMap& weightMap,
                      double lengthPenalization)
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
                weightMap[*it]= pow(evCurv[i],2)*evLength[i] + lengthPenalization*evLength[i];
                ++it;
                ++i;
            }while(i<evCurv.size());
        }


        void computeWeightMap(const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              const EnergyInput energyInput,
                              WeightMap& weightMap)
        {
            switch(energyInput.type)
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
                case EnergyType::Elastica:
                {
                    elastica(KImage,begin, end, weightMap,energyInput.lengthPenalization);
                    break;
                }
            }

        }

        double energyValue(const Curve& curve, const std::map<KSpace::SCell,double>& weightMap)
        {
            auto it = curve.begin();
            double v=0;
            do
            {
                v+=weightMap.at(*it);
                ++it;
            }while(it!=curve.end());

            return v;
        }

        double energyValue(const Curve& curve, const KSpace& KImage, const EnergyInput energyInput)
        {
            WeightMap weightMap;
            computeWeightMap(KImage,curve.begin(),curve.end(),energyInput,weightMap);

            return energyValue(curve,weightMap);
        }

        double energyValue(const DigitalSet& ds, const EnergyInput energyInput)
        {
            const DGtal::Z2i::Domain& domain = ds.domain();
            KSpace kspace;
            kspace.init(domain.lowerBound(),domain.upperBound(),true);

            Curve curve;
            DIPaCUS::Misc::computeBoundaryCurve(curve,ds);

            return energyValue(curve,kspace,energyInput);
        }
    }
}

