/*
 *  main.cpp
 *  
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include <nds.h>
#include <assert.h>
#include <list>
#include <string>
#include <stdio.h>
#include <sstream>

#include "sprites.h"
#include "ship.h"
#include "render.h"
#include "entity.h"
#include "player.h"
#include "gameState.h"
#include "enemy.h"
#include "bulletManager.h"
#include "collision.h"
#include "wireframe.h"

 /* Sounds */
#include "soundbank.h"
#include "soundbank_bin.h"
#include <maxmod9.h>

/* Custom Fonts */
#include "font.h"

#include "helper.h"

#include <sstream>

bool guiButton1Pressed = true;
bool guiButton2Pressed = false;
bool guiButton3Pressed = false;
bool guiButton4Pressed = false;

bool changeStats = false;
int mShieldOffset = 28;
int agiOffset = 5;
int atkOffset = 5;
int armorOffset = 30;
float counter = 0;
int countLimit = 30;
int spawnIndex = 0;
bool reset = false;
bool pause = false;
bool stopShield = false;
bool overShield = false;
bool agilityMode = false;
int enemiesPerWave = 8;
bool helpScreen = false;
bool titleScreen = false;

int baseAtk;
int lastGuiButtonPressed;


/* Sprite Size Reference 
SpriteSize sizes[] = {
	SpriteSize_8x8, 
	SpriteSize_8x16,
	SpriteSize_16x8,
	SpriteSize_8x32,
	SpriteSize_16x16, 
	SpriteSize_32x8,
	SpriteSize_16x32,  
	SpriteSize_32x16, 
	SpriteSize_32x32, 
	SpriteSize_32x64,
	SpriteSize_64x32, 
	SpriteSize_64x64, 	
};
*/

void InitSound()
{
	/* Initialize maxmod using the memory based soundbank set up. */
    mmInitDefaultMem((mm_addr)soundbank_bin);
	// mmInitDefaultMem((mm_addr)soundbank_bin);
	mmSelectMode(MM_MODE_A );

	//for (int i = 1; i < 16; i++)
		//mmUnlockChannels(i);
	
	//Load the module
	mmLoad(MOD_MINTRO);
	mmLoad(MOD_MENDING);
	mmLoad(MOD_MSECONDHALF);
	mmLoad(MOD_MFIRSTHALF);
	mmLoad(MOD_MFINALBOSS);
	mmSetModuleVolume(175);
	
	//Load the sound effects
	mmLoadEffect(SFX_EXPLOSION);
	mmLoadEffect(SFX_SHIPHIT);
	mmLoadEffect(SFX_EDESTROY);
	mmLoadEffect(SFX_EANNIHILATE);
	mmLoadEffect(SFX_EERROR);
	mmLoadEffect(SFX_EGUN1);
	mmLoadEffect(SFX_EGUN2);
	mmLoadEffect(SFX_EGUN3);
	mmLoadEffect(SFX_EGUN4);
	mmLoadEffect(SFX_ELASER);
	mmLoadEffect(SFX_EUPGRADECOMPLETE);
	mmLoadEffect(SFX_EWARNINGBEEP);
	mmLoadEffect(SFX_EERADICATE);
	mmLoadEffect(SFX_EBEEP1);
	mmLoadEffect(SFX_EBEEP2);
	mmLoadEffect(SFX_EBEEP3);
	mmLoadEffect(SFX_EBEEP4);
}


