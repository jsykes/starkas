/*
 *  GameState.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */

#include "gameState.h"

// GLOBALS
bool exitLoop = false;

// Global static pointer used to ensure a single instance of the class.
GameState* GameState::m_pInstance = NULL;

// This function is called to create an instance of the class. Calling the
// constructor publicly is not allowed. The constructor is private and is 
// only called by this Instance function
GameState* GameState::Instance()
{
	if(!m_pInstance) // Only allow one instance of class to be generated.
	m_pInstance = new GameState;
	return m_pInstance;
}

void StoryWait ( int seconds )
{
	int time_left = seconds * 60;
	do
	{
		scanKeys();
		if(keysDown() & KEY_A)
			{exitLoop = true; break;}
		swiWaitForVBlank();
		time_left--;
	}while(time_left > 0);
}

void GameState::Wait ( int seconds )
{
	int time_left = seconds * 60;
	do
	{
		swiWaitForVBlank();
		time_left--;
	}while(time_left > 0);
}

void GameState::Intro()
{
	do
	{
		Render::Instance()->DisplayBlankMain();
		Render::Instance()->DisplayBlankSub();
		StoryWait(2);
		if(exitLoop == true)
			break;
		mmStart(MOD_MINTRO, MM_PLAY_LOOP );	
		StoryWait(4);
		if(exitLoop == true)
			break;
		Render::Instance()->DisplayTeamLogo();
		StoryWait(8);
		if(exitLoop == true)
			break;
		Render::Instance()->DisplayBlankMain();
		Render::Instance()->DisplayBlankSub();
		Wait(3);
		if(exitLoop == true)
			break;
		StoryWait(3);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory1();
		Render::Instance()->StoryText("\n\nIn the year 1986, a great \n\ndiscovery was made. It was an \n\n"
										"ancient aircraft that must \n\nhave been buried long ago.");
		StoryWait(10);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory2();
		Render::Instance()->StoryText("\n\nThe information was kept\n\nsecret, and was taken\n\nunderground "
										"for study.");
		StoryWait(8);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory3();
		Render::Instance()->StoryText("\n\nThe study has shown great\n\ntechnology, but much of it was\n\n"
										"inoperable. The ship was badly\n\ndamaged and unable to fly.");
		StoryWait(10);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory4();
		Render::Instance()->StoryText("\n\nThe potential for such an\n\naircraft was immense. So the\n\n"
										"decision was made to rebuild\n\nit...\n\n\nThe craft later became known\n\n"
										"as Starkas.");
		StoryWait(12);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		//Render::Instance()->Story5();
		Render::Instance()->StoryText("\n\nWith a mix between alien\n\nand human technology, this ship\n\n"
										"was to become a weapon.");
		StoryWait(8);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		//Render::Instance()-Story6();
		Render::Instance()->StoryText("\n\nBecause the core design was\n\nalien, additions to it were\n\n"
										"possible..\n\n\n\nOne addition was the ability\n\nto harvest "
										"scrap to use\n\nfor upgrades..");
		StoryWait(10);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory7();
		Render::Instance()->StoryText("\n\nTwenty five years later..\n\nthe design was coming along\n\nwell..\n\n\n\n"
										"                         until..");
		StoryWait(8);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory5();
		Render::Instance()->StoryText("\n\nA fleet of alien ships\n\nentered earth's atmosphere.\n\n"
										"It was clear what they wanted..");
		StoryWait(6);
		if(exitLoop == true)
			break;
		Render::Instance()->DisplayLevelOne(); 
		StoryWait(6);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->StoryText("\n\nThe only choice is to fight..\n\nand there is only one asset\n\n"
										"that can stand a chance..");
		StoryWait(8);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->StoryText("\n\nand Starkas isn't what it\n\nused to be...");
		StoryWait(6);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		Render::Instance()->DisplayStory6();
		Render::Instance()->StoryText("\n\n\n\nJohn Sykes\n\n     &\n\n    Daniel O'Sullivan\n\n\n\n            Presents..");
		StoryWait(8);
		if(exitLoop == true)
			break;
		Render::Instance()->InitFont();
		mmStop();
		
	}while(0);
   
    exitLoop = false;
    /* Intro game state ended */
}

void GameState::Title()
{
	Render::Instance()->InitFont();
	mmStop();
	mmEffect(SFX_EXPLOSION);
	mmEffect(SFX_EXPLOSION);
	mmEffect(SFX_EXPLOSION);

	/* Display the backgrounds. */
	Render::Instance()->DisplayTitleScreenMain();
	Render::Instance()->DisplayTitleScreenSub();
   
	touchPosition touch;
	touchRead(&touch);
   
	/* Check if user touched screen to proceed */
	bool exit = false;
	do { 
	scanKeys();
	if(keysHeld() & KEY_TOUCH)
	{
	   exit = true;	
	}
	
	} while (exit == false);
}

