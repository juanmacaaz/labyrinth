#include "HudSpace.h"
#include "Engine.h"
#include "Entitie.h"

HudSpace::HudSpace(Engine* engine) : Space(engine) 
{
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = pc.createPhysicsWorld(settings);



	ProjectionData proyectionData = { 45.0f, 0.01f, 100.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	hudCamera = new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), proyectionData, this->engine->getWWidth(), this->engine->getWHeight());


	hudElements.push_back(new Entitie(this, "key", Block::WALL, "basic-nolight", Vector3(0.15, -0.05, -0.1), 0.1));
	hudElements.push_back(new Entitie(this, "key", Block::WALL, "basic-nolight", Vector3(0.15, -0.05, -0.085), 0.1));
	hudElements.push_back(new Entitie(this, "key", Block::WALL, "basic-nolight", Vector3(0.15, -0.05, -0.07), 0.1));
	hudElements.push_back(new Entitie(this, "key", Block::WALL, "basic-nolight", Vector3(0.15,- 0.05, -0.055), 0.1));

}

void HudSpace::render() {
	for (auto e : hudElements) e->render(hudCamera);
}

void HudSpace::update() {
	for (auto e : hudElements) e->update();
}