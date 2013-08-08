/*
 *  Render.cpp
 *  
 *
 *  Created by John Sykes & Daniel O'Sullavan
 *  Copyright 2010.
 *
 */
 
#include "render.h"
 
// Global static pointer used to ensure a single instance of the class.
Render* Render::m_pInstance = NULL;

// This function is called to create an instance of the class. Calling the
// constructor publicly is not allowed. The constructor is private and is 
// only called by this Instance function
Render* Render::Instance()
{
	if(!m_pInstance) // Only allow one instance of class to be generated.
	m_pInstance = new Render;
	return m_pInstance;
}

/*  Define some sprite configuration specific constants. Was part of initSprites function.
* 
*  We will use these to compute the proper index into memory for certain
*  tiles or palettes.
*
*  OFFSET_MULTIPLIER is calculated based on the following formula from
*  GBATEK (http://nocash.emubase.de/gbatek.htm#dsvideoobjs):
*      TileVramAddress = TileNumber * BoundaryValue
*  Since SPRITE_GFX is a uint16*, the compiler will increment the address
*  it points to by 2 for each change in 1 of the array index into
*  SPRITE_GFX. (The compiler does pointer arithmetic.)
*/

	static const int BYTES_PER_16_COLOR_TILE = 32;
	static const int COLORS_PER_PALETTE = 16;
	static const int BOUNDARY_VALUE = 32; // This is the default boundary value (can be set in REG_DISPCNT)
	static const int OFFSET_MULTIPLIER = BOUNDARY_VALUE / sizeof(SPRITE_GFX[0]);
	static const int OFFSET_MULTIPLIER_SUB = BOUNDARY_VALUE / sizeof(SPRITE_GFX_SUB[0]);
	
	/* Keep track of the available tiles (for sprites) */
	int nextAvailableTileIdxMain = 0;
	int nextAvailableTileIdxSub = 0;
 