void GameState::StartGame(Player * player, Enemy * enemy1, Enemy * enemy2, Enemy * enemy3, Enemy * enemy5, Enemy * enemy6, Enemy * enemy7,
							Enemy * enemy10, Enemy * enemy11, Enemy * enemy12, Enemy * enemy13, Enemy * boss1, Enemy * boss2, 
							Enemy * boss3, OamState * oam, OamState * oamsub, SpriteInfo * spriteInfoMain, SpriteInfo * spriteInfoSub)
{
   /* Load the backgrounds. */
   Render::Instance()->DisplayLevelOne();
   
   /* Load Player Graphics */
   Render::Instance()->DisplayPlayer(oam, spriteInfoMain, true);
   
   /* Load enemy ship graphics */
   Render::Instance()->DisplayEnemy(1, oam, spriteInfoMain, true);
   Render::Instance()->DisplayEnemy(2, oam, spriteInfoMain, true);
   Render::Instance()->DisplayEnemy(3, oam, spriteInfoMain, true);
   Render::Instance()->DisplayBoss1(4, oam, spriteInfoMain, true);
   Render::Instance()->DisplayEnemy2(5, oam, spriteInfoMain, true);
   Render::Instance()->DisplayEnemy2(6, oam, spriteInfoMain, true);
   Render::Instance()->DisplayEnemy2(7, oam, spriteInfoMain, true);
   Render::Instance()->DisplayBoss2(8, oam, spriteInfoMain, true);
   Render::Instance()->DisplayBoss3(9, oam, spriteInfoMain, true);
   
   /* Initialize the wireframe */
   Render::Instance()->DisplayWireframeShip(oamsub, spriteInfoSub, 60, 100, 0);   // number at end is the gfx and sprite id
   Render::Instance()->DisplayWireframeShield(oamsub, spriteInfoSub, 60, 100, 1);  
   Render::Instance()->DisplayWireframeSpecks(oamsub, spriteInfoSub, 257, 100, 2);
   Render::Instance()->DisplayWireframeHull(oamsub, spriteInfoSub, 257, 100, 3);
   
   /* Load upgrade buttons */
   Render::Instance()->DisplayButton(oamsub, spriteInfoSub, 206, 68, 4);
   Render::Instance()->DisplayButton(oamsub, spriteInfoSub, 206, 92, 5);
   Render::Instance()->DisplayButton(oamsub, spriteInfoSub, 206, 117, 6);
   Render::Instance()->DisplayButton(oamsub, spriteInfoSub, 206, 142, 7);
	
   Render::Instance()->ChangeGUI(1);

   /* Set up players position */
   player->SetPositionX(150);
   player->SetPositionY(150);
   
   /* Position enemy ships */
   enemy1->SetPositionX(100);
   enemy1->SetPositionY(-25);
   
   enemy2->SetPositionX(110);
   enemy2->SetPositionY(-25);
   
   enemy3->SetPositionX(90);
   enemy3->SetPositionY(-25);
   
   boss1->SetPositionX(-64);
   boss1->SetPositionY(-64);
   
   boss2->SetPositionX(-64);
   boss2->SetPositionY(-64);
   
   boss3->SetPositionX(-64);
   boss3->SetPositionY(-64);
   
   enemy5->SetPositionX(40);
   enemy5->SetPositionY(-32);
   enemy5->stopAI = true;
   
   enemy6->SetPositionX(100);
   enemy6->SetPositionY(-32);
   enemy6->stopAI = true;
   
   enemy7->SetPositionX(50);
   enemy7->SetPositionY(-32);
   enemy7->stopAI = true;
   
   enemy10->SetPositionX(-32);
   enemy10->SetPositionY(-32);
   enemy10->stopAI = true;
   
   enemy11->SetPositionX(50);
   enemy11->SetPositionY(-32);
   enemy11->stopAI = true;
   
   enemy12->SetPositionX(75);
   enemy12->SetPositionY(-32);
   enemy12->stopAI = true;
   
   enemy13->SetPositionX(100);
   enemy13->SetPositionY(-32);
   enemy13->stopAI = true;
    
   /* Initialize the Font */
   Render::Instance()->InitFont();  
}

void GameState::GameOver(OamState * oam, OamState * oamsub)
{
	// Clears all the sprites
	oamClear(oamsub,0,0);
	InitOAM(oam, oamsub);
	
	// Game over sequence
	Render::Instance()->DisplayBlankSub();
	mmStart(MOD_MENDING, MM_PLAY_LOOP);
	Render::Instance()->InitFont();
	Render::Instance()->GameOverText();
	Wait(7);
	Render::Instance()->InitFont();
	mmStop();
}

void GameState::Ending()
{
	Render::Instance()->InitFont();
	Render::Instance()->DisplayStory6();
	Render::Instance()->DisplayBlankSub();
	Wait(5);
	Render::Instance()->InitFont();
	Render::Instance()->StoryText("Congratulations!!\n\n\nEarth has been saved\nfrom the alien threat!\n\n\n\n               ...For now..");
	Wait(10);
	StoryWait(240);
	Render::Instance()->InitFont();
	mmStop();
}