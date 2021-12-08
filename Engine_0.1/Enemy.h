#pragma once
#include "Entitie.h"

class GameSpace;
class KeyEnemy;

class Enemy :
    public Entitie
{
private:

	GameSpace* space;
	float velocity;
	int visita_pos;
	long timer;
	int n_keys;

public:

	Enemy(GameSpace* space, Vector3 initPosition, int n_keys);
	bool moveTo(float x, float y);
	void update();
	void nextPosition();
	int getPosition();
	void setEnemyVelocity(float vel);
	float getEnemyVelocity();
	CollisionBody* getBody();
};

