#include "SoundManager.h"

SoundManager SoundManager::m_SoundManager;

SoundManager* SoundManager::Instance()
{
	return &m_SoundManager;
}

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{

}

void SoundManager::Init()
{
	//first of all init audio engine
	VirtualFileInit();
	//oslInitAudioME(OSL_FMT_MP3);
	oslInitAudio();

	//button sound
	buttonSound = oslLoadSoundFile("Assets/Sounds/button1.wav",OSL_FMT_NONE);

	//TNT
	tnt = oslLoadSoundFile("Assets/Sounds/tnt.wav",OSL_FMT_NONE);

	door = oslLoadSoundFile("Assets/Sounds/door.wav",OSL_FMT_NONE);

	breakSound = oslLoadSoundFile("Assets/Sounds/break.wav",OSL_FMT_NONE);

	bow = oslLoadSoundFile("Assets/Sounds/bow.wav",OSL_FMT_NONE);

	//plop sound
	plopSound = oslLoadSoundFile("Assets/Sounds/plop.wav",OSL_FMT_NONE);

    fallSounds[0] = oslLoadSoundFile("Assets/Sounds/Damage/fallbig.wav",OSL_FMT_NONE);
    fallSounds[1] = oslLoadSoundFile("Assets/Sounds/Damage/fallsmall.wav",OSL_FMT_NONE);
    //cave sounds
    caveSounds[0] = oslLoadSoundFile("Assets/Sounds/cave2.wav",OSL_FMT_NONE);
    caveSounds[1] = oslLoadSoundFile("Assets/Sounds/cave3.wav",OSL_FMT_NONE);
    caveSounds[2] = oslLoadSoundFile("Assets/Sounds/cave4.wav",OSL_FMT_NONE);
    caveSounds[3] = oslLoadSoundFile("Assets/Sounds/cave5.wav",OSL_FMT_NONE);
    caveSounds[4] = oslLoadSoundFile("Assets/Sounds/cave6.wav",OSL_FMT_NONE);
    caveSounds[5] = oslLoadSoundFile("Assets/Sounds/cave7.wav",OSL_FMT_NONE);
	//grass sounds
	grassSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/grass1.wav",OSL_FMT_NONE);
	grassSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/grass2.wav",OSL_FMT_NONE);
	grassSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/grass3.wav",OSL_FMT_NONE);
	grassSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/grass4.wav",OSL_FMT_NONE);

	//grawel
	grawelSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/gravel1.wav",OSL_FMT_NONE);
	grawelSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/gravel2.wav",OSL_FMT_NONE);
	grawelSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/gravel3.wav",OSL_FMT_NONE);
	grawelSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/gravel4.wav",OSL_FMT_NONE);

	//stone
	stoneSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/stone1.wav",OSL_FMT_NONE);
	stoneSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/stone2.wav",OSL_FMT_NONE);
	stoneSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/stone3.wav",OSL_FMT_NONE);
	stoneSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/stone4.wav",OSL_FMT_NONE);

	//wood
	woodSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/wood1.wav",OSL_FMT_NONE);
	woodSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/wood2.wav",OSL_FMT_NONE);
	woodSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/wood3.wav",OSL_FMT_NONE);
	woodSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/wood4.wav",OSL_FMT_NONE);

    //cloth
    clothSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/cloth1.wav",OSL_FMT_NONE);
	clothSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/cloth2.wav",OSL_FMT_NONE);
	clothSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/cloth3.wav",OSL_FMT_NONE);
	clothSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/cloth4.wav",OSL_FMT_NONE);

    //sand
    sandSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/sand1.wav",OSL_FMT_NONE);
	sandSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/sand2.wav",OSL_FMT_NONE);
	sandSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/sand3.wav",OSL_FMT_NONE);
	sandSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/sand4.wav",OSL_FMT_NONE);

    //snow
    snowSounds[0] = oslLoadSoundFile("Assets/Sounds/walking/snow1.wav",OSL_FMT_NONE);
	snowSounds[1] = oslLoadSoundFile("Assets/Sounds/walking/snow2.wav",OSL_FMT_NONE);
	snowSounds[2] = oslLoadSoundFile("Assets/Sounds/walking/snow3.wav",OSL_FMT_NONE);
	snowSounds[3] = oslLoadSoundFile("Assets/Sounds/walking/snow4.wav",OSL_FMT_NONE);

	// Ambient
	ambientSounds[0] = oslLoadSoundFile("Assets/Sounds/ambient/track1.bgm",OSL_FMT_STREAM);
	ambientSounds[1] = oslLoadSoundFile("Assets/Sounds/ambient/track2.bgm",OSL_FMT_STREAM);
	ambientSounds[2] = oslLoadSoundFile("Assets/Sounds/ambient/track3.bgm",OSL_FMT_STREAM);
	ambientSounds[3] = oslLoadSoundFile("Assets/Sounds/ambient/track4.bgm",OSL_FMT_STREAM);
	ambientSounds[4] = oslLoadSoundFile("Assets/Sounds/ambient/track5.bgm",OSL_FMT_STREAM);
	ambientSounds[5] = oslLoadSoundFile("Assets/Sounds/ambient/track6.bgm",OSL_FMT_STREAM);

	eatSounds[0] = oslLoadSoundFile("Assets/Sounds/eat/eat1.wav",OSL_FMT_NONE);
	eatSounds[1] = oslLoadSoundFile("Assets/Sounds/eat/eat2.wav",OSL_FMT_NONE);
	eatSounds[2] = oslLoadSoundFile("Assets/Sounds/eat/eat3.wav",OSL_FMT_NONE);

    hitSounds[0] = oslLoadSoundFile("Assets/Sounds/Damage/hit1.wav",OSL_FMT_NONE);
    hitSounds[1] = oslLoadSoundFile("Assets/Sounds/Damage/hit2.wav",OSL_FMT_NONE);
    hitSounds[2] = oslLoadSoundFile("Assets/Sounds/Damage/hit3.wav",OSL_FMT_NONE);


	srand(time(NULL));

	//set default values
	currentWalkSound = 0;
	lastWalkSound = 0;

	playerSounds = true;
}

