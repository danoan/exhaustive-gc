#include "utils.h"

template<class TPointIterator>
LinelSet getLinels(const DigitalSet& ds, TPointIterator begin, TPointIterator end)
{
    LinelSet ls;

    const Domain& domain = ds.domain();
    DGtal::Z2i::KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    Curve curve;
    DIPaCUS::Misc::computeBoundaryCurve(curve,ds);
    for(auto l:curve)
    {
        auto incPixels = kspace.sUpperIncident(l);
        bool found=false;
        for(auto ip:incPixels)
        {
            for(auto it=begin;it!=end;++it)
            {
                Point p = *it;
                if( p==kspace.sCoords(ip))
                {
                    ls.insert(l);
                    found=true;
                    break;
                }
            }
            if(found) break;
        }
    }

    return ls;
}