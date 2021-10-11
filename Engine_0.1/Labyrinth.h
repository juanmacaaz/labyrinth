#pragma once

#include "Cube.h"
#include <vector>
using namespace std;

class Camera;
class Space;

class Labyrinth 
{
public:

	Labyrinth(Space* space);
	void render(Camera* camera);

private:

	// Apuntadores a clases contenedoras
	Space* space;

	// Atributos
	vector<Cube> cubes;
	
	// Funciones privadas
	void generateMap();
};

