#include "Graph.h"
#include <queue>

struct comparator
{
    bool operator()(pair<CVertex*, double> pV1, pair<CVertex*, double> pV2) {
        return pV1.second > pV2.second;
    }
};


void DijkstraQueue(CGraph& graph, CVertex* pStart)
{
    priority_queue<pair<CVertex*, double>, vector<pair<CVertex*, double>>, comparator> queue;
    double newdistance;

    CVertex* pActual = pStart;

    for (CVertex& v : graph.m_Vertices) {
        v.m_DijkstraDistance = DBL_MAX;
        v.m_DijkstraVisit = false;
    }

    pActual->m_DijkstraDistance = 0;
    queue.push(make_pair(pActual, pActual->m_DijkstraDistance));

    while (!queue.empty()) {
        pActual = queue.top().first;
        queue.pop();

        if (!pActual->m_DijkstraVisit) {

            for (CEdge* e : pActual->m_Edges) {
                newdistance = pActual->m_DijkstraDistance + e->m_Length;

                if (e->m_pDestination->m_DijkstraDistance > newdistance) {
                    e->m_pDestination->m_DijkstraDistance = newdistance;
                    queue.push(make_pair(e->m_pDestination, e->m_pDestination->m_DijkstraDistance));
                    e->m_pDestination->m_Origen = e;
                }
            }
            pActual->m_DijkstraVisit = true;
        }
    }
}