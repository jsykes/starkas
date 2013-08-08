/*
 *  Player.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"
#include "sound.h"

#define PI (3.14159265358979323846264338327)

class Player: public Ship
{
public:

	Player(SpriteInfo * _spriteInfo);
	virtual ~Player();
	
	// Accessors
	void InGameInput(BulletManager *bulletManager, OamState * oam);
	void AwardPoints(int number);
	void SetEnemiesKilled(int number);
	void SetMaxEnemiesToBoss(int number);
	void SetScore(int number);
	
	int  GetEnemiesKilled();
	int  GetMaxEnemiesToBoss();
	int  ReturnScore();

	// Abilities
	void StrafeLeft();
	void StrafeRight();
	void ResetAll();
	
private:

	int enemiesKilled, maxEnemiesToBoss, score;

protected:

	int strafeRadians;
	
};

#endif