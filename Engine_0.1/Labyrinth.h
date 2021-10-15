#pragma once

#include "Cube.h"
#include "Graph.h"
#include <vector>
using namespace std;

class Camera;
class Space;

class Labyrinth 
{
public:

	Labyrinth(Space* space);
	void render(Camera* camera);
	CGraph getGraph();

private:

	// Apuntadores a clases contenedoras
	Space* space;
	CGraph graph;

	// Atributos
	vector<Cube> cubes;
	
	// Funciones privadas
	vector<vector<char>> generateMap();
};

