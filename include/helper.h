

void SpawnEnemies(int &index, Player * player, Enemy * enemy1, Enemy * enemy2, Enemy * enemy3, Enemy * enemy5, Enemy * enemy6, 
					Enemy * enemy7, Enemy * enemy10, Enemy * enemy11, Enemy * enemy12, Enemy * enemy13, Enemy * boss1, Enemy * boss2, 
					Enemy * boss3, SpriteEntry * enemy1Entry, SpriteEntry * enemy2Entry, SpriteEntry * enemy3Entry, SpriteEntry * enemy5Entry,
					SpriteEntry * enemy6Entry, SpriteEntry * enemy7Entry, SpriteEntry * enemy10Entry, SpriteEntry * enemy11Entry, 
					SpriteEntry * enemy12Entry, SpriteEntry * enemy13Entry, SpriteEntry * boss1Entry, SpriteEntry * boss2Entry, 
					SpriteEntry * boss3Entry, BulletManager * bulletManager, bool playSoundBoss[], int enemiesPerWave)
{
	
	
	//0 = spawn level 1 enemies, 1 = spawn level 1 boss, 2 = level 2 enemies, etc.
	switch (index)
	{
	//level 1 enemies
	case 0: {
		enemy1->stopAI = false;
		enemy2->stopAI = false;
		enemy3->stopAI = false;
		
		if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 3))
		{
			if (enemy1->isDead)
				enemy1->isDead = false;
			if (enemy2->isDead)
				enemy2->isDead = false;
			if (enemy3->isDead)
				enemy3->isDead = false;
		}
		
		if (!enemy1->isDead)
			enemy1->Engage(1, bulletManager, player);			
		if (!enemy2->isDead)
			enemy2->Engage(1, bulletManager, player);
		if (!enemy3->isDead)
			enemy3->Engage(2, bulletManager, player);
		
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy1, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy2, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy3, bulletManager, &*bulletManager->I);
		}	
			
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy1->stopAI = true;
			enemy2->stopAI = true;
			enemy3->stopAI = true;
			enemy1->Reset(2, bulletManager);
			enemy2->Reset(2, bulletManager);
			enemy3->Reset(2, bulletManager);
			index++;
			playSoundBoss[0] = true;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> enemy1Position = enemy1->GetPosition();
        enemy1Entry->x = (int)enemy1Position.x;
        enemy1Entry->y = (int)enemy1Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy1->SetBounds(enemy1Position.x+10, enemy1Position.y+10, 10);
		
		MathVector2D<float> enemy2Position = enemy2->GetPosition();
        enemy2Entry->x = (int)enemy2Position.x;
        enemy2Entry->y = (int)enemy2Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy2->SetBounds(enemy2Position.x+10, enemy2Position.y+10, 10);
		
		MathVector2D<float> enemy3Position = enemy3->GetPosition();
        enemy3Entry->x = (int)enemy3Position.x;
        enemy3Entry->y = (int)enemy3Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy3->SetBounds(enemy3Position.x+10, enemy3Position.y+10, 10);
		
		
		break;}
	//level 1 boss
	case 1:{		
		boss1->stopAI = false;
		boss1->Engage(13, bulletManager, player);
			
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss1, bulletManager, &*bulletManager->I);			
		}	
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + enemiesPerWave);
		}
		
		MathVector2D<float> boss1Position = boss1->GetPosition();
        boss1Entry->x = (int)boss1Position.x;
        boss1Entry->y = (int)boss1Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss1->SetBounds(boss1Position.x+24, boss1Position.y+24, 24);
		break;}
		
	//level 2 enemies
	case 2:{
			Render::Instance()->DisplayLevelTwo();
			enemy5->stopAI = false;
			enemy6->stopAI = false;
			enemy7->stopAI = false;
			
			if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 3))
			{
				if (enemy5->isDead)
					enemy5->isDead = false;
				if (enemy6->isDead)
					enemy6->isDead = false;
				if (enemy7->isDead)
					enemy7->isDead = false;
			}
			
			if (!enemy5->isDead)
				enemy5->Engage(2, bulletManager, player);
			
			if (!enemy6->isDead)
				enemy6->Engage(2, bulletManager, player);
			
			if (!enemy7->isDead)
				enemy7->Engage(3, bulletManager, player);
			
		
			for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
				bulletManager->I++)
			{
				Collision::Instance()->CollisionBossPlayer(1, player, enemy5, bulletManager, &*bulletManager->I);
				Collision::Instance()->CollisionBossPlayer(1, player, enemy6, bulletManager, &*bulletManager->I);
				Collision::Instance()->CollisionBossPlayer(1, player, enemy7, bulletManager, &*bulletManager->I);
			}	
		
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy5->stopAI = true;
			enemy6->stopAI = true;
			enemy7->stopAI = true;
			enemy5->Reset(1, bulletManager);
			enemy6->Reset(1, bulletManager);
			enemy7->Reset(1, bulletManager);
			index++;
			playSoundBoss[1] = true;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> enemy5Position = enemy5->GetPosition();
        enemy5Entry->x = (int)enemy5Position.x;
        enemy5Entry->y = (int)enemy5Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy5->SetBounds(enemy5Position.x+10, enemy5Position.y+10, 10);
		
		MathVector2D<float> enemy6Position = enemy6->GetPosition();
        enemy6Entry->x = (int)enemy6Position.x;
        enemy6Entry->y = (int)enemy6Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy6->SetBounds(enemy6Position.x+10, enemy6Position.y+10, 10);
		
		MathVector2D<float> enemy7Position = enemy7->GetPosition();
        enemy7Entry->x = (int)enemy7Position.x;
        enemy7Entry->y = (int)enemy7Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy7->SetBounds(enemy7Position.x+10, enemy7Position.y+10, 10);
		break;}
	
	//level 2 boss
	case 3:{
		boss2->stopAI = false;
		boss2->Engage(13, bulletManager, player);
			
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss2, bulletManager, &*bulletManager->I);			
		}
		
		MathVector2D<float> boss2Position = boss2->GetPosition();
        boss2Entry->x = (int)boss2Position.x;
        boss2Entry->y = (int)boss2Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss2->SetBounds(boss2Position.x+32, boss2Position.y+32, 32);
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + enemiesPerWave);
		}
		
		break;}
	
	//level 3 enemies
	case 4:{
		Render::Instance()->DisplayLevelThree();
		enemy1->stopAI = false;
		enemy2->stopAI = false;
		enemy3->stopAI = false;
		enemy5->stopAI = false;
		enemy6->stopAI = false;
		enemy7->stopAI = false;
		
		
		if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 6))
			{
				if (enemy1->isDead)
					enemy1->isDead = false;
				if (enemy2->isDead)
					enemy2->isDead = false;
				if (enemy3->isDead)
					enemy3->isDead = false;
				if (enemy5->isDead)
					enemy5->isDead = false;
				if (enemy6->isDead)
					enemy6->isDead = false;
				if (enemy7->isDead)
					enemy7->isDead = false;
			}
			
			
		if (!enemy1->isDead)
			enemy1->Engage(3, bulletManager, player);			
		
		if (!enemy2->isDead)
			enemy2->Engage(3, bulletManager, player);
		
		if (!enemy3->isDead)
			enemy3->Engage(4, bulletManager, player);
		
		if (!enemy5->isDead)
			enemy5->Engage(2, bulletManager, player);
		
		if (!enemy6->isDead)
			enemy6->Engage(7, bulletManager, player);
		
		if (!enemy7->isDead)
			enemy7->Engage(1, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy1, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy2, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy3, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy5, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy6, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy7, bulletManager, &*bulletManager->I);
		}	
		
			
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy1->stopAI = true;
			enemy2->stopAI = true;
			enemy3->stopAI = true;
			enemy5->stopAI = true;
			enemy6->stopAI = true;
			enemy7->stopAI = true;
			
			enemy1->Reset(1, bulletManager);
			enemy2->Reset(1, bulletManager);
			enemy3->Reset(1, bulletManager);
			enemy5->Reset(1, bulletManager);
			enemy6->Reset(1, bulletManager);
			enemy7->Reset(1, bulletManager);
			
			
			index++;
			playSoundBoss[2] = true;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> enemy1Position = enemy1->GetPosition();
        enemy1Entry->x = (int)enemy1Position.x;
        enemy1Entry->y = (int)enemy1Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy1->SetBounds(enemy1Position.x+16, enemy1Position.y+16, 16);
		
		MathVector2D<float> enemy2Position = enemy2->GetPosition();
        enemy2Entry->x = (int)enemy2Position.x;
        enemy2Entry->y = (int)enemy2Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy2->SetBounds(enemy2Position.x+16, enemy2Position.y+16, 16);
		
		MathVector2D<float> enemy3Position = enemy3->GetPosition();
        enemy3Entry->x = (int)enemy3Position.x;
        enemy3Entry->y = (int)enemy3Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy3->SetBounds(enemy3Position.x+16, enemy3Position.y+16, 16);
		
		MathVector2D<float> enemy5Position = enemy5->GetPosition();
        enemy5Entry->x = (int)enemy5Position.x;
        enemy5Entry->y = (int)enemy5Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy5->SetBounds(enemy5Position.x+16, enemy5Position.y+16, 16);
		
		MathVector2D<float> enemy6Position = enemy6->GetPosition();
        enemy6Entry->x = (int)enemy6Position.x;
        enemy6Entry->y = (int)enemy6Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy6->SetBounds(enemy6Position.x+16, enemy6Position.y+16, 16);
		
		MathVector2D<float> enemy7Position = enemy7->GetPosition();
        enemy7Entry->x = (int)enemy7Position.x;
        enemy7Entry->y = (int)enemy7Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy7->SetBounds(enemy7Position.x+16, enemy7Position.y+16, 16);
		
		break;}
		
	case 5:{
		boss3->stopAI = false;
		boss3->Engage(14, bulletManager, player);
			
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss3, bulletManager, &*bulletManager->I);			
		}
		
		MathVector2D<float> boss3Position = boss3->GetPosition();
        boss3Entry->x = (int)boss3Position.x;
        boss3Entry->y = (int)boss3Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss3->SetBounds(boss3Position.x+32, boss3Position.y+32, 32);
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + enemiesPerWave);
			//mmStop();
			//mmUnload(MOD_MFIRSTHALF);
			mmStart(MOD_MSECONDHALF, MM_PLAY_LOOP);
		}
		
		break;}

		
	case 6:{
		Render::Instance()->DisplayLevelFour();
		/*enemy10->stopAI = false;
		enemy11->stopAI = false;
		enemy12->stopAI = false;
		enemy13->stopAI = false;
		
		Render::Instance()->displayLevelFour();
		enemy10->engage(1, bulletManager);
		
		enemy11->engage(1, bulletManager);
		
		enemy12->engage(1, bulletManager);
		
		enemy13->engage(1, bulletManager);
		*/		
		enemy1->stopAI = false;
		enemy5->stopAI = false;
		enemy6->stopAI = false;
		enemy7->stopAI = false;
		
		if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 4))
			{
				if (enemy1->isDead)
					enemy1->isDead = false;
				if (enemy5->isDead)
					enemy5->isDead = false;
				if (enemy6->isDead)
					enemy6->isDead = false;
				if (enemy7->isDead)
					enemy7->isDead = false;
			}
			
			
		if (!enemy1->isDead)
			enemy1->Engage(8, bulletManager, player);
		
		if (!enemy5->isDead)
			enemy5->Engage(9, bulletManager, player);
		
		if (!enemy6->isDead)
			enemy6->Engage(6, bulletManager, player);
		
		if (!enemy7->isDead)
			enemy7->Engage(5, bulletManager, player);
		
		/*for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy10, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy11, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy12, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy13, bulletManager, &*bulletManager->I);
		}*/
	
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy1, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy5, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy6, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy7, bulletManager, &*bulletManager->I);
		}
		
		/*if (player->getEnemiesKilled() >= player->getMaxEnemiesToBoss())
		{
			enemy10->stopAI = true;
			enemy11->stopAI = true;
			enemy12->stopAI = true;
			enemy13->stopAI = true;
			enemy10->Reset(2, bulletManager);
			enemy11->Reset(2, bulletManager);
			enemy12->Reset(2, bulletManager);
			enemy13->Reset(2, bulletManager);
			index++;
		}*/
		
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy1->stopAI = true;
			enemy5->stopAI = true;
			enemy6->stopAI = true;
			enemy7->stopAI = true;
			enemy1->Reset(2, bulletManager);
			enemy5->Reset(2, bulletManager);
			enemy6->Reset(2, bulletManager);
			enemy7->Reset(2, bulletManager);
			index++;
			playSoundBoss[0] = true;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		/*MathVector2D<float> enemy10Position = enemy10->GetPosition();
        enemy10Entry->x = (int)enemy10Position.x;
        enemy10Entry->y = (int)enemy10Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy10->SetBounds(enemy10Position.x+16, enemy10Position.y+16, 16);
		
		MathVector2D<float> enemy11Position = enemy11->GetPosition();
        enemy11Entry->x = (int)enemy11Position.x;
        enemy11Entry->y = (int)enemy11Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy11->SetBounds(enemy11Position.x+16, enemy11Position.y+16, 16);
		
		MathVector2D<float> enemy12Position = enemy12->GetPosition();
        enemy12Entry->x = (int)enemy12Position.x;
        enemy12Entry->y = (int)enemy12Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy12->SetBounds(enemy12Position.x+16, enemy12Position.y+16, 16);
		
		MathVector2D<float> enemy13Position = enemy13->GetPosition();
        enemy13Entry->x = (int)enemy13Position.x;
        enemy13Entry->y = (int)enemy13Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy13->SetBounds(enemy13Position.x+16, enemy13Position.y+16, 16);
		*/
		
		MathVector2D<float> enemy1Position = enemy1->GetPosition();
        enemy1Entry->x = (int)enemy1Position.x;
        enemy1Entry->y = (int)enemy1Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy1->SetBounds(enemy1Position.x+16, enemy1Position.y+16, 16);
		
		MathVector2D<float> enemy5Position = enemy5->GetPosition();
        enemy5Entry->x = (int)enemy5Position.x;
        enemy5Entry->y = (int)enemy5Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy5->SetBounds(enemy5Position.x+16, enemy5Position.y+16, 16);
		
		MathVector2D<float> enemy6Position = enemy6->GetPosition();
        enemy6Entry->x = (int)enemy6Position.x;
        enemy6Entry->y = (int)enemy6Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy6->SetBounds(enemy6Position.x+16, enemy6Position.y+16, 16);
		
		MathVector2D<float> enemy7Position = enemy7->GetPosition();
        enemy7Entry->x = (int)enemy7Position.x;
        enemy7Entry->y = (int)enemy7Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy7->SetBounds(enemy7Position.x+16, enemy7Position.y+16, 16);
		
		
		
		break;}
	case 7:{
		boss1->stopAI = false;
		boss1->Engage(13, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss1, bulletManager, &*bulletManager->I);	
		}
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			playSoundBoss[1] = true;
			index++;
			boss1->Reset(2, bulletManager);
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		
		MathVector2D<float> boss1Position = boss1->GetPosition();
        boss1Entry->x = (int)boss1Position.x;
        boss1Entry->y = (int)boss1Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss1->SetBounds(boss1Position.x+32, boss1Position.y+32, 32);
		break;}
	
	case 8:{
		boss2->stopAI = false;
		boss2->Engage(14, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss2, bulletManager, &*bulletManager->I);			
		}
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			boss2->Reset(2, bulletManager);
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + enemiesPerWave);
		}
		
		MathVector2D<float> boss2Position = boss2->GetPosition();
        boss2Entry->x = (int)boss2Position.x;
        boss2Entry->y = (int)boss2Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss2->SetBounds(boss2Position.x+32, boss2Position.y+32, 32);
		
		
		break;}
	
	case 9:{
		Render::Instance()->DisplayLevelFive();
		enemy1->stopAI = false;
		enemy2->stopAI = false;
		enemy3->stopAI = false;
		enemy6->stopAI = false;
		
		if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 4))
			{
				if (enemy1->isDead)
					enemy1->isDead = false;
				if (enemy2->isDead)
					enemy2->isDead = false;
				if (enemy6->isDead)
					enemy6->isDead = false;
				if (enemy3->isDead)
					enemy3->isDead = false;
			}
			
			
		if (!enemy1->isDead)
			enemy1->Engage(11, bulletManager, player);
		
		if (!enemy2->isDead)
			enemy2->Engage(12, bulletManager, player);
		
		if (!enemy6->isDead)
			enemy6->Engage(13, bulletManager, player);
		
		if (!enemy3->isDead)
			enemy3->Engage(6, bulletManager, player);
			
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy1, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy2, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy3, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy6, bulletManager, &*bulletManager->I);
		}	
			
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy1->stopAI = true;
			enemy2->stopAI = true;
			enemy3->stopAI = true;
			enemy6->stopAI = true;
			enemy1->Reset(2, bulletManager);
			enemy2->Reset(2, bulletManager);
			enemy3->Reset(2, bulletManager);
			enemy6->Reset(2, bulletManager);
			index++;
			playSoundBoss[2] = true;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> enemy1Position = enemy1->GetPosition();
        enemy1Entry->x = (int)enemy1Position.x;
        enemy1Entry->y = (int)enemy1Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy1->SetBounds(enemy1Position.x+16, enemy1Position.y+16, 16);
		
		MathVector2D<float> enemy2Position = enemy2->GetPosition();
        enemy2Entry->x = (int)enemy2Position.x;
        enemy2Entry->y = (int)enemy2Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy2->SetBounds(enemy2Position.x+16, enemy2Position.y+16, 16);
		
		MathVector2D<float> enemy3Position = enemy3->GetPosition();
        enemy3Entry->x = (int)enemy3Position.x;
        enemy3Entry->y = (int)enemy3Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy3->SetBounds(enemy3Position.x+16, enemy3Position.y+16, 16);
		
		MathVector2D<float> enemy6Position = enemy6->GetPosition();
        enemy6Entry->x = (int)enemy6Position.x;
        enemy6Entry->y = (int)enemy6Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy6->SetBounds(enemy6Position.x+16, enemy6Position.y+16, 16);
		
		break;}
	case 10:{
		boss3->stopAI = false;
		boss3->Engage(13, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss3, bulletManager, &*bulletManager->I);			
		}
		
		
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
			playSoundBoss[1] = true;
			index++;
			boss3->Reset(2, bulletManager);
		}
		
		MathVector2D<float> boss3Position = boss3->GetPosition();
        boss3Entry->x = (int)boss3Position.x;
        boss3Entry->y = (int)boss3Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss3->SetBounds(boss3Position.x+32, boss3Position.y+32, 32);
		
		break;}
	
	case 11:{
		boss2->stopAI = false;
		boss2->Engage(14, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss2, bulletManager, &*bulletManager->I);			
		}
		
		
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			boss2->Reset(2, bulletManager);
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + enemiesPerWave);
		}
		
		MathVector2D<float> boss2Position = boss2->GetPosition();
        boss2Entry->x = (int)boss2Position.x;
        boss2Entry->y = (int)boss2Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss2->SetBounds(boss2Position.x+32, boss2Position.y+32, 32);
		
		break;}
	case 12:{
		Render::Instance()->DisplayLevelSix();
		enemy2->stopAI = false;
		enemy3->stopAI = false;
		enemy5->stopAI = false;
		enemy6->stopAI = false;
		enemy7->stopAI = false;
		
		if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 5))
			{
				if (enemy2->isDead)
					enemy2->isDead = false;
				if (enemy5->isDead)
					enemy5->isDead = false;
				if (enemy6->isDead)
					enemy6->isDead = false;
				if (enemy7->isDead)
					enemy7->isDead = false;
				if (enemy3->isDead)
					enemy3->isDead = false;
			}
			
			
		if (!enemy2->isDead)
			enemy2->Engage(6, bulletManager, player);
		
		if (!enemy5->isDead)
			enemy5->Engage(5, bulletManager, player);
		
		if (!enemy6->isDead)
			enemy6->Engage(6, bulletManager, player);
		
		if (!enemy7->isDead)
			enemy7->Engage(5, bulletManager, player);
		if (!enemy3->isDead)
			enemy3->Engage(12, bulletManager, player);
			
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy7, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy2, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy3, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy5, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy6, bulletManager, &*bulletManager->I);
		}	
			
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy7->stopAI = true;
			enemy2->stopAI = true;
			enemy3->stopAI = true;
			enemy6->stopAI = true;
			enemy5->stopAI = true;
			enemy7->Reset(2, bulletManager);
			enemy2->Reset(2, bulletManager);
			enemy3->Reset(2, bulletManager);
			enemy6->Reset(2, bulletManager);
			enemy5->Reset(2, bulletManager);
			index++;
			playSoundBoss[0] = true;
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> enemy7Position = enemy7->GetPosition();
        enemy7Entry->x = (int)enemy7Position.x;
        enemy7Entry->y = (int)enemy7Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy7->SetBounds(enemy7Position.x+16, enemy7Position.y+16, 16);
		
		MathVector2D<float> enemy2Position = enemy2->GetPosition();
        enemy2Entry->x = (int)enemy2Position.x;
        enemy2Entry->y = (int)enemy2Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy2->SetBounds(enemy2Position.x+16, enemy2Position.y+16, 16);
		
		MathVector2D<float> enemy3Position = enemy3->GetPosition();
        enemy3Entry->x = (int)enemy3Position.x;
        enemy3Entry->y = (int)enemy3Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy3->SetBounds(enemy3Position.x+16, enemy3Position.y+16, 16);
		
		MathVector2D<float> enemy5Position = enemy5->GetPosition();
        enemy5Entry->x = (int)enemy5Position.x;
        enemy5Entry->y = (int)enemy5Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy5->SetBounds(enemy5Position.x+16, enemy5Position.y+16, 16);
		
		MathVector2D<float> enemy6Position = enemy6->GetPosition();
        enemy6Entry->x = (int)enemy6Position.x;
        enemy6Entry->y = (int)enemy6Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy6->SetBounds(enemy6Position.x+16, enemy6Position.y+16, 16);
		
		break;}
	case 13:{
	
		boss1->stopAI = false;
		boss1->Engage(13, bulletManager, player);
				
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss1, bulletManager, &*bulletManager->I);			
		}
		
	
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
			playSoundBoss[2] = true;
			index++;
			boss1->Reset(2, bulletManager);
		}
		
		MathVector2D<float> boss1Position = boss1->GetPosition();
        boss1Entry->x = (int)boss1Position.x;
        boss1Entry->y = (int)boss1Position.y;
