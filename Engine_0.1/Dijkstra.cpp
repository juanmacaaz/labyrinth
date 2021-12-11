#include "Graph.h"
#include <queue>

struct Compare {
    bool operator()(CVertex* v1, CVertex* v2) {
        return v1->m_DijkstraDistance > v2->m_DijkstraDistance;
    }
};



void DijkstraQueue(CGraph& graph, CVertex* pStart)
{
    if (graph.MemberP(pStart)) {
        for (auto& v : graph.m_Vertices) {
            v.m_DijkstraDistance = numeric_limits<double>::max();
            v.m_JaHePassat = false;
        }
        pStart->m_DijkstraDistance = 0;
        priority_queue<CVertex*, vector<CVertex*>, Compare> cua;
        cua.push(pStart);
        while (!cua.empty()) {
            CVertex* va = cua.top();
            cua.pop();
            if (!va->m_JaHePassat) {
                for (CEdge* i : va->m_Edges) {
                    if (i->m_pDestination->m_DijkstraDistance > (va->m_DijkstraDistance + i->m_Length)) {
                        i->m_pDestination->m_DijkstraDistance = i->m_Length + va->m_DijkstraDistance;
                        i->m_pDestination->arestaMinima = i;
                    }
                    cua.push(i->m_pDestination);
                }
                va->m_JaHePassat = true;
            }
        }
    }
}