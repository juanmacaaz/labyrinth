#pragma once


#include <glm.hpp>

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

#include "Camera.h"

class Space;

class Actor
{
public:

	const float VELOCIDAD = 1000.0f;
	const float SALTO = 2.75f;
	const float ALTURA_CAMARA = 0.5f;

	enum CameraID { MAIN_CAMERA = 0, MAP_CAMERA = 1 };

	Actor(Space* space, Transform transform);

	void setMainCamera(Camera camera);
	void setMapCamera(Camera camera);

	Camera* getCamera();
	CollisionBody* getBody();
	void update();
	void updateMain();
	void updateMap();

private:
	// Apuntadores a clases contenedoras
	Space* space;

	Camera camera[2];
	RigidBody* body;
	CameraID cameraID;
};

