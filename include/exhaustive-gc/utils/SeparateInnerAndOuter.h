#ifndef EXHAUSTIVE_GC_SEPARATEINNERANDOUTER_H
#define EXHAUSTIVE_GC_SEPARATEINNERANDOUTER_H

#include <DGtal/helpers/StdDefs.h>
#include <exhaustive-gc/model/GCInitData.h>
#include "gcurve/GluedCurveRange.h"

namespace ExhaustiveGC
{

    class SeparateInnerAndOuter
    {
    public:
        typedef DGtal::Z2i::Curve Curve;
        typedef DGtal::Z2i::KSpace KSpace;

        typedef GCurve::GluedCurveRange GluedCurveRange;
        typedef GluedCurveRange::GluedCurveSeedIterator GluedCurveSeedIterator;
        typedef GluedCurveRange::GluedCurveLinkIterator GluedCurveLinkIterator;

        typedef std::vector<GCInitData> SeedVector;

    public:
        SeparateInnerAndOuter(Curve& innerCurve,
                              Curve& outerCurve):KImage(KImage),
                                                 innerCurve(innerCurve),
                                                 outerCurve(outerCurve){}

        void operator()(SeedVector& fromInnerSeeds,
                        SeedVector& fromOuterSeeds)
        {
            GluedCurveRange csr(KImage,
                                5,
                                innerCurve.begin(),
                                innerCurve.end(),
                                outerCurve.begin(),
                                outerCurve.end());

            innerAndOuterList(fromInnerSeeds,
                              fromOuterSeeds,
                              csr.beginSeed(),
                              csr.endSeed(),
                              csr.beginLink());
        }

    private:
        void innerAndOuterList(SeedVector& fromInnerSCells,
                               SeedVector& fromOuterSCells,
                               GluedCurveSeedIterator begin,
                               GluedCurveSeedIterator end,
                               GluedCurveLinkIterator beginLink)
        {
            GluedCurveLinkIterator linkIT = beginLink;
            for(GluedCurveSeedIterator it = begin;it!=end;++it)
            {
                GCInitData gcID;

                gcID.seed = *it;
                gcID.connectors.insert(gcID.connectors.begin(),beginLink,beginLink+it->numLinkLinels);
                switch( it->linkType )
                {
                    case GluedCurve::LinkType::INTERN_TO_EXTERN:
                        fromInnerSCells.push_back(gcID);
                        break;
                    case GluedCurve::LinkType::EXTERN_TO_INTERN:
                        fromOuterSCells.push_back(gcID);
                        break;
                }
            }
        }

    public:
        KSpace& KImage;
        DGtal::Z2i::Curve& innerCurve;
        DGtal::Z2i::Curve& outerCurve;
    };
}

#endif //EXHAUSTIVE_GC_SEPARATEINNERANDOUTER_H
