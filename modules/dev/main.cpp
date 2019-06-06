#include <iostream>

#include <DGtal/helpers/StdDefs.h>

#include <DIPaCUS/base/Shapes.h>
#include <DIPaCUS/derivates/Misc.h>

using namespace DGtal::Z2i;

struct Node
{
    Node(){};
    Node(const Point &p, int degree) : p(p), degree(degree) {}

    Point p;
    int degree;
};

namespace std
{
    template<>
    struct hash<Node>
    {
        size_t operator()(const Node& node) const
        {
            return (node.p[0]*13 + node.p[1]*51)%227;
        }
    };
}

typedef std::map<Point,Node> Graph;
typedef std::set<Cell> LinelSet;
typedef std::set<Cell> PointelSet;

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
    for(auto it=g.begin();it!=g.end();++it)
    {
        const Node& n = it->second;
        std::cout << "P: " << n.p << "\td: " << n.degree << std::endl;
    }

    return os;
}

LinelSet innerLinels(const Curve& curve)
{
    KSpace kspace;
    DIPaCUS::Properties::BoundingBox bb;
    DIPaCUS::Properties::curveBoundingBox(bb,curve.begin(),curve.end());
    kspace.init(bb.lb,bb.ub,true);

    LinelSet ls;
    auto innerRange = curve.getInnerPointsRange();
    for(auto it=innerRange.begin();it!=innerRange.end();++it)
    {
        Cell pixel = kspace.uSpel(*it);

        auto linels = kspace.uLowerIncident(pixel);
        assert(linels.size()==4);
        ls.insert(linels.begin(),linels.end());
    }

    return ls;
}

bool degreeEdgesInvariant(const Curve& curve, const Graph& graph)
{
    LinelSet ls = innerLinels(curve);
    int numEdges=ls.size();
    int sumD=0;
    for(auto it=graph.begin();it!=graph.end();++it)
    {
        const Node& n= it->second;
        sumD+=n.degree;
    }

    return numEdges*2==sumD;
}




int main()
{
    DigitalSet square = DIPaCUS::Shapes::flower();
    Curve curve;
    DIPaCUS::Misc::computeBoundaryCurve(curve,square);

    const Domain& domain = square.domain();

    KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    Graph graph;
    std::set<Point> pointelSet;

    LinelSet linels = innerLinels(curve);

    for(auto itL=linels.begin();itL!=linels.end();++itL)
    {
        auto pointels = kspace.uLowerIncident(*itL);
        assert(pointels.size()==2);
        for(auto itP=pointels.begin();itP!=pointels.end();++itP)
        {
            pointelSet.insert(itP->preCell().coordinates);
        }
    }


    Point neigh[4] = {Point(2,0),Point(-2,0), Point(0,-2), Point(0,2)};
    for(auto it=pointelSet.begin();it!=pointelSet.end();++it)
    {
        int d = 0;
        for(int i=0;i<4;++i)
        {
            Point np = *it + neigh[i];
            if(pointelSet.find(np)!=pointelSet.end()) ++d;
        }

        graph[*it] = Node(*it,d);
    }

    assert(degreeEdgesInvariant(curve,graph));
    std::cout << graph << std::endl;

    return 0;
}