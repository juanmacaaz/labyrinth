#pragma once

#include "Cube.h"
#include "Graph.h"
#include <vector>
using namespace std;

class Camera;
class GameSpace;

class Labyrinth 
{
public:

	Labyrinth(GameSpace* space, int width, int height);
	void render(Camera* camera);
	CGraph getGraph();
	vector<vector<char>> getMaze();

private:

	// Apuntadores a clases contenedoras
	GameSpace* space;
	CGraph graph;

	// Atributos
	vector<Cube> cubes;
	vector<vector<char>> m_maze;
	int m_width, m_height;
	
	// Funciones privadas
	void generateMap();
	void generateMaze();

	void getFrontierUp(int i, const int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);
	void getFrontierRight(const int i, int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);
	void getFrontierDown(int i, const int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);
	void getFrontierLeft(const int i, int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);

	void repairUp();
	void repairRight();
	void repairLeft();
	void repairDown();
};

