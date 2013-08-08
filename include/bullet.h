/*
 *  Bullet.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class Bullet
{
private:

		// Position of bullet, velocity, id number, bounding sphere position, owner.
		int posX, posY, velocityX, velocityY, id, sPositionX, sPositionY, owner;
		
		// Radius of the bounding sphere
		float sRadius;	
		
		// Bullet vital status
		bool isDead;
		
		// SpriteEntry to input and update the graphic for render
		SpriteEntry * spriteEntry;

		
public:

		Bullet(int id, int _owner, SpriteEntry * _spriteEntry, int _posX, int _posY, int _velocityX, int _velocityY);
		~Bullet();	
		
		void Update();
		void SetIsDead(bool value);
		void SetBounds(int sPositionX, int sPositionY, int sRadius);
		void SetOwner(int value);
		void Create(int xPos, int yPos, int velocityX, int velocityY);
		void Reset();
		void SetPositionX(int value);
		void SetPositionY(int value);
		
		int GetOwner();
		int GetRadius();
		int GetID();
		int GetPositionX();
		int GetPositionY();
		int GetSPositionX();
		int GetSPositionY();
		
		bool GetIsDead();
};

#endif