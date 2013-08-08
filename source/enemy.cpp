/*
 *  Enemy.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
 #include "enemy.h"
 
Enemy::Enemy(SpriteInfo * _spriteInfo)
{
    spriteInfo = _spriteInfo;
	
	isDead = false;
	stopAI = false;
	newPoint = true;
	update = true;
	point1 = true;
	point2 = false;
	point3 = false;
	point4 = false;
	
    /* Place the ship in an interesting part of the screen. */
	position.x = SCREEN_WIDTH / 2 - spriteInfo->width * 2 +
                 spriteInfo->width / 2;
	position.y = SCREEN_HEIGHT / 2 - spriteInfo->height;
	
    /* Stop the ship from moving */
	velocity.x = 0;
	velocity.y = 0;

    /* Point the ship at a cool angle. */
	angle = 5.67232007;
	
    /* Set up some sane kinematic static properties. */
	turnSpeed = .0368;
	thrust = .5;
	maxSpeed = 1.0;
}

Enemy::~Enemy()
{}

void Enemy::GoTo(float x, float y, float speed)  // speed must be .0,.25, .50
{

	if (x > position.x)
	{
		position.x += thrust + speed;
	}
	if (x < position.x)
	{
		position.x -= thrust + speed;
	}
	if (y > position.y)
	{
		position.y += thrust + speed;
	}
	if (y < position.y)
	{
		position.y -= thrust + speed;
	}
	if(position.x == x && position.y == y)
	{
	    newPoint = true;
		
	    if(point1)
		{
		   point1 = false;
		   point2 = true;
		}
		else if(point2)
		{
		   point2 = false;
		   point3 = true;
		}
		else if(point3)
		{
		   point3 = false;
		   point4 = true;
		}
		else if(point4)
		{
		   point4 = false;
		   point1 = true;
		}
    }
}

/* Waits however many seconds passed in */
void Enemy::WaitToShoot (bool shootSmart, int seconds, BulletManager * bulletManager, Player * player )
{
	float velocityX = 0;
	float velocityY = 1;
	
	if (shootSmart){
		velocityX = atan(player->GetPosition().x - position.x);
		velocityY = atan(player->GetPosition().y - position.y);
		}
	
	  if(update == true)
	  {
		endwait = timer + seconds;
		update = false;
	  }
	  if (timer < endwait) 
	  {
			// if timer has not been reached	
			timer++;
	  }
	  else
	  {
		// if timer has been reached
		bulletManager->CreateBullet(2, position.x, position.y, velocityX * GetAgi(), velocityY * GetAgi());   // agi changes the bullet speed
		update = true;
		timer = 0;
	}
}

