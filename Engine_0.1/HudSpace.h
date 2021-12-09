#pragma once
#include "Space.h"

#include <vector>

class Camera;
class Entitie;

enum NUM {
	right_you, left_you, right_enemy, left_enemy, right_objective, left_objective
};

class HudSpace : public Space
{
public:

	HudSpace(Engine* engine);
	~HudSpace();

	void render();
	void update();

	void updateYouScore(int you_score);
	void updateEnemyScore(int enemy_score);
	void updateObjectiveScore(int objective_score);


private:

	Camera* hudCamera;

	Vector3 positions[6] = { Vector3(0.15, 0.048, -0.075), Vector3(0.15, 0.048, -0.085), 
		Vector3(0.15, 0.048, 0.085), Vector3(0.15, 0.048, 0.075),
		Vector3(0.15, 0.05, 0.003), Vector3(0.15, 0.05, -0.003) };

	float scale[6] = { 0.006, 0.006, 0.006, 0.006, 0.004, 0.004 };

	vector<vector<Entitie*>> vectors_numeros;

	vector<Entitie*> hudElements, scores;
};
