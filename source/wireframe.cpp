/*
 *  Wireframe.cpp
 *  
 *
 *  Edited by John Sykes & Daniel O'Sullavan
 *  Copyright 2010. All Rights Reserved.
 *
 */

#include "wireframe.h"

// Global static pointer used to ensure a single instance of the class.
Wireframe* Wireframe::m_pInstance = NULL;

// This function is called to create an instance of the class. Calling the
// constructor publicly is not allowed. The constructor is private and is 
// only called by this Instance function
Wireframe* Wireframe::Instance()
{
	if(!m_pInstance) // Only allow one instance of class to be generated.
	m_pInstance = new Wireframe;
	return m_pInstance;
}

void Wireframe::UpdateWireframeShield(int index, OamState * oam, SpriteInfo * spriteInfo)
{
	if (index == 0)
		spriteInfo[1].entry->x = 257;
	if (index == 1)
		spriteInfo[1].entry->x = 60;
}

void Wireframe::UpdateWireframeSpecks(int index, OamState * oam, SpriteInfo * spriteInfo)
{
	if (index == 0){
		spriteInfo[2].entry->priority = OBJPRIORITY_0;
		spriteInfo[2].entry->x = 257;}
	if (index == 1){
		spriteInfo[2].entry->priority = OBJPRIORITY_0;
		spriteInfo[2].entry->x = 60;}
}

void Wireframe::UpdateWireframeHull(int index, OamState * oam, SpriteInfo * spriteInfo)
{
	if (index == 0){
		spriteInfo[3].entry->priority = OBJPRIORITY_0;
		spriteInfo[3].entry->x = 257;}
	if (index == 1){
		spriteInfo[3].entry->priority = OBJPRIORITY_0;
		spriteInfo[3].entry->x = 60;}
}