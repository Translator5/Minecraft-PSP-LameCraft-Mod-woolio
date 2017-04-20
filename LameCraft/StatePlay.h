
#ifndef STATEPLAY_H_
#define STATEPLAY_H_

#include <Aurora/Utils/StateManager.h>
#include <Aurora/Utils/GameState.h>

#include <math.h>
#include <psptypes.h>

#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>
#include <Aurora/Utils/Timer.h>
#include <Aurora/System/SystemManager.h>
#include <Aurora/Graphics/Models/ObjModel.h>
#include <Aurora/Graphics/Camera.h>
#include <Aurora/Graphics/Sprite.h>
#include <Aurora/Graphics/Effects/SkyLight.h>
#include <Aurora/Graphics/Effects/SnowBall2.h>

#include "LameMob.h"
#include "CraftWorld2.h"
#include "InputHelper.h"
#include "SoundManager.h"
#include "Chest2.h"
#include "Furnace2.h"


using namespace Aurora::Graphics;
using namespace Aurora::Utils;
using namespace Aurora::System;
using namespace Aurora;


class StatePlay : public CGameState
{
public:
	StatePlay();
	virtual ~StatePlay();

	void Init();
	void InitParametric(bool makeTrees,bool makePumpkins,bool makeTypes,bool makeWater,bool makeCaves,bool makeSnow,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seedIII, int terBuilderType);
	void Enter();
	void CleanUp();

	void Pause();
	void Resume();
	void LoadTextures();

	void HandleEvents(StateManager* sManager);
	void Update(StateManager* sManager);
	void Draw(StateManager* sManager);

	void LoadMap(std::string fileName,bool compressed);
	void SetWorldAndSaveName(std::string worldName,std::string fileName);
	void InitCamera();

	//keys helpers
	bool keyPressed(int currentKey);
	bool keyHold(int currentKey);
	void PutInInventory(int id, int num, bool st);

private:

	void advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice);
	bool TryToMove(Vector3 moveVector,float dt);
	void SetDayTimeAfterLoad();
	void CraftItem2x2();
	void CraftItem3x3();

	void CheckForFurnFuel(Furnace* Fur);
	void CheckForFurnWorking(Furnace* Fur);
	void ReadyFurnSmelting(Furnace* Fur);

    int FindFurnaceId(int x, int y, int z);

	int FindChestId(int x, int y, int z);

	void HungerTime();
	void HealthTime();
	void OxygenTime();

private:

	RenderManager *mRender;
	SystemManager *mSystemMgr;
	SoundManager *mSoundMgr;
	InputHelper *mIhelper;
	Camera *fppCam;

	std::string saveFileName;
	int freeMemory;
	float freeMemoryTimer;

    float cloudsMove;
    bool cloudsWay;

	CraftWorld *mWorld;
	ObjModel *dModel[5];

    SkyLight *skyLight;
    SkyLight *skyMoonLight;

    bool cycle;
	float sunTime;
	float sunTimeTick;
	bool sunMoonSwitch;
	bool startDt;
    float dT; //time of destr
    float dET; //end time of destt
    float dS; //speed of destr
    char dStd; //destroy animation

    bool hurt;
    float hurt_time;
    float dtt;

    float furnaceTimes;

    Vector3 testPos1;

	Vector3 cubePos;
	bool showCube;


    int craftSlotId[4];
    int craftSlotAm[4];
    bool craftSlotSt[4];

    int craftSlotId3[9];
    int craftSlotAm3[9];
    bool craftSlotSt3[9];

    int craftItemId;
    int craftItemAm;
    bool craftItemSt;

    int craftItemId3;
    int craftItemAm3;
    bool craftItemSt3;

    float musicTimeGo;
    float musicTime;

    char chestId;
    char furnaceId;
    Chest* UseChest;
    Furnace* UseFurnace;
	//zmienne do poruszania
	float GRAVITY;
	float JUMPVELOCITY;
	float CLIMBVELOCITY;

	Vector3 playerVelocity;
	Vector3 playerPosition;
	Vector3 newPlayerPos;
	Vector3 oldPlayerPos;

	bool walkingOnGround;
	bool jumping;
	bool headInWater;
	bool footInWater;
	bool headInLava;
	bool footInLava;

	bool invEn;
	bool upEn;
	bool craft3xEn;
	bool chestEn;
	bool furnaceEn;

    char barPosition;
    char invXPosition;
    char invYPosition;

    short time_z; //cave sounds timer

	int ram1;
	int ram2;
	float tickHunger;
	float tickHealth;
	int tickChunk;
	float tickOS;
	short chunks; // 0 - 7;

    int chunkId;

	int terrainType;

	Timer mTimer;
	float dt;

	//textures info
	//int texture[16];
	int texture[16];
	int blue;
	int red;
	int black;

    int snowBall4;
	int cloudsTex;
	int suntex;
	int moontex;

	unsigned char currentTexture;
	unsigned char timeTexture;

	Sprite *invSprite;
    Sprite *crtSprite;
    Sprite *chtSprite;
    Sprite *selectInvSprite;
	Sprite *barSprite;
	Sprite *crossSprite;
	Sprite *selectSprite;

	Sprite *furArrowSprite;
	Sprite *furFireSprite;
    Sprite *furSprite;

	Sprite *hpCellSprite;
	Sprite *hp44Sprite;
	Sprite *hp34Sprite;
	Sprite *hp24Sprite;
	Sprite *hp14Sprite;

	Sprite *hgCellSprite;
	Sprite *hg44Sprite;
	Sprite *hg34Sprite;
	Sprite *hg24Sprite;
	Sprite *hg14Sprite;

	Sprite *bubbleSprite;

	float cameraSpeed;
	float cameraMoveSpeed;

	//menu sprites
	Sprite *buttonSprite;
	Sprite *sbuttonSprite;
	Sprite *nbuttonSprite;
	Sprite *moverSprite;

	int menuState;//0 game,1 menu
	bool menuOptions;
	int optionsMenuPos;
	int selectPos;

    char statisticsPage;

	//some settings
	bool canFly;
	bool devMode;
	bool analogLeft,analogRight,analogUp,analogDown;

	//for sound of walkinng
	float walkSoundAccu;
	bool  isWalking;

	//Headbob
	bool canHeadBob;
	float bobCycle;
	bool bobType;

    float shift_x;
    float shift_y;

    float changeY;

    bool anim[3];
	bool makeScreen;
	bool dieFactor;

    void DrawText(int x,int y, unsigned int color, float size, const char *message, ...);
    void DrawText2(int x,int y, unsigned int color, float size, const char *message, ...);

	std::vector<SnowBall2*> mSnowBalls;

};

#endif
