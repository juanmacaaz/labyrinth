#include "Labyrinth.h"

Labyrinth::Labyrinth(GameSpace* space, int width, int height)
{
	this->space = space;
	this->m_width = width;
	this->m_height = height;

	generateMaze();
	this->graph = CGraph(m_maze);

	generateMap();
	
	
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

vector<vector<char>> Labyrinth::getMaze()
{
	return this->m_maze;
}

void Labyrinth::generateMap()
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
}

void Labyrinth::generateMaze()
{
	m_maze.resize(m_height);
	for (int i = 0; i < m_maze.size(); i++) { m_maze[i].resize(m_width, '#'); }

	vector<pair<int, int>> frontiers;
	vector<pair<int, int>> neighbours;

	srand((unsigned)time(NULL));

	int x_start = 1 + rand() % (m_height - 1);
	int y_start = 1 + rand() % (m_width - 1);
	int x_end = 1 + rand() % (m_height - 1);
	int y_end = 1 + rand() % (m_width - 1);

	frontiers.push_back(make_pair(x_start, y_start));
	neighbours.push_back(make_pair(x_start, y_start));

	while (!frontiers.empty()) {
		int n = rand() % (frontiers.size());
		pair<int, int> frontier = frontiers[n];
		pair<int, int> neighbour = neighbours[n];

		frontiers.erase(frontiers.begin() + n);
		neighbours.erase(neighbours.begin() + n);

		if (m_maze[frontier.first][frontier.second] == '#') {

			m_maze[frontier.first][frontier.second] = '1';
			m_maze[neighbour.first][neighbour.second] = '1';

			getFrontierUp(frontier.first, frontier.second, frontiers, neighbours);
			getFrontierRight(frontier.first, frontier.second, frontiers, neighbours);
			getFrontierDown(frontier.first, frontier.second, frontiers, neighbours);
			getFrontierLeft(frontier.first, frontier.second, frontiers, neighbours);
		}

	}
	m_maze[x_start][y_start] = 'E';

	while (m_maze[x_end][y_end] == '#' || m_maze[x_end][y_end] == 'E') {
		x_end = 1 + rand() % (m_height - 1);
		y_end = 1 + rand() % (m_width - 1);
	}

	m_maze[x_end][y_end] = 'S';
}

void Labyrinth::getFrontierUp(int i, const int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours) {
	if (i >= 2) {
		if (m_maze[i - 2][j] == '#') {
			frontiers.push_back(make_pair(i - 2, j));
			neighbours.push_back(make_pair(i - 1, j));
		}

	}
}

void Labyrinth::getFrontierRight(const int i, int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours) {
	if (j < m_maze[i].size() - 2) {
		if (m_maze[i][j + 2] == '#') {
			frontiers.push_back(make_pair(i, j + 2));
			neighbours.push_back(make_pair(i, j + 1));
		}

	}
}

void Labyrinth::getFrontierDown(int i, const int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours) {
	if (i < m_maze.size() - 2) {
		if (m_maze[i + 2][j] == '#') {
			frontiers.push_back(make_pair(i + 2, j));
			neighbours.push_back(make_pair(i + 1, j));
		}

	}
}

void Labyrinth::getFrontierLeft(const int i, int j, vector<pair<int, int>>& frontiers, vector<pair<int, int>>& neighbours) {
	if (j >= 2) {
		if (m_maze[i][j - 2] == '#') {
			frontiers.push_back(make_pair(i, j - 2));
			neighbours.push_back(make_pair(i, j - 1));
		}

	}
}

void Labyrinth::repairUp() {
	bool repair = false;
	for (int i = 0; i < m_width; i++) {
		if (m_maze[0][i] != '#') {
			repair = true;
		}
	}

	if (repair) {
		vector<char> fila(m_maze[0].size(), '#');
		m_maze.insert(m_maze.begin(), fila);
	}
}

void Labyrinth::repairRight() {
	bool repair = false;
	for (int i = 0; i < m_maze.size(); i++) {
		if (m_maze[i][m_maze[i].size() - 1] != '#') {
			repair = true;
			break;
		}
	}

	if (repair) {
		for (int i = 0; i < m_maze.size(); i++) {
			m_maze[i].push_back('#');
		}
	}
}

void Labyrinth::repairDown() {
	bool repair = false;
	for (int i = 0; i < m_width; i++) {
		if (m_maze[m_maze.size() - 1][i] != '#') {
			repair = true;
			break;
		}
	}

	if (repair) {
		vector<char> fila(m_maze[m_maze.size() - 1].size(), '#');
		m_maze.push_back(fila);
	}
}


void Labyrinth::repairLeft() {
	bool repair = false;
	for (int i = 0; i < m_maze.size(); i++) {
		if (m_maze[i][0] != '#') {
			repair = true;
			break;
		}
	}

	if (repair) {
		for (int i = 0; i < m_maze.size(); i++) {
			m_maze[i].insert(m_maze[i].begin(), '#');
		}
	}
}
