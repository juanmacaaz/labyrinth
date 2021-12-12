#pragma once
#include "Entitie.h"

class GameSpace;
class KeyEnemy;
class MenuSpace;

class Enemy :
    public Entitie
{
private:

	GameSpace* space;
	float velocity;
	int visita_pos;
	long timer;
	int n_keys;
	Vector3 initPosition;

public:

	Enemy(GameSpace* space, Vector3 initPosition, int n_keys);
	bool moveTo2(float x, float z);
	bool moveTo(float x, float y);
	void update();
	void nextPosition();
	int getPosition();
	void setEnemyVelocity(float vel);
	float getEnemyVelocity();
	CollisionBody* getBody();
	int n_llave;
};

