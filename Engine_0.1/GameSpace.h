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

struct Dificultad {
	int n_keys;
	int size_map;
	float velocity_e;
	float velocity_a;
};

class GameSpace : public Space
{
public:

	GameSpace(Engine* engine, Dificultad dificultad);

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

