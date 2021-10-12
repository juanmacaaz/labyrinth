#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Space.h"

Engine::Engine()
{
	initGlfwGL();
	loadShaders();
	loadTextures();
	loadModels();

	space = new Space(this);
}

int Engine::run()
{
	double lasttime = glfwGetTime();
	glUseProgram(shader["basic-nolight"]);

	glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		space->update();

		space->render();

		glfwSwapBuffers(window);
		glfwPollEvents();

		while (glfwGetTime() < lasttime + 1.0 / 60);
		lasttime += 1.0 / 60;
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

map<string, Model> Engine::getModels()
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

void Engine::loadShaders()
{
	shader["basic-nolight"] = LoadShader("shaders\\shader.vs", "shaders\\shader.fs");
}

void Engine::loadTextures()
{
	texture[Block::WHITE] = loadTexture("textures\\uncompressed\\White.jpg");
	texture[Block::WOOD] = loadTexture("textures\\uncompressed\\madera.jpg");
	texture[Block::BOX] = loadTexture("textures\\uncompressed\\container.jpg");
	texture[Block::WALL] = loadTexture("textures\\uncompressed\\wall.jpg");
	//texture[Block::KEY] = loadTexture("textures\\uncompressed\\ceramica.jpg");
}

void Engine::loadModels()
{
	models["waifu"] = loadModel("models\\waifu.obj");
	models["cube"] = loadModel("models\\cube.obj");
	models["key"] = loadModel("models\\plastic_chair.obj");
}

void Engine::initGlfwGL()
{
	if (!glfwInit())
		return;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	w_width = mode->width;
	w_height = mode->height;

	glfwWindowHint(GLFW_SAMPLES, 8);
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
	stbi_set_flip_vertically_on_load(true);

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

Model Engine::loadModel(const char* modelDir)
{
	vector<glm::vec3> out_vertices;
	vector<glm::vec2> out_uvs;
	vector<glm::vec3> out_normals;
	loadOBJ(modelDir, out_vertices, out_uvs, out_normals);
	return Model( out_vertices , out_uvs , out_normals );
}
