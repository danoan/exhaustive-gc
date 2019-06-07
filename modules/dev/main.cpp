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
typedef std::list<SCell> PointelList;
typedef std::map<Point,std::set<KSpace::SCell> > ActiveLinels;

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


struct Edge
{
    enum EdgeOrientation{PosVertical,NegVertical,PosHorizontal,NegHorizontal};

    Edge(const KSpace::SCell& linel,
         const EdgeOrientation orientation,
         const KSpace::SCell& face,
         const KSpace::SCell& source,
         const KSpace::SCell& target):linel(linel),
                                      orientation(orientation),
                                      face(face),
                                      source(source),
                                      target(target){}

    inline Point kpSource(){ return source.preCell().coordinates; }
    inline Point kpTarget(){ return target.preCell().coordinates; }
    inline Point kpLinel(){ return linel.preCell().coordinates; }
    inline Point kpFace(){ return face.preCell().coordinates; }

    KSpace::SCell linel;
    KSpace::SCell face;
    KSpace::SCell source,target;

    EdgeOrientation orientation;

};

void insertEdges(const Curve& curve, const KSpace& kspace, std::stack<Edge>& edges)
{
    for(auto it=curve.rbegin();it!=curve.rend();++it)
    {
        KSpace::SCell source = kspace.sIndirectIncident(*it,*kspace.sDirs(*it));
        KSpace::SCell target = kspace.sDirectIncident(*it,*kspace.sDirs(*it));
        KSpace::SCell pixel = kspace.sDirectIncident(*it,*kspace.sOrthDirs(*it));

        Edge::EdgeOrientation orientation;
        if(it->preCell().positive)
        {
            if(it->preCell().coordinates[0]%2==0) orientation = Edge::PosVertical;
            else orientation = Edge::PosHorizontal;
        }else
        {
            if(it->preCell().coordinates[0]%2==0) orientation = Edge::NegVertical;
            else orientation = Edge::NegHorizontal;
        }

        edges.push( Edge(*it,
                         orientation,
                         pixel,
                         source,
                         target) );
    }
}

//Edges is meant to be passed by copy
void insertActiveLinels(ActiveLinels& activeLinels,std::stack<Edge> edges)
{
    while(!edges.empty())
    {
        Edge e = edges.top(); edges.pop();
        Point pixel = e.face.preCell().coordinates;
        activeLinels[pixel].insert(e.linel);
    }
}

void swapActiveLinelSet(const KSpace& kspace, const KSpace::SCell& face, ActiveLinels& activeLinels)
{
    std::set<KSpace::SCell>& activeLinelSet = activeLinels[face.preCell().coordinates];
    std::set<KSpace::SCell> newActiveLinelSet;

    auto incLinels = kspace.sLowerIncident(face);
    for(auto it=incLinels.begin();it!=incLinels.end();++it)
    {
        if(activeLinelSet.find(*it)==activeLinelSet.end())
        {
            newActiveLinelSet.insert( kspace.sCell(it->preCell().coordinates,!it->preCell().positive));
        }
    }

    activeLinelSet.clear();
    activeLinelSet.insert(newActiveLinelSet.begin(),newActiveLinelSet.end());
}


void updatePointels(const KSpace& kspace, ActiveLinels& activeLinels, const Edge& edge, PointelList& pointelList)
{
    swapActiveLinelSet(kspace,edge.face,activeLinels);
    std::set<KSpace::SCell>& activeLinelsSet = activeLinels[edge.face.preCell().coordinates];

    SCell currPointel = edge.source;
    while(currPointel!=edge.target)
    {
        currPointel = kspace.sCell(currPointel.preCell().coordinates,false);  //Make the pointel a source
        auto linels = kspace.sUpperIncident( currPointel );
        KSpace::SCell nextLinel;
        for(auto it=linels.begin();it!=linels.end();++it)
        {
            nextLinel= *it;
            if(activeLinelsSet.find(nextLinel)!=activeLinelsSet.end()) break;

        }

        currPointel = kspace.sDirectIncident(nextLinel,*kspace.sDirs(nextLinel)); //The pointel here is target
        pointelList.push_back(currPointel);
    }
}

SCell linelFromPointels(const KSpace& kspace, SCell& s, SCell& t)
{
    Point diff = t.preCell().coordinates - s.preCell().coordinates;
    diff/=2;

    Point linelKP = s.preCell().coordinates + diff;

    bool positive;
    if( diff[0]>0 || diff[1]>0 ) positive = true;
    else positive = false;

    return kspace.sCell( linelKP, !positive);
}

template<class TSCellsIterator>
Curve makeCurveFromPointels(const KSpace& kspace, TSCellsIterator begin, TSCellsIterator end)
{
    Curve curve;
    auto it1 = begin;
    auto it2 = it1; it2++;
    while(it2!=end)
    {
        SCell linel = linelFromPointels(kspace, *it1,*it2);
        curve.push_back( linel );
        ++it1;++it2;
    }

    curve.push_back( linelFromPointels(kspace, *it1,*begin) );
}


#include <DGtal/io/boards/Board2D.h>
int main(int argc, char* argv[])
{
    DigitalSet square = DIPaCUS::Shapes::square();
    Curve curve;
    DIPaCUS::Misc::computeBoundaryCurve(curve,square);

    const Domain& domain = square.domain();

    KSpace kspace;
    kspace.init(domain.lowerBound(),domain.upperBound(),true);

    Graph graph;
    LinelSet linels = innerLinels(curve);

    for(auto itL=linels.begin();itL!=linels.end();++itL)
    {
        auto pointels = kspace.uLowerIncident(*itL);
        assert(pointels.size()==2);
        for(auto itP=pointels.begin();itP!=pointels.end();++itP)
        {
            Point p = itP->preCell().coordinates;
            if(graph.find(p)==graph.end()) graph[p] = Node(p,0);
            graph[p].degree+=1;
        }
    }


    assert(degreeEdgesInvariant(curve,graph));
    std::cout << graph << std::endl;




    std::stack<Edge> edges;
    insertEdges(curve,kspace,edges);


    ActiveLinels activeLinels;
    insertActiveLinels(activeLinels,edges);


    PointelList pointelList;
    while(edges.size()>1)
    {
        Edge e = edges.top(); edges.pop();       //E-1
        Edge E = edges.top();                    //E0

        Point p1 = e.kpSource();
        Point p0 = e.kpTarget();
        Point P1 = E.kpTarget();
        bool betweenDegree3 = (graph[p1].degree!=2) && (graph[p0].degree==3) && (graph[P1].degree!=2);
        if(betweenDegree3)
        {
            updatePointels(kspace,activeLinels,e,pointelList);
        }else
        {
            pointelList.push_back(e.target);
        }
    }


    std::vector<Point> pv;
    for(auto it=pointelList.begin();it!=pointelList.end();++it)
    {
        pv.push_back( it->preCell().coordinates );
    }


    Curve newCurve = makeCurveFromPointels(kspace,pointelList.begin(),pointelList.end());

    DGtal::Board2D board;
    board << newCurve;
//    for(auto it=scells.begin();it!=scells.end();++it) board << *it;
    board.saveSVG("newCurve.svg");

    return 0;
}