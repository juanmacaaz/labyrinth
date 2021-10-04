#include "Space.h"

#include "Common.h"

Space::Space(Engine* engine)
{
	this->engine = engine;

	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = Common::getPhysicsInstance().createPhysicsWorld(settings);

	ProjectionData proyectionData = { 45.0f, 0.01f, 100.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	Transform t(Vector3(3.0f, 2.0f, 3.0f), Quaternion().identity());
	this->actor = new Actor(this, t);

	this->actor->setMainCamera(Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), 
		proyectionData, this->engine->getWWidth(), this->engine->getWHeight()));
	this->actor->setMapCamera(Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), 
		proyectionData, this->engine->getWWidth(), this->engine->getWHeight()));

	this->labyrinth = new Labyrinth(this);
}

void Space::update()
{
	actor->update();
	world->update(1.0f / 60.0f);
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

void Space::render()
{
	labyrinth->render(actor->getCamera());
}