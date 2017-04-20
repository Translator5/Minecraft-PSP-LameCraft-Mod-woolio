#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

extern "C"
{
    #include "sound_utils/pgeWav.h"
    #include "sound_utils/oslib.h"
}

#include <stdlib.h>
#include <time.h>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static SoundManager m_SoundManager;
	static SoundManager* Instance();

	void Init();

    void PlayBreakSound();
    void PlayHitSound();
    void PlayEatSound();

    void PlayZombieHurtSound(float distanceToPlayer);
    void PlayZombieDieSound(float distanceToPlayer);
    void PlayZombieSaySound(float distanceToPlayer);

    void PlayCowHurtSound(float distanceToPlayer);
    void PlayCowSaySound(float distanceToPlayer);

    void PlayCreeperHurtSound(float distanceToPlayer);
    void PlaySheepHurtSound(float distanceToPlayer);

    void PlayRainSound(int volume);

    void PlaySplashSound();
    void PlayFuseSound();
    void PlayShearSound();
    void PlayBowSound();
	void PlayMenuSound();
	void PlayPlopSound();
	void PlayWalkSound(int type);
	void PlayDigSound(int type);
	void PlayEndDigSound(int type);
	void TNTSound();
	void PlayDoorSound(bool open);
	void PlayFallSound(float i);
	void PlayGlassSound();
    void PlayNoteSound(unsigned int noteType, float pitch);

    void PlayDiskSound(int diskNumber);
	int PlayRandomAmbient();

	void StopAmbient();
	void StopDiskSounds();

	bool playerSounds;
	bool ambientSoundsEnabled;

	int currentAmbientSound;
	int lastAmbientSound;

private:

	int currentWalkSound;
	int lastWalkSound;

	//sounds
	pgeWav *buttonSound;
	//plop sound
	pgeWav *plopSound;
	//grass sounds
	pgeWav *grassSounds[4];
	pgeWav *grawelSounds[4];
	pgeWav *stoneSounds[4];
	pgeWav *woodSounds[4];
	pgeWav *sandSounds[4];
	pgeWav *snowSounds[4];

	pgeWav *eatSounds[3];

	pgeWav *hitSounds[3];
    pgeWav *fallSounds[2];

    pgeWav *zombieHurtSounds[2];
    pgeWav *zombieSaySound;
    pgeWav *zombieDieSound;

    pgeWav *cowHurtSounds[2];
    pgeWav *cowSaySound;

    pgeWav *creeperHurtSounds[2];

    pgeWav *sheepHurtSounds[2];

	pgeWav *doorOpen;
	pgeWav *doorClose;
	pgeWav *tnt;
	pgeWav *bow;
	pgeWav *breakSound;
	pgeWav *fuse;
	pgeWav *splash;
	pgeWav *glass;
	pgeWav *shear;

	pgeWav *rainSound;

	pgeWav *digSounds[3];

	pgeWav *noteSounds[2]; // bass and pling

	// this lib can stream
	OSL_SOUND *ambientSounds[6];

	OSL_SOUND *diskSounds[3];

};

#endif

