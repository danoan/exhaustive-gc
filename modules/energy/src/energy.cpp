#include "exhaustive-gc/energy/energy.h"

namespace ExhaustiveGC
{
    namespace Energy
    {
        void curvatureEstimation(CurvatureEstimationsVector& ev,
                                 const EnergyInput& energyInput,
                                 const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end)
        {
            using namespace GEOC::API::GridCurve::Curvature;
            switch(energyInput.estimator)
            {
                case EnergyInput::AlgorithmEstimator::MDCA:
                {
                    symmetricClosed<EstimationAlgorithms::ALG_MDCA> (KImage,
                                                                     begin,
                                                                     end,
                                                                     ev);
                    break;
                }
                case EnergyInput::AlgorithmEstimator::II:
                {
                    //double scaledRadius = energyInput.radius/energyInput.gridStep;
                    GEOC::Estimator::Standard::IICurvature<Curve::ConstIterator>(begin,
                                                                                 end,
                                                                                 ev,
                                                                                 energyInput.gridStep,
                                                                                 true,
                                                                                 energyInput.radius);

                    break;
                }

            }

        }

        void squaredCurvature(const EnergyInput& energyInput,
                              const KSpace& KImage,
                              Curve::ConstIterator begin,
                              Curve::ConstIterator end,
                              WeightMap& weightMap)
        {
            using namespace GEOC::API::GridCurve::Curvature;

            EstimationsVector ev;
            curvatureEstimation(ev,energyInput,KImage,begin,end);

            auto it = begin;
            int i=0;
            do
            {
                weightMap[*it]= pow(ev[i],2);
                ++it;
                ++i;
            }while(i<ev.size());
        }

        void intSquaredCurvature(const EnergyInput& energyInput,
                                 const KSpace& KImage,
                                 Curve::ConstIterator begin,
                                 Curve::ConstIterator end,
                                 WeightMap& weightMap)
        {
            using namespace GEOC::API::GridCurve;

            Curvature::EstimationsVector evCurv;
            curvatureEstimation(evCurv,energyInput,KImage,begin,end);

            Length::EstimationsVector evLength;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED>(KImage,begin,end,evLength);


            auto it = begin;
            int i=0;
            do
            {
                weightMap[*it]= pow(evCurv[i],2)*evLength[i];
                ++it;
                ++i;
            }while(i<evCurv.size());
        }


        void elastica(const EnergyInput& energyInput,
                      const KSpace& KImage,
                      Curve::ConstIterator begin,
                      Curve::ConstIterator end,
                      WeightMap& weightMap)
        {
            using namespace GEOC::API::GridCurve;

            Curvature::EstimationsVector evCurv;
            curvatureEstimation(evCurv,energyInput,KImage,begin,end);

            Length::EstimationsVector evLength;
            Length::mdssClosed<Length::EstimationAlgorithms::ALG_PROJECTED >(KImage,begin,end,evLength);


            auto it = begin;
            int i=0;
            do
            {
                weightMap[*it]= pow(evCurv[i],2)*evLength[i] + energyInput.lengthPenalization*evLength[i];
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
                    squaredCurvature(energyInput,KImage,begin,end,weightMap);
                    break;
                }
                case EnergyType::IntSquaredCurvature:
                {
                    intSquaredCurvature(energyInput,KImage,begin, end, weightMap);
                    break;
                }
                case EnergyType::Elastica:
                {
                    elastica(energyInput,KImage,begin, end, weightMap);
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

