#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include <string>
#include <vector>
#include <glm.hpp>

class Model {
public:
	std::vector<glm::vec3> out_vertices;
	std::vector<glm::vec2> out_uvs;
	std::vector<glm::vec3> out_normals;
	Model(std::vector<glm::vec3> a, std::vector<glm::vec2> b, std::vector<glm::vec3> c) {
		out_vertices = a; out_uvs = b; out_normals = c;
	}
	Model() {}
};

bool loadOBJ(
	const char* path,
	std::vector<glm::vec3>& out_vertices,
	std::vector<glm::vec2>& out_uvs,
	std::vector<glm::vec3>& out_normals
);