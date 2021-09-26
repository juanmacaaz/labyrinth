#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720

using namespace glm;

struct ProjectionData
{
	float FOV;
	float zNear;
	float zFar;

	float wWidth;
	float wHeigth;
};

class Camera
{
public:
	Camera(vec3 cameraPosition, vec3 cameraTarget, ProjectionData proyectionData);
	Camera() {}
	mat4 getViewMatrix();
	mat4 getProyectionMatrix();
	void computeNewOrientation(double xpos, double ypos);
	void setPosition(vec3 position);
	vec3 getPosition();
	float getVerticalAngle();
	float getHorizantalAngle();
	float getSpeed();
	void setDirection(vec3 d);
	void setTarget(vec3 d);
	vec3 getUP();
	void setUP(vec3 up);
	vec3 getDirectrion();

private:
	ProjectionData proyectionData;
	mat4 proyectionMatrix;

	vec3 cameraPosition;
	vec3 cameraTarget;
	vec3 up;

	float horizontalAngle = 3.14f;
	float verticalAngle = 0.0f;
	float initialFoV = 45.0f;

	float speed = 0.10f;
	float mouseSpeed = 0.005f;

};


