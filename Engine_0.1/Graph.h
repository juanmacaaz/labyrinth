#pragma once

#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

using namespace std;
#undef max
#undef min

// =============================================================================
// CGPoint =====================================================================
// =============================================================================

class CGPoint
{

public:
	int m_X, m_Y;

	CGPoint() : m_X(0), m_Y(0) {}
	CGPoint(const int x, const int y = 0) : m_X(x), m_Y(y) {}
	CGPoint(const CGPoint& p) : m_X(p.m_X), m_Y(p.m_Y) {}

};



// =============================================================================
// GRAPH Classes ===============================================================
// =============================================================================
/*
Els grafs son dirigits. Per construir un graf no dirigit hi ha dos arestes que
conecten els vertexs en les dos direccions. Aquetes arestes estan relacionades
amb apuntadors.
*/

class CEdge;
class CGraph;
class CMaxFlow;

// CVertex =====================================================================

class CVertex {
public:
	// Atributs generals de CVertex
	string m_Name; // Nom del vertex
	CGPoint m_Point;
	list<CEdge*> m_Edges;
	CEdge* m_Origen;
	double m_DijkstraDistance;
	bool m_Visited, m_isVisita, m_DijkstraVisit;
	int id;
	bool m_JaHePassat;
	CEdge* arestaMinima;
	// M�todes
	CEdge* FindEdge(const char* name);
	bool MemberP(CEdge* pEdge);
	bool NeighbordP(CVertex* pVertex);
	void Unlink(CEdge* pEdge);
	CVertex(const char* name, double x, double y)
		: m_Name(name)
		, m_Point(x, y)
	{}
};


// CEdge =======================================================================

class CEdge {
public:
	string m_Name; // Nom del edge
	int m_Length; // Valor que se le asocia al edge: longitud, peso, coste, etc.
	CVertex* m_pOrigin;
	CVertex* m_pDestination;
	CEdge* m_pReverseEdge; // En caso de grafo no dirigido cada arista tiene su inverso.
	bool m_Processed;
public:
	CEdge(const char* name, int length, CVertex* pOrigin, CVertex* pDestination, CEdge* pReverseEdge)
		: m_Name(name)
		, m_Length(length)
		, m_pOrigin(pOrigin)
		, m_pDestination(pDestination)
		, m_pReverseEdge(pReverseEdge)
	{}

};

// CGraph ======================================================================

class CGraph {
public:
	list<CVertex> m_Vertices;
	list<CEdge> m_Edges;
	list<CVertex*> m_Visits;
	vector<pair<int, int>> enemyRoute;

public:
	CGraph() {}
	CGraph(vector<vector<char>>& map, const int algorithm);
	~CGraph() {}
	void Clear();

	// Vertices
	CVertex* NewVertex(const char* name, int x, int y);

	bool MemberP(CVertex* pVertex);
	size_t GetNVertices() { return m_Vertices.size(); }
	CVertex* FindVertex(const char* name);
	CVertex* GetVertex(const char* name);
	CVertex* GetVertex(const int index);
	CVertex* GetVertex(int x, int y);

	// Edges
	CEdge* NewEdge(const char* name, int value, CVertex* pOrigin, CVertex* pDestination);
	CEdge* NewEdge(CVertex* pOrigin, CVertex* pDestination, int distance);
	CEdge* FindEdge(CVertex* pVOrigin, CVertex* pVDestination);
	CEdge* FindEdge(const char* name);
	bool MemberP(CVertex* pVOrigin, CVertex* pVDestination) { return FindEdge(pVOrigin, pVDestination) != NULL; }
	bool MemberP(CEdge* pEdge);
	size_t GetNEdges() { return m_Edges.size(); }

private:

	bool checkUp(vector<vector<char>>& map, int i, int j);
	bool checkRight(vector<vector<char>>& map, int i, int j);
	bool checkDown(vector<vector<char>>& map, int i, int j);
	bool checkLeft(vector<vector<char>>& map, int i, int j);
	bool CheckPerpendicular(vector<vector<char>>& map, int i, int j);
	int getNumVecinos(vector<vector<char>>& map, int i, int j);
	void addNodoToGraph(vector<vector<char>>& map, size_t& index, int& i, int& j);
	void createNodes(vector<vector<char>>& map);
	void findandCreateUpEdge(vector<vector<char>>& map, int i, const int j);
	void findAndCreateRightEdge(vector<vector<char>>& map, const int i, int j);
	void createEdges(vector<vector<char>>& map);
};

// CTrack ======================================================================

class CTrack {
public:
	list<CEdge*> m_Edges;
	CGraph* m_pGraph;

	CTrack(CGraph* pGraph) {
		m_pGraph = pGraph;
	}
	void SetGraph(CGraph* pGraph) {
		Clear();
		m_pGraph = pGraph;

	}
	CTrack(const CTrack& t) : m_pGraph(t.m_pGraph), m_Edges(t.m_Edges) {}
	CTrack operator=(const CTrack& t) {
		m_pGraph = t.m_pGraph;
		m_Edges = t.m_Edges;
		return *this;
	}

	void Clear() { m_Edges.clear(); }
	void AppendBefore(CTrack& t);
	void Append(CTrack& t);

	double Length();
};

// ALGORITHMS ==================================================================

void SalesmanTrackBacktracking(CGraph& g, list<CVertex*>& visits);
void SalesmanTrackBranchAndBound(CGraph& g, list<CVertex*>& visits);
void DijkstraQueue(CGraph& g, CVertex* pStart);
void SalesmanTrackGreedy(CGraph& graph, list<CVertex*>& visits);