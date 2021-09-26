#pragma once

#include <map>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Space.h"

class Space;

using namespace std;

enum Block
{
	WHITE = 1,
	WALL = 2,
	BOX = 3,
	WOOD = 4
};

class Engine
{
public:

	Engine();
	int run();

	map<string, GLuint> getShaders();
	map<int, GLuint> getTextures();
	GLFWwindow* getEngineWindow();

private:

	// Atributos
	GLFWwindow* window;
	map<string, GLuint> shader;
	map<int, GLuint> texture;
	Space* space;
	
	// Funciones privadas
	void loadShaders();
	void loadTextures();
	void initGlfwGL();

	GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path);
	GLuint loadTexture(const char* imagepath);
};

