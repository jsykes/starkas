/*
 *  Player.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include "player.h"

Player::Player(SpriteInfo * _spriteInfo)
{
	enemiesKilled = 0;
	
    spriteInfo = _spriteInfo;
	
    /* Stop the ship from moving */
	velocity.x = 0;
	velocity.y = 0;

    /* Point the ship at a cool angle. */
	angle = 5.67232007;
	
    /* Set up some sane kinematic static properties. */
	turnSpeed = .0368;
	thrust = .05;
	maxSpeed = 1.0;
	score = 0;
}
 
Player::~Player()
{}

void Player::StrafeLeft()
{
	strafeRadians = angle -90;
	float incX = thrust * sin(strafeRadians);
	float incY = -(thrust * cos(strafeRadians));
	
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

void Player::StrafeRight()
{
	strafeRadians = angle +90;
	float incX = thrust * sin(strafeRadians);
	float incY = -(thrust * cos(strafeRadians));
	
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

void Player::InGameInput(BulletManager *bulletManager, OamState * oam)
{

    /* Handle up and down parts of D-Pad. */
    if (keysDown() & KEY_UP) {
        // Play our sound only when the button is initially pressed
		//mmEffect(SFX_THRUST);
    }
	if (keysHeld() & KEY_UP) {
		//accelerate ship
		accelerate();
	}
	else
		{
			velocity.x *= 0.95;
			velocity.y *= 0.95;
		}
	
	if (keysHeld() & KEY_DOWN) {
		//reverse ship direction
		reverse();
    }
	
    /* Handle left and right parts of D-Pad. */
	if (keysHeld() & KEY_LEFT) {
		//rotate counter clockwise
		turnCounterClockwise();
    } else if (keysHeld() & KEY_RIGHT) {
		//rotate clockwise
		turnClockwise();
	}
	
	if (keysHeld() & KEY_L)
	{
		StrafeLeft();
	}
	
	if (keysHeld() & KEY_R)
	{
		StrafeRight();
	}
	bulletVelocity.x = (3 * (sin(GetAngleDeg()         //determine which way facing to shoot
			   * (2 * PI / DEGREES_IN_CIRCLE))));
	bulletVelocity.y = (3 *(-cos(GetAngleDeg() 
			   * (2 * PI / DEGREES_IN_CIRCLE))));


	/* Shoot if A is pressed */
	if (keysDown() & KEY_A) {
		bulletManager->CreateBullet(1, position.x, position.y, bulletVelocity.x, bulletVelocity.y);
	}
	
	if (!keysDown() & KEY_UP){
	velocity.x *= 0.95;
	velocity.y *= 0.95;}
	
	if (keysDown() & KEY_B) {
	}
}

int Player::GetEnemiesKilled()
{
	return enemiesKilled;
}

void Player::SetEnemiesKilled(int number)
{
	enemiesKilled++;
}

int Player::GetMaxEnemiesToBoss()
{
	return maxEnemiesToBoss;
}

void Player::SetMaxEnemiesToBoss(int number)
{
	maxEnemiesToBoss = number;
}

void Player::AwardPoints(int number){score += number;}
int Player::ReturnScore(){return score;}
void Player::SetScore(int number){score = number;}

void Player::ResetAll()
{
	position.x = -32;
	position.y = -32;
	maxEnemiesToBoss = 3;
	enemiesKilled = 0;
	SetHull(GetMaxHull());
	SetArmor(GetMaxArmor());
	SetShields(GetMaxShields());
	score = 0;
	SetAtk(10);
	SetDef(2);
	SetAgi(6);
	maxSpeed = ((float)GetAgi() / 5);
}