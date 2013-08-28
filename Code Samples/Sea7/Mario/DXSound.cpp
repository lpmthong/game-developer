#include "DXSound.h"
#include "trace.h"

DXSound::DXSound(void)
{
	this->m_pSoundManager = NULL;
}

DXSound::~DXSound(void)
{
}


BOOL DXSound::Init(HWND hWnd)
{
	HRESULT result;

	this->m_pSoundManager = new CSoundManager();
	if (this->m_pSoundManager == NULL)
		return FALSE;

	result = this->m_pSoundManager->Initialize(hWnd, DSSCL_PRIORITY);
	if (FAILED(result))
		return FALSE;

	result = this->m_pSoundManager->SetPrimaryBufferFormat(2, 22050, 16);
	if (FAILED(result))
		return FALSE;

	return TRUE;
}

CSound* DXSound::LoadSound(char *lpszFileName)
{
	CSound* wave = NULL;

	//Ensure the file is small
	HANDLE hFile = CreateFile(lpszFileName, 0, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile != NULL)
	{
		//Check if open a 100Mb wav file
		DWORD dwFileSizeHight = 0;
		DWORD dwFileSize;
		dwFileSize = GetFileSize(hFile, &dwFileSizeHight);
		if (dwFileSizeHight != 0 && dwFileSize > 100000000)
		{
			trace(L"The File Too Large. You Could Run Out Of Memory!");
			return NULL;
		}
	}

	//Load the file sound into the DirectSound buffer
	HRESULT result = this->m_pSoundManager->Create(&wave, lpszFileName, 0, GUID_NULL);
	if (FAILED(result))
	{
		trace(L"Could Not Create Sound Buffer");
		return NULL;
	}

	return wave;
}

void DXSound::Play(CSound* wave, bool bLooped)
{
	if (wave == NULL)
		return;

	if (wave->IsSoundPlaying())
	{
		//Stop the sound and reset the position
		this->Stop(wave);
	}

	if (bLooped)
		wave->Play(0, DSBPLAY_LOOPING, -100L);
	else
		wave->Play();
}

void DXSound::Stop(CSound* wave)
{
	if (wave)
	{
		wave->Stop();
		wave->Reset();
	}
}

void DXSound::End()
{
	if (this->m_pSoundManager)
	{
		delete this->m_pSoundManager;
		this->m_pSoundManager = NULL;
	}
}