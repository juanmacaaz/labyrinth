#include "Cube.h"

#include "Common.h"
#include <gtc/type_ptr.hpp>

void Cube::fillVertices(Vector3 p)
{
    vertices = {
         -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

}

void Cube::render(Camera* camera)
{
    GLuint gWVP = glGetUniformLocation(shader, "gWVP");
    GLuint tex = glGetUniformLocation(shader, "tex");

    mat4 p = camera->getProyectionMatrix();
    mat4 v = camera->getViewMatrix();

    float t[16];

    body->getTransform().getOpenGLMatrix(t);
    mat4 test = glm::make_mat4(t);
    mat4 w = p * v * test;

    glUseProgram(shader);

    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glUniformMatrix4fv(gWVP, 1, GL_FALSE, &w[0][0]);
    glUniform1i(tex, 0);

    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


Cube::Cube(PhysicsWorld* world, GLuint texture, GLuint shader, Vector3 initPosition, BodyType bodyType)
{
	this->texture = texture;
	this->shader  = shader;

	Quaternion orientation = Quaternion::identity();

	Transform transform(initPosition, orientation);

	const Vector3 halfExtents(0.5f, 0.5f, 0.5f);
	BoxShape* boxShape = Common::getPhysicsInstance().createBoxShape(halfExtents);

	body = world->createRigidBody(transform);

	body->addCollider(boxShape, Transform::identity());
    
    body->setMass(20.3f);
    body->setType(bodyType);

    body->getCollider(0)->getMaterial().setBounciness(0.0f);
    body->getCollider(0)->getMaterial().setFrictionCoefficient(0.0f);

    fillVertices(initPosition);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
}

GLfloat* Cube::getVertices()
{
    return &vertices[0];
}
