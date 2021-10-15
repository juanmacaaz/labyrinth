#include "MenuSpace.h"

MenuSpace::MenuSpace(Engine* engine) : Space(engine)
{
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = pc.createPhysicsWorld(settings);
}

void MenuSpace::render()
{
}

void MenuSpace::update()
{
}

