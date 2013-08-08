/*
 *  Enemy.h
 *  
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#ifndef ENEMY_H
#define ENEMY_H 

#include "player.h"

#define PI (3.14159265358979323846264338327)

class Enemy: public Ship
{

public:

    Enemy(SpriteInfo * _spriteInfo);
	virtual ~Enemy();
	
	// Resets the enemy 'like making another but reusing'
	// Booleans for start and stop AI, and if it's dead.
	// Engage is to engage the player and attack.
	void Reset(int index, BulletManager * bulletManager);
	bool initAI, stopAI, isDead;
	void Engage(int scheme, BulletManager * bulletManager, Player * player);
	
private:

	// AI
	
	// Timer information
	clock_t endwait;
	float timer;
	
	// Dictates shooting speed, GoTo for movement to point, randoms
	// for random position destination, and booleans for movement and update
	// is for shooting timer.
	void WaitToShoot(bool shootSmart, int seconds, BulletManager * bulletManager, Player * player);
	void GoTo(float x, float y, float speed);
	int randX, randY;
	bool point1, point2, point3, point4, update, newPoint;
	
};

#endif