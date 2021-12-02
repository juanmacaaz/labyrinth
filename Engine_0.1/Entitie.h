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
	
	float orientation[3];
	vector<GLfloat> vertices;

	BoxShape* genereateBoindingBox(Transform& transform);

public:

	Entitie(Space* space, string model, int texture, string shader, Vector3 initPosition, float scale = 1);
	~Entitie();

	void deleteData();

	void rotateX(const float degrees);
	void rotateY(const float degrees);

	void rotateZ(const float degrees);

	void movePosition(const Vector3& v);

	void render(Camera* camera);
	virtual void update() {};
	RigidBody* getBody();

	static float Distance(vec3 c1, Vector3 c2, float distance)
	{
		float dx = abs(c2.x - c1.x);
		if (dx > distance) return 0;

		float dy = abs(c2.z - c1.z);
		if (dy > distance) return 0;

		return 1;
	}
};