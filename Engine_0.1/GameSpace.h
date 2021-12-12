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
	int id;
	int n_keys;
	int size_map;
	float velocity_e;
	float velocity_a;
};

class GameSpace : public Space
{
public:

	GameSpace(Engine* engine, Dificultad dificultad);
	~GameSpace();

	void render();
	void update();

	Actor* getActor();
	Enemy* getEnemy();
	Camera* getCamera();

	Labyrinth* getlabyrinth();
	void add_entitie(Entitie* e);
	vector<Entitie*>* getEntidades();

	void deleteEntitie(Entitie* entitie);
	Dificultad dificultad;
	
	int id_dificultad;
	int max_render;

private:
	// Atributos
	Actor* actor;
	Labyrinth* labyrinth;
	Enemy* enemy;
	Enemy* enemy2;

	vector<Entitie*> entidades;
};