void createSprite(OamState * oam, SpriteInfo *spriteInfo, const void* spriteName_Pal, uint32 spriteName_Pal_Len,
          const void* spriteName_Tiles, uint32 spriteName_Tiles_Len,int OAM_ID, bool isMainScreen,int width, int height, int angle, int x, int y, int size)
{

	/* Create the sprite. */
    assert(OAM_ID < SPRITE_COUNT);
    spriteInfo = &spriteInfo[OAM_ID];
    SpriteEntry * spriteEntry = &oam->oamMemory[OAM_ID];
	
	/* Initialize spriteEntry */
    spriteInfo->oamId = OAM_ID;
    spriteInfo->width = width;
    spriteInfo->height = height;
    spriteInfo->angle = angle;
    spriteInfo->entry = spriteEntry;
	//spriteInfo->gfx = oamAllocateGfx(oam, SpriteSize_32x32, SpriteColorFormat_16Color);
	
	/*
     *  Configure attribute 0. 
     *
     *  OBJCOLOR_16 will make a 16-color sprite. We specify that we want an
     *  affine sprite (via isRotateScale) here because we would like to rotate
     *  the ship.
     */
    //spriteEntry->y = SCREEN_HEIGHT / 2 - spriteInfo->height;
	spriteEntry->y = y;
    spriteEntry->isRotateScale = true;
    /* This assert is a check to see a matrix is available to store the affine
     * transformation matrix for this sprite. Of course, you don't have to have
     * the matrix id match the affine id, but if you do make them match, this
     * assert can be helpful. */
    assert(!spriteEntry->isRotateScale || (spriteInfo->oamId < MATRIX_COUNT));
    spriteEntry->isSizeDouble = false;
    spriteEntry->blendMode = OBJMODE_NORMAL;
    spriteEntry->isMosaic = false;
    spriteEntry->colorMode = OBJCOLOR_16;
    spriteEntry->shape = OBJSHAPE_SQUARE;
	
    /*
     *  Configure attribute 1.
     *
     *  rsMatrixId refers to the loation of affine transformation matrix. We
     *  set it to a location computed with a macro. OBJSIZE_32, in our case
     *  since we are making a square sprite, creates a 32x32 sprite.
     */
    //spriteEntry->x = SCREEN_WIDTH / 2 - spriteInfo->width * 2 +
    //                spriteInfo->width / 2;
	spriteEntry->x = x;
    spriteEntry->rotationIndex = spriteInfo->oamId;
    
	if (size == 32)
		spriteEntry->size = OBJSIZE_32;
	if (size == 64)
		spriteEntry->size = OBJSIZE_64;

    /* 
     *  Configure attribute 2.
     * 
     *  Configure which tiles the sprite will use, which priority layer it will
     *  be placed onto, which palette the sprite should use, and whether or not
     *  to show the sprite.
     */
	if(isMainScreen) 
	{
		spriteEntry->gfxIndex = nextAvailableTileIdxMain;
		nextAvailableTileIdxMain += spriteName_Tiles_Len / BYTES_PER_16_COLOR_TILE;
	}
	if(!isMainScreen)
	{
		spriteEntry->gfxIndex = nextAvailableTileIdxSub;
		nextAvailableTileIdxSub += spriteName_Tiles_Len / BYTES_PER_16_COLOR_TILE;
	}
	
    spriteEntry->priority = OBJPRIORITY_1;
    spriteEntry->palette = spriteInfo->oamId;

    /* Rotate the sprite */
    RotateSprite(&oam->oamRotationMemory[spriteInfo->oamId],
                 spriteInfo->angle);


	if(isMainScreen == true)
	{
		/* Copy over the sprite palettes */
		dmaCopyHalfWords(SPRITE_DMA_CHANNEL,
						 spriteName_Pal,
						 &SPRITE_PALETTE[spriteInfo->oamId *
										 COLORS_PER_PALETTE],
						 spriteName_Pal_Len);
						 
		/* Copy the sprite graphics to sprite graphics memory */
		dmaCopyHalfWords(SPRITE_DMA_CHANNEL,
						 spriteName_Tiles,
						 &SPRITE_GFX[spriteEntry->gfxIndex * OFFSET_MULTIPLIER],
						 spriteName_Tiles_Len);
	}
	else
	{
		/* Copy over the sprite palettes */
		dmaCopyHalfWords(SPRITE_DMA_CHANNEL,
						 spriteName_Pal,
						 &SPRITE_PALETTE_SUB[spriteInfo->oamId *
										 COLORS_PER_PALETTE],
						 spriteName_Pal_Len);
						 
	/* Copy the sprite graphics to sprite graphics memory */
		dmaCopyHalfWords(SPRITE_DMA_CHANNEL,
						 spriteName_Tiles,
						 &SPRITE_GFX_SUB[spriteEntry->gfxIndex * OFFSET_MULTIPLIER_SUB],
						 spriteName_Tiles_Len);
	}
}

void Render::InitFont()
{
	const int tile_base = 0;
	const int map_base = 7;

    consoleInit(&bottomScreen,1, BgType_Text4bpp, BgSize_R_128x128 , tile_base, map_base, false, false);

	ConsoleFont font;

	font.gfx = (u16*)fontTiles;
	font.pal = (u16*)fontPal;
	font.numChars = 95;
	font.numColors =  fontPalLen / 2;
	font.bpp = 4;
	font.asciiOffset = 32;
	font.convertSingleColor = false;
	
	consoleSetFont(&bottomScreen, &font);
}

void Render::StatText(int s, int a, int h, int ms, int ma, int mh, int killCount, int untilBoss)
{
	consoleSetWindow(&bottomScreen, 6, 2, 15, 5);
	std::cout << "Shield: " << s << "/" << ms;
	std::cout << "\nArmor:  " << a << "/" << ma;
	std::cout << "\nHull:   " << h << "/" << mh;
	std::cout << "\n\nKills: " << killCount << "/" << untilBoss;
}

void Render::ScoreText(int score)
{
	consoleSetWindow(&bottomScreen, 20, 2, 22, 5);
	std::cout << "Scrap " << score;
}

void Render::AttributeText(int atk, int def, int agi)
{
	consoleSetWindow(&bottomScreen, 18, 10, 35, 16);
	std::cout << "Atk: " << atk;
	std::cout << "\n\n\nDef: " << def;
	std::cout << "\n\n\nAgi: " << agi;
	std::cout << "\n\n\nRepair ";
}

