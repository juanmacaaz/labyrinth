#pragma once
#include "Space.h"

#include <vector>

class Camera;
class Entitie;

class HudSpace : public Space
{
public:

	HudSpace(Engine* engine);

	void render();
	void update();

private:

	Camera* hudCamera;

	vector<Entitie*> hudElements;

};
