/*
 *  Entity.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include <math.h>
#include "entity.h"
 
int Entity::radToDeg(float rad)
{
	return (int)(rad * (DEGREES_IN_CIRCLE/(2 * PI)));
}

void Entity::accelerate() {
	
	float incX = thrust * sin(angle);
	float incY = -(thrust * cos(angle));
	
    //the following method of speed limitation is not accurate, traveling
    //diagonally is faster than straight, which is not the desired limitation
	//a more accurate method is needed but is good enough for this game build.
	
	velocity.x += incX;
	//make sure can't go too fast in x direction
	if (velocity.x > maxSpeed) {
		velocity.x = maxSpeed;
	}
	if (velocity.x < -maxSpeed) {
		velocity.x = -maxSpeed;
	}
	
	velocity.y += incY;
	//make sure can't go too fast in y direction
	if (velocity.y > maxSpeed) {
		velocity.y = maxSpeed;
	}
	if (velocity.y < -maxSpeed) {
		velocity.y = -maxSpeed;
	}
}

void Entity::move() {
	//move the ship
	//keep within bounds
	if ((position.x > 0) && (position.x < 220))
		position.x += velocity.x;
	if ((position.y > 0) && (position.y < 160))
		position.y += velocity.y;
	
	if (position.x < 0)
		position.x++;
	if (position.x > 220)
		position.x--;
	if (position.y < 0)
		position.y++;
	if (position.y > 160)
		position.y--;
}

void Entity::reverse() {
	
	float incX = thrust * sin(angle);
	float incY = -(thrust * cos(angle));
	
    //the following method of speed limitation is not accurate, traveling
    //diagonally is faster than straight, which is not the desired limitation
	//a more accurate method is needed but is good enough for this game build.
	
	velocity.x -= incX;
	//make sure can't go too fast in x direction
	if (velocity.x > maxSpeed) {
		velocity.x = maxSpeed;
	}
	if (velocity.x < -maxSpeed) {
		velocity.x = -maxSpeed;
	}
	
	velocity.y -= incY;
	//make sure can't go too fast in y direction
	if (velocity.y > maxSpeed) {
		velocity.y = maxSpeed;
	}
	if (velocity.y < -maxSpeed) {
		velocity.y = -maxSpeed;
	}
}

void Entity::turnClockwise() {
	angle += turnSpeed;
}

void Entity::turnCounterClockwise() {
	angle -= turnSpeed;
}

void Entity::SetBounds(int _sPositionX, int _sPositionY, int _sRadius)
{
	sPositionX = _sPositionX;
	sPositionY = _sPositionY;
	sRadius = _sRadius;
}

MathVector2D<float> Entity::GetPosition() {
	return position;
}
MathVector2D<float> Entity::GetVelocity() {
	return velocity;
}

void Entity::SetPositionX(float x) {
	position.x = x;
}
void Entity::SetPositionY(float y) {
	position.y = y;
}
void Entity::SetVelocityX(float x) {
	velocity.x = x;
}
void Entity::SetVelocityY(float y) {
	velocity.y = y;
}

int Entity::GetAngleDeg() {
	return radToDeg(angle);
}

int Entity::GetRadius(){return sRadius; }