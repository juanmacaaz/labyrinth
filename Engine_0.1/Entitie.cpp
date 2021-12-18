#include "Entitie.h"

using namespace std;
#include <gtc/type_ptr.hpp>

#include "Engine.h"
#include "Space.h"
#include "Camera.h"

#include "OBJ_Loader.h"

#define MAX_RENDER_DISTANCE 10

BoxShape* Entitie::genereateBoindingBox(Transform& transform)
{
	float minX = INFINITY;
	float minY = INFINITY;
	float minZ = INFINITY;

	float maxX = -INFINITY;
	float maxY = -INFINITY;
	float maxZ = -INFINITY;

	for (int i = 0; i < vertices.size(); i += 5) {

		if (vertices[i] < minX) minX = vertices[i];
		if (vertices[i + 1] < minY) minY = vertices[i + 1];
		if (vertices[i + 2] < minZ) minZ = vertices[i + 2];

		if (vertices[i] > maxX) maxX = vertices[i];
		if (vertices[i + 1] > maxY) maxY = vertices[i + 1];
		if (vertices[i + 2] > maxZ) maxZ = vertices[i + 2];

	}

	const Vector3 halfExtents((maxX - minX) / 2, (maxY - minY) / 2, (maxZ - minZ) / 2);
	transform = Transform(Vector3((maxX + minX) / 2, (maxY + minY) / 2, (maxZ + minZ) / 2), Quaternion::identity());
	return space->getPC().createBoxShape(halfExtents);
}

Entitie::Entitie(Space* space, string modelName, int texture, string shader, Vector3 initPosition, float scale)
{
	fog = space->getEngine()->fog;
	this->texture = space->getEngine()->getTextures()[texture];
	this->shader = space->getEngine()->getShaders()["shader_fog"];
	this->space = space;

	vector<objl::Mesh> model = space->getEngine()->getModels()[modelName];

	Quaternion orientation = Quaternion::identity();
	Transform transform(initPosition, orientation);

	for (auto mesh: model)
		for (int i = 0; i < mesh.Vertices.size(); i++) {
			vertices.push_back(mesh.Vertices[i].Position.X * scale);
			vertices.push_back(mesh.Vertices[i].Position.Y * scale);
			vertices.push_back(mesh.Vertices[i].Position.Z * scale);
			vertices.push_back(mesh.Vertices[i].TextureCoordinate.X);
			vertices.push_back(mesh.Vertices[i].TextureCoordinate.Y);
		}
	
	body = space->getWorld()->createRigidBody(transform);
	
	Transform t;
	CollisionShape* e = genereateBoindingBox(t);

	body->addCollider(e, t);
	body->getCollider(0)->setCollisionCategoryBits(0x0001);
	body->getCollider(0)->setCollideWithMaskBits(0x0001);
	body->updateLocalCenterOfMassFromColliders();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(GLfloat)));
	model_id = glGetUniformLocation(this->shader, "model");
	position_id = glGetUniformLocation(this->shader, "projection");
	view_id = glGetUniformLocation(this->shader, "view");
	tex_id = glGetUniformLocation(this->shader, "tex");
	pos_id = glGetUniformLocation(this->shader, "pos");
	fog_id = glGetUniformLocation(this->shader, "fog");

	CameraEye = glGetUniformLocation(this->shader, "CameraEye");
	glActiveTexture(texture);
}

Entitie::~Entitie()
{
	//delete this->body;
}

void Entitie::deleteData()
{
	space->getWorld()->destroyRigidBody(body);
	glDeleteBuffers(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Entitie::rotateX(const float degrees) {
	orientation[0] = orientation[0] + degrees;
	Matrix3x3 m = {
		1, 0, 0,
		0, cos(orientation[0]), -sin(orientation[0]),
		0, sin(orientation[0]), cos(orientation[0])
	};
	body->setTransform(Transform(body->getTransform().getPosition(), m));
}

void Entitie::rotateY(const float degrees) {
	orientation[1] = orientation[1] + degrees;
	Matrix3x3 m = Matrix3x3(cos(orientation[1]), 0, sin(orientation[1]),
		0, 1, 0,
		-sin(orientation[1]), 0, cos(orientation[1]));
	body->setTransform(Transform(body->getTransform().getPosition(), m));
}

void Entitie::rotateZ(const float degrees) {
	orientation[2] = orientation[2] + degrees;
	Matrix3x3 m = Matrix3x3(cos(orientation[2]), -sin(orientation[2]), 0,
		sin(orientation[2]), cos(orientation[2]), 0,
		0, 0, 1);
	body->setTransform(Transform(body->getTransform().getPosition(), m));
}

void Entitie::movePosition(const Vector3& v) {
	body->setTransform(Transform(body->getTransform().getPosition() + v, Quaternion::identity()));
}

void Entitie::render(Camera* camera, int MAX_RENDER)
{
	if (!Distance(camera->getPosition(), body->getTransform().getPosition(), MAX_RENDER)) return;

	mat4 p = camera->getProyectionMatrix();
	mat4 v = camera->getViewMatrix();

	float m[16];
	body->getTransform().getOpenGLMatrix(m);

	glUseProgram(shader);
	glBindTexture(GL_TEXTURE_2D, texture);

	glUniformMatrix4fv(view_id, 1, GL_FALSE, &v[0][0]);
	glUniformMatrix4fv(position_id, 1, GL_FALSE, &p[0][0]);
	glUniformMatrix4fv(model_id, 1, GL_FALSE, &m[0]);

	glUniform3fv(CameraEye, 1, &camera->getPosition()[0]);
	glUniform3fv(pos_id, 1, &body->getTransform().getPosition()[0]);

	glUniform1i(tex_id, 0);
	glUniform1i(fog_id, fog);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(GLfloat)));

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
}

RigidBody* Entitie::getBody()
{
	return body;
}