void touchControls(touchPosition touch, Player * player)
{
	if (keysDown() & KEY_TOUCH)
		{
			
			if ((touch.px > 10) && (touch.px < 34) && (!helpScreen))
			{
				if ((touch.py < 46) && (touch.py > 6))
				{
					Render::Instance()->ChangeGUI(1);
					
					if(guiButton1Pressed == false)
						{changeStats = true;}
					guiButton1Pressed = true;
					guiButton2Pressed = false;
					guiButton3Pressed = false;
					guiButton4Pressed = false;
				}
				if ((touch.py < 96) && (touch.py > 56))
				{
					Render::Instance()->ChangeGUI(2);
					
					if(guiButton2Pressed == false)
						{changeStats = true;}
					guiButton1Pressed = false;
					guiButton2Pressed = true;
					guiButton3Pressed = false;
					guiButton4Pressed = false;
				}
				if ((touch.py < 140) && (touch.py > 100))
				{
					Render::Instance()->ChangeGUI(3);
					
					if(guiButton3Pressed == false)
						{changeStats = true;}
					guiButton1Pressed = false;
					guiButton2Pressed = false;
					guiButton3Pressed = true;
					guiButton4Pressed = false;
				}
				if ((touch.py < 184) && (touch.py > 144))
				{
					Render::Instance()->ChangeGUI(4);
					
					if(guiButton4Pressed == false)
						{changeStats = true;}
					guiButton1Pressed = false;
					guiButton2Pressed = false;
					guiButton3Pressed = false;
					guiButton4Pressed = true;
				}
			}
			if ((touch.px > 215) && (touch.px < 230) && (!helpScreen))
			{
				if ((touch.py > 77) && (touch.py < 92))
				{
					// atk upgrade button pressed
					if (player->ReturnScore() >= 500 && player->GetAtk() < 25)
					{
						player->SetAtk(player->GetAtk() + 1);
						player->AwardPoints(-500);
						mmEffect(SFX_EUPGRADECOMPLETE);
					}
					else
						mmEffect(SFX_EERROR);
				}
				if ((touch.py > 102) && (touch.py < 114))
				{
					// def upgrade button pressed
					if (player->ReturnScore() >= 500 && player->GetDef() < 10)
					{
						player->SetDef(player->GetDef() + 1);
						player->AwardPoints(-500);
						mmEffect(SFX_EUPGRADECOMPLETE);
					}
					else
						mmEffect(SFX_EERROR);
				}
				if ((touch.py > 128) && (touch.py < 140))
				{
					// agi upgrade button pressed
					if (player->ReturnScore() >= 500 && player->GetAgi() < 26)
					{
						player->SetAgi(player->GetAgi() + 1);
						player->AwardPoints(-500);
						mmEffect(SFX_EUPGRADECOMPLETE);
					}
					else
						mmEffect(SFX_EERROR);
				}
				if ((touch.py > 150) && (touch.py < 163))
				{
					// repair button pressed
					if (player->ReturnScore() >= 300)
					{
						if(player->GetArmor() <= player->GetMaxArmor() -10)
						{
							player->SetArmor(player->GetArmor() + 10);
							player->AwardPoints(-300);
							mmEffect(SFX_EUPGRADECOMPLETE);
						}
						//else
							//player->SetArmor(player->GetMaxArmor());
					}
					else
						mmEffect(SFX_EERROR);
				}
			}
		}
		if(changeStats)
		{
			if(guiButton1Pressed)
			{
				
				// STANDARD MODE
				
				mmEffect(SFX_EBEEP1);
				if(lastGuiButtonPressed == 2)
				{
					player->SetAtk(player->GetAtk() - atkOffset);
				}
				if(lastGuiButtonPressed == 3)
				{
					player->SetAgi(player->GetAgi() - agiOffset);
					player->SetMaxShields(player->GetMaxShields() + mShieldOffset);
				}
				if(lastGuiButtonPressed == 4)
				{
					player->SetMaxShields(player->GetMaxShields() - mShieldOffset);
					player->SetAtk(baseAtk);
					if(player->GetShields() > player->GetMaxShields())
						{player->SetShields(player->GetMaxShields());}
				}
				lastGuiButtonPressed = 1;
				
				agilityMode = false;
				overShield = false;
				stopShield = false;
			}
			else if(guiButton2Pressed)
			{
				// COMBAT MODE
				
				mmEffect(SFX_EBEEP2);
				if(lastGuiButtonPressed == 3)
				{
					player->SetAgi(player->GetAgi() - agiOffset);
					player->SetMaxShields(player->GetMaxShields() + mShieldOffset);
				}
				if(lastGuiButtonPressed == 4)
				{
					player->SetMaxShields(player->GetMaxShields() - mShieldOffset);
					player->SetAtk(baseAtk);
					if(player->GetShields() > player->GetMaxShields())
						{player->SetShields(player->GetMaxShields());}
				}
				
				player->SetAtk(player->GetAtk() + atkOffset);  // add increase bullet speed.
															   // cut shield in half, slow regen
				

				lastGuiButtonPressed = 2;
				
				agilityMode = false;
				overShield = false;
				stopShield = true;
			}
			else if(guiButton3Pressed)
			{
			
				// AGILITY MODE
				
				mmEffect(SFX_EBEEP3);
				if(lastGuiButtonPressed == 2)
				{
					player->SetAtk(player->GetAtk() - atkOffset);
				}
				if(lastGuiButtonPressed == 4)
				{
					player->SetMaxShields(player->GetMaxShields() - mShieldOffset);
					player->SetAtk(baseAtk);
					if(player->GetShields() > player->GetMaxShields())
						{player->SetShields(player->GetMaxShields());}
				}	
				
				stopShield = false;
				overShield = false;
				agilityMode = true;
				
				player->SetAgi(player->GetAgi() + agiOffset);
				
				lastGuiButtonPressed = 3;
				
				player->SetMaxShields(player->GetMaxShields() - mShieldOffset);
				
				if (player->GetShields() > player->GetMaxShields())
					player->SetShields(player->GetMaxShields());
				
			}
			else if(guiButton4Pressed)
			{
				//OVERSHIELD MODE
				
				mmEffect(SFX_EBEEP4);
				if(lastGuiButtonPressed == 2)
				{
					player->SetAtk(player->GetAtk() - atkOffset);
				}
				if(lastGuiButtonPressed == 3)
				{
					player->SetAgi(player->GetAgi() - agiOffset);
					player->SetMaxShields(player->GetMaxShields() + mShieldOffset);
				}
				lastGuiButtonPressed = 4;
			

				stopShield = false;              // used for various computations. 1. shield regen.
				overShield = true;
				agilityMode = false;
				
				player->SetMaxShields(player->GetMaxShields() + mShieldOffset);

				baseAtk = player->GetAtk();
				player->SetAtk(player->GetAtk() / 2);
				

			}
			changeStats = false;
		}
		
		if ((touch.px > 206) && (touch.px < 240))
			{
				if ((touch.py > 35) && (touch.py < 64))
				{
					if ((!helpScreen) && (!titleScreen)){
					Render::Instance()->InitFont();
					helpScreen = true;
					pause = true;
					Render::Instance()->DisplayHelpScreen();}
				}
			}
			
			if ((helpScreen) && (touch.px > 12) && (touch.px < 35) && (touch.py > 161) && (touch.py < 183))
			{
				if (guiButton1Pressed)
					Render::Instance()->ChangeGUI(1);
				if (guiButton2Pressed)
					Render::Instance()->ChangeGUI(2);
				if (guiButton3Pressed)
					Render::Instance()->ChangeGUI(3);
				if (guiButton4Pressed)
					Render::Instance()->ChangeGUI(4);
				
				//pause = false;
				helpScreen = false;
			}
		
		
}




