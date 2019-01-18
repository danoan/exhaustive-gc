#include <DGtal/kernel/PointVector.h>
#include <DGtal/io/boards/Board2D.h>

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
        typedef DGtal::Z2i::DigitalSet DigitalSet;
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
            std::cout << spl.size() << std::endl;

            FilterSeedPairs(spl,10,20);
            std::cout << spl.size() << std::endl;

            typedef GenerateSeedPairs::SeedPair SeedPair;
            typedef std::vector< CheckableSeedPair > CheckableSeedPairVector;
            CheckableSeedPairVector cspv;

            std::for_each(spl.begin(),spl.end(),[&cspv](SeedPair sp) mutable {cspv.push_back( CheckableSeedPair(sp) );});


            CurveCandidatesGenerator<1> CE;
            CE.registerChecker( new GluedIntersectionChecker() );
            CE.registerChecker( new MinimumDistanceChecker(KImage) );


            CheckableSeedPair bestCombination[1];

            CE(minCurve,
               cspv,
               KImage,
               bestCombination,
               "../output/combinations/LFLIM" + std::to_string(itnum));

        }


        void run()
        {
            DGtal::Board2D board;
            DigitalSet dsSquare = DIPaCUS::Shapes::square();

            double l1,l2;
            for(int i=0;i<1;++i)
            {
                Curve minCurve;

                Curve innerCurve,outerCurve;
                KSpace KImage = InitImage::eval(innerCurve,outerCurve,dsSquare);

                checkAllPossibilities(KImage,
                                      innerCurve,
                                      outerCurve,
                                      minCurve,
                                      i );

                dsSquare.clear();
                DIPaCUS::Misc::CompactSetFromClosedCurve<Curve::ConstIterator>(dsSquare,minCurve.begin(),minCurve.end());

                board << dsSquare;
                board.saveEPS("../output/combinations/LFLIM/square.eps");
            }
        }


    }
}

