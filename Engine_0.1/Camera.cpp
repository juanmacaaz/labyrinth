#include "Camera.h"

Camera::Camera(vec3 cameraPosition, vec3 cameraTarget, ProjectionData proyectionData, int w_width, int w_height)
{
	this->proyectionData = proyectionData;
	this->w_width = w_width;
	this->w_height = w_height;

	this->proyectionMatrix = glm::perspective(
		glm::radians(proyectionData.FOV),
		proyectionData.wWidth / proyectionData.wHeigth,
		proyectionData.zNear,
		proyectionData.zFar);
	this->cameraPosition = cameraPosition;
	this->cameraTarget = cameraTarget;
	up = vec3(0, 1, 0);
}

mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraTarget, up);
}

mat4 Camera::getProyectionMatrix()
{
	return proyectionMatrix;
}

void Camera::computeNewOrientation(double xpos, double ypos)
{
	horizontalAngle += mouseSpeed * float(w_width / 2 - xpos);
	verticalAngle += mouseSpeed * float(w_height / 2 - ypos);
}

void Camera::setPosition(vec3 position)
{
	cameraPosition = position;
}

vec3 Camera::getPosition()
{
	return cameraPosition;
}

float Camera::getVerticalAngle()
{
	return verticalAngle;
}

float Camera::getHorizantalAngle()
{
	return horizontalAngle;
}

float Camera::getSpeed()
{
	return speed;
}

void Camera::setVerticalAngle(float d)
{
	verticalAngle = d;
}

void Camera::setDirection(vec3 d)
{
	cameraTarget = d;
}

void Camera::setTarget(vec3 d)
{
	cameraTarget = d;
}

vec3 Camera::getUP()
{
	return up;
}

void Camera::setUP(vec3 up)
{
	this->up = up;
}

vec3 Camera::getDirectrion()
{
	return cameraTarget;
}
