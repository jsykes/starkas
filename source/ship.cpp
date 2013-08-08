/*
 *  Ship.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */

#include "ship.h"

void Ship::SetAttributes(int _atk, int _def, int _agi, int _shields, int _hull)
{
	atk = _atk;
	def = _def;
	agi = _agi;
	maxShields = _shields;
	maxArmor = def * 10;
	maxHull = _hull;
	shields = _shields;
	armor = def * 10;
	hull = _hull;
	maxSpeed = (float)agi / 5;
}

int Ship::GetShields(){ return shields; }
int Ship::GetArmor(){ return armor; }
int Ship::GetHull(){ return hull; }
int Ship::GetAtk(){ return atk; }
int Ship::GetDef(){ return def; }
int Ship::GetAgi(){ return agi; }
int Ship::GetMaxShields() { return maxShields; }
int Ship::GetMaxArmor() { return maxArmor; }
int Ship::GetMaxHull() { return maxHull; }
void Ship::SetShields(int value) { shields = value; }
void Ship::SetArmor(int value) { armor = value; }
void Ship::SetHull(int value) { hull = value; }
void Ship::SetAtk(int value){ atk = value; }
void Ship::SetDef(int value){ def = value; maxArmor = def * 10; armor += 10; }
void Ship::SetAgi(int value){ agi = value; maxSpeed = (float)agi / 10; thrust = (float)agi / 10;}
void Ship::SetMaxShields(int value){ maxShields = value;}
void Ship::AddMaxArmor(int value){maxArmor += value;}

void Ship::TakeDamage(int value)
{
	if (shields > 0)
	{
		if (shields < value)
		{
			value = (value - shields);
			shields = 0;
		}
		else
		{
			shields -= value;
			value = 0;
		}
	}
	
	if (value > 0)
	{
		if (armor < value)
		{
			value = (value - armor);
			armor = 0;
		}
		else
		{
			armor -= value;
			value = 0;
		}
	}
	
	if (value > 0)
	{
		if (hull < value)
		{
			value = (value - hull);
			hull = 0;
		}
		else
		{
			hull -= value;
			value = 0;
		}
	}
}