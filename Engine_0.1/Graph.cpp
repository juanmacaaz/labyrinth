#include "Graph.h"
#include <stdarg.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>
using namespace std;

// =============================================================================
// CVertex =====================================================================
// =============================================================================

// MemberP =====================================================================

bool CVertex::MemberP(CEdge* pEdge)
{
    for (CEdge* pE : m_Edges) if (pE == pEdge) return true;
    return false;
}

// NeighbordP ==================================================================

bool CVertex::NeighbordP(CVertex* pVertex)
{
    for (CEdge* pE : m_Edges) if (pE->m_pDestination == pVertex) return true;
    return false;

}

// FindEdge =====================================================================

CEdge* CVertex::FindEdge(const char* name)
{
    for (CEdge* pEdge : m_Edges) {
        if (strcmp(pEdge->m_Name.c_str(), name) == 0) return pEdge;
    }
    return NULL;
}

// Unlink ======================================================================

void CVertex::Unlink(CEdge* pEdge)
{
    for (list<CEdge*>::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it) {
        if (pEdge == *it) {
            m_Edges.erase(it);
            break;
        }
    }
}

// =============================================================================
// CGraph ======================================================================
// =============================================================================


CGraph::CGraph(vector<vector<char>>& map)
{
    createNodes(map);
    createEdges(map);
}

// Clear =======================================================================

void CGraph::Clear()
{
    m_Vertices.clear();
    m_Edges.clear();
}

// NewVertex ==================================================================

CVertex* CGraph::NewVertex(const char* name, int x, int y)
{
    m_Vertices.push_back(CVertex(name, x, y));
    return &m_Vertices.back();
}


// MemberP =====================================================================

bool CGraph::MemberP(CVertex* pVertex)
{
    for (CVertex& v : m_Vertices) {
        if (&v == pVertex) return true;
    }
    return false;
}

// FindVertex =================================================================

CVertex* CGraph::FindVertex(const char* name)
{
    for (CVertex& v : m_Vertices) {
        if (strcmp(v.m_Name.c_str(), name) == 0) return &v;
    }
    return NULL;
}

// GetVertex ===================================================================

CVertex* CGraph::GetVertex(const char* name)
{
    CVertex* pV = FindVertex(name);
    return pV;
}

// GetVertex ===================================================================

CVertex* CGraph::GetVertex(const int index)
{
    int i = index;
    for (CVertex& v : m_Vertices) {
        if (i == 0) return &v;
        --i;
    }
}

CVertex* CGraph::GetVertex(int x, int y)
{
    for (CVertex& v : m_Vertices) {

        if (v.m_Point.m_X == x && v.m_Point.m_Y == y) {
            return &v;
        }
    }
}

// NewEdge =====================================================================

CEdge* CGraph::NewEdge(CVertex* pVOrigin, CVertex* pVDestination, int distance)
{
    char name[10];
    size_t i = m_Edges.size() + 1;

    for (;;) {
        sprintf_s(name, "E%04llu", i);
        if (FindEdge(name) == NULL) break;
        ++i;
    }

    m_Edges.push_back(CEdge(name, distance, pVOrigin, pVDestination, NULL));
    CEdge* pEdge = &m_Edges.back();
    pVOrigin->m_Edges.push_back(pEdge);
    string rname(name);
    rname += "$Reverse";
    m_Edges.push_back(CEdge(rname.c_str(), distance, pVDestination, pVOrigin, NULL));
    CEdge* pRevEdge = &m_Edges.back();
    pVDestination->m_Edges.push_back(pRevEdge);
    pEdge->m_pReverseEdge = pRevEdge;
    pRevEdge->m_pReverseEdge = pEdge;
    return pEdge;
}

// FindEdge ====================================================================

CEdge* CGraph::FindEdge(CVertex* pVOrigin, CVertex* pVDestination)
{
    for (CEdge& e : m_Edges) {
        if (e.m_pOrigin == pVOrigin && e.m_pDestination == pVDestination) return &e;
    }
    return NULL;
}

// FindEdge ====================================================================

CEdge* CGraph::FindEdge(const char* name)
{
    for (CEdge& e : m_Edges) {
        if (strcmp(e.m_Name.c_str(), name) == 0) return &e;
    }
    return NULL;
}

// MemberP =====================================================================

bool CGraph::MemberP(CEdge* pEdge)
{
    for (CEdge& e : m_Edges) {
        if (&e == pEdge) return true;
    }
    return false;
}

// Create graph from a map of char =============================================

bool CGraph::checkUp(vector<vector<char>>& matriu, int i, int j) {
    if (matriu[i - 1][j] != '#') { return true; }
    else { return false; }
}

