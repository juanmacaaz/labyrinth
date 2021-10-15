#pragma once

#include "Cube.h"
#include <vector>
using namespace std;

class Camera;
class GameSpace;

class Labyrinth 
{
public:

	Labyrinth(GameSpace* space);
	void render(Camera* camera);

private:

	// Apuntadores a clases contenedoras
	GameSpace* space;

	// Atributos
	vector<Cube> cubes;
	
	// Funciones privadas
	void generateMap();
};

