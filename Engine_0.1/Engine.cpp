#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "GameSpace.h"
#include "MenuSpace.h"
#include "HudSpace.h"
#include "Space.h"

vector<objl::Mesh>& loadModel2(const char* imagepath, objl::Loader* Loader);
unsigned int loadCubemap(vector<std::string> faces);

Engine::Engine()
{
	initGlfwGL();
	loadShaders();
	loadTextures("textures\\uncompressed\\wall-min.jpg", "textures\\uncompressed\\bedrock.jpg");
	loadModels();
	loadModels(0);

	loadSkymap(0);
	accumulator = 0;

	menuSpace = new MenuSpace(this);
	hudSpace = new HudSpace(this);
	currentSpace = menuSpace;

	//models.clear();
}

Engine::~Engine()
{

}

int Engine::run()
{
	double lasttime = glfwGetTime();
	glUseProgram(shader["basic-nolight"]);

	//glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		double elapseTime = currentTime - lasttime;
		lasttime = currentTime;

		accumulator += elapseTime;
		if (accumulator >= 1.0 / 60.0) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			currentSpace->update();

			renderSkybox();
			if (currentSpace == gameSpace) {
				hudSpace->render();
			}

			currentSpace->render();

			glfwSwapBuffers(window);
			glfwPollEvents();
			accumulator = 0;
		}
		
	}

	glfwTerminate();
	return 0;
}

map<string, GLuint> Engine::getShaders()
{
	return shader;
}

map<int, GLuint> Engine::getTextures()
{
	return texture;
}

map<string, vector<objl::Mesh>> Engine::getModels()
{
	return models;
}

GLFWwindow* Engine::getEngineWindow()
{
	return window;
}

int Engine::getWWidth()
{
	return w_width;
}

int Engine::getWHeight()
{
	return w_height;
}

void Engine::initGameSpace(Dificultad dificultad) {
	gameSpace = new GameSpace(this, dificultad);
}

void Engine::setGameSpace()
{
	currentSpace = gameSpace;
}

GameSpace* Engine::getGameSpace()
{
	return this->gameSpace;
}

void Engine::setMenuSpace()
{
	currentSpace = menuSpace;
}

void Engine::renderSkybox()
{
	//glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	GLuint projection = glGetUniformLocation(shader["sky-map"], "projection");
	GLuint view = glGetUniformLocation(shader["sky-map"], "view");
	GLuint pos = glGetUniformLocation(shader["sky-map"], "pos");
	GLuint skybox = glGetUniformLocation(shader["sky-map"], "skybox");

	glUniform1i(skybox, 0);

	glUseProgram(shader["sky-map"]);

	glActiveTexture(skyboxTex);
	glBindTexture(GL_TEXTURE_2D, skyboxTex);

	mat4 p = currentSpace->getCamera()->getProyectionMatrix();
	mat4 v = currentSpace->getCamera()->getViewMatrix();

	vec3 posicion = currentSpace->getCamera()->getPosition();

	glUniformMatrix4fv(projection, 1, GL_FALSE, &p[0][0]);
	glUniformMatrix4fv(view, 1, GL_FALSE, &v[0][0]);
	glUniform3fv(pos, 1, &posicion[0]);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDisableVertexAttribArray(0);
	glDepthFunc(GL_LESS);
	//glDepthMask(GL_TRUE);
}

void Engine::loadShaders()
{
	shader["basic-nolight"] = LoadShader("shaders\\shader.vs", "shaders\\shader.fs");
	shader["sky-map"] = LoadShader("shaders\\shader_mtl.vs", "shaders\\shader_mtl.fs");
}

void Engine::loadTextures(const char* wall, const char* floor)
{
	texture[Block::WALL] = loadTexture(wall);
	texture[Block::FLOOR] = loadTexture(floor);
	//manzana y enemigo
	texture[Block::WOOD] = loadTexture("textures\\uncompressed\\madera-min.jpg");
}

void Engine::setTexturas(const int level)
{
	if (level == 0) {
		//castillo
		loadTextures("textures\\uncompressed\\wall-min.jpg", "textures\\uncompressed\\bedrock.jpg");
	}
	else if (level == 1) {
		//jungla
		loadTextures("textures\\uncompressed\\wall-min.jpg", "textures\\uncompressed\\bedrock.jpg");
	}
	else if (level == 2) {
		//desirto
		loadTextures("textures\\uncompressed\\wall-min.jpg", "textures\\uncompressed\\bedrock.jpg");
	}
}

void Engine::loadModels(const int level)
{
	objl::Loader* Loader = new objl::Loader();
	if (level == 0) {
		//castillo
		models["waifu"] = loadModel2("models\\waifu.obj", Loader);
		models["key"] = loadModel2("models\\hud\\key.obj", Loader);
		models["cube"] = loadModel2("models\\cube.obj", Loader);
	}

	else if (level == 1) {
		//jungla
		models["waifu"] = loadModel2("models\\waifu.obj", Loader);
		models["key"] = loadModel2("models\\hud\\banana.obj", Loader);
		models["cube"] = loadModel2("models\\cube.obj", Loader);
	}
	else if (level == 2) {
		//desirto
		models["waifu"] = loadModel2("models\\waifu.obj", Loader);
		models["key"] = loadModel2("models\\hud\\cactus.obj", Loader);
		models["cube"] = loadModel2("models\\cube.obj", Loader);
	}
}

