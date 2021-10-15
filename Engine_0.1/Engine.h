#pragma once

#include <map>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "read_model.h"

using namespace std;

class MenuSpace;
class GameSpace;

enum Block
{
	WHITE = 1,
	WALL = 2,
	BOX = 3,
	WOOD = 4,
	KEY = 5
};

class Engine
{
public:

	Engine();
	int run();

	map<string, GLuint> getShaders();
	map<int, GLuint> getTextures();
	map<string, Model> getModels();
	GLFWwindow* getEngineWindow();
	int getWWidth();
	int getWHeight();

private:

	// Atributos
	GLFWwindow* window;
	map<string, GLuint> shader;
	map<int, GLuint> texture;
	map<string, Model> models;
	GameSpace* gameSpace;
	MenuSpace* menuSpace;
	int w_width, w_height;
	
	// Funciones privadas
	void loadShaders();
	void loadTextures();
	void loadModels();

	void initGlfwGL();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path);
	GLuint loadTexture(const char* imagepath);
	struct Model loadModel(const char* imagepath);
};

