#include "Labyrinth.h"

#include "KeyEnemy.h"
#include "KeyActor.h"

#include "GameSpace.h"
#include "Engine.h"


Labyrinth::Labyrinth(GameSpace* space, int width, int height, const int n_keys, const int algorithm)
{
	this->space = space;
	this->m_width = width;
	this->m_height = height;

	generateMaze();
	generateVisits(n_keys,'K');
	this->graph = CGraph(m_maze, algorithm);
	generateVisits(n_keys, 'A');
	cout << "Total vertices: " << this->graph.enemyRoute.size() << endl;
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

vector<int> Labyrinth::getEndPosition()
{
	return this->m_endPosition;
}

vector<pair<int, int>> Labyrinth::getEnemyRoute()
{
	return this->graph.enemyRoute;
}

void Labyrinth::generateMap()
{
	for (int i = 0; i < m_maze.size(); i++) {
		for (int j = 0; j < m_maze[i].size(); j++) {
			if (m_maze[i][j] == '#') {
				cubes.push_back(Cube(space, 2, Vector3(j, 1.0f, i)));
				cubes.push_back(Cube(space, 2, Vector3(j, 2.0f, i)));
			}
			else if (m_maze[i][j] == 'K' || m_maze[i][j] == 'S') {
				cubes.push_back(Cube(space, 1, Vector3(j, 0.0f, i)));
				KeyEnemy* ka = new KeyEnemy(this->space, Vector3(j, 0.75, i));
				enemyKeys.push_back(ka);
				this->space->add_entitie(new KeyEnemy(this->space, Vector3(j, 0.75, i)));
			}
			else if (m_maze[i][j] == 'A') {
				cubes.push_back(Cube(space, 1, Vector3(j, 0.0f, i)));
				this->space->add_entitie(new KeyActor(this->space, Vector3(j, 0.75, i)));
			}
			else {
				cubes.push_back(Cube(space, 1, Vector3(j, 0.0f, i)));
			}
		}
	}
}

void Labyrinth::generateVisits(const int n_keys,const char representar)
{
	srand((unsigned)time(NULL));
	queue<int> limit;

	int x, y = 0;
	int length = round(m_width / n_keys);

	for (int i = length; i < m_width - 1; i += length) { 
		if (limit.size() != n_keys) { limit.push(i); }
		else { break; }
	}
	if (limit.size() != n_keys) { limit.push(m_width - 2); }

	int anterior = 1;
	while (!limit.empty()) {
		do {
			x = rand() % (limit.front() - anterior + 1) + anterior;
			y = 1 + rand() % (m_height - 1);
		} while (m_maze[y][x] != '1' && m_maze[y][x] != 'V');

		anterior = limit.front();
		limit.pop();
		m_maze[y][x] = representar;
		if (representar == 'A')
			cout << "Y:" << y << "X:" << x << endl;;
	}
}

void Labyrinth::generateMaze()
{
	srand((unsigned)time(NULL));

	int x_start, y_start, x_end, y_end;
	vector<pair<int, int>> frontiers;
	vector<pair<int, int>> neighbours;
	
	m_maze.resize(m_height);
	for (int i = 0; i < m_maze.size(); i++) { m_maze[i].resize(m_width, '#'); }

	x_start = 1 + rand() % (m_height - 1);
	y_start = 1 + rand() % (m_width - 1);

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

	this->m_height = this->m_maze.size();
	this->m_width = this->m_maze.size();

	do {
		x_start = 1 + rand() % (m_width - 1);
		y_start = 1 + rand() % (m_height - 1);
	} while (m_maze[x_start][y_start] != '1');


	m_maze[x_start][y_start] = 'E';
	this->m_initialPosition = { y_start, x_start };

	do {
		x_end = 1 + rand() % (m_width - 1);
		y_end = 1 + rand() % (m_height - 1);
	} while (m_maze[x_end][y_end] != '1');

	m_maze[x_end][y_end] = 'S';
	this->m_endPosition = { y_end, x_end };
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