void Render::GameOverText()
{
	consoleSetWindow(&bottomScreen, 0, 2, 32, 16);
	std::cout << "\n\nYou have lost the war,\n\nand Earth has been overrun... \n\n\n\n                     SAD DAY";
}

void Render::StoryText(std::string text)
{
	consoleSetWindow(&bottomScreen, 0, 2, 32, 16);
	std::cout << text;
}

void Render::InitVideo()
{
    /*
     *  Map VRAM to display a background on the main and sub screens.
     * 
     *  The vramSetMainBanks function takes four arguments, one for each of the
     *  major VRAM banks. We can use it as shorthand for assigning values to
     *  each of the VRAM bank's control registers.
     *
     *  We map banks A and B to main screen  background memory. This gives us
     *  256KB, which is a healthy amount for 16-bit graphics.
     *
     *  We map bank C to sub screen background memory.
     *
     *  We map bank D to LCD. This setting is generally used for when we aren't
     *  using a particular bank.
     *
     *  We map bank E to main screen sprite memory (aka object memory).
     */
	 
	 vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                     VRAM_B_MAIN_BG_0x06020000,
                     VRAM_C_SUB_BG_0x06200000,
                     VRAM_D_SUB_SPRITE);

    vramSetBankE(VRAM_E_MAIN_SPRITE);
	vramSetBankF(VRAM_F_MAIN_SPRITE);
	vramSetBankI(VRAM_I_SUB_SPRITE);
	
	/*  Set the video mode on the main screen. */
    videoSetMode(MODE_5_2D | // Set the graphics mode to Mode 5
                 DISPLAY_BG2_ACTIVE | // Enable BG2 for display
                 DISPLAY_BG3_ACTIVE | // Enable BG3 for display
                 DISPLAY_SPR_ACTIVE | // Enable sprites for display
                 DISPLAY_SPR_1D       // Enable 1D tiled sprites
                 );

	//Set the video mode on the sub screen. 
	videoSetModeSub(MODE_5_2D | // Set the graphics mode to Mode 5
                    DISPLAY_BG3_ACTIVE |  // Enable BG3 for display
					DISPLAY_SPR_ACTIVE |  // Enable sprites for display
					DISPLAY_SPR_1D);

}
 
void Render::InitBackgrounds()
{
    /*  Set up affine background 3 on main as a 16-bit color background. */
    REG_BG3CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(0) | // The starting place in memory
                 BG_PRIORITY(3); // A low priority

    /*  Set the affine transformation matrix for the main screen background 3
     *  to be the identity matrix.
     */
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

    /*  Place main screen background 3 at the origin (upper left of the
     *  screen).
     */
    REG_BG3X = 0;
    REG_BG3Y = 0;

    /*  Set up affine background 2 on main as a 16-bit color background. */
    REG_BG2CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(8) | // The starting place in memory
                 BG_PRIORITY(2);  // A higher priority

    /*  Set the affine transformation matrix for the main screen background 3
     *  to be the identity matrix.
     */
    REG_BG2PA = 1 << 8;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1 << 8;

    /*  Place main screen background 2 in an interesting place. */
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8;
    REG_BG2Y = -32 << 8;

    /*  Set up affine background 3 on the sub screen as a 16-bit color
     *  background.
     */
    REG_BG3CNT_SUB = BG_BMP16_256x256 |
                     BG_BMP_BASE(9) | // The starting place in memory
                     BG_PRIORITY(3); // A low priority

    /*  Set the affine transformation matrix for the sub screen background 3
     *  to be the identity matrix.
     */
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;

    /*
     *  Place main screen background 3 at the origin (upper left of the screen)
     */
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
}

void Render::DisplayEnemy(int ID, OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen)
{
	createSprite(oam, spriteInfo, enemyShipPal, enemyShipPalLen, enemyShipTiles, enemyShipTilesLen, ID, isMainScreen, 32, 32, 29000, -32, -32, 32);
}