bool CGraph::checkRight(vector<vector<char>>& matriu, int i, int j) {
    if (matriu[i][j + 1] != '#') { return true; }
    else { return false; }
}

bool CGraph::checkDown(vector<vector<char>>& matriu, int i, int j) {
    if (matriu[i + 1][j] != '#') { return true; }
    else { return false; }
}

bool CGraph::checkLeft(vector<vector<char>>& matriu, int i, int j) {
    if (matriu[i][j - 1] != '#') { return true; }
    else { return false; }
}

bool CGraph::CheckPerpendicular(vector<vector<char>>& matriu, int i, int j) {
    if ((checkUp(matriu, i, j) && checkLeft(matriu, i, j)) ||
        (checkUp(matriu, i, j) && checkRight(matriu, i, j)) ||
        (checkDown(matriu, i, j) && checkLeft(matriu, i, j)) ||
        (checkDown(matriu, i, j) && checkRight(matriu, i, j))) {
        return true;
    }
    else {
        return false;
    }
}

int CGraph::getNumVecinos(vector<vector<char>>& matriu, int i, int j) {
    int numVecinos = 0;

    if (checkUp(matriu, i, j)) { numVecinos++; }
    if (checkRight(matriu, i, j)) { numVecinos++; }
    if (checkLeft(matriu, i, j)) { numVecinos++; }
    if (checkDown(matriu, i, j)) { numVecinos++; }

    return numVecinos;
}

void CGraph::addNodoToGraph(vector<vector<char>>& map, size_t& index, int& i, int& j) {
    char name[10];
    sprintf_s(name, "V%04llu", index);
    index++;
    NewVertex(name, j, i);
    map[i][j] = 'V';
}

void CGraph::createNodes(vector<vector<char>>& map) {
    vector<vector<char>> mapV = map;
    char name[10];
    size_t index = 0;
    for (int i = 1; i < map.size() - 1; i++) {
        for (int j = 1; j < map.size() - 1; j++) {

            if (map[i][j] == '1') {
                if (getNumVecinos(map, i, j) > 2) {
                    addNodoToGraph(mapV, index, i, j);
                }
                else if ((checkUp(map, i, j) && !checkDown(map, i, j)) || (!checkUp(map, i, j) && checkDown(map, i, j))) {  //check Eje vertical
                    addNodoToGraph(mapV, index, i, j);
                }
                else if ((checkRight(map, i, j) && !checkLeft(map, i, j)) || (!checkRight(map, i, j) && checkLeft(map, i, j))) {    //chek eje horizontal
                    addNodoToGraph(mapV, index, i, j);
                }
                else if (CheckPerpendicular(map, i, j)) {
                    addNodoToGraph(mapV, index, i, j);
                }
            }
            else if (map[i][j] == 'S') {
                index++;
                NewVertex("Salida", j, i);
            }
            else if (map[i][j] == 'E') {
                index++;
                NewVertex("Entrada", j, i);
            }
            else if (map[i][j] == 'K') {
                sprintf_s(name, "V%04llu", index);
                index++;
                m_Visits.push_back(NewVertex(name, j, i));
            }
        }
    }
    map = mapV;
}

void CGraph::findandCreateUpEdge(vector<vector<char>>& map, int i, const int j) {
    int iOriginal = i;
    int jOriginal = j;
    i--;
    int distance = 1;
    while (i > 0 && map[i][j] != '#') {
        if (map[i][j] == 'V' || map[i][j] == 'E' || map[i][j] == 'S') {
            NewEdge(GetVertex(jOriginal, iOriginal), GetVertex(j, i), distance);
            break;
        }
        i--;
        distance++;
    }
}

void CGraph::findAndCreateRightEdge(vector<vector<char>>& map, const int i, int j) {
    int iOriginal = i;
    int jOriginal = j;
    j++;
    int distance = 1;
    while (j < map.size() - 1 && map[i][j] != '#') {
        if (map[i][j] == 'V' || map[i][j] == 'E' || map[i][j] == 'S') {
            NewEdge(GetVertex(jOriginal, iOriginal), GetVertex(j, i), distance);
            break;
        }
        j++;
        distance++;
    }
}

void CGraph::createEdges(vector<vector<char>>& map) {
    for (int i = 1; i < map.size() - 1; i++) {
        for (int j = 1; j < map.size() - 1; j++) {
            if (map[i][j] == 'V' || map[i][j] == 'E' || map[i][j] == 'S') {
                findandCreateUpEdge(map, i, j);
                findAndCreateRightEdge(map, i, j);
            }
        }
    }
}
