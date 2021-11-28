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
class Enemy;

class GameSpace : public Space
{
public:

	GameSpace(Engine* engine);

	void render();
	void update();

	Actor* getActor();
	Enemy* getEnemy();
	Labyrinth* getlabyrinth();
	vector<Entitie*>* getEntidades();

	void deleteEntitie(Entitie* entitie);

private:
	// Atributos
	Actor* actor;
	Labyrinth* labyrinth;
	Enemy* enemy;

	vector<Entitie*> entidades;
};

