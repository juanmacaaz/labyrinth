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
	~Space();

	virtual Camera* getCamera();

	virtual void render();
	virtual void update();

	PhysicsWorld* getWorld();
	Engine* getEngine();
	GLFWwindow* getWindow();

	PhysicsCommon& getPC();
	void deleteEntitie(Entitie* entitie);

	void isPressed();
	bool press;

protected:

	// Apuntador a clase contenedora
	Engine* engine;

	// Atributos
	PhysicsCommon pc;
	PhysicsWorld* world;
};
