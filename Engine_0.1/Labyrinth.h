#pragma once

#include <vector>
using namespace std;

#include "Space.h"
#include "Cube.h"
#include "Engine.h"

class Space;

class Labyrinth: public IRender 
{
public:

	Labyrinth(Space* space);
	void render(Camera* camera);

private:

	// Apuntadores a clases contenedoras
	Space* space;

	// Atributos
	vector<Cube*> cubes;
	
	// Funciones privadas
	void generateMap();
};

