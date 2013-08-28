#include "sound.h"

class SoundManager
{
public:
	LPDIRECTSOUNDBUFFER BackMusicBuffer;
	LPDIRECTSOUNDBUFFER ShootBuffer;
	LPDIRECTSOUNDBUFFER FinishMapBuffer;
	LPDIRECTSOUNDBUFFER UpLevelBuffer;
	LPDIRECTSOUNDBUFFER EnemyDieBuffer;
	LPDIRECTSOUNDBUFFER	BonusAppear_LevelDownBuffer;
	LPDIRECTSOUNDBUFFER BrickBrokenBuffer;
	LPDIRECTSOUNDBUFFER DyingBuffer;
	LPDIRECTSOUNDBUFFER ExtraLifeBuffer;
	LPDIRECTSOUNDBUFFER GetCoinBuffer;
	LPDIRECTSOUNDBUFFER JumpBuffer;
	LPDIRECTSOUNDBUFFER MenuChangeBuffer;

	sound BackMusicSound;
	sound ShootSound;
	sound FinishMapSound;
	sound UpLevelSound;
	sound EnemyDieSound;
	sound BonusAppear_LevelDownSound;
	sound BrickBrokenSound;
	sound DyingSound;
	sound ExtraLifeSound;
	sound GetCoinSound;
	sound JumpSound;
	sound MenuChangeSound;

