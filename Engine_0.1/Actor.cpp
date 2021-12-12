#include "Actor.h"

#include "Common.h"

#include <vector>
#include <gtc/type_ptr.hpp>

#include "GameSpace.h"
#include "Engine.h"
#include "Entitie.h"
#include "Labyrinth.h"
#include "Enemy.h"
#include "HudSpace.h"
#include "MenuSpace.h"

Actor::Actor(GameSpace* space)
{
	this->space = space;
	n_manzanas = 0;

	original_position = Vector3(this->space->getlabyrinth()->getInitialPosition()[0], 1.4,
		this->space->getlabyrinth()->getInitialPosition()[1]);

	entitie = new Entitie(space, "waifu", Block::WOOD, "basic-nolight", original_position, 0.25f);

	RigidBody* body = entitie->getBody();

	body->setMass(65.0f);
	body->getCollider(0)->setCollideWithMaskBits(0x0003);
	body->removeCollider(body->getCollider(0));

	CapsuleShape* capsuleShape = Common::getPhysicsInstance().createCapsuleShape(0.30, 1.2);
	body->updateLocalCenterOfMassFromColliders();
	body->addCollider(capsuleShape, Transform::identity());
	body->getCollider(0)->getMaterial().setBounciness(0.0f);
	body->getCollider(0)->getMaterial().setFrictionCoefficient(0.2f);
}

Actor::~Actor()
{
	delete this->entitie;
}

void Actor::setMainCamera(Camera* camera)
{
	this->camera[MAIN_CAMERA] = camera;
}

void Actor::addManzana() {
	space->getEngine()->LoadCoin(space->getEngine()->levelmusic);
	n_manzanas++;
	space->getEngine()->hudSpace->updateYouScore(n_manzanas);
	cout << "Has cogido una manzana tienes " << n_manzanas << endl;

	if (space->dificultad.n_keys - 3 == n_manzanas) {
		space->getEngine()->LoadCoin(3);
	}

	if (space->dificultad.n_keys == n_manzanas) {
		space->getEngine()->getMenuSpace()->setWinLose(0);
		space->getEngine()->setMenuSpace();
		cout << "Has GANADO!! " << endl;
		//exit(2);
	}
}

void Actor::toInitPosition() {
	entitie->getBody()->setAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));
	entitie->getBody()->setLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	entitie->getBody()->setTransform(Transform(original_position, Quaternion::identity()));
	entitie->getBody()->setAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));
	entitie->getBody()->setLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
}

void Actor::setMapCamera(Camera* camera)
{
	this->camera[MAP_CAMERA] = camera;
}

Camera* Actor::getCamera()
{
	return camera[cameraID];
}

CollisionBody* Actor::getBody()
{
	return entitie->getBody();
}

void Actor::update()
{
	if (glfwGetKey(space->getWindow(), GLFW_KEY_Z)) {
		cameraID = MAP_CAMERA;
		updateMap();
	}
	else {
		cameraID = MAIN_CAMERA;
		updateMain();
	}
}

void Actor::updateMain()
{
	space->getEnemy()->setEnemyVelocity(0.01f);
	double xpos, ypos;
	glfwGetCursorPos(space->getWindow(), &xpos, &ypos);
	glfwSetCursorPos(space->getWindow(), space->getEngine()->getWWidth() / 2, space->getEngine()->getWHeight() / 2);

	camera[MAIN_CAMERA]->computeNewOrientation(xpos, ypos);

	float verticalAngle = camera[MAIN_CAMERA]->getVerticalAngle();
	float horizontalAngle = camera[MAIN_CAMERA]->getHorizantalAngle();

	if (verticalAngle > 1.5f) {
		camera[MAIN_CAMERA]->setVerticalAngle(1.5f);
		verticalAngle = 1.5f;
	}

	if (verticalAngle < -1.5f) {
		camera[MAIN_CAMERA]->setVerticalAngle(-1.5f);
		verticalAngle = -1.5f;
	}

	vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	Vector3 directionM(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);

	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);

	glm::vec3 up = glm::cross(right, direction);

	float factor = (abs(directionM[1])) * VELOCIDAD;

	directionM[1] = 0;

	const float VEL = VELOCIDAD + factor;

	if (glfwGetKey(space->getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		entitie->getBody()->applyForceToCenterOfMass(directionM * VEL);
	}

	if (glfwGetKey(space->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		entitie->getBody()->applyForceToCenterOfMass(-1 * directionM * VEL);
	}

	if (glfwGetKey(space->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		const float aux = directionM[0];
		directionM[0] = -directionM[2];
		directionM[2] = aux;

		entitie->getBody()->applyForceToCenterOfMass(directionM * VEL);
	}

	if (glfwGetKey(space->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		const float aux = directionM[0];
		directionM[0] = directionM[2];
		directionM[2] = -aux;

		entitie->getBody()->applyForceToCenterOfMass(directionM * VEL);
	}

	orientation = Matrix3x3(cos(horizontalAngle), 0, sin(horizontalAngle),
		0, 1, 0,
		-sin(horizontalAngle), 0, cos(horizontalAngle));

	entitie->getBody()->setTransform(Transform(entitie->getBody()->getTransform().getPosition(), orientation));
	entitie->getBody()->setLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));

	//entitie->getBody()->setAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));

	camera[MAIN_CAMERA]->setUP(up);

	vec3 pos;
	memcpy((void*)&pos[0], (void*)&entitie->getBody()->getTransform().getPosition()[0], sizeof(float) * 3);

	pos[1] += ALTURA_CAMARA;
	camera[MAIN_CAMERA]->setPosition(pos);
	camera[MAIN_CAMERA]->setDirection(direction);
}

inline void Actor::updateMap()
{
	vec3 pos;
	space->getEnemy()->setEnemyVelocity(0.02f);

	entitie->getBody()->setLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	entitie->getBody()->setAngularVelocity(Vector3(0.0f, 0.0f, 0.0f));

	entitie->getBody()->setTransform(Transform(entitie->getBody()->getTransform().getPosition(), orientation));
	memcpy((void*)&pos[0], (void*)&entitie->getBody()->getTransform().getPosition()[0], sizeof(float) * 3);
	camera[MAP_CAMERA]->setPosition(vec3(pos[0], distance_view, pos[2] + 0.001f));
	camera[MAP_CAMERA]->setDirection(vec3(camera[MAIN_CAMERA]->getDirectrion()[0] * 0.0005f, -1, camera[MAIN_CAMERA]->getDirectrion()[2] * 0.0005f));
	entitie->render(camera[MAP_CAMERA]);
}
