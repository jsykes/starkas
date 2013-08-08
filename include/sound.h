

#ifndef SOUND_H
#define SOUND_H
/*
 *  Sound.h
 * 
 *  Created by John Sykes & Daniel O'Sullavan on 5/24/10.
 *  Copyright 2010.
 *
 */

 
 
 /* Sounds */
#include "soundbank.h"
#include "soundbank_bin.h"
#include <maxmod9.h>
#include <string>



class Sound
{

public:

Sound();

int b;

void PlaySound(std::string a);



};


#endif

