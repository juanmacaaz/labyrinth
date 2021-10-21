#pragma once

#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
using namespace glm;
using namespace std;

class Space;
class Camera;

class Entitie
{
protected:

	Space* space;

	GLuint VAO;
	GLuint VBO;
	GLuint texture;
	GLuint shader;
	RigidBody* body;
	
	vector<GLfloat> vertices;

	BoxShape* genereateBoindingBox(Transform& transform);

public:

	Entitie(Space* space, string model, int texture, string shader, Vector3 initPosition, float scale = 1);
	~Entitie();

	void deleteData();

	void render(Camera* camera);
	virtual void update() {};
	RigidBody* getBody();
};