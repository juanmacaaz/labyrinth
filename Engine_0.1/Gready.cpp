#include "Graph.h"



// SalesmanTrackGreedy =========================================================

CVertex* getVertexMinDistance(list<CVertex*> candidats, CVertex* v1) {
	float minDistance = DBL_MAX;

	for (CVertex* v : candidats) {

		if (v->m_DijkstraDistance < minDistance) {
			v1 = v;
			minDistance = v1->m_DijkstraDistance;
		}
	}
	return v1;
}

void getInverseTrack(CVertex* pOrigen, CVertex* pDestino, CTrack& track) {
	list<CEdge*> path;
	CVertex* pActual = pDestino;
	while (pActual != pOrigen) {
		path.push_front(pActual->m_Origen);
		pActual = pActual->m_Origen->m_pOrigin;
	}
	for (CEdge* e : path) { track.m_Edges.push_back(e); }
}


void SalesmanTrackGreedy(CGraph& graph, list<CVertex*>& visits)
{
	CVertex* v = visits.front();
	CVertex* v1 = v;
	CTrack track(&graph);
	list<CVertex*> candidats = visits;
	candidats.pop_front();
	candidats.pop_back();

	while (!candidats.empty()) {
		DijkstraQueue(graph, v);
		v1 = getVertexMinDistance(candidats, v1);
		getInverseTrack(v, v1, track);
		candidats.remove(v1);
		v = v1;
	}

	DijkstraQueue(graph, v);
	getInverseTrack(v, visits.back(), track);

	for (CEdge* pE : track.m_Edges) {
		graph.enemyRoute.push_back(make_pair(pE->m_pDestination->m_Point.m_X, pE->m_pDestination->m_Point.m_Y));
	}
}
