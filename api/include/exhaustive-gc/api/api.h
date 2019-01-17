#include <DGtal/kernel/PointVector.h>
#include "DIPaCUS/base/Shapes.h"
#include <exhaustive-gc/checker/GluedIntersectionChecker.h>
#include <exhaustive-gc/checker/MinimumDistanceChecker.h>
#include <exhaustive-gc/api/utils/FilterSeedPairs.h>
#include <exhaustive-gc/control/CurveCandidatesGenerator.h>
#include <exhaustive-gc/api/utils/InitImage.h>
#include <exhaustive-gc/api/utils/ImageFromCurve.h>
#include "exhaustive-gc/api/utils/GenerateSeedPairs.h"


namespace ExhaustiveGC
{
    namespace API
    {
        typedef DGtal::Z2i::KSpace KSpace;
        typedef DGtal::Z2i::Curve Curve;

        void checkAllPossibilities(KSpace& KImage,
                                   Curve& innerCurve,
                                   Curve& outerCurve,
                                   Curve& minCurve,
                                   int itnum)
        {

            GenerateSeedPairs::SeedPairsList spl;
            GenerateSeedPairs(spl,KImage,innerCurve,outerCurve);

            FilterSeedPairs(spl,4,10);

            typedef GenerateSeedPairs::SeedPair SeedPair;
            typedef std::vector< CheckableSeedPair > CheckableSeedPairVector;
            CheckableSeedPairVector cspv;

            std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp){cspv.push_back( CheckableSeedPair(sp) );});


            CurveCandidatesGenerator<1> CE;
            CE.registerChecker( new GluedIntersectionChecker() );
            CE.registerChecker( new MinimumDistanceChecker(KImage) );



            double currLength=0;
            //TODO::Better use a global estimator
            {
                using namespace GEOC::API::GridCurve::Length;
                EstimationsVector localLengthEstimations;
                lmdssClosed<EstimationAlgorithms::ALG_PROJECTED>(KImage,innerCurve.begin(),innerCurve.end(),localLengthEstimations,1.0);

                for(int i=0;i<localLengthEstimations.size();++i)
                {
                    currLength+=localLengthEstimations[i];
                }
            }

            CheckableSeedPair bestCombination[1];

            CE(minCurve,
               cspv,
               KImage,
               bestCombination,
               "../output/combinations/LFLIM" + std::to_string(itnum),
               currLength);

        }


        void run()
        {
            DigitalSet dsSquare = DIPaCUS::Shapes::square();
            InitImage::Image2D image(dsSquare.domain());
            DIPaCUS::Representation::digitalSetToImage(image,dsSquare);

            double l1,l2;
            for(int i=0;i<1;++i)
            {
                Curve minCurve;

                Curve innerCurve,outerCurve;
                KSpace KImage = InitImage::eval(innerCurve,outerCurve,image);

                checkAllPossibilities(KImage,
                                      innerCurve,
                                      outerCurve,
                                      minCurve,
                                      i );

                ImageFromCurve(image,image.domain(),minCurve);
            }
        }


    }
}

