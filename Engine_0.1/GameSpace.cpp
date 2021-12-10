#include "GameSpace.h"

#include "Common.h"
#include "Actor.h"
#include "Engine.h"
#include "Labyrinth.h"
#include "Engine.h"
#include "Entitie.h"
#include "Key.h"
#include "Enemy.h"
#include "HudSpace.h"

GameSpace::GameSpace(Engine* engine, Dificultad dificultad) : Space(engine)
{
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	this->dificultad = dificultad;

	world = pc.createPhysicsWorld(settings);
	
	ProjectionData proyectionDataMain = { 75.0f, 0.01f, 15.0f, this->engine->getWWidth() , this->engine->getWHeight() };
	ProjectionData proyectionDataMap = { 30.0f, 0.01f, 15.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	this->labyrinth = new Labyrinth(this, dificultad.size_map, dificultad.size_map, dificultad.n_keys, dificultad.id);

	this->actor = new Actor(this);

	this->actor->setMainCamera(new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f),
		proyectionDataMain, this->engine->getWWidth(), this->engine->getWHeight()));
	this->actor->setMapCamera(new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f),
		proyectionDataMap, this->engine->getWWidth(), this->engine->getWHeight()));

	int x = labyrinth->getEnemyRoute()[0].first;
	int z = labyrinth->getEnemyRoute()[0].second;
	enemy = new Enemy(this, Vector3(x, 0.505, z), labyrinth->getEnemyRoute().size());
	getEngine()->hudSpace->updateObjectiveScore(dificultad.n_keys);
	getEngine()->hudSpace->updateEnemyScore(0);
	getEngine()->hudSpace->updateYouScore(0);

}

GameSpace::~GameSpace()
{
	delete this->actor;
	delete this->labyrinth;
	delete this->enemy;
	for (Entitie* e : entidades) { e->deleteData(); }
}

void GameSpace::update()
{
	int x = labyrinth->getEnemyRoute()[enemy->getPosition()].first;
	int z = labyrinth->getEnemyRoute()[enemy->getPosition()].second;

	enemy->moveTo(x, z);

	actor->update();
	enemy->update();

	for (auto e : entidades) e->update();
	world->update(1.0f / 60.0f);
	if (glfwGetKey(this->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		engine->setMenuSpace();
	}
}

Actor* GameSpace::getActor()
{
	return actor;
}

Enemy* GameSpace::getEnemy()
{
	return enemy;
}

Camera* GameSpace::getCamera()
{
	return actor->getCamera();
}

Labyrinth* GameSpace::getlabyrinth()
{
	return this->labyrinth;
}

void GameSpace::add_entitie(Entitie* e) {
	this->entidades.push_back(e);
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