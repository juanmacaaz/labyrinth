#pragma once

#include "Actor.h"
#include "Labyrinth.h"

class Actor;
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

private:

	// Apuntador a clase contenedora
	Engine* engine;

	// Atributos
	PhysicsWorld* world;
	Actor* actor;
	Labyrinth* labyrinth;
};

