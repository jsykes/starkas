/*
 *  BulletManager.h
 *
 *  Created by John Sykes & Daniel O'Sullavan on 5/13/10.
 *  Copyright 2010.
 *
 */
 
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <list>
#include "bullet.h"
#include "render.h"

class BulletManager
{
protected:

	// SpriteInfo for render, the OAM used, pointer to render object.
	SpriteInfo * spriteInfo;
	OamState * oam;
	Render * render;
	
	// Random bullet sound effects
	int randomBulletSound;
	
	// The id that points to object, the next id, the player bullet speeds, enemy bullet speeds, enemy bullet count, and ID for render
	int idCount, nextID, pBulletMax, pBulletCount, eBulletMax, eBulletCount, entityID;
	bool interrupt;
	
	// Player and enemy bullet position
	int pX, pY, eX, eY;

public:

	BulletManager(SpriteInfo * _spriteinfo,  OamState * oam);
	~BulletManager();
	
	// Lists to manage bullets & Iterators for bullets and id numbers
	std::list<Bullet> bulletList;
	std::list<Bullet>::iterator I;
	std::list<int> availableID;
	std::list<int>::iterator J;

	// Create and update bullets, call game over if needed.
	void CreateBullet(int entityID, float xPos, float yPos, float bulletVelocityX, float bulletVelocityY);
	void UpdateBullets();
	void GameOverReset();

};


#endif