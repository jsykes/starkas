/*
 *  Render.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 *
 * This class handles a lot of the memory management and functions related to rendering graphics to the screen. */
 
#ifndef RENDER_H
#define RENDER_H

#include "sprites.h"
#include <assert.h>
#include <stdio.h>
#include <iostream>

// Backgrounds
#include "titleScreenMain.h"
#include "titleScreenSub.h"
#include "levelOne.h"
#include "blank.h"
#include "teamLogo.h"

#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"
#include "level7.h"

#include "story1.h"
#include "story2.h"
#include "story3.h"
#include "story4.h"
#include "story5.h"
#include "story6.h"
#include "story7.h"

#include "helpscreen.h"

// GUI
#include "gui_btn1.h"
#include "gui_btn2.h"
#include "gui_btn3.h"
#include "gui_btn4.h"

// Wireframe
#include "wireframeship.h"
#include "wireframeshield.h"
#include "wireframespecks.h"
#include "wireframehull.h"

#include "font.h"

// Button
#include "button.h"

// Sprites
#include "playerShip.h"
#include "enemyShip.h"
#include "enemyShip2.h"
#include "enemyShip3.h"
#include "boss1.h"
#include "boss2.h"
#include "boss3.h"

// Bullets
#include "laser.h"

class Render
 {
 
	// Select a low priority DMA channel to perform our background copying.
	static const int DMA_CHANNEL = 3;
	
public:

	static Render* Instance();
	
	// Init
	void InitVideo();
	void InitFont();
	void InitBackgrounds();
	
	PrintConsole bottomScreen;
	
	// Text
	void StatText(int s, int a, int h, int ms, int ma, int mh, int killCount, int untilBoss);
	void ScoreText(int score);
	void AttributeText(int atk, int def, int agi);
	void StoryText(std::string text);
	void GameOverText();
	
	void ChangeGUI(int index);
	
	// Display
	void DisplayLevelOne();
	void DisplayLevelTwo();
	void DisplayLevelThree();
	void DisplayLevelFour();
	void DisplayLevelFive();
	void DisplayLevelSix();
	void DisplayLevelSeven();

	void DisplayStory1();
	void DisplayStory2();
	void DisplayStory3();
	void DisplayStory4();
	void DisplayStory5();
	void DisplayStory6();
	void DisplayStory7();
	void DisplayGUI();
	void DisplayTeamLogo();
	void DisplayBlankSub();
	void DisplayBlankMain();
	void DisplayHelpScreen();
	
	void DisplayTitleScreenSub();
	void DisplayTitleScreenMain();
	void DisplayBoss1(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen);
	void DisplayBoss2(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen);
	void DisplayBoss3(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen);
	void DisplayPlayer(OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen);
	void DisplayEnemy(int ID, OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen);
	void DisplayEnemy2(int ID, OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen);
	void DisplayEnemy3(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen);
	void DisplayBullet(int ID, OamState * oam, SpriteInfo *spriteInfo, int posX, int posY, bool isMainScreen);
	void DisplayWireframeShip(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID);
	void DisplayWireframeShield(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID);
	void DisplayWireframeSpecks(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID);
	void DisplayWireframeHull(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID);
	void DisplayButton(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID);
	void DisplayScore(int ID, OamState * oam, SpriteInfo *spriteInfo, char digit, int x);
	
private:

	Render(){}
	static Render* m_pInstance;
	
};

#endif