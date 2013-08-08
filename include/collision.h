/*
 *  Collision.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#ifndef COLLISION_H
#define COLLISION_H
 
#include "enemy.h"
 
 //This is a singleton
class Collision
{
protected:

		Player * player;
		Enemy * enemy1;
		Enemy * enemy2;
		Enemy * enemy3;
		Enemy * enemy5;
		Enemy * enemy6;
		Enemy * enemy7;
	
	
public:

	static Collision* Instance();
		
	// Booleans for what collision took place (for bullets)
	bool playerIsHit, enemyHitByPlayerBullet, prevHit;
		
	// Check for collision (even crashes)
	void CollisionCheck(Player * player, Enemy * enemy);
	void CollisionCheck(Bullet * b);
	void CollisionCheck(Player * player, Enemy * enemy, BulletManager * bulletManager);
	void CollisionCheck(int index, Bullet * b, BulletManager * bulletManager);
	void CollisionBossPlayer(int index, Player * player, Enemy * boss, BulletManager * bulletManager, Bullet * b);


private:

	Collision(){};
	static Collision* m_pInstance;
	
};

#endif