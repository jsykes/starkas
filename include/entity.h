/*
 *  Entity.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#ifndef ENTITY_H
#define ENTITY_H

#include "sprites.h"

#define PI (3.14159265358979323846264338327)

template <class T>
struct MathVector2D {
    T x;
    T y;
};

class Entity 
{
public:

    //Provides interface into game engine. Connects object to sprite.
	SpriteInfo * spriteInfo;   

    /* 
     *  Kinematic Dynamics
     *
     *  These variables track dynamic kinematic properties of the ship.
     *  Position and velocity is stored as two dimensional floating-point
     *  vectors (in the mathematical context, not the STL context). The angle
     *  of the ship is stored in radians in a float.
     */
	 
    MathVector2D<float> position;
    MathVector2D<float> velocity;
    float angle, sRadius; //in radians, for the collision sphere
	int sPositionX, sPositionY; // x and y position for sphere center
	
    /*
     *  Kinematic Statics
     *
     *  These variables rarely change. When modified, they can change how the
     *  ship handles. The turning speed is stored in radians as a float. It
     *  should be a relatively small portion of 2 * PI. Thrust, maximum speed,
     *  and the mass of the ship are each stored as floats.
     */
	 
	float turnSpeed;
    float thrust;
    float maxSpeed;
	
	/*
     *  radToDeg
     *
     *  This function converts radians (our unit of choice for measuring
     *  angles) to the libnds degree system. We only use this function from
     *  within the Ship object, so we can make this a protected function.
     */
    int radToDeg(float rad);
	
	
	// Entity Abilities
	void accelerate();
	void move();
	void reverse();
	void turnClockwise();
	void turnCounterClockwise();
	
	
	// Accessors and Initialization
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetVelocityX(float x);
	void SetVelocityY(float y);
	
	MathVector2D<float> GetPosition();
	MathVector2D<float> GetVelocity();
	int GetRadius();
	float GetAngleRad();
    int GetAngleDeg();
	
	void SetBounds(int sPositionX, int sPositionY, int sRadius);
	
};

#endif