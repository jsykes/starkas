/*
 *  Ship.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */

#ifndef SHIP_H
#define SHIP_H

#include <math.h>
#include "bulletManager.h"

class Ship: public Entity
{
private:

	int shields, armor, hull, maxShields, maxArmor, maxHull, atk, def, agi;
	
public:

	// Stores bullet velocity to shoot according to direction faced.
    MathVector2D<float> bulletVelocity;
	
	// Accessors
	void SetAttributes(int atk, int def, int agi, int shields, int hull);
	void SetMaxShields(int value);
	void SetShields(int value);
	void SetArmor(int value);
	void SetHull(int value);
	void SetAtk(int atk);
	void SetDef(int def);
	void SetAgi(int agi);
	
	int  GetShields();
	int  GetArmor();
	int  GetHull();
	int  GetAtk();
	int  GetDef();
	int  GetAgi();
	int  GetMaxShields();
	int  GetMaxArmor();
	int  GetMaxHull();
	
	// Abilities
	void TakeDamage(int value);
	void AddMaxArmor(int value);
	
};

#endif