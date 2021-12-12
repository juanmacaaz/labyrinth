#include "Graph.h"
#include <queue>



// SalesmanTrackBranchAndBound1 ===================================================

struct BB1 {
	BB1(int node, vector<int> combinaciones, double lenght) : m_node(node), m_combinacion(combinaciones), m_lenght(lenght) {}

	int m_node;
	vector<int> m_combinacion;
	double m_lenght;
};

struct comparator {
	bool operator()(const BB1* s1, const BB1* s2) {
		return s1->m_lenght > s2->m_lenght;
	}
};

void generarteFirstPathBB(CGraph& graph, CVertex* pInicio, CVertex* pStart, CVertex* pfinal, CTrack& track) {
	DijkstraQueue(graph, pInicio);
	CVertex* pActual = pfinal;
	while (pActual != pStart) {
		track.m_Edges.push_front(pActual->m_Origen);
		pActual = pActual->m_Origen->m_pOrigin;
	}
}

void generateLastPathBB(CGraph& graph, CVertex* pInicio, CVertex* pStart, CVertex* pfinal, CTrack& track) {
	DijkstraQueue(graph, pInicio);
	CVertex* pActual = pfinal;
	while (pActual != pStart) {
		track.m_Edges.push_back(pActual->m_Origen->m_pReverseEdge);
		pActual = pActual->m_Origen->m_pOrigin;
	}
}

void generateAdjaenciaMatrixBB(CGraph& graph, list<CVertex*> candidats, vector<vector<CTrack>>& adjacencia)
{
	int i = 0;
	for (CVertex* pStart : candidats) {
		int j = 0;
		DijkstraQueue(graph, pStart);
		for (CVertex* pEnd : candidats) {
			CVertex* pActual = pEnd;
			CTrack track(&graph);

			while (pActual != pStart) {
				track.m_Edges.push_front(pActual->m_Origen);
				pActual = pActual->m_Origen->m_pOrigin;
			}
			adjacencia[i][j] = track;
			j++;
		}
		i++;
	}
}

void SalesmanTrackBranchAndBound(CGraph& graph, list<CVertex*>& visits)
{
	CTrack bestTrack(&graph);

	vector<vector<CTrack>> adjacencia;
	adjacencia.resize(visits.size());
	for (int i = 0; i < adjacencia.size(); i++) { adjacencia[i].resize(visits.size(), CTrack(NULL)); }

	generateAdjaenciaMatrixBB(graph, visits, adjacencia);

	vector<int> visitas;
	for (int i = 1; i < adjacencia.size() - 1; i++) { visitas.push_back(i); }

	double maxLength = DBL_MAX;
	priority_queue<BB1*, std::vector<BB1*>, comparator> queue;

	for (int i : visitas) {
		vector<int> combinaciones;
		for (int i2 : visitas) { if (i != i2) combinaciones.push_back(i2); }

		double newLengt = adjacencia[0][i].Length() + adjacencia[adjacencia.size() - 1][combinaciones.back()].Length();
		newLengt += adjacencia[i][combinaciones.front()].Length();
		for (int k = 0; k < combinaciones.size() - 1; k++) { newLengt += adjacencia[combinaciones[k]][combinaciones[k + 1]].Length(); }

		queue.push(new BB1(i, combinaciones, newLengt));
	}
	vector<int> aux;
	BB1 best = BB1(1, aux, DBL_MAX);

	while (!queue.empty()) {
		BB1* b1 = queue.top();
		queue.pop();

		if (b1->m_lenght < best.m_lenght) {
			best = *b1;
			maxLength = best.m_lenght;
		}

		for (int i = 0; i < b1->m_combinacion.size() - 1; i++) {
			for (int j = 1; j < b1->m_combinacion.size(); j++) {

				swap(b1->m_combinacion[i], b1->m_combinacion[j]);

				double newLengt = adjacencia[0][b1->m_node].Length() + adjacencia[adjacencia.size() - 1][b1->m_combinacion.back()].Length();
				newLengt += adjacencia[b1->m_node][b1->m_combinacion.front()].Length();
				for (int k = 0; k < b1->m_combinacion.size() - 1; k++) { newLengt += adjacencia[b1->m_combinacion[k]][b1->m_combinacion[k + 1]].Length(); }

				if (newLengt < maxLength) {
					BB1* newBB1 = new BB1(b1->m_node, b1->m_combinacion, newLengt);
					queue.push(newBB1);
					maxLength = newLengt;
				}
				swap(b1->m_combinacion[i], b1->m_combinacion[j]);
			}

		}
	}

	bestTrack.Append(adjacencia[best.m_node][best.m_combinacion.front()]);
	for (int i = 0; i != best.m_combinacion.size() - 1; i++) {
		bestTrack.Append(adjacencia[best.m_combinacion[i]][best.m_combinacion[i + 1]]);
	}

	bestTrack.AppendBefore(adjacencia[0][best.m_node]);
	bestTrack.Append(adjacencia[best.m_combinacion.back()][adjacencia.size() - 1]);

	for (CEdge* pE : bestTrack.m_Edges) {
		graph.enemyRoute.push_back(make_pair(pE->m_pDestination->m_Point.m_X, pE->m_pDestination->m_Point.m_Y));
	}
}