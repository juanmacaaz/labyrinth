#pragma once

#include <vector>
using namespace std;

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

#include <glm.hpp>
using namespace glm;

#include "Space.h"
#include "Camera.h"

class Camera;
class Actor;
class Entitie;
class Labyrinth;
class Engine;

class GameSpace : public Space
{
public:

	GameSpace(Engine* engine);

	void render();
	void update();
	
	Actor* getActor();
	Labyrinth* getlabyrinth();

	void deleteEntitie(Entitie* entitie);

private:
	// Atributos
	Actor* actor;
	Labyrinth* labyrinth;

	vector<Entitie*> entidades;
};

