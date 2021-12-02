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

	void render();
	void update();


private:

	Camera* hudCamera;

	Vector3 positions[6] = { Vector3(0.15, 0.048, -0.075), Vector3(0.15, 0.048, -0.085), 
		Vector3(0.15, 0.048, 0.085), Vector3(0.15, 0.048, 0.075),
		Vector3(0.15, 0.05, 0.003), Vector3(0.15, 0.05, -0.003) };

	float scale[6] = { 0.006, 0.006, 0.006, 0.006, 0.004, 0.004 };

	//vector<Entitie*> right_you, left_you, right_enemy, left_enemy, right_objective, left_objective;
	vector<vector<Entitie*>> vectors_numeros;

	vector<Entitie*> hudElements, scores;

	int you_score, enemy_score, objective_score;

	void updateYouScore();
	void updateEnemyScore();
	void updateObjectiveScore();
};