int main()
{


    /*  Turn on the 2D graphics core. */
    powerOn(POWER_ALL_2D);

    /*
     *  Configure the VRAM and background control registers.
     *
     *  Place the main screen on the top physical screen. Then arrange the
     *  VRAM banks. Next, confiure the background control registers.
     */
	 
	lcdMainOnTop();
	
	//gameState.Intro();
	for(;;)
	{
    Render::Instance()->InitVideo();
    Render::Instance()->InitBackgrounds();
	
	InitSound();


	/* Main Screen OAM */
	OamState *oam = &oamMain;
	SpriteInfo spriteInfoMain[SPRITE_COUNT];
	
	/* Sub Screen OAM */
	OamState *oamsub = &oamSub;
	SpriteInfo spriteInfoSub[SPRITE_COUNT];
	
    InitOAM(oam, oamsub);
	
 	
	/* Make the player object */
    static const int SHUTTLE_OAM_ID = 0;
    SpriteEntry * playerEntry = &oam->oamMemory[SHUTTLE_OAM_ID];
    SpriteRotation * playerRotation = &oam->oamRotationMemory[SHUTTLE_OAM_ID];
    Player * player = new Player(&spriteInfoMain[SHUTTLE_OAM_ID]);
	player->SetAttributes(8, 2, 5, 40, 20);
	
	/* Make the enemy1 object */
    static const int ENEMY1_OAM_ID = 1;
    SpriteEntry * enemy1Entry = &oam->oamMemory[ENEMY1_OAM_ID];
    //SpriteRotation * enemy1Rotation = &oam->oamRotationMemory[ENEMY1_OAM_ID];
    Enemy * enemy1 = new Enemy(&spriteInfoMain[ENEMY1_OAM_ID]);
	enemy1->SetAttributes(5,1,1,5,5);
	
	/* Make the enemy2 object */
    static const int ENEMY2_OAM_ID = 2;
    SpriteEntry * enemy2Entry = &oam->oamMemory[ENEMY2_OAM_ID];
    //SpriteRotation * enemy2Rotation = &oam->oamRotationMemory[ENEMY2_OAM_ID];
    Enemy * enemy2 = new Enemy(&spriteInfoMain[ENEMY2_OAM_ID]);
	enemy2->SetAttributes(5,1,1,5,5);
	
	/* Make the enemy3 object */
    static const int ENEMY3_OAM_ID = 3;
    SpriteEntry * enemy3Entry = &oam->oamMemory[ENEMY3_OAM_ID];
    //SpriteRotation * enemy3Rotation = &oam->oamRotationMemory[ENEMY3_OAM_ID];
    Enemy * enemy3 = new Enemy(&spriteInfoMain[ENEMY3_OAM_ID]);
	enemy3->SetAttributes(5,1,1,5,5);
	
	static const int BOSS1_OAM_ID = 4;
	SpriteEntry * boss1Entry = &oam->oamMemory[BOSS1_OAM_ID];
	//SpriteRotation * boss1Rotation = &oam->oamRotationMemory[BOSS1_OAM_ID];
	Enemy * boss1 = new Enemy(&spriteInfoMain[BOSS1_OAM_ID]);
	boss1->SetAttributes(10,10,2, 50, 50);
	
	/* Make the enemy3 object */
    static const int ENEMY5_OAM_ID = 5;
    SpriteEntry * enemy5Entry = &oam->oamMemory[ENEMY5_OAM_ID];
    //SpriteRotation * enemy5Rotation = &oam->oamRotationMemory[ENEMY5_OAM_ID];
    Enemy * enemy5 = new Enemy(&spriteInfoMain[ENEMY5_OAM_ID]);
	enemy5->SetAttributes(7,2,1,10,10);
	
	/* Make th//e enemy3 object */
    static const int ENEMY6_OAM_ID = 6;
    SpriteEntry * enemy6Entry = &oam->oamMemory[ENEMY6_OAM_ID];
    //SpriteRotation * enemy3Rotation = &oam->oamRotationMemory[ENEMY3_OAM_ID];
    Enemy * enemy6 = new Enemy(&spriteInfoMain[ENEMY6_OAM_ID]);
	enemy6->SetAttributes(7,2,1,10,10);
	
	/* Make the enemy3 object */
    static const int ENEMY7_OAM_ID = 7;
    SpriteEntry * enemy7Entry = &oam->oamMemory[ENEMY7_OAM_ID];
    //SpriteRotation * enemy7Rotation = &oam->oamRotationMemory[ENEMY7_OAM_ID];
    Enemy * enemy7 = new Enemy(&spriteInfoMain[ENEMY7_OAM_ID]);
	enemy7->SetAttributes(7,2,2,10,10);
	
	static const int BOSS2_OAM_ID = 8;
	SpriteEntry * boss2Entry = &oam->oamMemory[BOSS2_OAM_ID];
	//SpriteRotation * boss2Rotation = &oam->oamRotationMemory[BOSS2_OAM_ID];
	Enemy * boss2 = new Enemy(&spriteInfoMain[BOSS2_OAM_ID]);
	boss2->SetAttributes(15,10,3, 50, 50);	
	
	static const int BOSS3_OAM_ID = 9;
	SpriteEntry * boss3Entry = &oam->oamMemory[BOSS3_OAM_ID];
	//SpriteRotation * boss2Rotation = &oam->oamRotationMemory[BOSS2_OAM_ID];
	Enemy * boss3 = new Enemy(&spriteInfoMain[BOSS3_OAM_ID]);
	boss3->SetAttributes(20,20,3, 50, 50);	
	
	/* Make the enemy3 object */
    static const int ENEMY10_OAM_ID = 10;
    SpriteEntry * enemy10Entry = &oam->oamMemory[ENEMY10_OAM_ID];
    //SpriteRotation * enemy7Rotation = &oam->oamRotationMemory[ENEMY7_OAM_ID];
    Enemy * enemy10 = new Enemy(&spriteInfoMain[ENEMY10_OAM_ID]);
	enemy10->SetAttributes(7,2,2,10,10);
	
	/* Make the enemy3 object */
    static const int ENEMY11_OAM_ID = 11;
    SpriteEntry * enemy11Entry = &oam->oamMemory[ENEMY11_OAM_ID];
    //SpriteRotation * enemy7Rotation = &oam->oamRotationMemory[ENEMY7_OAM_ID];
    Enemy * enemy11 = new Enemy(&spriteInfoMain[ENEMY11_OAM_ID]);
	enemy11->SetAttributes(7,2,1,10,10);
	
	/* Make the enemy3 object */
    static const int ENEMY12_OAM_ID = 12;
    SpriteEntry * enemy12Entry = &oam->oamMemory[ENEMY12_OAM_ID];
    //SpriteRotation * enemy7Rotation = &oam->oamRotationMemory[ENEMY7_OAM_ID];
    Enemy * enemy12 = new Enemy(&spriteInfoMain[ENEMY12_OAM_ID]);
	enemy12->SetAttributes(7,2,2,10,10);
	
	/* Make the enemy3 object */
    static const int ENEMY13_OAM_ID = 13;
    SpriteEntry * enemy13Entry = &oam->oamMemory[ENEMY13_OAM_ID];
    //SpriteRotation * enemy7Rotation = &oam->oamRotationMemory[ENEMY7_OAM_ID];
    Enemy * enemy13 = new Enemy(&spriteInfoMain[ENEMY13_OAM_ID]);
	enemy13->SetAttributes(7,2,2,10,10);


	
	BulletManager * bulletManager = new BulletManager(spriteInfoMain, oam);
	
	bool playSoundBoss[3] = {false};
	//used to determine if previous wireframe for hull was set to 0
	bool previousFrame0 = true;
	
	player->SetMaxEnemiesToBoss(enemiesPerWave);

	titleScreen = true;
	GameState::Instance()->Intro();
	GameState::Instance()->Title();
	
	GameState::Instance()->StartGame(player, enemy1, enemy2, enemy3, enemy5, enemy6, enemy7, enemy10, enemy11, enemy12, enemy13, boss1, boss2, boss3, oam,
						oamsub,  spriteInfoMain, spriteInfoSub);
	
	
	/* Main Game Loop */
	//mmStop();
	mmStart(MOD_MFIRSTHALF, MM_PLAY_LOOP);
	
    for (;reset == false;) {
	
	
	
		// Pause Game
		if (keysDown() & KEY_START) 
		{
			pause = true;
		}
		for(;pause == true;)
		{
			scanKeys();
			touchPosition touch;
			touchRead(&touch);	
			touchControls(touch, player);		//calls function to change the ui
			//oamClear(oamsub,0,0);
			if (helpScreen)
				oamDisable(oamsub);
				
		Render::Instance()->InitFont();
		if (!helpScreen){
			Render::Instance()->StatText(player->GetShields(), player->GetArmor(), player->GetHull(),
									  player->GetMaxShields(), player->GetMaxArmor(), player->GetMaxHull(),
									  player->GetEnemiesKilled(), player->GetMaxEnemiesToBoss());
		
		
			Render::Instance()->ScoreText(player->ReturnScore());
			Render::Instance()->AttributeText(player->GetAtk(), player->GetDef(), player->GetAgi());
			oamEnable(oamsub);

		}	
			if ((keysDown() & KEY_START) && (!helpScreen)) 
			{
				pause = false;
			}
		
			swiWaitForVBlank();
			UpdateOAMSub(oamsub);
		}
		
        /* Update the game state. */
	    scanKeys();
		player->InGameInput(bulletManager, oam);
        player->move();
		
		
		/* Determine voice sound for boss */
		for (int i = 0; i < 3; i++){
			if ((playSoundBoss[i]) && (i == 0))
			{
				mmEffect(SFX_EDESTROY);
				playSoundBoss[i] = false;
			}
			if ((playSoundBoss[i]) && (i == 1))
			{
				mmEffect(SFX_EANNIHILATE);
				playSoundBoss[i] = false;
			}
			if ((playSoundBoss[i]) && (i == 2))
			{
				mmEffect(SFX_EERADICATE);
				playSoundBoss[i] = false;
			}
		}
		
		
		touchPosition touch;
		touchRead(&touch);	
		touchControls(touch, player);		//calls function to change the ui
	
        /* Update ship sprite attributes. */
        MathVector2D<float> playerPosition = player->GetPosition();
        playerEntry->x = (int)playerPosition.x;
        playerEntry->y = (int)playerPosition.y;
        RotateSprite(playerRotation, player->GetAngleDeg());
		player->SetBounds(playerPosition.x+16, playerPosition.y+16, 16);
		
		bulletManager->UpdateBullets();		
		
		if (!stopShield){
		if(counter >= countLimit)
		{
			if(player->GetShields() < player->GetMaxShields())
			{ player->SetShields(player->GetShields()+1);}
			counter = 0;}
		}
		
		
		Render::Instance()->InitFont();
		Render::Instance()->StatText(player->GetShields(), player->GetArmor(), player->GetHull(),
									  player->GetMaxShields(), player->GetMaxArmor(), player->GetMaxHull(),
									  player->GetEnemiesKilled(), player->GetMaxEnemiesToBoss());
		
		
		Render::Instance()->ScoreText(player->ReturnScore());
		Render::Instance()->AttributeText(player->GetAtk(), player->GetDef(), player->GetAgi());
		
		
		if (((float)player->GetShields() / (float)player->GetMaxShields()) * 100 < 10)
			Wireframe::Instance()->UpdateWireframeShield(0, oamsub, spriteInfoSub);
		else
			Wireframe::Instance()->UpdateWireframeShield(1, oamsub, spriteInfoSub);
			
			
		if (((float)player->GetArmor() / (float)player->GetMaxArmor()) * 100 < 40)
			Wireframe::Instance()->UpdateWireframeSpecks(1, oamsub, spriteInfoSub);
		else
			Wireframe::Instance()->UpdateWireframeSpecks(0, oamsub, spriteInfoSub);
		
		
		if (((float)player->GetHull() / (float)player->GetMaxHull()) * 100 < 100){
			if (previousFrame0)
				mmEffect(SFX_EWARNINGBEEP);
			previousFrame0 = false;
			Wireframe::Instance()->UpdateWireframeHull(1, oamsub, spriteInfoSub);}
			
		else{
			previousFrame0 = true;
			Wireframe::Instance()->UpdateWireframeHull(0, oamsub, spriteInfoSub);}
		
		SpawnEnemies(spawnIndex, player, enemy1, enemy2, enemy3, enemy5, enemy6, enemy7, enemy10, enemy11, enemy12, enemy13, 
					boss1, boss2, boss3, enemy1Entry, enemy2Entry, enemy3Entry, enemy5Entry, enemy6Entry, enemy7Entry, enemy10Entry, 
					enemy11Entry, enemy12Entry, enemy13Entry, boss1Entry, boss2Entry, boss3Entry, bulletManager, playSoundBoss, enemiesPerWave);
		
		
		if (counter > 20)
			titleScreen = false;
			
		if ((!overShield) && (!agilityMode))
			counter += .5;
		
		if (agilityMode)
			counter += 0.16;
			
		if (overShield)
			counter += 1.5;
			
			//WD8Q3-J7CP3-7DCYF-73RYR-M79YB
		// PLAYER DEAD
		if (player->GetHull() <= 0){
			GameState::Instance()->GameOver(oam, oamsub);
			reset = true;
			spawnIndex = 0;  // just in case
			player->ResetAll();
		}	
		// PLAYER BEATS GAME
		//if (player->gameWin == true)
		if (spawnIndex == 19)
		{
			InitOAM(oam, oamsub);
			Render::Instance()->InitFont();
			GameState::Instance()->Ending();
			spawnIndex = 0;
			//player->gameWin = false;
			reset = true;
			player->ResetAll();
		}	
		
			
        /*
         *  Update the OAM.
         *
         *  We have to copy our copy of OAM data into the actual OAM during
         *  VBlank (writes to it are locked during other times).
         */
        swiWaitForVBlank();
        UpdateOAM(oam, oamsub);
    }
	
	// GAME IS RESTARTING
	
	oamClear(oam,0,0);
	oamClear(oamsub,0,0);
	InitOAM(oam,oamsub);
	reset = false;
	
	//Re-Init Globals
	guiButton1Pressed = true;
	guiButton2Pressed = false;
	guiButton3Pressed = false;
	guiButton4Pressed = false;
	changeStats = false;
	mShieldOffset = 28;
	agiOffset = 5;
	atkOffset = 5;
	armorOffset = 30;
	counter = 0;
	countLimit = 30;
	spawnIndex = 0;
	reset = false;
	pause = false;
	stopShield = false;
	overShield = false;
	agilityMode = false;
	enemiesPerWave = 8;

}

    return 0;
}
