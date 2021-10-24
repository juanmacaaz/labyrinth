#pragma once
#include <glm.hpp>

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

#include "Camera.h"

class GameSpace;
class Entitie;

class Actor
{
public:

	const float VELOCIDAD = 4000.0f;
	const float SALTO = 2.75f;
	const float ALTURA_CAMARA = 0.5f;

	enum CameraID { MAIN_CAMERA = 0, MAP_CAMERA = 1 };

	Actor(GameSpace* space, Transform transform);

	void setMainCamera(Camera* camera);
	void setMapCamera(Camera* camera);

	Camera* getCamera();

	CollisionBody* getBody();

	void update();
	void updateMain();
	void updateMap();

private:
	// Apuntadores a clases contenedoras
	GameSpace* space;

	Camera* camera[2];

	CameraID cameraID;
	Entitie* entitie;
	Matrix3x3 orientation;
};