//        rotateSprite(boss1Rotatin, boss1->getAngleDeg());
		boss1->SetBounds(boss1Position.x+32, boss1Position.y+32, 32);
		
		break;}
		
	case 14:{	
		boss3->stopAI = false;
		boss3->Engage(14, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			
			Collision::Instance()->CollisionBossPlayer(2, player, boss3, bulletManager, &*bulletManager->I);			
		}
		
	
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			boss3->Reset(2, bulletManager);
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + enemiesPerWave);
		}
		
		MathVector2D<float> boss3Position = boss3->GetPosition();
        boss3Entry->x = (int)boss3Position.x;
        boss3Entry->y = (int)boss3Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss3->SetBounds(boss3Position.x+32, boss3Position.y+32, 32);
	
		break;}
	case 15:{
		Render::Instance()->DisplayLevelSeven();
		enemy1->stopAI = false;
		enemy2->stopAI = false;
		enemy3->stopAI = false;
		enemy5->stopAI = false;
		enemy6->stopAI = false;
		enemy7->stopAI = false;
		
		
		if (player->GetEnemiesKilled() <= (player->GetMaxEnemiesToBoss() - 6))
			{
				if (enemy1->isDead)
					enemy1->isDead = false;
				if (enemy2->isDead)
					enemy2->isDead = false;
				if (enemy3->isDead)
					enemy3->isDead = false;
				if (enemy5->isDead)
					enemy5->isDead = false;
				if (enemy6->isDead)
					enemy6->isDead = false;
				if (enemy7->isDead)
					enemy7->isDead = false;
			}
			
			
		if (!enemy1->isDead)
			enemy1->Engage(13, bulletManager, player);			
		
		if (!enemy2->isDead)
			enemy2->Engage(14, bulletManager, player);
		
		if (!enemy3->isDead)
			enemy3->Engage(13, bulletManager, player);
		
		if (!enemy5->isDead)
			enemy5->Engage(14, bulletManager, player);
		
		if (!enemy6->isDead)
			enemy6->Engage(11, bulletManager, player);
		
		if (!enemy7->isDead)
			enemy7->Engage(6, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
			bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(1, player, enemy1, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy2, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy3, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy5, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy6, bulletManager, &*bulletManager->I);
			Collision::Instance()->CollisionBossPlayer(1, player, enemy7, bulletManager, &*bulletManager->I);
		}	
		
			
		if (player->GetEnemiesKilled() >= player->GetMaxEnemiesToBoss())
		{
			enemy1->stopAI = true;
			enemy2->stopAI = true;
			enemy3->stopAI = true;
			enemy5->stopAI = true;
			enemy6->stopAI = true;
			enemy7->stopAI = true;
			
			enemy1->Reset(1, bulletManager);
			enemy2->Reset(1, bulletManager);
			enemy3->Reset(1, bulletManager);
			enemy5->Reset(1, bulletManager);
			enemy6->Reset(1, bulletManager);
			enemy7->Reset(1, bulletManager);
			
			playSoundBoss[0] = true;
			index++;
			
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> enemy1Position = enemy1->GetPosition();
        enemy1Entry->x = (int)enemy1Position.x;
        enemy1Entry->y = (int)enemy1Position.y;
       //rotateSprite(enemy1Rotation, enemy1->getAngleDeg());
		enemy1->SetBounds(enemy1Position.x+16, enemy1Position.y+16, 16);
		
		MathVector2D<float> enemy2Position = enemy2->GetPosition();
        enemy2Entry->x = (int)enemy2Position.x;
        enemy2Entry->y = (int)enemy2Position.y;
        //rotateSprite(enemy2Rotation, enemy2->getAngleDeg());
		enemy2->SetBounds(enemy2Position.x+16, enemy2Position.y+16, 16);
		
		MathVector2D<float> enemy3Position = enemy3->GetPosition();
        enemy3Entry->x = (int)enemy3Position.x;
        enemy3Entry->y = (int)enemy3Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy3->SetBounds(enemy3Position.x+16, enemy3Position.y+16, 16);
		
		MathVector2D<float> enemy5Position = enemy5->GetPosition();
        enemy5Entry->x = (int)enemy5Position.x;
        enemy5Entry->y = (int)enemy5Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy5->SetBounds(enemy5Position.x+16, enemy5Position.y+16, 16);
		
		MathVector2D<float> enemy6Position = enemy6->GetPosition();
        enemy6Entry->x = (int)enemy6Position.x;
        enemy6Entry->y = (int)enemy6Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy6->SetBounds(enemy6Position.x+16, enemy6Position.y+16, 16);
		
		MathVector2D<float> enemy7Position = enemy7->GetPosition();
        enemy7Entry->x = (int)enemy7Position.x;
        enemy7Entry->y = (int)enemy7Position.y;
        //rotateSprite(enemy3Rotation, enemy3->getAngleDeg());
		enemy7->SetBounds(enemy7Position.x+16, enemy7Position.y+16, 16);
		
		break;}
	case 16:{
		boss1->stopAI = false;
		boss1->Engage(14, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss1, bulletManager, &*bulletManager->I);		
		}
		
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			playSoundBoss[1] = true;
			index++;
			boss1->Reset(2, bulletManager);
			
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		
		MathVector2D<float> boss1Position = boss1->GetPosition();
        boss1Entry->x = (int)boss1Position.x;
        boss1Entry->y = (int)boss1Position.y;
//        rotateSprite(boss1Rotatin, boss1->getAngleDeg());
		boss1->SetBounds(boss1Position.x+32, boss1Position.y+32, 32);
		
		break;}
		
	case 17:{
		boss2->stopAI = false;
		boss2->Engage(15, bulletManager, player);
		
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss2, bulletManager, &*bulletManager->I);						
		}		
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			playSoundBoss[2] = true;
			index++;
			boss2->Reset(2, bulletManager);
			mmStart(MOD_MFINALBOSS, MM_PLAY_LOOP);
			player->SetMaxEnemiesToBoss(player->GetMaxEnemiesToBoss() + 1);
		}
		MathVector2D<float> boss2Position = boss2->GetPosition();
        boss2Entry->x = (int)boss2Position.x;
        boss2Entry->y = (int)boss2Position.y;
//        rotateSprite(boss1Rotatin, boss1->getAngleDeg());
		boss2->SetBounds(boss2Position.x+32, boss2Position.y+32, 32);
		
		break;}
		
	case 18:{
		boss3->stopAI = false;
		boss3->Engage(16, bulletManager, player);
		
		for (bulletManager->I = bulletManager->bulletList.begin(); bulletManager->I != bulletManager->bulletList.end(); 
		bulletManager->I++)
		{
			Collision::Instance()->CollisionBossPlayer(2, player, boss3, bulletManager, &*bulletManager->I);		
		}
		
		
		if (player->GetEnemiesKilled() == (player->GetMaxEnemiesToBoss()))
		{
			index++;
			boss3->Reset(2, bulletManager);
			player->SetMaxEnemiesToBoss(enemiesPerWave);
//			gameState.GameOver();
			
		}		
		
		MathVector2D<float> boss3Position = boss3->GetPosition();
        boss3Entry->x = (int)boss3Position.x;
        boss3Entry->y = (int)boss3Position.y;
//        rotateSprite(boss1Rotation, boss1->getAngleDeg());
		boss3->SetBounds(boss3Position.x+32, boss3Position.y+32, 32);
	
		break;}

}

}