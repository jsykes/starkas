/*
 *  GameState.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "enemy.h"

// This is a singleton
class GameState
{
public:

	static GameState* Instance();
	
	// Timer
	int endwait, timer;
	bool update;
	
	// States
	void Intro();
	void Title();
	void GameOver(OamState * oam, OamState * oamsub);
	void Ending();
	void Wait(int counter);
	void StartGame(Player * player, Enemy * enemy1, Enemy * enemy2, Enemy * enemy3, Enemy * enemy5, Enemy * enemy6, Enemy * enemy7,
					Enemy * enemy10, Enemy * enemy11, Enemy * enemy12, Enemy * enemy13, Enemy * boss1, Enemy * boss2, Enemy * boss3, 
					OamState * oam, OamState * oamsub, SpriteInfo *spriteInfoMain, SpriteInfo * spriteInfoSub);
					
private:

	GameState(){};
	static GameState* m_pInstance;
	
};

#endif