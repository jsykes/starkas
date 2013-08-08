/*
 *  Wireframe.h
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "render.h"

// This is a singleton
class Wireframe
{
public:

	static Wireframe* Instance();
	
	// Update the GUI of ship status
	void UpdateWireframeShield(int index, OamState * oam, SpriteInfo * spriteInfo);	
	void UpdateWireframeSpecks(int index, OamState * oam, SpriteInfo * spriteInfo);
	void UpdateWireframeHull(int index, OamState * oam, SpriteInfo * spriteInfo);


private:

	Wireframe(){}
	static Wireframe* m_pInstance;
	
};

#endif