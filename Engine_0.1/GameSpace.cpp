#include "GameSpace.h"

#include "Common.h"
#include "Actor.h"
#include "Engine.h"
#include "Labyrinth.h"
#include "Engine.h"
#include "Entitie.h"
#include "Key.h"
#include "Enemy.h"

GameSpace::GameSpace(Engine* engine) : Space(engine)
{
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = pc.createPhysicsWorld(settings);

	ProjectionData proyectionDataMain = { 75.0f, 0.01f, 15.0f, this->engine->getWWidth() , this->engine->getWHeight() };
	ProjectionData proyectionDataMap = { 30.0f, 0.01f, 15.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	this->labyrinth = new Labyrinth(this, 21, 21, 15);

	this->actor = new Actor(this);

	this->actor->setMainCamera(new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f),
		proyectionDataMain, this->engine->getWWidth(), this->engine->getWHeight()));
	this->actor->setMapCamera(new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f),
		proyectionDataMap, this->engine->getWWidth(), this->engine->getWHeight()));

	enemy = new Enemy(this, Vector3(this->getlabyrinth()->getEndPosition()[0], 0.505, this->getlabyrinth()->getEndPosition()[1]));
}

void GameSpace::update()
{
	Vector3 pos = actor->getBody()->getTransform().getPosition();
	enemy->moveTo(pos.x, pos.z);
	actor->update();
	enemy->update();
	for (auto e : entidades) e->update();
	world->update(1.0f / 30.0f);
	if (glfwGetKey(this->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		engine->setMenuSpace();
	}
}

Actor* GameSpace::getActor()
{
	return actor;
}

Labyrinth* GameSpace::getlabyrinth()
{
	return this->labyrinth;
}

vector<Entitie*>* GameSpace::getEntidades()
{
	return &this->entidades;
}

void GameSpace::deleteEntitie(Entitie* entitie)
{
	entidades.erase(find(entidades.begin(), entidades.end(), entitie));
}

void GameSpace::render()
{
	enemy->render(actor->getCamera());
	labyrinth->render(actor->getCamera());
	for (auto e : entidades) e->render(actor->getCamera());
}