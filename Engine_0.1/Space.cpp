#include "Space.h"

#include "Common.h"
#include "Actor.h"
#include "Engine.h"
#include "Labyrinth.h"
#include "Engine.h"
#include "Entitie.h"
#include "Key.h"

Space::Space(Engine* engine)
{
	this->engine = engine;

	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = pc.createPhysicsWorld(settings);

	ProjectionData proyectionData = { 45.0f, 0.01f, 100.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	Transform t(Vector3(3.0f, 1.0f, 3.0f), Quaternion().identity());
	this->actor = new Actor(this, t);

	this->actor->setMainCamera(Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), 
		proyectionData, this->engine->getWWidth(), this->engine->getWHeight()));
	this->actor->setMapCamera(Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), 
		proyectionData, this->engine->getWWidth(), this->engine->getWHeight()));

	entidades.push_back(new Key(this, Vector3(6, 1.5, 6)));
	entidades.push_back(new Key(this, Vector3(8, 1.5, 6)));
	entidades.push_back(new Key(this, Vector3(10, 1.5, 6)));
	entidades.push_back(new Key(this, Vector3(6, 1.5, 8)));
	entidades.push_back(new Key(this, Vector3(6, 1.5, 10)));
	entidades.push_back(new Key(this, Vector3(7, 1.5, 7)));

	this->labyrinth = new Labyrinth(this);

	entidades.push_back(new Entitie(this, "waifu", Block::WALL, "basic-nolight", Vector3(8, 0.5, 8)));
	
}

void Space::update()
{
	actor->update();
	for (auto e : entidades) e->update();
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

Actor* Space::getActor()
{
	return actor;
}

PhysicsCommon& Space::getPC()
{
	return pc;
}

void Space::deleteEntitie(Entitie* entitie)
{
	entidades.erase(find(entidades.begin(), entidades.end(), entitie));
}

void Space::render()
{
	labyrinth->render(actor->getCamera());
	for (auto e : entidades) e->render(actor->getCamera());
}