void Engine::loadSkymap(int level)
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	vector<std::string> faces
	{
		"skymap\\right.jpg",
		"skymap\\left.jpg",
		"skymap\\top.jpg",
		"skymap\\bottom.jpg",
		"skymap\\front.jpg",
		"skymap\\back.jpg"
	};

	skyboxTex = loadCubemap(faces);
}


void Engine::loadModels()
{
	objl::Loader* Loader = new objl::Loader();

	//Main Menu Buttons
	models["main_title"] = loadModel2("models\\main_menu\\main_title.obj", Loader);
	models["start_button"] = loadModel2("models\\main_menu\\start_button.obj", Loader);
	models["levels_button"] = loadModel2("models\\main_menu\\levels_button.obj", Loader);
	models["exit_button"] = loadModel2("models\\main_menu\\exit_button.obj", Loader);

	//Levels Menu Buttons
	models["levels_title"] = loadModel2("models\\levels_menu\\levels_title.obj", Loader);
	models["difficulty_text"] = loadModel2("models\\levels_menu\\difficulty_text.obj", Loader);
	models["back_button"] = loadModel2("models\\levels_menu\\back_button.obj", Loader);

	models["low_text"] = loadModel2("models\\levels_menu\\low_text.obj", Loader);
	models["medium_text"] = loadModel2("models\\levels_menu\\medium_text.obj", Loader);
	models["high_text"] = loadModel2("models\\levels_menu\\high_text.obj", Loader);

	models["castle_button"] = loadModel2("models\\levels_menu\\castle_button.obj", Loader);
	models["jungle_button"] = loadModel2("models\\levels_menu\\jungle_button.obj", Loader);
	models["desert_button"] = loadModel2("models\\levels_menu\\desert_button.obj", Loader);

	models["x"] = loadModel2("models\\levels_menu\\x.obj", Loader);

	//Pause Menu
	models["continue_button"] = loadModel2("models\\pause_menu\\continue_button.obj", Loader);
	models["return_main_menu"] = loadModel2("models\\pause_menu\\return_main_menu.obj", Loader);

	//HUD
	models["num_0"] = loadModel2("models\\hud\\numbers\\num_0.obj", Loader);
	models["num_1"] = loadModel2("models\\hud\\numbers\\num_1.obj", Loader);
	models["num_2"] = loadModel2("models\\hud\\numbers\\num_2.obj", Loader);
	models["num_3"] = loadModel2("models\\hud\\numbers\\num_3.obj", Loader);
	models["num_4"] = loadModel2("models\\hud\\numbers\\num_4.obj", Loader);
	models["num_5"] = loadModel2("models\\hud\\numbers\\num_5.obj", Loader);
	models["num_6"] = loadModel2("models\\hud\\numbers\\num_6.obj", Loader);
	models["num_7"] = loadModel2("models\\hud\\numbers\\num_7.obj", Loader);
	models["num_8"] = loadModel2("models\\hud\\numbers\\num_8.obj", Loader);
	models["num_9"] = loadModel2("models\\hud\\numbers\\num_9.obj", Loader);

	models["objective_text"] = loadModel2("models\\hud\\objective_text.obj", Loader);
	models["enemy_text"] = loadModel2("models\\hud\\enemy_text.obj", Loader);
	models["you_text"] = loadModel2("models\\hud\\you_text.obj", Loader);

	//Loading Menu
	models["loading_text"] = loadModel2("models\\extra_menus\\loading_text.obj", Loader);

	//WIN - LOSE
	models["win_text"] = loadModel2("models\\extra_menus\\win_text.obj", Loader);
	models["lose_text"] = loadModel2("models\\extra_menus\\lose_text.obj", Loader);

	//3D models
	models["tower"] = loadModel2("models\\tower.obj", Loader);
	models["palm"] = loadModel2("models\\palm.obj", Loader);
	models["pyramid"] = loadModel2("models\\pyramid.obj", Loader);

	//Materials
	//models["title_material"] = loadModel2("models\\materials\\title.mtl", Loader);
	models["materias"] = loadModel2("models\\box_stack.obj", Loader);
}

void Engine::initGlfwGL()
{
	if (!glfwInit())
		return;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	w_width = mode->width;
	w_height = mode->height;

	//glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(w_width, w_height, "Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = 1;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cout << "glewInit failed: " << glewGetErrorString(err) << std::endl;
		exit(1);
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwPollEvents();
	glfwSetCursorPos(window, w_width / 2, w_height / 2);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint Engine::LoadShader(const char* vertex_file_path, const char* fragment_file_path) {

	// Crear los shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Leer el Vertex Shader desde archivo
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		return 0;
	}

	// Leer el Fragment Shader desde archivo
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compilar Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Revisar Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compilar Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Revisar Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Vincular el programa por medio del ID
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Revisar el programa
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	printf("Compiling shader : %i\n", ProgramID);

	return ProgramID;
}

GLuint Engine::loadTexture(const char* imagepath)
{
	GLuint textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameterf(textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(textureID, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(textureID, GL_TEXTURE_WRAP_T, GL_CLAMP);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(false);

	unsigned char* data = stbi_load(imagepath, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	std::cout << "Loaded:" << textureID << std::endl;
	return textureID;
}

inline vector<objl::Mesh>& loadModel2(const char* imagepath, objl::Loader* Loader)
{
	Loader->LoadFile(imagepath);
	return Loader->LoadedMeshes;
}

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}