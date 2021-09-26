#include "Actor.h"

#include "Common.h"

#include <vector>
#include <gtc/type_ptr.hpp>



Actor::Actor(Space* space, Transform transform)
{
	this->space = space;

	body = space->getWorld()->createRigidBody(transform);

	body->setType(BodyType::DYNAMIC);

	//const Vector3 halfExtents(0.5f, 0.5f, 0.5f);
	CapsuleShape* capsuleShape = Common::getPhysicsInstance().createCapsuleShape(0.35, 1.2);

	body->addCollider(capsuleShape, Transform::identity());

	body->getCollider(0)->getMaterial().setBounciness(0.0f);
	body->setMass(0.5);
}

void Actor::setMainCamera(Camera camera)
{
	this->camera[MAIN_CAMERA] = camera;
}

void Actor::setMapCamera(Camera camera)
{
	this->camera[MAP_CAMERA] = camera;
}

Camera* Actor::getCamera()
{
	return &camera[cameraID];
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

inline void Actor::updateMain()
{
	double xpos, ypos;
	glfwGetCursorPos(space->getWindow(), &xpos, &ypos);
	glfwSetCursorPos(space->getWindow(), WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

	camera[MAIN_CAMERA].computeNewOrientation(xpos, ypos);

	float verticalAngle = camera[MAIN_CAMERA].getVerticalAngle();
	float horizontalAngle = camera[MAIN_CAMERA].getHorizantalAngle();

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
		body->applyForceToCenterOfMass(directionM * VEL);
	}

	if (glfwGetKey(space->getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		body->applyForceToCenterOfMass(-1 * directionM * VEL);
	}

	if (glfwGetKey(space->getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		const float aux = directionM[0];
		directionM[0] = -directionM[2];
		directionM[2] = aux;

		body->applyForceToCenterOfMass(directionM * VEL);
	}

	if (glfwGetKey(space->getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		const float aux = directionM[0];
		directionM[0] = directionM[2];
		directionM[2] = -aux;

		body->applyForceToCenterOfMass(directionM * VEL);
	}

	const float gravity = body->getLinearVelocity()[1];

	/*
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && abs(gravity) < 0.001f) {
		directionM[1] = SALTO;
		body->applyForceToCenterOfMass(directionM * VELOCIDAD);
	}
	*/

	body->setTransform(Transform(body->getTransform().getPosition(), Quaternion::identity()));
	body->setLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));

	camera[MAIN_CAMERA].setUP(up);

	vec3 pos;
	memcpy((void*)&pos[0], (void*)&body->getTransform().getPosition()[0], sizeof(float) * 3);

	pos[1] += ALTURA_CAMARA;
	camera[MAIN_CAMERA].setPosition(pos);
	camera[MAIN_CAMERA].setDirection(direction);
}

inline void Actor::updateMap()
{
	vec3 pos;
	body->setLinearVelocity(Vector3(0.0f, 0.0f, 0.0f));
	memcpy((void*)&pos[0], (void*)&body->getTransform().getPosition()[0], sizeof(float) * 3);
	camera[MAP_CAMERA].setPosition(vec3(pos[0], 10, pos[2] + 0.001f));
	camera[MAP_CAMERA].setDirection(vec3(camera[MAIN_CAMERA].getDirectrion()[0] * 0.0005f, -1, camera[MAIN_CAMERA].getDirectrion()[2] * 0.0005f));
}
