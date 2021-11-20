#include "Graph.h"
#include <vector>


// =============================================================================
// SalesmanTrackBacktracking ===================================================
// =============================================================================

struct NodeCami {
    CEdge* m_pEdge;
    NodeCami* m_pAnterior;
};

void SalesmanTrackBacktrackingRecursivo(NodeCami* pAnterior, CVertex* pActual, CVertex* pDesti,
    CTrack& bestPath, double& pathLenght, double& bestPathLengh, int& contador)
{
    if (pActual == pDesti) {
        if (pathLenght < bestPathLengh && contador == 0) {
            bestPath.Clear();
            while (pAnterior) {
                bestPath.m_Edges.push_front(pAnterior->m_pEdge);
                pAnterior = pAnterior->m_pAnterior;
            }
            bestPathLengh = pathLenght;
        }

    }
    if (pathLenght < bestPathLengh) {
        NodeCami node;
        node.m_pAnterior = pAnterior;

        for (CEdge* pE : pActual->m_Edges) {

            if (!pE->m_Processed) {
                node.m_pEdge = pE;
                pathLenght += pE->m_Length;
                pE->m_Processed = true;

                if (pE->m_pDestination->m_isVisita && !pE->m_pDestination->m_Visited) {
                    pE->m_pDestination->m_Visited = true;
                    contador--;
                    SalesmanTrackBacktrackingRecursivo(&node, pE->m_pDestination, pDesti, bestPath, pathLenght, bestPathLengh, contador);
                    contador++;
                    pE->m_pDestination->m_Visited = false;
                }
                else {
                    SalesmanTrackBacktrackingRecursivo(&node, pE->m_pDestination, pDesti, bestPath, pathLenght, bestPathLengh, contador);
                }

                pathLenght -= pE->m_Length;
                pE->m_Processed = false;
            }
        }
    }
}


void SalesmanTrackBacktracking(CGraph& graph, list<CVertex*>& visits)
{
    CVertex* pInici = visits.front();
    CVertex* pDesti = visits.back();
    CTrack bestPath(&graph);

    double pathLenght = 0;
    double bestPathLengh = DBL_MAX;

    for (CEdge& pE : graph.m_Edges) {
        pE.m_Processed = false;
        pE.m_pDestination->m_isVisita = false;
        pE.m_pDestination->m_Visited = false;
    }

    list<CVertex*> candidats = visits;
    candidats.pop_back();
    candidats.pop_front();
    int contador = candidats.size();

    for (CVertex* v : candidats) { v->m_isVisita = true; }

    SalesmanTrackBacktrackingRecursivo(NULL, pInici, pDesti, bestPath, pathLenght, bestPathLengh, contador);
    for (CEdge* pE : bestPath.m_Edges) {
        graph.enemyRoute.push_back(make_pair(pE->m_pDestination->m_Point.m_X, pE->m_pDestination->m_Point.m_Y));
    }
}