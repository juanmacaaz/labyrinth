#include "Space.h"

#include "Engine.h"
#include "Engine.h"
#include "Entitie.h"

Space::Space(Engine* engine)
{
	this->engine = engine;
}

void Space::update()
{
	world->update(1.0f / 30.0f);
}

PhysicsWorld* Space::getWorld()
{
	return world;
}

Engine* Space::getEngine()
{
	return engine;
}

GLFWwindow* Space::getWindow()
{
	return engine->getEngineWindow();
}

PhysicsCommon& Space::getPC()
{
	return pc;
}

void Space::deleteEntitie(Entitie* entitie)
{
	// 
}

void Space::render()
{
	// Aqui se llamaria a los metodos render
}