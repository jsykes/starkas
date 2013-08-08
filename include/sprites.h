/*
 *  Sprites.h
 *  
 *  Edited by John Sykes and Daniel O'Sullavan
 *  Copyright 2010. All rights reserved.
 *
 */
 
#ifndef SPRITES_H
#define SPRITES_H

#include <nds.h>

static const int SPRITE_DMA_CHANNEL = 3;

typedef struct {
    int oamId;
    int width;
    int height;
    int angle;
	u16* gfx;
    SpriteEntry * entry;
} SpriteInfo;

/*
 *  updateOAM
 *
 *  Update the OAM.
 *
 */
void UpdateOAM(OamState * oam, OamState * oamsub);
void UpdateOAMSub(OamState * oamsub);

/*
 *  initOAM
 *
 *  Initialize the OAM.
 *
 */
void InitOAM(OamState * oam, OamState * oamsub);

/*
 *  rotateSprite
 *
 *  Rotate a sprite.
 *
 */
void RotateSprite(SpriteRotation * spriteRotation, int angle);

/*
 *  setSpriteVisibility
 *
 *  Hide or show a sprite of a certain type: affine double bound, affine
 *  non-double bound, or ordinary.
 *
 */
void SetSpriteVisibility(SpriteEntry * spriteEntry, bool hidden,
                         bool affine = false, bool doubleBound = false);

#endif