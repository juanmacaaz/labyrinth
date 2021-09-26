#pragma once

#include <vector>

#include <glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "IRender.h"

using namespace reactphysics3d;
using namespace glm;
using namespace std;

class Cube: public IRender
{

public:

	Cube(PhysicsWorld* world, GLuint texture, GLuint shader, Vector3 initPosition, BodyType bodyType);
	GLfloat* getVertices();

	void render(Camera* camera);

private:

	// Atributos
	GLuint VAO;
	GLuint VBO;
	GLuint texture;
	GLuint shader;
	RigidBody* body;
	vector<GLfloat> vertices;

	// Funciones privadas
	void fillVertices(Vector3 p);
};

