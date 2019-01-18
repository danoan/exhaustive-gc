#include "exhaustive-gc/utils/SeparateInnerAndOuter.h"

using namespace ExhaustiveGC;

void SeparateInnerAndOuter::operator()(SeedVector& fromInnerSeeds,
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


void SeparateInnerAndOuter::innerAndOuterList(SeedVector& fromInnerSCells,
                                              SeedVector& fromOuterSCells,
                                              GluedCurveSeedIterator begin,
                                              GluedCurveSeedIterator end,
                                              GluedCurveLinkIterator beginLink)
{
    GluedCurveLinkIterator linkIT = beginLink;
    for(GluedCurveSeedIterator it = begin;it!=end;++it)
    {
        GCInitData gcID(*it);

        gcID.connectors.insert(gcID.connectors.begin(),linkIT,linkIT+it->numLinkLinels);
        linkIT=linkIT+it->numLinkLinels;
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