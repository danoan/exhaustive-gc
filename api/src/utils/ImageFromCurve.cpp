#include "exhaustive-gc/api/utils/ImageFromCurve.h"

using namespace ExhaustiveGC::API;

ImageFromCurve::ImageFromCurve(Image2D &image,
                               const Domain &domain,
                               const Curve &curve)

{
    Curve::InnerPointsRange innerPixelsRange = curve.getInnerPointsRange();
    Curve::OuterPointsRange outerPixelsRange = curve.getOuterPointsRange();

    std::stack<Point> toExplorePoints;
    Point filter[4] = {Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)};
    DigitalSet dsOut(domain);
    DigitalSet dsForbidden(domain);
    {
        Curve::InnerPointsRange::ConstIterator it = innerPixelsRange.begin();

        do {
            dsForbidden.insert(*it);
            dsOut.insert(*it);
            ++it;
        } while (it != innerPixelsRange.end());
    }

    {
        Curve::OuterPointsRange::ConstIterator it = outerPixelsRange.begin();

        do {
            dsForbidden.insert(*it);
            ++it;
        } while (it != outerPixelsRange.end());
    }


    for (auto it = dsOut.begin(); it != dsOut.end(); ++it)
    {
        toExplorePoints.push(*it);
        for(int i=0;i<4;++i) toExplorePoints.push(*it + filter[i]);
    }

    while(!toExplorePoints.empty())
    {
        Point p = toExplorePoints.top(); toExplorePoints.pop();

        if(p[0]<domain.lowerBound()[0] || p[1]<domain.lowerBound()[1]) continue;
        if(p[0]>domain.upperBound()[0] || p[1]>domain.upperBound()[1]) continue;
        if(dsOut(p)) continue;
        if(dsForbidden(p)) continue;

        dsOut.insert(p);
        for(int i=0;i<4;++i) toExplorePoints.push(p+filter[i]);

    }

    for(auto it=image.domain().begin();it!=image.domain().end();++it)
    {
        image.setValue(*it,0);
    }

    for(auto it=dsOut.begin();it!=dsOut.end();++it)
    {
        image.setValue(*it,255);
    }
}