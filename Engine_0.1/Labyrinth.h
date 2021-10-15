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

	Labyrinth(GameSpace* space);
	void render(Camera* camera);
	CGraph getGraph();

private:

	// Apuntadores a clases contenedoras
	GameSpace* space;
	CGraph graph;

	// Atributos
	vector<Cube> cubes;
	
	// Funciones privadas
	vector<vector<char>> generateMap();
};

