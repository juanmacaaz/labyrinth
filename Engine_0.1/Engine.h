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

#include "OBJ_Loader.h"

using namespace std;

class Space;
class MenuSpace;
class GameSpace;
class HudSpace;
struct Dificultad;

enum Block
{
	FLOOR = 1,
	WALL = 2,
	WOOD = 4,
	KEY = 5,
	TOWER = 6,
	PALM = 7,
	PYRAMID = 8,
	EKEY = 9,
};

class Engine
{
public:

	Engine();
	~Engine();
	MenuSpace* getMenuSpace();
	int run();

	map<string, GLuint> getShaders();
	map<int, GLuint> getTextures();
	map<string, vector<objl::Mesh>> getModels();
	GLFWwindow* getEngineWindow();
	void setTexturas(const int level);
	void loadModels(const int level);
	void LoadMusic(const int level);
	void LoadInstructions();
	int levelmusic = 0;
	void LoadCoin(const int level);
	int getWWidth();
	int getWHeight();

	void initGameSpace(Dificultad dificultad);

	void setGameSpace();
	GameSpace* getGameSpace();

	void setMenuSpace();
	void setSkybox(int skymap_new_tex);
	//MenuSpace* getMenuSpace();
	HudSpace* hudSpace;

	void renderSkybox();
	void renderIntrucciones();

	unsigned int skyboxTex_act;

	unsigned int skyboxTex_menu;
	unsigned int skyboxTex_easy;
	unsigned int skyboxTex_medium;
	unsigned int skyboxTex_hard;

	unsigned int instrucciones;
	
	unsigned int fog = 0;

private:
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;

	unsigned int instruccionesVAO;
	unsigned int instruccionesVBO;
	unsigned int instruccionesEBO;
	// Atributos
	GLFWwindow* window;
	map<string, GLuint> shader;
	map<int, GLuint> texture;
	map<string, vector<objl::Mesh>> models;
	GameSpace* gameSpace;
	MenuSpace* menuSpace;

	Space* currentSpace;
	long double accumulator;

	int w_width, w_height;

	// Funciones privadas
	void loadShaders();
	void loadTextures(const char* wall, const char* floor, const char* key, const char* enemy);
	void loadModels();
	void LoadMusicDefault();
	void loadSkymaps();
	void loadImages();
	void initGlfwGL();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLuint LoadShader(const char* vertex_file_path, const char* fragment_file_path);
	GLuint loadTexture(const char* imagepath);
	GLuint loadImatge(const char* imagepath);
};