	SoundManager(HWND hWnd)
	{
		//BackMusic
		if(!BackMusicSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		BackMusicBuffer =BackMusicSound.LoadWaveToSoundBuffer("Sounds\\BackMusic.wav");
		if (!BackMusicBuffer)
		{
			MessageBox(NULL, "Unable to load BackMusic.wav", "ERROR", MB_OK);
			return;
		}
		//Shoot
		if(!ShootSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		ShootBuffer=NULL;
		//FinishMap
		if(!FinishMapSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		FinishMapBuffer=NULL;
		//UpLevel
		if(!UpLevelSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		UpLevelBuffer=NULL;
		//EnemyDie
		if(!EnemyDieSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		EnemyDieBuffer=NULL;
		//BonusAppear_LevelDown
		if(!BonusAppear_LevelDownSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		BonusAppear_LevelDownBuffer=NULL;
		//BrickBroken
		if(!BrickBrokenSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		BrickBrokenBuffer=NULL;
		//Dying
		if(!DyingSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		DyingBuffer=NULL;
		//ExtraLife
		if(!ExtraLifeSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		ExtraLifeBuffer=NULL;
		//GetCoin
		if(!GetCoinSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		GetCoinBuffer=NULL;
		//Jump
		if(!JumpSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		JumpBuffer=NULL;
		//MenuChange
		if(!MenuChangeSound.initDirectSound(hWnd))
		{
			MessageBox(NULL,"Unable to init DirectSound","ERROR",MB_OK);
		}
		MenuChangeBuffer =NULL;
	}
	void Play(string name,bool isLoop)
	{
		if(name=="BackMusic")
		{
			if(BackMusicBuffer!=NULL)
				BackMusicBuffer->Release();
			BackMusicBuffer =BackMusicSound.LoadWaveToSoundBuffer("Sounds\\BackMusic.wav");
			if (!BackMusicBuffer)
			{
				MessageBox(NULL, "Unable to load BackMusic.wav", "ERROR", MB_OK);
				return;
			}
			playsound(BackMusicSound,BackMusicBuffer,isLoop);
		}
		else if(name=="Shoot")
		{
			if(ShootBuffer!=NULL)
				ShootBuffer->Release();
			ShootBuffer =ShootSound.LoadWaveToSoundBuffer("Sounds\\Shoot.wav");
			if (!ShootBuffer)
			{
				MessageBox(NULL, "Unable to load Shoot.wav", "ERROR", MB_OK);
				return;
			}
			playsound(ShootSound,ShootBuffer,isLoop);
		}
		else if(name=="FinishMap")
		{
			if(FinishMapBuffer!=NULL)
				FinishMapBuffer->Release();
			FinishMapBuffer =FinishMapSound.LoadWaveToSoundBuffer("Sounds\\FinishMap.wav");
			if (!FinishMapBuffer)
			{
				MessageBox(NULL, "Unable to load FinishMap.wav", "ERROR", MB_OK);
				return;
			}
			playsound(FinishMapSound,FinishMapBuffer,isLoop);
		}
		else if(name=="UpLevel")
		{
			if(UpLevelBuffer!=NULL)
				UpLevelBuffer->Release();
			UpLevelBuffer =UpLevelSound.LoadWaveToSoundBuffer("Sounds\\LevelUp.wav");
			if (!UpLevelBuffer)
			{
				MessageBox(NULL, "Unable to load LevelUp.wav", "ERROR", MB_OK);
				return;
			}
			playsound(UpLevelSound,UpLevelBuffer,isLoop);
		}
		else if(name=="EnemyDie")
		{
			if(EnemyDieBuffer!=NULL)
				EnemyDieBuffer->Release();
			EnemyDieBuffer =EnemyDieSound.LoadWaveToSoundBuffer("Sounds\\EnemyDie.wav");
			if (!EnemyDieBuffer)
			{
				MessageBox(NULL, "Unable to load EnemyDie.wav", "ERROR", MB_OK);
				return;
			}
			playsound(EnemyDieSound,EnemyDieBuffer,isLoop);
		}
		else if(name=="BonusAppear_LevelDown")
		{
			if(BonusAppear_LevelDownBuffer!=NULL)
				BonusAppear_LevelDownBuffer->Release();
			BonusAppear_LevelDownBuffer =BonusAppear_LevelDownSound.LoadWaveToSoundBuffer("Sounds\\BonusAppear_LevelDown.wav");
			if (!BonusAppear_LevelDownBuffer)
			{
				MessageBox(NULL, "Unable to load BonusAppear_LevelDown.wav", "ERROR", MB_OK);
				return;
			}
			playsound(BonusAppear_LevelDownSound,BonusAppear_LevelDownBuffer,isLoop);
		}
		else if(name=="BrickBroken")
		{
			if(BrickBrokenBuffer!=NULL)
				BrickBrokenBuffer->Release();
			BrickBrokenBuffer =BrickBrokenSound.LoadWaveToSoundBuffer("Sounds\\BrickBroken.wav");
			if (!BrickBrokenBuffer)
			{
				MessageBox(NULL, "Unable to load BrickBroken.wav", "ERROR", MB_OK);
				return;
			}
			playsound(BrickBrokenSound,BrickBrokenBuffer,isLoop);
		}
		else if(name=="Dying")
		{
			if(DyingBuffer!=NULL)
				DyingBuffer->Release();
			DyingBuffer =DyingSound.LoadWaveToSoundBuffer("Sounds\\Dying.wav");
			if (!DyingBuffer)
			{
				MessageBox(NULL, "Unable to load Dying.wav", "ERROR", MB_OK);
				return;
			}
			playsound(DyingSound,DyingBuffer,isLoop);
		}
		else if(name=="ExtraLife")
		{
			if(ExtraLifeBuffer!=NULL)
				ExtraLifeBuffer->Release();
			ExtraLifeBuffer =ExtraLifeSound.LoadWaveToSoundBuffer("Sounds\\ExtraLife.wav");
			if (!ExtraLifeBuffer)
			{
				MessageBox(NULL, "Unable to load ExtraLife.wav", "ERROR", MB_OK);
				return;
			}
			playsound(ExtraLifeSound,ExtraLifeBuffer,isLoop);
		}
		else if(name=="GetCoin")
		{
			if(GetCoinBuffer!=NULL)
				GetCoinBuffer->Release();
			GetCoinBuffer =GetCoinSound.LoadWaveToSoundBuffer("Sounds\\GetCoin.wav");
			if (!GetCoinBuffer)
			{
				MessageBox(NULL, "Unable to load GetCoin.wav", "ERROR", MB_OK);
				return;
			}
			playsound(GetCoinSound,GetCoinBuffer,isLoop);
		}
		else if(name=="Jump")
		{
			if(JumpBuffer!=NULL)
				JumpBuffer->Release();
			JumpBuffer =JumpSound.LoadWaveToSoundBuffer("Sounds\\Jump.wav");
			if (!JumpBuffer)
			{
				MessageBox(NULL, "Unable to load Jump.wav", "ERROR", MB_OK);
				return;
			}
			playsound(JumpSound,JumpBuffer,isLoop);
		}
		else if(name=="MenuChange")
		{
			if(MenuChangeBuffer!=NULL)
				MenuChangeBuffer->Release();
			MenuChangeBuffer =MenuChangeSound.LoadWaveToSoundBuffer("Sounds\\MenuChange.wav");
			if (!MenuChangeBuffer)
			{
				MessageBox(NULL, "Unable to load MenuChange.wav", "ERROR", MB_OK);
				return;
			}
			playsound(MenuChangeSound,MenuChangeBuffer,isLoop);
		}
	}
private:
	void playsound(sound s,LPDIRECTSOUNDBUFFER Buffer,bool isLoop)
	{
		if(!isLoop)
			s.playSound(Buffer);
		else
			s.playSoundLoop(Buffer);
	}
};