#include "Labyrinth.h"

Labyrinth::Labyrinth(GameSpace* space)
{
	this->space = space;
	vector<vector<char>> map = generateMap();
	this->graph = CGraph(map);
}

vector<vector<char>> Labyrinth::generateMap()
{
	vector<vector<vector<int>>> zone = {
{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}} };

	float y = 0.0f;
	for (int m = 0; m < zone.size(); m++) {
		float z = 0.0f;
		for (int i = 0; i < zone[m].size(); i++) {
			float x = 0.0f;
			for (int j = 0; j < zone[m][i].size(); j++) {
				if (zone[m][i][j] != 0) {
					cubes.push_back(Cube(space, zone[m][i][j], Vector3(x, y, z)));
				}
				x += 1.0f;
			}
			z += 1.0f;
		}
		y += 1.0f;
	}

	vector<vector<char>> map;
	vector<char> v0 = { '#','#' ,'#' };
	map.push_back(v0);
	vector<char> v1 = { '#','E' ,'#' };
	map.push_back(v1);
	vector<char> v2 = { '#','#' ,'#' };
	map.push_back(v2);
	
	return map;
}

void Labyrinth::render(Camera* camera)
{
	for (auto cube : cubes)
		cube.render(camera);
}

CGraph Labyrinth::getGraph()
{
	return this->graph;
}
