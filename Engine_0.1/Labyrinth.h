#pragma once

#include "Cube.h"
#include "Graph.h"
#include <vector>
#include <queue>
using namespace std;

class Camera;
class GameSpace;
class KeyEnemy;

class Labyrinth
{
public:

	Labyrinth(GameSpace* space, int width, int height, const int n_keys, const int algorithm);
	void render(Camera* camera);
	CGraph getGraph();
	vector<vector<char>> getMaze();
	vector<int> getInitialPosition();
	vector<int> getEndPosition();
	vector<pair<int, int>> getEnemyRoute();
	vector<KeyEnemy*> enemyKeys;

private:

	// Apuntadores a clases contenedoras
	GameSpace* space;
	CGraph graph;

	// Atributos
	vector<Cube> cubes;
	vector<vector<char>> m_maze;
	int m_width, m_height;
	vector<int> m_initialPosition, m_endPosition;

	// Funciones privadas
	void generateMap();
	void generateVisits(const int n_keys, const char representar);
	void generateMaze();
	void generateTestMap();

	void getFrontierUp(int i, const int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);
	void getFrontierRight(const int i, int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);
	void getFrontierDown(int i, const int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);
	void getFrontierLeft(const int i, int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours);

	void repairUp();
	void repairRight();
	void repairLeft();
	void repairDown();
};