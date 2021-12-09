#include "HudSpace.h"
#include "Engine.h"
#include "Entitie.h"

HudSpace::HudSpace(Engine* engine) : Space(engine) 
{
	PhysicsWorld::WorldSettings settings;
	settings.gravity = Vector3(0, -9.8f, 0);

	world = pc.createPhysicsWorld(settings);



	ProjectionData proyectionData = { 45.0f, 0.01f, 100.0f, this->engine->getWWidth() , this->engine->getWHeight() };

	hudCamera = new Camera(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), proyectionData, this->engine->getWWidth(), this->engine->getWHeight());

	for (int i = 0; i < 6; i++) {
		vector<Entitie*> nombre_calquiera;
		for (int j = 0; j < 10; j++) {
			nombre_calquiera.push_back(new Entitie(this, "num_"+std::to_string(j), Block::FLOOR, "basic-nolight", positions[i], scale[i]));
		}
		vectors_numeros.push_back(nombre_calquiera);
	}

	//YOU SCORE
	hudElements.push_back(new Entitie(this, "key_model", Block::FLOOR, "basic-nolight", Vector3(0.15, 0.048, -0.065), 0.08));
	hudElements.push_back(new Entitie(this, "you_text", Block::FLOOR, "basic-nolight", Vector3(0.15, 0.058, -0.08), 0.002));

	//ENEMY SCORE	
	hudElements.push_back(new Entitie(this, "key_model", Block::FLOOR, "basic-nolight", Vector3(0.15, 0.048, 0.065), 0.08));
	hudElements.push_back(new Entitie(this, "enemy_text", Block::FLOOR, "basic-nolight", Vector3(0.15, 0.058, 0.08), 0.002));

	//OBJECTIVE SCORE	
	hudElements.push_back(new Entitie(this, "objective_text", Block::FLOOR, "basic-nolight", Vector3(0.15, 0.058, 0.0), 0.002));

	for (int i = 0; i < 6; i++) {
		scores.push_back(vectors_numeros[i][0]);
	}
}

void HudSpace::render() {
	for (auto e : hudElements) e->render(hudCamera);
	for (auto s : scores) s->render(hudCamera);
}

void HudSpace::update() {

}


void HudSpace::updateYouScore(int you_score) {
	int left_number = 0;
	int right_number = you_score % 10;

	if (you_score >= 10)
		left_number = you_score / 10 % 10;

	scores[0] = vectors_numeros[NUM::right_you][right_number];
	scores[1] = vectors_numeros[NUM::left_you][left_number];
}

void HudSpace::updateEnemyScore(int enemy_score) {
	int left_number = 0;
	int right_number = enemy_score % 10;

	if (enemy_score >= 10)
		left_number = enemy_score / 10 % 10;

	scores[2] = vectors_numeros[NUM::right_enemy][right_number];
	scores[3] = vectors_numeros[NUM::left_enemy][left_number];
}

void HudSpace::updateObjectiveScore(int objective_score) {
	int left_number = 0;
	int right_number = objective_score % 10;

	if (objective_score >= 10)
		left_number = objective_score / 10 % 10;

	scores[4] = vectors_numeros[NUM::right_objective][right_number];
	scores[5] = vectors_numeros[NUM::left_objective][left_number];
}