void Render::DisplayEnemy2(int ID, OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen)
{
	createSprite(oam, spriteInfo, enemyShip2Pal, enemyShip2PalLen, enemyShip2Tiles, enemyShip2TilesLen, ID, isMainScreen, 32, 32, 29000, -32, -32, 32);
}

void Render::DisplayEnemy3(int ID, OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen)
{
	createSprite(oam, spriteInfo, enemyShip3Pal, enemyShip3PalLen, enemyShip3Tiles, enemyShip3TilesLen, ID, isMainScreen, 32, 32, 29000, -32, -32, 32);
}

void Render::DisplayBoss1(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen)
{
	createSprite(oam, spriteInfo, boss1Pal, boss1PalLen, boss1Tiles, boss1TilesLen, ID, isMainScreen, 64, 64, 29000, -64, -64, 64);
}

void Render::DisplayBoss2(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen)
{
	createSprite(oam, spriteInfo, boss2Pal, boss2PalLen, boss2Tiles, boss2TilesLen, ID, isMainScreen, 64, 64, 29000, -64, -64, 64);
}

void Render::DisplayBoss3(int ID, OamState * oam, SpriteInfo * spriteInfo, bool isMainScreen)
{
	createSprite(oam, spriteInfo, boss3Pal, boss3PalLen, boss3Tiles, boss3TilesLen, ID, isMainScreen, 64, 64, 29000, -64, -64, 64);
}

void Render::DisplayBullet(int ID, OamState * oam, SpriteInfo *spriteInfo, int posX, int posY, bool isMainScreen)
{
	createSprite(oam, spriteInfo, laserPal, laserPalLen, laserTiles, laserTilesLen, ID, isMainScreen, 32, 32, 29000, posX, posY, 32);
}

void Render::DisplayPlayer(OamState * oam, SpriteInfo *spriteInfo, bool isMainScreen)
{
  createSprite(oam, spriteInfo, playerShipPal, playerShipPalLen, playerShipTiles, playerShipTilesLen, 0, isMainScreen, 32, 32, 20000, 20, 50, 32);
}

void Render::DisplayWireframeShip(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID)
{
	 createSprite(oam, spriteInfo, wireframeshipPal, wireframeshipPalLen, wireframeshipTiles, wireframeshipTilesLen, ID, false, 64, 64, 0, x, y, 64);
}

void Render::DisplayWireframeShield(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID)
{
	createSprite(oam, spriteInfo, wireframeshieldPal, wireframeshieldPalLen, wireframeshieldTiles, wireframeshieldTilesLen, ID, false, 32, 32, 0, x, y, 64);
}

void Render::DisplayWireframeSpecks(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID)
{
	 createSprite(oam, spriteInfo, wireframespecksPal, wireframespecksPalLen, wireframespecksTiles, wireframespecksTilesLen, ID, false, 32, 32, 0, x, y, 64);
}

void Render::DisplayWireframeHull(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID)
{
	createSprite(oam, spriteInfo, wireframehullPal, wireframehullPalLen, wireframehullTiles, wireframehullTilesLen, ID, false, 32, 32, 0, x, y, 64);
}

void Render::DisplayButton(OamState * oam, SpriteInfo * spriteInfo, int x, int y, int ID)
{
	 createSprite(oam, spriteInfo, buttonPal, buttonPalLen, buttonTiles, buttonTilesLen, ID, false, 32, 32, 0, x, y, 32);
}

/* Main Screen */
void Render::DisplayLevelOne() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     levelOneBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM(0), /* Our address for 
                                               * background 3 */
                     levelOneBitmapLen);
}

void Render::DisplayLevelTwo()
{
	dmaCopyHalfWords(DMA_CHANNEL, level2Bitmap, (uint16 *)BG_BMP_RAM(0), level2BitmapLen);
}

void Render::DisplayHelpScreen()
{
	dmaCopyHalfWords(DMA_CHANNEL, helpscreenBitmap, (uint16 *)BG_BMP_RAM_SUB(9), helpscreenBitmapLen);
}

void Render::DisplayLevelThree()
{
	dmaCopyHalfWords(DMA_CHANNEL, level3Bitmap, (uint16 *)BG_BMP_RAM(0), level3BitmapLen);
}

