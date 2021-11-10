#include "Labyrinth.h"

Labyrinth::Labyrinth(GameSpace* space, int width, int height)
{
	this->space = space;
	this->m_width = width;
	this->m_height = height;

	generateMaze();
	this->graph = CGraph(m_maze);

	//generateTestMap();
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

vector<int> Labyrinth::getInitialPosition()
{
	return this->m_initialPosition;
}

void Labyrinth::generateMap()
{
	for (int i = 0; i < m_maze.size(); i++) {
		for (int j = 0; j < m_maze[i].size(); j++) {
			if (m_maze[i][j] == '#') {
				cubes.push_back(Cube(space, 2, Vector3(j, 1.0f, i)));
				cubes.push_back(Cube(space, 2, Vector3(j, 2.0f, i)));
			}
			else if (m_maze[i][j] == '2') { //Para colocar las llaves
				cubes.push_back(Cube(space, 1, Vector3(j, 0.0f, i)));
				cubes.push_back(Cube(space, 5, Vector3(j, 1.0f, i)));
			}
			else {
				cubes.push_back(Cube(space, 1, Vector3(j, 0.0f, i)));
			}
		}
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

	repairUp();
	repairRight();
	repairLeft();
	repairDown();

	do {
		x_start = 1 + rand() % (m_maze.size() - 1);
		y_start = 1 + rand() % (m_maze.size() - 1);
	} while (m_maze[x_start][y_start] == '#' || m_maze[x_start][y_start] == 'E');

	
	m_maze[x_start][y_start] = 'E';
	this->m_initialPosition = { y_start, x_start };

	while (m_maze[x_end][y_end] == '#' || m_maze[x_end][y_end] == 'E') {
		x_end = 1 + rand() % (m_maze.size() - 1);
		y_end = 1 + rand() % (m_maze.size() - 1);
	}

	m_maze[x_end][y_end] = 'S';

}

void Labyrinth::generateTestMap()
{
	vector<vector<vector<int>>> zone = {
{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}} };

	for (int i = 0; i < zone[0].size(); i++) {
		for (int j = 0; j < zone[0][i].size(); j++) {
			cubes.push_back(Cube(space, 1, Vector3(j, 0.0f, i)));
		}
	}
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


vector<vector<int>> Labyrinth::getVisitsPositions(int n_visites) {
	vector<vector<int>> visites;
	vector<bool> visitat(m_maze.size(), false);
	srand((unsigned)time(NULL));
	while (n_visites > 0) {
		int pos = 1 + rand() % m_maze.size() - 1;
		if (!visitat[pos]) {
			for (int i = 0; i < m_maze[pos].size(); i++) {
				if (m_maze[pos][i] == 'V') {
					visites.push_back({ pos,i });
					n_visites--;
					break;
				}
			}
		}
		visitat[pos] = true;
	}
	return visites;
}