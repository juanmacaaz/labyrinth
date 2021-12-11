#include "Graph.h"



// SalesmanTrackGreedy =========================================================

void SalesmanTrackGreedy(CGraph& graph, list<CVertex*>& visits)
{
	CTrack t(&graph);
	list<CVertex*> candidats;
	for (auto& i : visits) {
		if (i != visits.front() && i != visits.back()) {
			candidats.push_back(i);
		}
	}

	CVertex* v = visits.front();
	while (!candidats.empty()) {
		DijkstraQueue(graph, v);
		CVertex* v1 = candidats.front();
		for (auto& j : candidats) {
			if (j->m_DijkstraDistance < v1->m_DijkstraDistance) {
				v1 = j;
			}
		}
		CVertex* aux = v1;
		while (aux != v) {
			t.m_Edges.push_back(aux->arestaMinima);
			aux = aux->arestaMinima->m_pOrigin;
		}
		candidats.remove(v1);
		v = v1;
	}
	DijkstraQueue(graph, v);
	CVertex* final = visits.back();
	while (v != final) {
		t.m_Edges.push_back(final->arestaMinima);
		final = final->arestaMinima->m_pOrigin;
	}

	for (CEdge* pE : t.m_Edges) {
		graph.enemyRoute.push_back(make_pair(pE->m_pDestination->m_Point.m_X, pE->m_pDestination->m_Point.m_Y));
	}
}