void Render::DisplayLevelFour()
{
	dmaCopyHalfWords(DMA_CHANNEL, level4Bitmap, (uint16 *)BG_BMP_RAM(0), level4BitmapLen);
}

void Render::DisplayLevelFive()
{
	dmaCopyHalfWords(DMA_CHANNEL, level5Bitmap, (uint16 *)BG_BMP_RAM(0), level5BitmapLen);
}

void Render::DisplayLevelSix()
{
	dmaCopyHalfWords(DMA_CHANNEL, level6Bitmap, (uint16 *)BG_BMP_RAM(0), level6BitmapLen);
}

void Render::DisplayLevelSeven()
{
	dmaCopyHalfWords(DMA_CHANNEL, level7Bitmap, (uint16 *)BG_BMP_RAM(0), level7BitmapLen);
}

void Render::DisplayStory1()
{
	dmaCopyHalfWords(DMA_CHANNEL, story1Bitmap, (uint16 *)BG_BMP_RAM(0), story1BitmapLen);
}

void Render::DisplayStory2()
{
	dmaCopyHalfWords(DMA_CHANNEL, story2Bitmap, (uint16 *)BG_BMP_RAM(0), story2BitmapLen);
}

void Render::DisplayStory3()
{
	dmaCopyHalfWords(DMA_CHANNEL, story3Bitmap, (uint16 *)BG_BMP_RAM(0), story3BitmapLen);
}

void Render::DisplayStory4()
{
	dmaCopyHalfWords(DMA_CHANNEL, story4Bitmap, (uint16 *)BG_BMP_RAM(0), story4BitmapLen);
}

void Render::DisplayStory5()
{
	dmaCopyHalfWords(DMA_CHANNEL, story5Bitmap, (uint16 *)BG_BMP_RAM(0), story5BitmapLen);
}

void Render::DisplayStory6()
{
	dmaCopyHalfWords(DMA_CHANNEL, story6Bitmap, (uint16 *)BG_BMP_RAM(0), story6BitmapLen);
}

void Render::DisplayStory7()
{
	dmaCopyHalfWords(DMA_CHANNEL, story7Bitmap, (uint16 *)BG_BMP_RAM(0), story7BitmapLen);
}

void Render::DisplayTitleScreenMain() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     titleScreenMainBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM(0), /* Our address for 
                                               * background 3 */
                     titleScreenMainBitmapLen);
}
void Render::DisplayBlankMain() {
    dmaCopyHalfWords(DMA_CHANNEL,
                   blankBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM(0), /* Our address for 
                                               * background 3 */
                     blankBitmapLen);
}
void Render::DisplayTeamLogo() {
    dmaCopyHalfWords(DMA_CHANNEL,
                   teamLogoBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM(0), /* Our address for 
                                               * background 3 */
                     teamLogoBitmapLen);
}


/* Sub Screen */
void Render::DisplayTitleScreenSub() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     titleScreenSubBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM_SUB(9), /* Our address for sub
                                               * background 3 */
                     titleScreenSubBitmapLen);
}
void Render::DisplayBlankSub() {
    dmaCopyHalfWords(DMA_CHANNEL,
                   blankBitmap, /* This variable is generated for us by
                                       * grit. */
                     (uint16 *)BG_BMP_RAM_SUB(9), /* Our address for sub
                                               * background 3 */
                     blankBitmapLen);
}

void Render::ChangeGUI(int index)
{
	switch (index)
	{
		case 1:
			dmaCopyHalfWords(DMA_CHANNEL,
                     gui_btn1Bitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(9), 
                     gui_btn1BitmapLen);
			break;
		case 2:
			dmaCopyHalfWords(DMA_CHANNEL,
                     gui_btn2Bitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(9), 
                     gui_btn2BitmapLen);
			break;
		case 3:
			dmaCopyHalfWords(DMA_CHANNEL,
                     gui_btn3Bitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(9), 
                     gui_btn3BitmapLen);
			break;
		case 4:
			dmaCopyHalfWords(DMA_CHANNEL,
                     gui_btn4Bitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(9), 
                     gui_btn4BitmapLen);
			break;
	}
}