void Enemy::Engage(int scheme, BulletManager * bulletManager, Player * player)
{
    if (!stopAI)
	{
		if (scheme == 1){									// RANDOM MOVE  SHOOT DOWN(STUPID)  STANDARD SPEED
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .0f);}
			if(point2 == true)
			   {GoTo(randX, randY, .0f);}
			if(point3 == true)
			   {GoTo(randX, randY, .0f);}
			if(point4 == true)
			   {GoTo(randX, randY, .0f);}
			WaitToShoot(false, 100, bulletManager, player);
			}
			if (scheme == 2){									// RANDOM MOVE  SHOOT DOWN(STUPID)  MAX SPEED
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .50f);}
			if(point2 == true)
			   {GoTo(randX, randY, .50f);}
			if(point3 == true)
			   {GoTo(randX, randY, .50f);}
			if(point4 == true)
			   {GoTo(randX, randY, .50f);}
			WaitToShoot(false, 100, bulletManager, player);
			}
			if (scheme == 3){									// RANDOM MOVE  SHOOT SMART  STANDARD SPEED
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .0f);}
			if(point2 == true)
			   {GoTo(randX, randY, .0f);}
			if(point3 == true)
			   {GoTo(randX, randY, .0f);}
			if(point4 == true)
			   {GoTo(randX, randY, .0f);}
			WaitToShoot(true, 100, bulletManager, player);
			}
			if (scheme == 4){									// RANDOM MOVE  SHOOT SMART  MAX SPEED
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .50f);}
			if(point2 == true)
			   {GoTo(randX, randY, .50f);}
			if(point3 == true)
			   {GoTo(randX, randY, .50f);}
			if(point4 == true)
			   {GoTo(randX, randY, .50f);}
			WaitToShoot(true, 100, bulletManager, player);
			}
			if (scheme == 5){									// RANDOM MOVE  SHOOT SMART FASTER  STANDARD SPEED
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .0f);}
			if(point2 == true)
			   {GoTo(randX, randY, .0f);}
			if(point3 == true)
			   {GoTo(randX, randY, .0f);}
			if(point4 == true)
			   {GoTo(randX, randY, .0f);}
			WaitToShoot(true, 70, bulletManager, player);
			}
			if (scheme == 6){									// RANDOM MOVE  SHOOT SMART FASTER   MAX SPEED
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .50f);}
			if(point2 == true)
			   {GoTo(randX, randY, .50f);}
			if(point3 == true)
			   {GoTo(randX, randY, .50f);}
			if(point4 == true)
			   {GoTo(randX, randY, .50f);}
			WaitToShoot(true, 70, bulletManager, player);
			}
		//new	
		if (scheme == 7){									// CHASE PLAYER * NO SHOOT  STANDARD SPEED
			if(newPoint)
				{
					randX = player->GetPosition().x;
					randY = player->GetPosition().y;
					newPoint = false;	 
				}
				/* AI Movement */
				if(point1 == true)
				   {GoTo(randX, randY, .0f);}
				if(point2 == true)
				   {GoTo(randX, randY, .0f);}
				if(point3 == true)
				   {GoTo(randX, randY, .0f);}
				if(point4 == true)
				   {GoTo(randX, randY, .0f);}
				//WaitToShoot(true, 100, bulletManager, player);
		}
		if (scheme == 8){									// CHASE PLAYER * NO SHOOT  MAX SPEED
			if(newPoint)
				{
					randX = player->GetPosition().x;
					randY = player->GetPosition().y;
					newPoint = false;	 
				}
				/* AI Movement */
				if(point1 == true)
				   {GoTo(randX, randY, .50f);}
				if(point2 == true)
				   {GoTo(randX, randY, .50f);}
				if(point3 == true)
				   {GoTo(randX, randY, .50f);}
				if(point4 == true)
				   {GoTo(randX, randY, .50f);}
				//WaitToShoot(true, 100, bulletManager, player);
		}
		if (scheme == 9){									// CHASE PLAYER * SHOOT SMART  STANDARD SPEED
			if(newPoint)
				{
					randX = player->GetPosition().x;
					randY = player->GetPosition().y;
					newPoint = false;	 
				}
				/* AI Movement */
				if(point1 == true)
				   {GoTo(randX, randY, .0f);}
				if(point2 == true)
				   {GoTo(randX, randY, .0f);}
				if(point3 == true)
				   {GoTo(randX, randY, .0f);}
				if(point4 == true)
				   {GoTo(randX, randY, .0f);}
				WaitToShoot(true, 100, bulletManager, player);
		}
		if (scheme == 10){									// CHASE PLAYER * SHOOT SMART  MAX SPEED
			if(newPoint)
				{
					randX = player->GetPosition().x;
					randY = player->GetPosition().y;
					newPoint = false;	 
				}
				/* AI Movement */
				if(point1 == true)
				   {GoTo(randX, randY, .50f);}
				if(point2 == true)
				   {GoTo(randX, randY, .50f);}
				if(point3 == true)
				   {GoTo(randX, randY, .50f);}
				if(point4 == true)
				   {GoTo(randX, randY, .50f);}
				WaitToShoot(true, 100, bulletManager, player);
		}
		if (scheme == 11){									// CHASE PLAYER * SHOOT SMART FASTER  STANDARD SPEED
			if(newPoint)
				{
					randX = player->GetPosition().x;
					randY = player->GetPosition().y;
					newPoint = false;	 
				}
				/* AI Movement */
				if(point1 == true)
				   {GoTo(randX, randY, .0f);}
				if(point2 == true)
				   {GoTo(randX, randY, .0f);}
				if(point3 == true)
				   {GoTo(randX, randY, .0f);}
				if(point4 == true)
				   {GoTo(randX, randY, .0f);}
				WaitToShoot(true, 70, bulletManager, player);
		}
		if (scheme == 12){									// CHASE PLAYER * SHOOT SMART FASTER  MAX SPEED
			if(newPoint)
				{
					randX = player->GetPosition().x;
					randY = player->GetPosition().y;
					newPoint = false;	 
				}
				/* AI Movement */
				if(point1 == true)
				   {GoTo(randX, randY, .50f);}
				if(point2 == true)
				   {GoTo(randX, randY, .50f);}
				if(point3 == true)
				   {GoTo(randX, randY, .50f);}
				if(point4 == true)
				   {GoTo(randX, randY, .50f);}
				WaitToShoot(true, 50, bulletManager, player);
		}
		if (scheme == 13){									// BOSS 1
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .0f);}
			if(point2 == true)
			   {GoTo(randX, randY, .0f);}
			if(point3 == true)
			   {GoTo(randX, randY, .0f);}
			if(point4 == true)
			   {GoTo(randX, randY, .0f);}
			WaitToShoot(true, 40, bulletManager, player);
		}
		if (scheme == 14){									// BOSS 2
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .50f);}
			if(point2 == true)
			   {GoTo(randX, randY, .50f);}
			if(point3 == true)
			   {GoTo(randX, randY, .50f);}
			if(point4 == true)
			   {GoTo(randX, randY, .50f);}
			WaitToShoot(true, 30, bulletManager, player);
		}
		if (scheme == 15){									// BOSS 3
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .50f);}
			if(point2 == true)
			   {GoTo(randX, randY, .50f);}
			if(point3 == true)
			   {GoTo(randX, randY, .50f);}
			if(point4 == true)
			   {GoTo(randX, randY, .50f);}
			WaitToShoot(true, 20, bulletManager, player);
		}
		if (scheme == 16){									// FINAL BOSS
			
			if(newPoint)
			{
				randX = rand() % 240;
				randY = rand() % 100;
				newPoint = false;	 
			}
			/* AI Movement */
			if(point1 == true)
			   {GoTo(randX, randY, .50f);}
			if(point2 == true)
			   {GoTo(randX, randY, .50f);}
			if(point3 == true)
			   {GoTo(randX, randY, .50f);}
			if(point4 == true)
			   {GoTo(randX, randY, .50f);}
			WaitToShoot(true, 10, bulletManager, player);
		}
	}
}

void Enemy::Reset(int index, BulletManager * bulletManager)
{
	//1 = enemy, 2 = boss
	if (index == 1)
	{
		position.y = -32;
		position.x = (rand()%150)+1;
	}
	
	if (index == 2)
	{
		position.x = (rand()%150)+1;
		position.y = -64;
		SetHull(GetMaxHull());
		SetShields(GetMaxShields());
		SetArmor(GetMaxArmor());
	}
}