/*
 *  BulletManager.cpp

 
 #include "bulletManager.h"
 
 BulletManager::BulletManager(SpriteInfo * _spriteInfo, OAMTable * _oam, Render * _render)
 {
	spriteInfo = _spriteInfo;
	oam = _oam;
	render = _render;
	
	idCount = 4;
	pBulletCount = 0;
	pBulletMax = 3;
	
	
	SpriteEntry * pb1Entry = &oam->oamBuffer[4];
	SpriteEntry * pb2Entry = &oam->oamBuffer[5];
	SpriteEntry * pb3Entry = &oam->oamBuffer[6];
	SpriteEntry * eb1Entry = &oam->oamBuffer[7];
	SpriteEntry * eb2Entry = &oam->oamBuffer[8];
	SpriteEntry * eb3Entry = &oam->oamBuffer[9];
	
	Bullet * pb1 = new Bullet(4, 50, 50, 0, 0);
	Bullet * pb2 = new Bullet(5, 200, 200, 0, 0);
	Bullet * pb3 = new Bullet(6, 200, 200, 0, 0);
	Bullet * eb1 = new Bullet(7, 200, 200, 0, 0);
	Bullet * eb2 = new Bullet(8, 200, 200, 0, 0);
	Bullet * eb3 = new Bullet(9, 200, 200, 0, 0);
	
	runOnce = true;
	
 }

 
BulletManager::~BulletManager(){}
 
 void BulletManager::CreateBullet(int entityID, float xPos, float yPos, float velocityX, float velocityY)
 {
 
 

if(runOnce == true)
{
/*
 	render->displayBullet(4, oam, spriteInfo, (int)50, (int)50);
	render->displayBullet(5, oam, spriteInfo, (int)200, (int)200);
	render->displayBullet(6, oam, spriteInfo, (int)200, (int)200);
	render->displayBullet(7, oam, spriteInfo, (int)200, (int)200);
	render->displayBullet(8, oam, spriteInfo, (int)200, (int)200);
	render->displayBullet(9, oam, spriteInfo, (int)200, (int)200);
	runOnce = false;

}
 
	if(entityID == 1 && pBulletCount < pBulletMax)
	{
		pBulletCount++;
		
		pb1->Set(xPos, yPos, velocityX, velocityY);
		pb1->SetIsDead(false);
	}
	
 }
 
 
void BulletManager::UpdateBullets()
{

	if(pb1->getIsDead() == true)
	{
	   pBulletCount--;
	   //pb1->Set(pb1Entry, 200, 200, 0, 0);
	}
	else
	{
		pb1->Update();
	}
	
}
 
 
 */
 
 
 