void SoundManager::PlayMenuSound()
{
	oslPlaySound(buttonSound, 1);
}

void SoundManager::PlayPlopSound()
{
	if(playerSounds)
		oslPlaySound(plopSound,1);
}

void SoundManager::TNTSound()
{
	if(playerSounds)
		oslPlaySound(tnt,6);
}

void SoundManager::doorSound()
{
	if(playerSounds)
		oslPlaySound(door,3);
}

void SoundManager::PlayBreakSound()
{
	if(playerSounds)
		oslPlaySound(breakSound,1);
}

void SoundManager::PlayBowSound()
{
	if(playerSounds)
		oslPlaySound(bow,1);
}

void SoundManager::PlayHitSound()
{
	if(playerSounds)
    {
		oslPlaySound(hitSounds[rand() % 3],3);
    }
}

void SoundManager::PlayEatSound()
{
	if(playerSounds)
    {
		oslPlaySound(eatSounds[rand() % 3],3);
    }
}

void SoundManager::PlayCaveSound()
{
	if(playerSounds)
    {
        short randSound = rand() % 5;
        oslPlaySound(caveSounds[randSound],6);
    }
}

void SoundManager::PlayFallSound(float i)
{
	if(playerSounds)
    {
        if (i < -9 && i > -21)
        {
            oslPlaySound(fallSounds[1],6);
        }
        if (i < -21)
        {
            oslPlaySound(fallSounds[0],6);
        }
    }
}

void SoundManager::PlayWalkSound(int type)
{
	if(playerSounds)
	{
		switch(type)
		{
			case 0://grass
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(grassSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(grassSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 1://gravel
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(grawelSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(grawelSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 2://stone
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(stoneSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(stoneSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
			case 3://wood
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(woodSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(woodSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 4://cloth
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(clothSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(clothSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 5://sand
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(sandSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(sandSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
            case 6://snow
			{
				currentWalkSound = rand() % 4;

				//stop last sound
				oslStopSound(snowSounds[lastWalkSound]);

				//play new sound
				oslPlaySound(snowSounds[currentWalkSound],1);

				//set last sound as current
				lastWalkSound = currentWalkSound;
			}
			break;
		}
	}
}

int SoundManager::PlayRandomAmbient()
{
 	currentAmbientSound = rand() % 6;

    oslPlaySound(ambientSounds[currentAmbientSound],2);


	switch(currentAmbientSound)
	{
		case 0:
			{
				return 500;
			}
			break;
		case 1:
			{
				return 500;
			}
			break;
		case 2:
			{
				return 500;
			}
			break;
        case 3:
			{
				return 500;
			}
			break;
		case 4:
			{
				return 500;
			}
			break;
		case 5:
			{
				return 500;
			}
			break;

	}
	//return 1;
}
