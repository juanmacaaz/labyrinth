#include "Space.h"

#include "Engine.h"
#include "Engine.h"
#include "Entitie.h"

Space::Space(Engine* engine)
{
	this->engine = engine;
}

void Space::update()
{
	//world->update(1.0f / 60.0f);
}

PhysicsWorld* Space::getWorld()
{
	return world;
}

Engine* Space::getEngine()
{
	return engine;
}

GLFWwindow* Space::getWindow()
{
	return engine->getEngineWindow();
}

PhysicsCommon& Space::getPC()
{
	return pc;
}

void Space::isPressed() {
	if (glfwGetKey(this->getWindow(), GLFW_KEY_LEFT) == GLFW_RELEASE && glfwGetKey(this->getWindow(), GLFW_KEY_RIGHT) == GLFW_RELEASE &&
		glfwGetKey(this->getWindow(), GLFW_KEY_UP) == GLFW_RELEASE && glfwGetKey(this->getWindow(), GLFW_KEY_DOWN) == GLFW_RELEASE &&
		glfwGetKey(this->getWindow(), GLFW_KEY_ENTER) == GLFW_RELEASE && glfwGetKey(this->getWindow(), GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		press = false;
}

void Space::deleteEntitie(Entitie* entitie)
{
	// 
}

void Space::render()
{
	// Aqui se llamaria a los metodos render
}