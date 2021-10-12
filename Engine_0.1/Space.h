#pragma once

#include <vector>
using namespace std;

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

#include <glm.hpp>
using namespace glm;

#include "Camera.h"
#include "Common.h"

class Camera;
class Actor;
class Entitie;
class Labyrinth;
class Engine;

class Space
{
public:

	Space(Engine* engine);

	void render();
	void update();

	PhysicsWorld* getWorld();
	Engine* getEngine();
	GLFWwindow* getWindow();

	Actor* getActor();

	PhysicsCommon& getPC();

private:

	// Apuntador a clase contenedora
	Engine* engine;

	// Atributos
	PhysicsCommon pc;
	PhysicsWorld* world;
	Actor* actor;
	Labyrinth* labyrinth;

	vector<Entitie*> entidades;
};

