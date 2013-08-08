/*
 *  BulletManager.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include "collision.h"
 
BulletManager::BulletManager(SpriteInfo * _spriteInfo, OamState * _oam)
{
	spriteInfo = _spriteInfo;
	oam = _oam;
	idCount = 10;
	interrupt = false;
	pBulletCount = 0;
	pBulletMax = 3;
	eBulletCount = 0;
	eBulletMax = 3;
}

BulletManager::~BulletManager(){}

void BulletManager::CreateBullet(int _entityID, float xPos, float yPos, float velocityX, float velocityY)
{
 
	entityID = _entityID;
 
	if((entityID == 1 && pBulletCount < pBulletMax) || (entityID == 2 && eBulletCount < eBulletMax))
	{
	
		if(entityID == 1)
		pBulletCount++;
		
		if(entityID == 2)
		eBulletCount++;
 
 
		if(!availableID.empty())
		{
			nextID = availableID.front();
			availableID.pop_front();
 
			SpriteEntry * spriteEntry = &oam->oamMemory[nextID];
	
			Bullet * b = new Bullet(nextID, entityID, spriteEntry, xPos, yPos, velocityX, velocityY);
			
			b->Create(xPos, yPos, velocityX, velocityY);
	
			bulletList.push_back(*b);
			
			randomBulletSound = (rand() % 5 + 1);
			if (randomBulletSound == 1)
				mmEffect(SFX_EGUN1);
			if (randomBulletSound == 2)
				mmEffect(SFX_EGUN2);
			if (randomBulletSound == 3)
				mmEffect(SFX_EGUN3);
			if (randomBulletSound == 4)
				mmEffect(SFX_EGUN4);
			if (randomBulletSound == 5)
				mmEffect(SFX_ELASER);
		
		}
		else
		{
			SpriteEntry * spriteEntry = &oam->oamMemory[idCount];
			Bullet * b = new Bullet(idCount, entityID, spriteEntry, xPos, yPos, velocityX, velocityY);
			render->DisplayBullet(idCount, oam, spriteInfo, (int)xPos, (int)yPos, true);
			bulletList.push_back(*b);
			idCount++;
		}
	}
}
 
 
void BulletManager::UpdateBullets()
{
	for(I = bulletList.begin(); I != bulletList.end(); I++)
    {  
		if(I->GetIsDead() == true)
		{
			
		   availableID.push_back(I->GetID());
		   
		   I->Reset();
		   
		   if(I->GetOwner() == 1)
		   pBulletCount--;
		   
		   if(I->GetOwner() == 2)
		   eBulletCount--;
		   
			I = bulletList.erase(I); 
			
		}
		else
		{
			I->Update();
		}
	}
}

void BulletManager::GameOverReset()
{
	for(I = bulletList.begin(); I != bulletList.end(); I++)
    {  
	 while (!I->GetIsDead()){I->Update();}	
	 I->Reset();
	}
	
	idCount = 10;
	UpdateBullets();
}