#pragma once
#include <windows.h>

#include <dsound.h>

#include "dsutil.h"

#include <string>
using namespace std;


#ifndef _DXAUDIO_H
#define _DXAUDIO_H

// DirectSound functions and variables
class sound
{
public:
	LPDIRECTSOUND8        g_pDS;	// The DirectSound Device

public:
	bool initDirectSound(HWND hwnd);
	void shutdownDirectSound(void);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);
	
	void playSound(LPDIRECTSOUNDBUFFER whichBuffer);
	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer);
	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer);

};

#endif