/*
 *  Collision.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include "collision.h"

// Global static pointer used to ensure a single instance of the class.
Collision* Collision::m_pInstance = NULL;

// This function is called to create an instance of the class. Calling the
// constructor publicly is not allowed. The constructor is private and is 
// only called by this Instance function

Collision* Collision::Instance()
{
	if(!m_pInstance) // Only allow one instance of class to be generated.
	m_pInstance = new Collision;
	return m_pInstance;
}

void Collision::CollisionBossPlayer(int index, Player * player, Enemy * boss, BulletManager * bulletManager, Bullet * b)
{
	
	if (b->GetOwner() == 1)
	{
		float posX = (b->GetPositionX() - boss->GetPosition().x);
		float posY = (b->GetPositionY() - boss->GetPosition().y);
		float distance = ((posX * posX) + (posY * posY));
		float rDistance = (boss->GetRadius() + b->GetRadius());
		rDistance = (rDistance * rDistance);
		
		if (distance < rDistance)
		{
			if (!enemyHitByPlayerBullet)
			{
				enemyHitByPlayerBullet = true;
				// bullet hit enemy1
				boss->TakeDamage(player->GetAtk());
				b->SetIsDead(true);
				b->Reset();
				mmEffect(SFX_SHIPHIT);
				
				
				if (boss->GetHull() <= 0)
				{
					mmEffect(SFX_EXPLOSION);
					boss->Reset(2, bulletManager);
					boss->initAI = false;
					player->SetEnemiesKilled(1);
					boss->isDead = true;
					
					if (index == 1)
						player->AwardPoints(100);
					if (index == 2)
						player->AwardPoints(500);
				}
			}
		}
		else
			enemyHitByPlayerBullet = false;
	}
	
	if (b->GetOwner() == 2)
	{
		float posX = (b->GetSPositionX() - player->sPositionX);
		float posY = (b->GetSPositionY() - player->sPositionY);
		float distance = ((posX * posX) + (posY * posY));
		float rDistance = (player->GetRadius() + b->GetRadius());
		rDistance = (rDistance * rDistance);
		
		if (distance < rDistance)
		{
			if (!playerIsHit)
			{
				mmEffect(SFX_SHIPHIT);
				playerIsHit = true;
				// bullet hit enemy1
				player->TakeDamage(boss->GetAtk());
				b->SetIsDead(true);
				b->Reset();			
			}
		}
		else
			playerIsHit = false;
	}
	
	float posX = (player->sPositionX - boss->sPositionX);
	float posY = (player->sPositionY - boss->sPositionY);
	float distance = ((posX * posX) + (posY * posY));
	float rDistance = (boss->GetRadius() + player->GetRadius());
	rDistance = (rDistance * rDistance);
	
	if (distance < rDistance)
	{
		if (!prevHit)
		{
			prevHit = true;
			// player hit enemy
			
			mmEffect(SFX_SHIPHIT);
			player->TakeDamage(boss->GetAtk());			
			boss->TakeDamage(player->GetAtk());
			
			if (boss->GetHull() <= 0)
			{
				mmEffect(SFX_EXPLOSION);
				boss->isDead = true;
				boss->Reset(2, bulletManager);
				boss->initAI = false;
				player->SetEnemiesKilled(1);
				if (index == 1)
					player->AwardPoints(50);
				if (index == 2)
					player->AwardPoints(250);
			}				
		}		
	}
	else
		prevHit = false;
}