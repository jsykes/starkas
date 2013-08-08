/*
 *  Bullet.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include "bullet.h"

// Constructor
Bullet::Bullet(int _id, int _owner,SpriteEntry * _spriteentry, int _posX, int _posY, int _velocityX, int _velocityY)
{
	spriteEntry = _spriteentry;
	posX = _posX;
	posY = _posY;
	velocityX = _velocityX;
	velocityY = _velocityY;
	isDead = false;
	id = _id;
	owner = _owner;
}

// Destructor
Bullet::~Bullet(){}

void Bullet::Update()
{
	SetBounds(posX+16, posY+16, 8);
	
	posX += velocityX;
	posY += velocityY;

	if ((spriteEntry->x > 240) || (spriteEntry->x < -50) || (spriteEntry->y < -50)
		|| (spriteEntry->y > 220))
	{
		isDead = true;
	}
	
	if(isDead)
	{
		Bullet::Reset();
	}
	else{
	spriteEntry->x = posX;
	spriteEntry->y = posY;}
}

void Bullet::Reset()
{
	posX = 200;
	posY = 200;
	velocityX = 0;
	velocityY = 0;
	spriteEntry->x = posX;
	spriteEntry->y = posY;
}

void Bullet::Create(int xPos, int yPos, int _velocityX, int _velocityY)
{
	posX = xPos;
	posY = yPos;
	velocityX = _velocityX;
	velocityY = _velocityY;
}

void Bullet::SetBounds(int _sPositionX, int _sPositionY, int _sRadius)
{
	sRadius = _sRadius;
}

bool Bullet::GetIsDead() { return isDead; }
void Bullet::SetIsDead( bool value) { isDead = value; }
int Bullet::GetID() { return id; }
int Bullet::GetRadius(){ return sRadius; }
int Bullet::GetOwner() { return owner; }

void Bullet::SetOwner(int value)
{
	owner = value;
}

void Bullet::SetPositionX(int value)
{
	posX = value;
}

void Bullet::SetPositionY(int value)
{
	posY = value;
}

int Bullet::GetPositionX()
{
	return posX;
}

int Bullet::GetPositionY()
{
	return posY;
}

int Bullet::GetSPositionX()
{
	return sPositionX;
}

int Bullet::GetSPositionY()
{
	return sPositionY;
}