#include "StatePlay.h"
#include "TextureHelper.h"

#include "WorldGenerator.h"

#define PI 3.1415926535897f
#define DEG_TO_RAD (PI / 180.0f)
#define TEXTURE_CHUNKS 8
#define SKY_MOVE 360.0f/24.0f/50.0f



StatePlay::StatePlay()
{
    mRender = NULL;
    mSystemMgr = NULL;
    fppCam = NULL;
    UseChest = NULL;
    UseFurnace = NULL;

    statisticsPage = 0;
    //utils
    freeMemory = 0;
    freeMemoryTimer = 0.0f;
    showCube = true;

    //zmienne do poruszania
    GRAVITY = -6.8f;//-6.8
    JUMPVELOCITY = 4.6f;
    CLIMBVELOCITY = 2.5f;

    walkingOnGround = false;
    jumping = false;
    headInWater = false;
    footInWater = false;
    headInLava = false;
    footInLava = false;
    invEn = false;
    craft3xEn = false;
    upEn = false;
    chestEn = false;
    furnaceEn = false;

    cycle = 0;

    dtt = 0.0f;
    furnaceTimes = 0.0f;
    //12.85f - one hour

    musicTimeGo = 0;

    //RenderManager::InstancePtr()
    timeTexture = 0;
    currentTexture = 0;

    chunkId = 0;
    chunks = 0;
    //---*

    startDt = false;
    dET = 0;
    dS = 0;
    dT = 0;
    dStd = -1;

    testPos1.x = -1;
    testPos1.y = -1;
    testPos1.z = -1;
    //---*

    barPosition = 0;
    invXPosition = 0;
    invYPosition = 0;

    shift_x = 0.0f;
    shift_y = 0.0f;

    craftItemId = -1;
    craftItemAm = -1;
    craftItemSt = 0;

    craftItemId3 = -1;
    craftItemAm3 = -1;
    craftItemSt3 = 0;

    chestId = -1;
    furnaceId = -1;

    ram1 = 0;
    ram2 = 0;
    dt = 0.0f;
    sunTime = 21600.0f; //6 am
    sunTimeTick = 0.0f;
    sunMoonSwitch = true;

    cameraSpeed = 2.0f / 60.0f;
    cameraMoveSpeed = 4.0f/ 60.0f;

    //stete to game
    menuState = 0;
    selectPos = 0;

    cloudsMove = 0;
    cloudsWay = 0;

    //flying
    canFly = false;
    devMode = false;
    makeScreen = false;

    //bob
	canHeadBob = true;
	bobCycle = 0.0f;
	changeY = 0.0f;
	anim[0] = 0;
	anim[1] = 0;
	anim[2] = 0;

	for(int i = 0; i <= 3; i += 1)
    {
        craftSlotId[i] = -1;
        craftSlotAm[i] = -1;
        craftSlotSt[i] = 0;
    }

    for(int i = 0; i <= 8; i += 1)
    {
        craftSlotId3[i] = -1;
        craftSlotAm3[i] = -1;
        craftSlotSt3[i] = 0;
    }

    tickHunger = 0.0f;
    tickHealth = 0.0f;
    hurt = false;
    hurt_time = 0;
    time_z = 0;
    tickChunk = 0;
    musicTime = 1000;
    tickOS = 0;

    dieFactor = true;
}

StatePlay::~StatePlay()
{

}

void StatePlay::InitCamera()
{
    fppCam = new Camera();
    fppCam->PositionCamera(playerPosition.x,playerPosition.y,playerPosition.z, playerPosition.x,playerPosition.y,playerPosition.z-5.0f, 0.0f,1.0f,0.0f);
    mRender->SetActiveCamera(fppCam);
}

void StatePlay::Init()
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    WorldGenerator *mGen = new WorldGenerator();

    //then create our perfect world
    mWorld = new CraftWorld();
    mWorld->initWorld(128, 16);
    delete mGen;
    //mWorld->initRandompMap(128,16);
    mWorld->setTextureSize(256,16);
    mWorld->initWorldBlocksLight();
    mWorld->SetWolrdTime(6);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
    mWorld->buildblocksVerts();

    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,mWorld->groundHeight(64,64)+1.5,64.0f);

    int	curchunkTarget = mWorld->getChunkId(playerPosition);
    //Rebuild nearby world
    mWorld->rebuildChunk(curchunkTarget);
    mWorld->rebuildTransparentChunk(curchunkTarget);
    mWorld->rebuildNearestChunks(curchunkTarget,playerPosition);

    dt = mTimer.GetDeltaTime();

    //block sets info

    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one

    //std::floor
    bobCycle = 3.14/2;

    LoadTextures();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;
}

void StatePlay::InitParametric(bool makeTrees,bool makeWater,bool makeCaves,bool makePumpkins,bool makeTypes,bool makeIron,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seed_1,int terrainBuilder)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    //

    //then create our perfect world
    mWorld = new CraftWorld();
    mWorld->initWorld(128, 16);

    WorldGenerator *mGen = new WorldGenerator();
    mGen->initRandompMap(128,16, mWorld,makeTrees,makePumpkins,makeTypes,makeWater,makeIron,makeCaves,makeCoal,makeGold,makeRedStone,makeDiamond,makeDirt,makeCanes,seed_1,terrainBuilder);
    delete mGen;
    //mWorld->initRandompMap(128,16,terrainType,makeFlat,makeTrees,makeWater,makeCaves);
    mWorld->setTextureSize(256,16);
    mWorld->initWorldBlocksLight();
    mWorld->SetWolrdTime(6);
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
    mWorld->buildblocksVerts();

    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,mWorld->groundHeight(64,64)+1.5,64.0f);

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    //Rebuild nearby world
    mWorld->rebuildChunk(curchunkTarget);
    mWorld->rebuildTransparentChunk(curchunkTarget);
    mWorld->rebuildNearestChunks(curchunkTarget,playerPosition);

    dt = mTimer.GetDeltaTime();

    //block sets info
    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one


    LoadTextures();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

}

void StatePlay::SetWorldAndSaveName(std::string worldName,std::string fileName)
{
    if(mWorld != NULL)
    {
        sprintf(mWorld->worldName,"%s",worldName.c_str());
    }
    saveFileName = fileName;
}

void StatePlay::LoadMap(std::string fileName,bool compressed)
{
    //set render manager instance
    mRender = RenderManager::InstancePtr();
    mSystemMgr = SystemManager::Instance();
    mSoundMgr = SoundManager::Instance();
    mIhelper = InputHelper::Instance();

    //save name
    saveFileName = fileName;
    //
    playerPosition = newPlayerPos = oldPlayerPos = Vector3(64.0f,80,64.0f);

    //then create our perfect world
    mWorld = new CraftWorld();

    if(compressed)
    {
        mWorld->LoadCompressedWorld(saveFileName);
        //set player pos from map
        playerPosition = mWorld->GetPlayerPos();
        newPlayerPos  = mWorld->GetPlayerPos();
        oldPlayerPos = mWorld->GetPlayerPos();
        mWorld->SetWolrdTime(mWorld->worldDayTime);
    }
    else
    {
        mWorld->LoadWorld(saveFileName.c_str());
        mWorld->SetWolrdTime(6);
    }

    mWorld->setTextureSize(256,16);
    mWorld->initWorldBlocksLight();
    mWorld->UpdatePlayerZoneBB(playerPosition);
    mWorld->buildMap();
    mWorld->buildblocksVerts();

    int	curchunkTarget = mWorld->getChunkId(playerPosition);

    //Rebuild nearby world
    mWorld->rebuildChunk(curchunkTarget);
    mWorld->rebuildTransparentChunk(curchunkTarget);
    mWorld->rebuildNearestChunks(curchunkTarget,playerPosition);

    dt = mTimer.GetDeltaTime();

    //block sets info
    //selectedCubeEnd = allcubes - 2;//because we don't want first one and last one

    LoadTextures();

    menuOptions = false;
    optionsMenuPos = 0;

    analogLeft = analogRight = analogUp = analogDown = false;

    walkSoundAccu = 0.0f;
    isWalking = false;

    SetDayTimeAfterLoad();

    mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
    mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
    mRender-> fovv = mWorld->mainOptions.fov;
    RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
}

void StatePlay::LoadTextures()
{
    //terrain texure
    texture[0] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain1);
    texture[1] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain2);
    texture[2] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain3);
    texture[3] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain4);
    texture[4] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain5);
    texture[5] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain6);
    texture[6] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain7);
    texture[7] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain8);
    texture[8] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain9);
    texture[9] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain10);
    texture[10] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain11);
    texture[11] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain12);
    texture[12] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain13);
    texture[13] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain14);
    texture[14] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain15);
    texture[15] = TextureHelper::Instance()->GetTexture(TextureHelper::Terrain16);

    cloudsTex = TextureHelper::Instance()->GetTexture(TextureHelper::clouds1);

    //water filter
    blue = TextureHelper::Instance()->GetTexture(TextureHelper::Blue);

    red = TextureHelper::Instance()->GetTexture(TextureHelper::Red);

    black = TextureHelper::Instance()->GetTexture(TextureHelper::Black);

    snowBall4 = TextureHelper::Instance()->GetTexture(TextureHelper::SnowBall3);

    suntex = TextureHelper::Instance()->GetTexture(TextureHelper::Sun);
    moontex = TextureHelper::Instance()->GetTexture(TextureHelper::Moon);

    //bar image
    barSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0,0,182,22);
    barSprite->SetPosition(240,253);
    barSprite->Scale(1.75f,1.75f);

    selectSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0,22,24,24);
    selectSprite->SetPosition(100,253);
    selectSprite->Scale(1.75f,1.75f);

    crossSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),201,13,9,9);
    crossSprite->SetPosition(240,136);
    crossSprite->Scale(2.0f,2.0f);

    buttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,22,200,20);
    buttonSprite->SetPosition(240,150);

    sbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),24,62,200,20);
    sbuttonSprite->SetPosition(240,150);

    nbuttonSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),56,102,200,20);
	nbuttonSprite->SetPosition(240,150);

	moverSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),191,2,9,20);

    invSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::inv));//200
    invSprite->SetPosition(240,136);
    invSprite->Scale(1.5f,1.5f);

    crtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::crt));//200
    crtSprite->SetPosition(240,136);
    crtSprite->Scale(1.5f,1.5f);

    chtSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::cht));//200
    chtSprite->SetPosition(240,136);
    chtSprite->Scale(1.5f,1.5f);

    furSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::fur));//200
    furSprite->SetPosition(240,136);
    furSprite->Scale(1.5f,1.5f);

    furArrowSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furArrow));//200
    furArrowSprite->SetPosition(240,136);
    furArrowSprite->Scale(1.5f,1.5f);

    furFireSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::furFire));//200
    furFireSprite->SetPosition(240,136);
    furFireSprite->Scale(1.5f,1.5f);

    selectInvSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::cursor));//200
    selectInvSprite->SetPosition(240,136);

    hpCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0,118,10,10);
    hpCellSprite->SetPosition(100,21);
    hpCellSprite->Scale(2,2);

    hp44Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),10,118,10,10);
    hp44Sprite->SetPosition(100,22);
    hp44Sprite->Scale(2,2);

    hp34Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),20,118,10,10);
    hp34Sprite->SetPosition(100,23);
    hp34Sprite->Scale(2,2);

    hp24Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),30,118,10,10);
    hp24Sprite->SetPosition(100,23);
    hp24Sprite->Scale(2,2);

    hp14Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),40,118,10,10);
    hp14Sprite->SetPosition(100,23);
    hp14Sprite->Scale(2,2);

    hgCellSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0,108,10,10);
    hgCellSprite->SetPosition(100,24);
    hgCellSprite->Scale(2,2);

    hg44Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),10,108,10,10);
    hg44Sprite->SetPosition(100,26);
    hg44Sprite->Scale(2,2);

    hg34Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),20,108,10,10);
    hg34Sprite->SetPosition(100,26);
    hg34Sprite->Scale(2,2);

    hg24Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),30,108,10,10);
    hg24Sprite->SetPosition(100,26);
    hg24Sprite->Scale(2,2);

    hg14Sprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),40,108,10,10);
    hg14Sprite->SetPosition(100,26);
    hg14Sprite->Scale(2,2);

    bubbleSprite = new Sprite(TextureHelper::Instance()->GetTexture(TextureHelper::Utils),0,98,10,10);
    bubbleSprite->SetPosition(100,27);
    bubbleSprite->Scale(2,2);

    dModel[0] = new ObjModel();
    dModel[0]->LoadObj("Assets/Lamecraft/Models/Destroy/1/textureCube.obj");
    dModel[0]->Optimize();

    dModel[1] = new ObjModel();
    dModel[1]->LoadObj("Assets/Lamecraft/Models/Destroy/2/textureCube.obj");
    dModel[1]->Optimize();

    dModel[2] = new ObjModel();
    dModel[2]->LoadObj("Assets/Lamecraft/Models/Destroy/3/textureCube.obj");
    dModel[2]->Optimize();

    dModel[3] = new ObjModel();
    dModel[3]->LoadObj("Assets/Lamecraft/Models/Destroy/4/textureCube.obj");
    dModel[3]->Optimize();

    dModel[4] = new ObjModel();
    dModel[4]->LoadObj("Assets/Lamecraft/Models/Destroy/5/textureCube.obj");
    dModel[4]->Optimize();


    skyLight = new SkyLight();
    skyMoonLight = new SkyLight();

}



void StatePlay::SetDayTimeAfterLoad()
{
if(!mWorld->freezeDayTime)
{
	if(mWorld->worldVersion >=3)
	{
		if(mWorld->worldDayTime >= 5.0f && mWorld->worldDayTime < 21.0f)
		{
			sunMoonSwitch = true;
		}else
		{

			sunMoonSwitch = false;
		}

		sunTime = mWorld->sunTime;
	}
}
}
void StatePlay::Enter()
{
    RenderManager::InstancePtr()->SetPerspective(55.0f, 480.0f / 272.0f, 0.18f, 1000.f);
}
void StatePlay::CleanUp()
{
    for(unsigned int i = 0; i < mSnowBalls.size(); i++)
    {
        delete mSnowBalls[i];
    }
    mSnowBalls.clear();

    for(int i = 0; i <= 4; i++)
    {
        delete dModel[i];
    }
    delete mRender->mCam;
    mRender->mCam = NULL;
    delete buttonSprite;
    delete sbuttonSprite;
    delete nbuttonSprite;
    delete moverSprite;
    delete barSprite;
    delete selectSprite;
    delete crossSprite;
    delete invSprite;
    delete crtSprite;
    delete chtSprite;
    delete selectInvSprite;
    delete skyLight;
    delete skyMoonLight;

    delete furSprite;
    delete furArrowSprite;
    delete furFireSprite;

    delete hpCellSprite;
    delete hp44Sprite;
    delete hp34Sprite;
    delete hp24Sprite;
    delete hp14Sprite;

    delete hgCellSprite;
    delete hg44Sprite;
    delete hg34Sprite;
    delete hg24Sprite;
    delete hg14Sprite;

    delete bubbleSprite;

    //delete fppCam;
    delete mWorld;

}

void StatePlay::Pause()
{

}

void StatePlay::Resume()
{

}

void StatePlay::CraftItem2x2()
{
    craftItemId = -1;
    craftItemAm = -1;
    craftItemSt = 0;

    int result = 0;
    for(int i = 0; i <= 3; i ++)
    {
        if(craftSlotId[i] != -1)
        {
            result += craftSlotId[i];
        }
    }

    switch(result)
    {
    case 8:
        if(craftSlotId[0] == 8 || craftSlotId[1] == 8 || craftSlotId[2] == 8 || craftSlotId[3] == 8)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 1196:
        if(craftSlotId[0] == 299 && craftSlotId[1] == 299 && craftSlotId[2] == 299 && craftSlotId[3] == 299)
        {
            craftItemId = 26;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    case 31:
        if(craftSlotId[0] == 31 || craftSlotId[1] == 31 || craftSlotId[2] == 31 || craftSlotId[3] == 31)
        {
            craftItemId = 34;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 1156:
        if(craftSlotId[0] == 289 && craftSlotId[1] == 289 && craftSlotId[2] == 289 && craftSlotId[3] == 289)
        {
            craftItemId = 27;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    case 99:
        if(craftSlotId[0] == 99 || craftSlotId[1] == 99 || craftSlotId[2] == 99 || craftSlotId[3] == 99)
        {
            craftItemId = 283;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 136:
        if(craftSlotId[0] == 34)
        {
            craftItemId = 105;
            craftItemSt = 1;
            craftItemAm = 1;
        }
    break;

    case 68:
        if((craftSlotId[0] == 34 && craftSlotId[2] == 34)  || (craftSlotId[1] == 34 && craftSlotId[3] == 34))
        {
            craftItemId = 276;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;

    case 553:
        if((craftSlotId[0] == 277 && craftSlotId[2] == 276) || (craftSlotId[1] == 277 && craftSlotId[3] == 276))
        {
            craftItemId = 48;
            craftItemSt = 1;
            craftItemAm = 4;
        }
    break;


    case 556: //scirrors
        if((craftSlotId[0] == 278 && craftSlotId[3] == 278))
        {
            craftItemId = 275;
            craftItemSt = 0;
            craftItemAm = 239;
        }
    break;

    default:
        craftItemId = -1;
        craftItemAm = -1;
        craftItemSt = 0;
    break;

    }
}

int StatePlay::FindChestId(int x, int y, int z)
{
    int o;
    o = -1;
    for(unsigned int i = 0; i < mWorld->mChests.size(); i++)
    {
        Chest* NewChest = mWorld->mChests[i];
        if(NewChest->chestX == x && NewChest->chestY == y && NewChest->chestZ == z)
        {
            o = i;
            break;
        }
    }

    return o;
}

int StatePlay::FindFurnaceId(int x, int y, int z)
{
    int o;
    o = -1;
    for(unsigned int i = 0; i < mWorld->mFurnaces.size(); i++)
    {
        Furnace* NewFurnace = mWorld->mFurnaces[i];
        if(NewFurnace->furnaceX == x && NewFurnace->furnaceY == y && NewFurnace->furnaceZ == z)
        {
            o = i;
            break;
        }
    }

    return o;
}

void StatePlay::CheckForFurnFuel(Furnace* Fur)
{
    int furnItem;

    furnItem = -1;

    if(Fur->furnaceSlotId[0] < 250 && Fur->furnaceSlotId[0] != -1)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(Fur->fuelTime <= 0 && furnItem != -1)
    {
        if(Fur->furnaceSlotId[1] == -1)
            return;

        bool used = false;

        switch(Fur->furnaceSlotId[1])
        {
        case 8:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 31:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 34:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 296:
            Fur->fuelTime = 5;
            used = true;
        break;
        case 276:
            Fur->fuelTime = 5;
            used = true;
        break;
        case 277:
            Fur->fuelTime = 80;
            used = true;
        break;
        case 292:
            Fur->fuelTime = 1000;
            used = true;
        break;
        case 306:
            Fur->fuelTime = 30;
            used = true;
        break;
        case 59:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 100:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 105:
            Fur->fuelTime = 15;
            used = true;
        break;
        case 125:
            Fur->fuelTime = 15;
            used = true;
        break;
        }

        if(used == true)
        {
            Fur->furnaceSlotAm[1] -= 1;
            if(Fur->furnaceSlotAm[1] == 0)
            {
                Fur->furnaceSlotAm[1] = -1;
                Fur->furnaceSlotId[1] = -1;
                Fur->furnaceSlotSt[1] = 0;
            }
        }
    }
}

void StatePlay::CheckForFurnWorking(Furnace* Fur)
{
    int furnItem;

    furnItem = -1;

    if(Fur->furnaceSlotId[0] < 250 && Fur->furnaceSlotId[0] != -1)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(furnItem != -1)
    {
        if(Fur->fuelTime > 0)
        {
            if(Fur->furnaceSlotId[2] == furnItem || Fur->furnaceSlotId[2] == -1)
            {
                if(Fur->furnaceSlotAm[2] <= 63)
                {
                    Fur->working = true;
                }
            }
            if(Fur->furnaceSlotId[2] != furnItem && Fur->furnaceSlotId[2] != -1)
            {
                Fur->working = false;
                Fur->meltingTime = 0;
            }
        }
        else
        {
            Fur->working = false;
            Fur->meltingTime = 0;
        }
        if(Fur->fuelTime == 0)
        {
            Fur->working = false;
            Fur->meltingTime = 0;
        }
    }
    else
    {
        Fur->working = false;
        Fur->meltingTime = 0;
    }
}

void StatePlay::ReadyFurnSmelting(Furnace* Fur)
{
    int furnItem;

    if(Fur->furnaceSlotId[0] < 250)
    {
        furnItem = mWorld->blockTypes[Fur->furnaceSlotId[0]].furnItem;
    }

    if(Fur->furnaceSlotId[0] >= 250)
    {
        furnItem = mWorld->itemTypes[Fur->furnaceSlotId[0]-250].furnItem;
    }

    if(furnItem != -1)
    {
        if(Fur->furnaceSlotId[2] == furnItem)
        {
           Fur->furnaceSlotAm[2] += 1;
        }
        if(Fur->furnaceSlotId[2] == -1)
        {
            Fur->furnaceSlotId[2] = furnItem;
            Fur->furnaceSlotSt[2] = true;
            Fur->furnaceSlotAm[2] = 1;
        }

        Fur->furnaceSlotAm[0] -= 1;
        if(Fur->furnaceSlotAm[0] <= 0)
        {
            Fur->furnaceSlotId[0] = -1;
            Fur->furnaceSlotAm[0] = -1;
            Fur->furnaceSlotSt[0] = 0;
        }
    }
}

void StatePlay::CraftItem3x3()
{
    craftItemId3 = -1;
    craftItemAm3 = -1;
    craftItemSt3 = 0;

    int result = 0;

    for(int i = 0; i <= 8; i ++)
    {
        if(craftSlotId3[i] != -1)
        {
            result += craftSlotId3[i];
        }
    }

    switch(result)
    {
    case 8://planks
        if(craftSlotId3[0] == 8 || craftSlotId3[1] == 8 || craftSlotId3[2] == 8 || craftSlotId3[3] == 8 || craftSlotId3[4] == 8 || craftSlotId3[5] == 8 || craftSlotId3[6] == 8 || craftSlotId3[7] == 8 || craftSlotId3[8] == 8)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 31://planks
        if(craftSlotId3[0] == 31 || craftSlotId3[1] == 31 || craftSlotId3[2] == 31 || craftSlotId3[3] == 31 || craftSlotId3[4] == 31 || craftSlotId3[5] == 31 || craftSlotId3[6] == 31 || craftSlotId3[7] == 31 || craftSlotId3[8] == 31)
        {
            craftItemId3 = 34;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 68://sticks
        if( (craftSlotId3[0] == 34 && craftSlotId3[3] == 34)  || (craftSlotId3[1] == 34 && craftSlotId3[4] == 34) || (craftSlotId3[2] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[6] == 34) || (craftSlotId3[4] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[5] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 276;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 1656: //fence
        if((craftSlotId3[0] == 276 && craftSlotId3[1] == 276 && craftSlotId3[2] == 276 && craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276) || (craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276 && craftSlotId3[6] == 276 && craftSlotId3[7] == 276 && craftSlotId3[8] == 276))
        {
            craftItemId3 = 59;
            craftItemSt3 = 1;
            craftItemAm3 = 2;
        }
    break;

    case 204: //door
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 306;
            craftItemSt3 = 0;
            craftItemAm3 = 1;
        }
        //wooden stair
        if((craftSlotId3[0] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 125;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 216://stone stair
        if((craftSlotId3[0] == 36 && craftSlotId3[3] == 36 && craftSlotId3[4] == 36 && craftSlotId3[6] == 36 && craftSlotId3[7] == 36 && craftSlotId3[8] == 36))
        {
            craftItemId3 = 60;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 162://brick stair
        if((craftSlotId3[0] == 27 && craftSlotId3[3] == 27 && craftSlotId3[4] == 27 && craftSlotId3[6] == 27 && craftSlotId3[7] == 27 && craftSlotId3[8] == 27))
        {
            craftItemId3 = 67;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 136://crafting
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34 && craftSlotId3[4] == 34) || (craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34) || (craftSlotId3[4] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 105;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1196://snow block
        if((craftSlotId3[0] == 299 && craftSlotId3[1] == 299 && craftSlotId3[3] == 299 && craftSlotId3[4] == 299) || (craftSlotId3[1] == 299 && craftSlotId3[2] == 299 && craftSlotId3[4] == 299 && craftSlotId3[5] == 299) || (craftSlotId3[3] == 299 && craftSlotId3[4] == 299 && craftSlotId3[6] == 299 && craftSlotId3[7] == 299) || (craftSlotId3[4] == 299 && craftSlotId3[5] == 299 && craftSlotId3[7] == 299 && craftSlotId3[8] == 299))
        {
            craftItemId3 = 26;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 553://torches
        if((craftSlotId3[0] == 277 && craftSlotId3[3] == 276) || (craftSlotId3[1] == 277 && craftSlotId3[4] == 276) || (craftSlotId3[2] == 277 && craftSlotId3[5] == 276) || (craftSlotId3[3] == 277 && craftSlotId3[6] == 276) || (craftSlotId3[4] == 277 && craftSlotId3[7] == 276) || (craftSlotId3[5] == 277 && craftSlotId3[8] == 276))
        {
            craftItemId3 = 48;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;


    case 556: //scirrors
        if((craftSlotId3[0] == 278 && craftSlotId3[4] == 278) || (craftSlotId3[1] == 278 && craftSlotId3[5] == 278) || (craftSlotId3[3] == 278 && craftSlotId3[7] == 278) || (craftSlotId3[4] == 278 && craftSlotId3[8] == 278))
        {
            craftItemId3 = 275;
            craftItemSt3 = 0;
            craftItemAm3 = 239;
        }
    break;

    case 99://clay
        if(craftSlotId3[0] == 99 || craftSlotId3[1] == 99 || craftSlotId3[2] == 99 || craftSlotId3[3] == 99 || craftSlotId3[4] == 99 || craftSlotId3[5] == 99 || craftSlotId3[6] == 99 || craftSlotId3[7] == 99 || craftSlotId3[8] == 99)
        {
            craftItemId3 = 283;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    // half blocks

    case 108://cobblestone
        if((craftSlotId3[0] == 36 && craftSlotId3[1] == 36 && craftSlotId3[2] == 36) || (craftSlotId3[3] == 36 && craftSlotId3[4] == 36 && craftSlotId3[5] == 36) || (craftSlotId3[6] == 36 && craftSlotId3[7] == 36 && craftSlotId3[8] == 36))
        {
            craftItemId3 = 82;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 102://half planks
        if((craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[2] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[4] == 34 && craftSlotId3[5] == 34) || (craftSlotId3[6] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34))
        {
            craftItemId3 = 86;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
        //4 bowls
        if((craftSlotId3[0] == 34 && craftSlotId3[4] == 34 && craftSlotId3[2] == 34) || (craftSlotId3[3] == 34 && craftSlotId3[7] == 34 && craftSlotId3[5] == 34))
        {
            craftItemId3 = 302;
            craftItemSt3 = 1;
            craftItemAm3 = 4;
        }
    break;

    case 9://stone
        if((craftSlotId3[0] == 3 && craftSlotId3[1] == 3 && craftSlotId3[2] == 3) || (craftSlotId3[3] == 3 && craftSlotId3[4] == 3 && craftSlotId3[5] == 3) || (craftSlotId3[6] == 3 && craftSlotId3[7] == 3 && craftSlotId3[8] == 3))
        {
            craftItemId3 = 84;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;


    // end

    case 903://mooshroom bowl
        if((craftSlotId3[1] == 300 && craftSlotId3[4] == 301 && craftSlotId3[7] == 302) || (craftSlotId3[1] == 301 && craftSlotId3[4] == 300 && craftSlotId3[7] == 302))
        {
            craftItemId3 = 303;
            craftItemSt3 = 0;
            craftItemAm3 = 1;
        }
    break;


    //wooden instruments
    case 654:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 34 && craftSlotId3[2] == 34)
        {
            craftItemId3 = 250;
            craftItemSt3 = 0;
            craftItemAm3 = 60;

        }
        if(craftSlotId3[0] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 34 && craftSlotId3[3] == 34)
        {
            craftItemId3 = 265;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
        break;

    case 620:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 34)
        {
            craftItemId3 = 270;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }
    break;

    case 586:
        if(craftSlotId3[1] == 34 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 260;
            craftItemSt3 = 0;
            craftItemAm3 = 60;
        }

    break;
    //stone instruments
    case 660:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 36 && craftSlotId3[2] == 36)
        {
            craftItemId3 = 251;
            craftItemSt3 = 0;
            craftItemAm3 = 132;

        }
        if(craftSlotId3[0] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 36 && craftSlotId3[3] == 36)
        {
            craftItemId3 = 266;
            craftItemSt3 = 0;
            craftItemAm3 = 132;

        }
        break;

    case 624:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 36)
        {
            craftItemId3 = 271;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
    break;

    case 588:
        if(craftSlotId3[1] == 36 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 261;
            craftItemSt3 = 0;
            craftItemAm3 = 132;
        }
    break;

    //iron instruments
    case 1386:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 278 && craftSlotId3[2] == 278)
        {
            craftItemId3 = 252;
            craftItemSt3 = 0;
            craftItemAm3 = 251;

        }
        if(craftSlotId3[0] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 278 && craftSlotId3[3] == 278)
        {
            craftItemId3 = 267;
            craftItemSt3 = 0;
            craftItemAm3 = 251;

        }
        break;

    case 1108:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 278)
        {
            craftItemId3 = 272;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
    break;

    case 830:
        if(craftSlotId3[1] == 278 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 262;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
    break;
    //diamond instruments
    case 1389:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 279 && craftSlotId3[2] == 279)
        {
            craftItemId3 = 253;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;

        }
        if(craftSlotId3[0] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[1] == 279 && craftSlotId3[3] == 278)
        {
            craftItemId3 = 268;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;

        }
        break;

    case 1110:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276 && craftSlotId3[0] == 279)
        {
            craftItemId3 = 273;
            craftItemSt3 = 0;
            craftItemAm3 = 1562;
        }
    break;

    case 831:
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 276 && craftSlotId3[7] == 276)
        {
            craftItemId3 = 263;
            craftItemSt3 = 0;
            craftItemAm3 = 251;
        }
    break;

    case 2502: //iron block
        if(craftSlotId3[0] == 278 && craftSlotId3[1] == 278 && craftSlotId3[2] == 278 && craftSlotId3[3] == 278 && craftSlotId3[4] == 278 && craftSlotId3[5] == 278 && craftSlotId3[6] == 278 && craftSlotId3[7] == 278 && craftSlotId3[8] == 278)
        {
            craftItemId3 = 66;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 2583: //hay bale
        if(craftSlotId3[0] == 287 && craftSlotId3[1] == 287 && craftSlotId3[2] == 287 && craftSlotId3[3] == 287 && craftSlotId3[4] == 287 && craftSlotId3[5] == 287 && craftSlotId3[6] == 287 && craftSlotId3[7] == 287 && craftSlotId3[8] == 2287)
        {
            craftItemId3 = 76;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 76: //hay bale to wheat
        if(craftSlotId3[0] == 76 || craftSlotId3[1] == 76 || craftSlotId3[2] == 76 && craftSlotId3[3] == 76 || craftSlotId3[4] == 76 || craftSlotId3[5] == 76 || craftSlotId3[6] == 76 && craftSlotId3[7] == 76 || craftSlotId3[8] == 76)
        {
            craftItemId3 = 287;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 66: //iron block to bars
        if(craftSlotId3[0] == 66 || craftSlotId3[1] == 66 || craftSlotId3[2] == 66 && craftSlotId3[3] == 66 || craftSlotId3[4] == 66 || craftSlotId3[5] == 66 || craftSlotId3[6] == 66 && craftSlotId3[7] == 66 || craftSlotId3[8] == 66)
        {
            craftItemId3 = 278;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 2520: //gold block
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 280 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 65;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 65: //gold block to bars
        if(craftSlotId3[0] == 65 || craftSlotId3[1] == 65 || craftSlotId3[2] == 65 && craftSlotId3[3] == 65 || craftSlotId3[4] == 65 || craftSlotId3[5] == 65 || craftSlotId3[6] == 65 && craftSlotId3[7] == 65 || craftSlotId3[8] == 65)
        {
            craftItemId3 = 280;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;



    case 2511: //diamond block
        if(craftSlotId3[0] == 279 && craftSlotId3[1] == 279 && craftSlotId3[2] == 279 && craftSlotId3[3] == 279 && craftSlotId3[4] == 279 && craftSlotId3[5] == 279 && craftSlotId3[6] == 279 && craftSlotId3[7] == 279 && craftSlotId3[8] == 279)
        {
            craftItemId3 = 64;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 64: //diamond block to diamonds
        if(craftSlotId3[0] == 64 || craftSlotId3[1] == 64 || craftSlotId3[2] == 64 && craftSlotId3[3] == 64 || craftSlotId3[4] == 64 || craftSlotId3[5] == 64 || craftSlotId3[6] == 64 && craftSlotId3[7] == 64 || craftSlotId3[8] == 64)
        {
            craftItemId3 = 279;
            craftItemSt3 = 1;
            craftItemAm3 = 9;
        }
    break;

    case 1932: //ladder
        if(craftSlotId3[0] == 276 && craftSlotId3[2] == 276 && craftSlotId3[3] == 276 && craftSlotId3[4] == 276 && craftSlotId3[5] == 276 && craftSlotId3[6] == 276 && craftSlotId3[8] == 276)
        {
            craftItemId3 = 6;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1156: //brickblock
        if((craftSlotId3[0] == 289 && craftSlotId3[1] == 289 && craftSlotId3[3] == 289 && craftSlotId3[4] == 289) || (craftSlotId3[1] == 289 && craftSlotId3[2] == 289 && craftSlotId3[4] == 289 && craftSlotId3[5] == 289) || (craftSlotId3[3] == 289 && craftSlotId3[4] == 289 && craftSlotId3[6] == 289 && craftSlotId3[7] == 289) || (craftSlotId3[4] == 289 && craftSlotId3[5] == 289 && craftSlotId3[7] == 289 && craftSlotId3[8] == 289))
        {
            craftItemId3 = 27;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 272: //chest
        if(craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[3] == 34 && craftSlotId3[5] == 34 && craftSlotId3[7] == 34 && craftSlotId3[0] == 34 && craftSlotId3[6] == 34 && craftSlotId3[8] == 34)
        {
            craftItemId3 = 100;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 288: //furnace
        if(craftSlotId3[1] == 36 && craftSlotId3[2] == 36 && craftSlotId3[3] == 36 && craftSlotId3[5] == 36 && craftSlotId3[7] == 36 && craftSlotId3[0] == 36 && craftSlotId3[6] == 36 && craftSlotId3[8] == 36)
        {
            craftItemId3 = 106;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 861: //bread
        if((craftSlotId3[0] == 287 && craftSlotId3[1] == 287 && craftSlotId3[2] == 287) || (craftSlotId3[3] == 287 && craftSlotId3[4] == 287 && craftSlotId3[5] == 287) || (craftSlotId3[6] == 287 && craftSlotId3[7] == 287 && craftSlotId3[8] == 287))
        {
            craftItemId3 = 288;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 2524: //golden apple
        if(craftSlotId3[0] == 280 && craftSlotId3[1] == 280 && craftSlotId3[2] == 280 && craftSlotId3[3] == 280 && craftSlotId3[4] == 284 && craftSlotId3[5] == 280 && craftSlotId3[6] == 280 && craftSlotId3[7] == 280 && craftSlotId3[8] == 280)
        {
            craftItemId3 = 285;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 834: //busket
        if((craftSlotId3[0] == 278 && craftSlotId3[4] == 278 && craftSlotId3[2] == 278) || (craftSlotId3[3] == 278 && craftSlotId3[7] == 278 && craftSlotId3[5] == 278))
        {
            craftItemId3 = 290;
            craftItemSt3 = 0;
            craftItemAm3 = 1;
        }
    break;

    case 879: //paper
        if((craftSlotId3[0] == 293 && craftSlotId3[1] == 293 && craftSlotId3[2] == 293) || (craftSlotId3[3] == 293 && craftSlotId3[4] == 293 && craftSlotId3[5] == 293) || (craftSlotId3[6] == 293 && craftSlotId3[7] == 293 && craftSlotId3[8] == 293))
        {
            craftItemId3 = 297;
            craftItemSt3 = 1;
            craftItemAm3 = 3;
        }
    break;

    case 891: //book
        if((craftSlotId3[0] == 297 && craftSlotId3[3] == 297 && craftSlotId3[6] == 297) || (craftSlotId3[1] == 297 && craftSlotId3[4] == 297 && craftSlotId3[7] == 297) || (craftSlotId3[2] == 297 && craftSlotId3[5] == 297 && craftSlotId3[8] == 297))
        {
            craftItemId3 = 298;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 1098: //book shelf
        if(craftSlotId3[0] == 34 && craftSlotId3[1] == 34 && craftSlotId3[2] == 34 && craftSlotId3[3] == 298 && craftSlotId3[4] == 298 && craftSlotId3[5] == 298 && craftSlotId3[6] == 34 && craftSlotId3[7] == 34 && craftSlotId3[8] == 34)
        {
            craftItemId3 = 35;
            craftItemSt3 = 1;
            craftItemAm3 = 1;
        }
    break;

    case 846: //watering can
        if(craftSlotId3[8] == 290 && craftSlotId3[4] == 278 && craftSlotId3[0] == 278)
        {
            craftItemId3 = 304;
            craftItemSt3 = 0;
            craftItemAm3 = 0;
        }
    break;

    case 1420: //diamond watering can
        if(craftSlotId3[1] == 279 && craftSlotId3[4] == 304 && craftSlotId3[3] == 279 && craftSlotId3[5] == 279 && craftSlotId3[7] == 279)
        {
            craftItemId3 = 305;
            craftItemSt3 = 0;
            craftItemAm3 = 0;
        }
    break;

    default:
        craftItemId3 = -1;
        craftItemAm3 = -1;
        craftItemSt3 = 0;
    break;

    }
}

void StatePlay::HandleEvents(StateManager* sManager)
{
    //update delta time
    dt = mTimer.GetDeltaTime();

    cameraSpeed = 2.0f * dt;
    cameraMoveSpeed = 4.0f * dt;

    //free memory counter
    if(devMode)
    {
        freeMemoryTimer += dt;
        if(freeMemoryTimer > 1.0f)
        {
            freeMemory = mSystemMgr->ramAvailable();
            freeMemoryTimer = 0.0f;
        }
    }

    //update input
    mSystemMgr->InputUpdate();
    if(mWorld->HP > 1)
    {
    if(menuState == 0)//game state
    {
        if(invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false)
        {
            if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
            {
                if (mWorld->invId[27+barPosition] != -1)
                {
                    changeY = -0.16f;
                    anim[0] = 1;
                }
                barPosition != 8 ? barPosition ++ : barPosition = 0;

                selectSprite->SetPosition(100 + (barPosition * 35),253);
                startDt = 0;
                dT = 0;
                dET = 0;
                dS = 0;
                dStd = -1;
            }
            //switch right
            if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
            {
                if (mWorld->invId[27+barPosition] != -1)
                {
                    changeY = -0.16f;
                    anim[0] = 1;
                }
                barPosition != 0 ? barPosition -- : barPosition = 8;

                selectSprite->SetPosition(100 + (barPosition * 35),253);
                startDt = 0;
                dT = 0;
                dET = 0;
                dS = 0;
                dStd = -1;
            }
        //menu
        if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
        {
            menuState = 1;
            menuOptions = false;
            optionsMenuPos = 0;
        }

        //camera input
        //rotate uo
        if(keyHold(InputHelper::Instance()->getButtonToAction(4)))
        {
            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            fppCam->PitchView(cameraSpeed);

            if (shift_y > -0.06)
            {

                shift_y -= 0.005;
            }
        }
        else
        {
            if (shift_y < 0)
            {

                shift_y += 0.005;
            }

        }
        //rotate down
        if(keyHold(InputHelper::Instance()->getButtonToAction(5)))
        {
            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            fppCam->PitchView(-cameraSpeed);

            if (shift_y < 0.06)
            {

                shift_y += 0.005;
            }
        }
        else
        {
            if (shift_y > 0)
            {

                shift_y -= 0.005;
            }

        }
        //rotate left
        if(keyHold(InputHelper::Instance()->getButtonToAction(6)))
        {
            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            fppCam->RotateView(cameraSpeed,0,1,0);

            if (shift_x < 0.06)
            {

                shift_x += 0.005;
            }
        }
        else
        {
            if (shift_x > 0)
            {

                shift_x -= 0.005;
            }
        }
        //rotate right
        if(keyHold(InputHelper::Instance()->getButtonToAction(7)))
        {
            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            fppCam->RotateView(-cameraSpeed,0,1,0);

            if (shift_x > -0.06)
            {

                shift_x -= 0.005;
            }
        }
        else
        {
            if (shift_x < 0)
            {

                shift_x += 0.005;
            }
        }

        //move right
        if(keyHold(InputHelper::Instance()->getButtonToAction(3)))
        {
            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            fppCam->StrafePhysic(cameraMoveSpeed);

            if(mWorld->HG > 0.0003)
            {
                mWorld->HG -= 0.0003;
            }
        }
        //move left
        if(keyHold(InputHelper::Instance()->getButtonToAction(2)))
        {
            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            fppCam->StrafePhysic(-cameraMoveSpeed);

            if(mWorld->HG > 0.0003)
            {
                mWorld->HG -= 0.0003;
            }
        }

        //move back
        if(keyHold(InputHelper::Instance()->getButtonToAction(1)))
        {
            if(mWorld->HG > 0.0003)
            {
                mWorld->HG -= 0.0003;
            }

            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            if(canFly)
                fppCam->MovePhysic(-cameraMoveSpeed);
            else
                fppCam->MovePhysicNoY(-cameraMoveSpeed);
        }

        //move forward
        if(keyHold(InputHelper::Instance()->getButtonToAction(0)))
        {
            if(mWorld->HG > 0.0003)
            {
                mWorld->HG -= 0.0003;
            }

            if (startDt == true)
            {
                startDt = false;
                dStd = -1;
            }
            if(canFly)
                fppCam->MovePhysic(cameraMoveSpeed);
            else
                fppCam->MovePhysicNoY(cameraMoveSpeed);
        }

        if(keyHold(InputHelper::Instance()->getButtonToAction(12)))
        {
            dStd = -1;
            if (headInWater || headInLava)	//Legit swimming
            {
                if (walkingOnGround)
                {
                    jumping = true;
                }else
                {
                    playerVelocity.y = 0.4 * JUMPVELOCITY;
                    walkingOnGround = false;
                }
            }
            if ((!headInWater || !headInLava) && !walkingOnGround && (footInWater || footInLava))	//Your above he water, so Jump out
            {

                playerVelocity.y = 1.0 * JUMPVELOCITY;
                walkingOnGround = false;
            }
            if(walkingOnGround)	//Just in case...
            {
                jumping = true;
                mWorld->mainStatistics.jumps += 1;
                if(mWorld->HG > 0.03)
                {
                    mWorld->HG -= 0.03;
                }
            }
            else
                jumping = false;	//Don't bounce
        }

        //add cube
        if(keyPressed(InputHelper::Instance()->getButtonToAction(14)))
        {
            //delete playSB;
            //playSB = new SnowBall2(playerPosition.x,playerPosition.y,playerPosition.z);
            //playSB->SetVeloc(fppCam->upDownAngle,(fppCam->horAngle/(float)180)*PI);
            if (startDt == true) //stop destroying
            {
                startDt = false;
            }

            if(keyPressed(InputHelper::Instance()->getButtonToAction(13))) //open inventory
            {
                if(craft3xEn == false && chestEn == false && furnaceEn == false)
                {
                invEn = true;
                return;
                }

            }

            /// EATING FOOD
            if (mWorld->invId[27+barPosition] == 288) ///BREAD
            {
                mSoundMgr->PlayEatSound();
                mWorld->mainStatistics.foodEaten += 1;
                mWorld->HG += 5;

                if(mWorld->HG > 20)
                {
                    mWorld->HG = 20;
                }
                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            if (mWorld->invId[27+barPosition] == 284) ///APPLE
            {
                mSoundMgr->PlayEatSound();
                mWorld->mainStatistics.foodEaten += 1;
                mWorld->HG += 4;

                if(mWorld->HG > 20)
                {
                    mWorld->HG = 20;
                }
                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0)
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            if (mWorld->invId[27+barPosition] == 303) ///MOOSHROOM BOWL
            {
                mSoundMgr->PlayEatSound();
                mWorld->mainStatistics.foodEaten += 1;
                mWorld->HG += 6;

                if(mWorld->HG > 20)
                {
                    mWorld->HG = 20;
                }
                mWorld->invId[27+barPosition] = 302; // turn it into simple stackable bowl
                mWorld->invSt[27+barPosition] = 1;
                return;
            }

            if (mWorld->invId[27+barPosition] == 285) ///GOLDEN APPLE
            {
                mSoundMgr->PlayEatSound();
                mWorld->mainStatistics.foodEaten += 1;
                mWorld->HG = 20;
                mWorld->HP = 20;
                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0)
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            if (mWorld->invId[27+barPosition] == 299) ///SNOWBALL THROWING
            {
                mSoundMgr->PlayBowSound();

                SnowBall2* NewSB = new SnowBall2(playerPosition.x,playerPosition.y,playerPosition.z);
                NewSB->SetVeloc(fppCam->upDownAngle,(fppCam->horAngle/(float)180)*PI);
                mSnowBalls.push_back(NewSB);

                mWorld->invAm[27+barPosition] -= 1;
                if (mWorld->invAm[27+barPosition] == 0) // [27+barPosition] - selected item/block
                {
                    mWorld->invAm[27+barPosition] = -1;
                    mWorld->invId[27+barPosition] = -1;
                    mWorld->invSt[27+barPosition] = 0;
                }
                return;
            }

            //add cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //get position and view vector
            Vector3 testPos;

            //move to the target +=0.5
            for(float i = 0; i < 5.25f; i+=0.25f)
            {
                testPos = fppCam->m_vPosition + (rayDir * i);

                if(mWorld->invId[27+barPosition] == 290) //busket
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 4) //if it is WATER
                    {
                        if((mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4))
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 4;
                        }
                        else
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;
                        }

                        mWorld->invId[27+barPosition] = 291;

                        int	curchunkTarget = mWorld->getChunkId(testPos);
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        fppCam->needUpdate = true;
                        return;
                    }

                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 112) //if it is lava
                    {
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;

                        mWorld->invId[27+barPosition] = 292;

                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        mWorld->RemoveLigtSourceAtPosition(testPos.x,testPos.y,testPos.z,112);
                        //Rebuild nearby world
                        mWorld->UpdateLightAreaIn(testPos);
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        fppCam->needUpdate = true;
                        return;
                    }

                }

                if(mWorld->invId[27+barPosition] == 304) ///watering can
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 4) //if it is WATER
                    {
                        if((mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4))
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 4;
                        }
                        else
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;
                        }

                        mWorld->invAm[27+barPosition] = 30;

                        int	curchunkTarget = mWorld->getChunkId(testPos);
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        fppCam->needUpdate = true;
                        return;
                    }
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 79) //if it is soil
                    {
                        if(mWorld->invAm[27+barPosition] > 0)
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 80; //watered soil

                            mWorld->invAm[27+barPosition] -= 1;

                            int	curchunkTarget = mWorld->getChunkId(testPos);
                            //Rebuild nearby world
                            mWorld->rebuildChunk(curchunkTarget);
                            mWorld->rebuildTransparentChunk(curchunkTarget);
                            mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                            fppCam->needUpdate = true;
                            return;
                        }
                    }
                }

                if(mWorld->invId[27+barPosition] == 305) ///watering can
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 4) //if it is WATER
                    {
                        if((mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z-1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z-1) == 4) || (mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x-1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4) || (mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z) == 4 && mWorld->GetBlock(testPos.x+1, testPos.y, testPos.z+1) == 4 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z+1) == 4))
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 4;
                        }
                        else
                        {
                            mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 0;
                        }

                        mWorld->invAm[27+barPosition] = 90;

                        int	curchunkTarget = mWorld->getChunkId(testPos);
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        fppCam->needUpdate = true;
                        return;
                    }
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 79) //if it is soil
                    {
                        for(int x = testPos.x -1; x <= testPos.x +1; x++)
                        {
                            for(int z = testPos.z -1; z <= testPos.z +1; z++)
                            {
                                if (mWorld->GetBlock(x, testPos.y, z) == 79)
                                {
                                    if(x < 0 || x > 127 || z < 0 || z > 127)
                                    {
                                        continue;
                                    }
                                    if(mWorld->invAm[27+barPosition] > 0)
                                    {
                                        mWorld->GetBlock(x, testPos.y, z) = 80; //watered soil

                                        int	curchunkTarget = mWorld->getChunkId(testPos);
                                        //Rebuild nearby world
                                        mWorld->rebuildChunk(curchunkTarget);
                                        mWorld->rebuildTransparentChunk(curchunkTarget);
                                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                                        fppCam->needUpdate = true;
                                    }
                                }
                            }
                        }
                    mWorld->invAm[27+barPosition] -= 9;
                    return;
                    }
                }
                //check if we are touch something
                if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z))
                {

                if(mWorld->invId[27+barPosition] >= 270 && mWorld->invId[27+barPosition] <= 274) //hoes
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 1) //if it is grass
                    {
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 2;
                        if(rand() % 10 == 1)
                        {
                            PutInInventory(286,1,1); //we put seed in inventory
                        }

                        mWorld->invAm[27+barPosition] -= 1; //bit break to our hoe
                        if(mWorld->invAm[27+barPosition] == 0) //if it has 0 of solid we jut destroy it
                        {
                            mWorld->invAm[27+barPosition] = -1;
                            mWorld->invId[27+barPosition] = -1;
                            mWorld->invSt[27+barPosition] = 0;
                        }
                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        fppCam->needUpdate = true;
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }

                    if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 2) //if it is dirt
                    {
                        mWorld->mainStatistics.soilPlowed += 1;
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 79;

                        mWorld->invAm[27+barPosition] -= 1;
                        if(mWorld->invAm[27+barPosition] == 0) //if it has 0 of solid we jut destroy it
                        {
                            mWorld->invAm[27+barPosition] = -1;
                            mWorld->invId[27+barPosition] = -1;
                            mWorld->invSt[27+barPosition] = 0;
                        }

                        int	curchunkTarget = mWorld->getChunkId(testPos);

                        fppCam->needUpdate = true;
                        //Rebuild nearby world
                        mWorld->rebuildChunk(curchunkTarget);
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }
                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == Crafting::getID()) // open crafting table menu
                {
                    craft3xEn = true;
                    return;
                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) >= 49 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z) <= 52) //door
                {
                    mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) + 4;
                    mWorld->GetBlock(testPos.x, testPos.y+1, testPos.z) = 58;
                    mSoundMgr->doorSound();

                    int	curchunkTarget = mWorld->getChunkId(testPos);
                    fppCam->needUpdate = true;
                    mWorld->rebuildTransparentChunk(curchunkTarget);
                    mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                    return;
                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) >= 53 && mWorld->GetBlock(testPos.x, testPos.y, testPos.z) <= 56) //door
                {
                    mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y, testPos.z) - 4;
                    mWorld->GetBlock(testPos.x, testPos.y+1, testPos.z) = 57;
                    mSoundMgr->doorSound();

                    int	curchunkTarget = mWorld->getChunkId(testPos);
                    fppCam->needUpdate = true;
                    mWorld->rebuildTransparentChunk(curchunkTarget);
                    mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                    return;
                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 57) //door
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) >= 49 && mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) <= 52) //door
                    {
                        mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) + 4;
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 58;
                        mSoundMgr->doorSound();

                        int	curchunkTarget = mWorld->getChunkId(testPos);
                        fppCam->needUpdate = true;
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }
                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 58) //door
                {
                    if (mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) >= 53 && mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) <= 56) //door
                    {
                        mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) = mWorld->GetBlock(testPos.x, testPos.y-1, testPos.z) - 4;
                        mWorld->GetBlock(testPos.x, testPos.y, testPos.z) = 57;
                        mSoundMgr->doorSound();

                        int	curchunkTarget = mWorld->getChunkId(testPos);
                        fppCam->needUpdate = true;
                        mWorld->rebuildTransparentChunk(curchunkTarget);
                        mWorld->rebuildNearestChunks(curchunkTarget,testPos);
                        return;
                    }
                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == Chest5::getID() || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 131 || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 132 || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 133)
                {
                    chestId = FindChestId(testPos.x,testPos.y,testPos.z);
                    if(chestId != -1)
                    {
                        craft3xEn = false;
                        chestEn = true;
                        UseChest = mWorld->mChests[chestId];
                        return;
                    }

                }

                if (mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 106 || mWorld->GetBlock(testPos.x, testPos.y, testPos.z) == 107)
                {
                    furnaceId = FindFurnaceId(testPos.x,testPos.y,testPos.z);
                    if(furnaceId != -1)
                    {
                        craft3xEn = false;
                        chestEn = false;
                        furnaceEn = true;
                        UseFurnace = mWorld->mFurnaces[furnaceId];
                        return;
                    }

                }


                    BoundingBox testBox = BoundingBox(Vector3(cubePos.x - 0.5f,cubePos.y - 0.5f,cubePos.z - 0.5f),Vector3(cubePos.x + 0.5f,cubePos.y + 0.5f,cubePos.z + 0.5f));
                    Ray tesRay = Ray(fppCam->m_vPosition,rayDir);

                    float distance = -1.0f;
                    tesRay.hasIntersected(testBox,distance);

                    if(distance != -1.0f)
                    {
                        Vector3 hitPos = fppCam->m_vPosition + (rayDir * distance);
                        Vector3 normal = (hitPos - cubePos);
                        normal.normalize();

                        Vector3 testPos2;

                        if(normal.x < -0.66f)
                            testPos2.x = -1.0f;
                        else if(normal.x > 0.66f)
                            testPos2.x = 1.0f;
                        else
                            testPos2.x = 0.0f;

                        if(normal.y < -0.66f)
                            testPos2.y = -1.0f;
                        else if(normal.y > 0.66f)
                            testPos2.y = 1.0f;
                        else
                            testPos2.y = 0.0f;

                        if(normal.z < -0.66f)
                            testPos2.z = -1.0f;
                        else if(normal.z > 0.66f)
                            testPos2.z = 1.0f;
                        else
                            testPos2.z = 0.0f;


                        testPos2 += testPos;

                        //check if this block is empty
                        if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID() || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0 || mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Cloud::getID())
                        {
                            //now check if player is not there ;) we don't want to place cubes where we stand
                            int boxX = (int)testPos2.x;
                            int boxY = (int)testPos2.y;
                            int boxZ = (int)testPos2.z;

                            BoundingBox blockBox = BoundingBox(Vector3(boxX,boxY,boxZ),Vector3(boxX + 1,boxY + 1,boxZ + 1));
                            BoundingBox playerBox = BoundingBox(Vector3(playerPosition.x - 0.15f,playerPosition.y - 1.3f,playerPosition.z - 0.15f),Vector3(playerPosition.x + 0.15f,playerPosition.y + 0.4f,playerPosition.z + 0.15f));

                            if(!blockBox.intersect(playerBox) || mWorld->invId[27+barPosition] == 48)
                            {
                                //check if you want put light source or normal block
                                if(mWorld->CanPutBlockHere(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]))
                                {
                                    if(mWorld->LightSourceBlock(mWorld->invId[27+barPosition]))
                                    {
                                        mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,mWorld->invId[27+barPosition]);
                                    }
                                    if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == Lava::getID())
                                    {
                                        mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 0;
                                        mWorld->RemoveLigtSourceAtPosition(testPos.x,testPos.y,testPos.z,112);
                                    }

                                    if (mWorld->invId[27+barPosition]<250) // if block in our hands
                                    {
                                        if(mWorld->invId[27+barPosition] == 100) // if we are putting chest
                                        {
                                            Chest* NewChest =  new Chest(testPos2.x,testPos2.y,testPos2.z);
                                            mWorld->mChests.push_back(NewChest);
                                        }

                                        if(mWorld->invId[27+barPosition] == 106) // if we are putting furnace
                                        {
                                            Furnace* NewFurnace =  new Furnace(testPos2.x,testPos2.y,testPos2.z);
                                            mWorld->mFurnaces.push_back(NewFurnace);
                                        }

                                        if(mWorld->invId[27+barPosition]!=-1) //multi-texturing blocks
                                        {

                                                switch(mWorld->invId[27+barPosition])
                                                {
                                                case 74:
                                                if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 123;
                                                }
                                                if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 124;
                                                }
                                                if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 74;
                                                }
                                                if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 122;
                                                }
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 74;
                                                }
                                                break;

                                                case 100:
                                                if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 132; // 3
                                                }
                                                if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 133; // 4
                                                }
                                                if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 100; // 1
                                                }
                                                if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 131; // 2
                                                }
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 100;
                                                }
                                                break;

                                                case 125:
                                                if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 125; // 3
                                                }
                                                if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 126; // 4
                                                }
                                                if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 127; // 1
                                                }
                                                if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 128; // 2
                                                }
                                                if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 125;
                                                }
                                                break;

                                                default:
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = mWorld->invId[27+barPosition];
                                                break;
                                                }

                                            if(mWorld->invAm[27+barPosition]==1)
                                            {
                                                mWorld->invAm[27+barPosition]= -1;
                                                mWorld->invId[27+barPosition]= -1;
                                                mWorld->invSt[27+barPosition]= 0;
                                            }
                                            else
                                            {
                                                mWorld->invAm[27+barPosition]-= 1;
                                            }

                                            }
                                    }
                                    else //if item in our hand
                                    {
                                        if(mWorld->invId[27+barPosition] == 286) // if it is seeds
                                        {
                                            if( mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 79 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 80) // planting seeds
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 134;
                                                fppCam->needUpdate = true;

                                                mWorld->invAm[27+barPosition] -= 1;
                                                if(mWorld->invAm[27+barPosition] == 0)
                                                {
                                                   mWorld->invAm[27+barPosition] = -1;
                                                   mWorld->invSt[27+barPosition] = 0;
                                                   mWorld->invId[27+barPosition] = -1;
                                                }
                                            }
                                        }

                                        if(mWorld->invId[27+barPosition] >= 300 && mWorld->invId[27+barPosition] <= 301) // if it is moshrooms
                                        {
                                            mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 77 + (mWorld->invId[27+barPosition] - 300);
                                            fppCam->needUpdate = true;

                                            mWorld->invAm[27+barPosition] -= 1;
                                            if(mWorld->invAm[27+barPosition] == 0)
                                            {
                                                mWorld->invAm[27+barPosition] = -1;
                                                mWorld->invSt[27+barPosition] = 0;
                                                mWorld->invId[27+barPosition] = -1;
                                            }
                                        }

                                        if(mWorld->invId[27+barPosition] >= 294 && mWorld->invId[27+barPosition] <= 296) // if it is flowers or saplings
                                        {
                                            if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 1 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 2) // if under is dirt or grass
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 119 + (mWorld->invId[27+barPosition] - 294); //very difficult algorithm >:
                                                fppCam->needUpdate = true;
                                                int chunkTarget = mWorld->getChunkId(testPos2);
                                                mWorld->rebuildChunk(chunkTarget);

                                                mWorld->invAm[27+barPosition] -= 1;
                                                if(mWorld->invAm[27+barPosition] == 0)
                                                {
                                                   mWorld->invAm[27+barPosition] = -1;
                                                   mWorld->invSt[27+barPosition] = 0;
                                                   mWorld->invId[27+barPosition] = -1;
                                                }
                                            }
                                        }

                                        if(mWorld->invId[27+barPosition] == 306) // if it is flowers or saplings
                                        {
                                            if(mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) == 0)
                                            {
                                            if(fppCam->horAngle > 45 && fppCam->horAngle < 135)
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 49; // 3
                                                mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                            }
                                            if(fppCam->horAngle > 225 && fppCam->horAngle < 315)
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 50; // 4
                                                mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                            }
                                            if(fppCam->horAngle < 45 || fppCam->horAngle > 315)
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 51; // 1
                                                mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                            }
                                            if(fppCam->horAngle > 135 && fppCam->horAngle < 225)
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 52; // 2
                                                mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                            }
                                            if(mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) == 0)
                                            {
                                                mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 49;
                                                mWorld->GetBlock(testPos2.x,testPos2.y+1,testPos2.z) = 57;
                                            }

                                            fppCam->needUpdate = true;
                                            int chunkTarget = mWorld->getChunkId(testPos2);
                                            mWorld->rebuildTransparentChunk(chunkTarget);
                                            mWorld->rebuildNearestChunks(chunkTarget,testPos2);

                                            mWorld->invAm[27+barPosition] -= 1;
                                            if(mWorld->invAm[27+barPosition] == 0)
                                            {
                                                mWorld->invAm[27+barPosition] = -1;
                                                mWorld->invSt[27+barPosition] = 0;
                                                mWorld->invId[27+barPosition] = -1;
                                            }
                                            }
                                        }

                                        if(mWorld->invId[27+barPosition] == 293) // if it is cane item
                                        {
                                            if(mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z) == 7) //check if under is sand
                                            {
                                                if(mWorld->GetBlock(testPos2.x-1,testPos2.y-1,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x+1,testPos2.y-1,testPos2.z) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z+1) == 4 || mWorld->GetBlock(testPos2.x,testPos2.y-1,testPos2.z-1) == 4)
                                                {
                                                    mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 33;
                                                    fppCam->needUpdate = true;

                                                    mWorld->invAm[27+barPosition] -= 1;
                                                    if(mWorld->invAm[27+barPosition] == 0)
                                                    {
                                                        mWorld->invAm[27+barPosition] = -1;
                                                        mWorld->invSt[27+barPosition] = 0;
                                                        mWorld->invId[27+barPosition] = -1;
                                                    }
                                                }
                                            }
                                        }

                                        if(mWorld->invId[27+barPosition] == 291) // if it is water busket
                                        {
                                            int chunkTarget = mWorld->getChunkId(testPos2);
                                            mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 4;
                                            mWorld->invId[27+barPosition] = 290;

                                            //mWorld->rebuildChunk(chunkTarget);
                                            //mWorld->rebuildTransparentChunk(chunkTarget);
                                            fppCam->needUpdate = true;
                                        }
                                        if(mWorld->invId[27+barPosition] == 292) // if it is lava busket
                                        {
                                            int chunkTarget = mWorld->getChunkId(testPos2);

                                            mWorld->GetBlock(testPos2.x,testPos2.y,testPos2.z) = 112;
                                            mWorld->invId[27+barPosition] = 290;
                                            mWorld->SetLigtSourcePosition(testPos2.x,testPos2.y,testPos2.z,112);
                                            mWorld->RebuildChunksLight(testPos2,chunkTarget,112);
                                            fppCam->needUpdate = true;
                                        }
                                    }
                                    fppCam->needUpdate = true;

                                    mWorld->mainStatistics.blockPlaced += 1;

                                    int chunkTarget = mWorld->getChunkId(testPos2);

                                    if(chunkTarget != -1)
                                    {
                                        mSoundMgr->PlayPlopSound();
                                        //rebuild
                                        if(mWorld->LightSourceBlock(mWorld->invId[27+barPosition]))
                                        {
                                            mWorld->RebuildChunksLight(testPos2,chunkTarget,(mWorld->invId[27+barPosition]));
                                        }

                                        //check if there are light sources nearby
                                        mWorld->UpdateLightAreaIn(testPos2);
                                        mWorld->rebuildTransparentChunk(chunkTarget);
                                        mWorld->rebuildNearestChunks(chunkTarget,testPos2);
                                        //rebuild chunks that are near this chunk
                                        mWorld->rebuildChunk(chunkTarget);
                                    }
                                }
                                fppCam->needUpdate = true;
                            }
                        }
                    }

                    break;
                }
            }


        }

        if(keyPressed(InputHelper::Instance()->getButtonToAction(13)))
        {
            //remove cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //we are takin our positiona and view vector
            Vector3 testPos2;

            testPos2 = Vector3(-1,-1,-1);

            //we are moving slowly to the target +=0.5
            for(float i = 0; i < 5.25f; i+=0.25f)
            {
                testPos2 = fppCam->m_vPosition + (rayDir * i);
                //check if we touch something
                if(mWorld->BlockEditable(testPos2.x,testPos2.y,testPos2.z))
                {
                    if (startDt == false)
                    {
                        testPos1.x  = testPos2.x;
                        testPos1.y  = testPos2.y;
                        testPos1.z  = testPos2.z;
                        switch(mWorld->BlockMaterial(testPos2.x,testPos2.y,testPos2.z))
                        {
                            case 2:

                            dET = 110;
                            if(mWorld->invId[27+barPosition] == 250)
                            {
                                dS = 1.5;
                            }
                            else if(mWorld->invId[27+barPosition] == 251)
                            {
                                dS = 3;
                            }
                            else if(mWorld->invId[27+barPosition] == 252)
                            {
                                dS = 5;
                            }
                            else if(mWorld->invId[27+barPosition] == 253)
                            {
                                dS = 8;
                            }
                            else if(mWorld->invId[27+barPosition] == 254)
                            {
                                dS = 11;
                            }
                            else
                            {
                                dS = 0.35;
                            }
                            break;

                            case 1:

                            dET = 125;
                            if(mWorld->invId[27+barPosition] == 265)
                            {
                                dS = 1.5;
                            }
                            else if(mWorld->invId[27+barPosition] == 266)
                            {
                                dS = 3;
                            }
                            else if(mWorld->invId[27+barPosition] == 267)
                            {
                                dS = 4;
                            }
                            else if(mWorld->invId[27+barPosition] == 268)
                            {
                                dS = 5;
                            }
                            else
                            {
                                dS = 1;
                            }
                            break;

                            case 3:

                            dET = 80;
                            if(mWorld->invId[27+barPosition] == 260)
                            {
                                dS = 4;
                            }
                            else if(mWorld->invId[27+barPosition] == 261)
                            {
                                dS = 6;
                            }
                            else if(mWorld->invId[27+barPosition] == 262)
                            {
                                dS = 8;
                            }
                            else if(mWorld->invId[27+barPosition] == 263)
                            {
                                dS = 10;
                            }
                            else
                            {
                                dS = 1.5;
                            }
                            break;

                            case 4:

                            dET = 50;
                            if(mWorld->invId[27+barPosition] == 275)
                            {
                                dS = 5;
                            }
                            else
                            {
                                dS = 2.5;
                            }
                            break;

                            case 5:
                            dET = 100;
                            if(mWorld->invId[27+barPosition] == 253)
                            {
                                dS = 0.3;
                            }
                            else
                            {
                                dS = 0.00001;
                            }
                            break;

                            case 6:
                            dET = 10000000;
                            dS = 0.000000001;
                            break;

                            break;

                            default:
                            dET = 15;
                            dS = 1;
                            break;

                        }
                        dT = 0;
                        startDt = true;
                    }

                }
            }
        }

        //remove cube
        if(keyHold(InputHelper::Instance()->getButtonToAction(13)))
        {
            if (startDt == true)
            {

                dT < dET ? dT += dS : dT = 0;
                if(dT < dET / 5)
                {
                    if(dStd != 0)
                    {
                        dStd = 0;
                    }
                }
                if(dT >= dET / 5 && dT < (dET / 5)*2)
                {
                    if(dStd != 1)
                    {
                        dStd = 1;
                    }
                }
                if(dT >= (dET / 5)*2 && dT < (dET / 5)*3)
                {
                    if(dStd != 2)
                    {
                        dStd = 2;
                    }
                }
                if(dT >= (dET / 5)*3 && dT < (dET / 5)*4)
                {
                    if(dStd != 3)
                    {
                        dStd = 3;
                    }
                }
                if(dT >= (dET / 5)*4 && dT < (dET / 5)*5)
                {
                    if(dStd != 4)
                    {
                        dStd = 4;
                    }
                }
                //remove block99
                if (dT >= dET)
                {
                    bool wasLight = false;
                    block_t oldBlock = 0;

                    if(mWorld->LightSourceBlock(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z)))//if it's light block
                    {
                        oldBlock = mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z);
                        wasLight = true;
                    }

                    if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 100 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 131 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 132 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 133) // if it is chest
                    {
                        chestId = FindChestId(testPos1.x,testPos1.y,testPos1.z);
                        delete mWorld->mChests[chestId];
                        mWorld->mChests.erase(mWorld->mChests.begin()+chestId);
                        //delete mWorld->mChests[chestId];
                    }

                    if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 104 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 105)
                    {
                        furnaceId = FindFurnaceId(testPos1.x,testPos1.y,testPos1.z);
                        delete mWorld->mFurnaces[furnaceId];
                        mWorld->mFurnaces.erase(mWorld->mFurnaces.begin()+furnaceId);
                        //delete mWorld->mChests[chestId];
                    }
                    //mWorld->BlockSoundAtPos(testPos1);

                    if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 275)
                    {
                        mWorld->invAm[27+barPosition] -= 1;
                        if(mWorld->invAm[27+barPosition] == 0)
                        {
                            mWorld->invId[27+barPosition] = -1;
                            mWorld->invAm[27+barPosition] = -1;
                            mWorld->invSt[27+barPosition] = 0;
                            mSoundMgr->PlayBreakSound();
                        }
                    }

                    switch(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z))
                    {
                    case 9:
                        if(mWorld->invId[27+barPosition] != 275)
                        {
                            if (rand() % 20 == 1)
                            {
                                PutInInventory(284,1,1);
                            }

                            if (rand() % 20 >= 17)
                            {
                                PutInInventory(296,1,1);
                            }
                        }
                        else
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 137:
                        PutInInventory(287,1,1);
                        PutInInventory(286,1 + rand() % 2,1);
                    break;
                    case 93:
                        if(mWorld->invId[27+barPosition] >= 260 && mWorld->invId[27+barPosition] <= 264)
                        {
                            PutInInventory(299,4,1);
                        }
                    break;
                    case 3:
                        if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 36:
                        if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 41:
                        if(mWorld->invId[27+barPosition] >= 251 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 42:
                        if(mWorld->invId[27+barPosition] >= 250 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 43:
                        if(mWorld->invId[27+barPosition] >= 252 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 44:
                        if(mWorld->invId[27+barPosition] >= 252 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 5:
                        if(mWorld->invId[27+barPosition] >= 252 && mWorld->invId[27+barPosition] <= 254)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    case 99:
                        PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),4,1);
                    break;
                    default:
                        if (mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z) != -1)
                        {
                            PutInInventory(mWorld->BlockLoot(testPos1.x,testPos1.y,testPos1.z),1,1);
                        }
                    break;
                    }

                    if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) >= 57 && mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) <= 58) // if it is ice
                    {
                        mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                        mWorld->GetBlock(testPos1.x,testPos1.y-1,testPos1.z) = 0;
                    }

                    if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) >= 49 && mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) <= 56) // if it is ice
                    {
                        mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                        mWorld->GetBlock(testPos1.x,testPos1.y+1,testPos1.z) = 0;
                    }

                    if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 32) // if it is ice
                    {
                        mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 4;
                    }
                    else if(mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 9 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 93 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 8 || mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) == 31)
                    {
                        mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                        mWorld->initPutBlocksLight(testPos1.x,testPos1.z);
                    }
                    else
                    {
                        mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z) = 0;
                    }

                    mWorld->mainStatistics.blockDestroyed += 1;
                    int   chunkTarget = mWorld->getChunkId(testPos1);

                    //check if this block is a support for light block
                    mWorld->CheckForTorchSupport(testPos1.x,testPos1.y,testPos1.z,mWorld->GetBlock(testPos1.x,testPos1.y,testPos1.z));


                    //before rebuilding update light info
                    if(wasLight)
                    {
                        mWorld->RemoveLigtSourceAtPosition(testPos1.x,testPos1.y,testPos1.z,oldBlock);
                    }

                    mWorld->UpdateLightAreaIn(testPos1);
                    if(chunkTarget != -1)
                    {
                        //rebuild
                        if(wasLight)
                        {
                            mWorld->RebuildChunksLight(testPos1,chunkTarget,oldBlock);
                        }
                        else
                        {
                            //check if there are light sources nearby
                            //rebuild chunks
                            mWorld->rebuildChunk(chunkTarget);
                            mWorld->rebuildTransparentChunk(chunkTarget);
                            mWorld->rebuildNearestChunks(chunkTarget,testPos1);
                        }
                    }

                    if(mWorld->HG > 0.01)
                    {
                        mWorld->HG -= 0.01;
                    }
                    fppCam->needUpdate = true;
                    testPos1 = Vector3(-1,-1,-1);
                    startDt = false;
                    dT = 0;
                    dET = 0;
                    dS = 0;
                    chestId = -1;
                    dStd = -1;
                }
            }
        }
        else
        {
            if (startDt != false)
            {
                dT = 0;
                dStd = -1;
                startDt = false;
                chestId = -1;
            }

        }
        //jump
        }

        /// INVENTORY

        if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
        {
        //Craft item

        if(keyPressed(InputHelper::Instance()->getButtonToAction(14))) // if you press R
        {
            if(keyPressed(InputHelper::Instance()->getButtonToAction(13))) //turn off inventory, if L
            {
                invEn = false;
                craft3xEn = false;
                furnaceEn = false;
                chestEn = false;
                upEn = false;
                furnaceEn = false;

                invXPosition = 0;
                invYPosition = 0;
                chestId = -1;
                selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));

                UseChest = 0;
                UseFurnace = 0;
                return;
            }
            if(invEn == true) // if 2x craft menu is open
            {
                if(craftItemId != -1) // if craft cell is not empty
                {
                    if(mWorld->mId == craftItemId) // if item in craft cell = item in your mouse
                    {
                        if(craftItemSt == 1) // if item in craft cell is stackble
                        {
                            if(mWorld->mAm+craftItemAm <= 64) //if sum of item in you mouse and items in craft cell is lower or equal than 64
                            {
                                for(int i = 0; i <= 3; i++) // check items in craft menu
                                {
                                    craftSlotAm[i] -= 1;
                                    if(craftSlotAm[i] == 0) // delete if 0
                                    {
                                        craftSlotId[i] = -1;
                                        craftSlotAm[i] = -1;
                                        craftSlotSt[i] = 0;
                                    }
                                }

                                mWorld->mAm += craftItemAm; // item in mouse ++
                                mWorld->mainStatistics.itemsCrafted += craftItemAm;

                                CraftItem2x2(); // repeat function because in craft menu we can lost items
                            }
                        }
                    }

                    if(mWorld->mId == -1) //if you haven't mouse item
                    {
                        for(int i = 0; i <= 3; i++)
                        {
                            craftSlotAm[i] -= 1;
                            if(craftSlotAm[i] == 0)
                            {
                                craftSlotId[i] = -1;
                                craftSlotAm[i] = -1;
                                craftSlotSt[i] = 0;
                            }
                        }
                        mWorld->mId = craftItemId; // mouse item id = id of craft cell item
                        mWorld->mAm = craftItemAm;
                        mWorld->mSt = craftItemSt;
                        mWorld->mainStatistics.itemsCrafted += craftItemAm;

                        CraftItem2x2();

                    }
                }
            }


            if(furnaceEn == true)
            {
                if(UseFurnace->furnaceSlotId[2] != -1)
                {
                    if(mWorld->mId == UseFurnace->furnaceSlotId[2])
                    {
                        if(UseFurnace->furnaceSlotSt[2] == 1)
                        {
                            if(mWorld->mAm+UseFurnace->furnaceSlotAm[2] <= 64)
                            {
                                mWorld->mAm += UseFurnace->furnaceSlotAm[2];

                                UseFurnace->furnaceSlotAm[2] = -1;
                                UseFurnace->furnaceSlotId[2] = -1;
                                UseFurnace->furnaceSlotSt[2] = 0;
                            }
                        }
                    }

                    if(mWorld->mId == -1) //if you haven't mouse item
                    {
                        mWorld->mId = UseFurnace->furnaceSlotId[2];
                        mWorld->mAm = UseFurnace->furnaceSlotAm[2];
                        mWorld->mSt = UseFurnace->furnaceSlotSt[2];

                        UseFurnace->furnaceSlotId[2] = -1;
                        UseFurnace->furnaceSlotAm[2] = -1;
                        UseFurnace->furnaceSlotSt[2] = 0;
                    }
                }
            }


            if(craft3xEn == true)
            {
                if(craftItemId3 != -1)
                {

                    if(mWorld->mId == craftItemId3)
                    {
                        if(craftItemSt3 == 1)
                        {
                            if(mWorld->mAm+craftItemAm3 <= 64)
                            {
                                for(int i = 0; i <= 8; i++)
                                {
                                    craftSlotAm3[i] -= 1;
                                    if(craftSlotAm3[i] == 0)
                                    {
                                        craftSlotId3[i] = -1;
                                        craftSlotAm3[i] = -1;
                                        craftSlotSt3[i] = 0;
                                    }
                                }

                                mWorld->mAm += craftItemAm3;
                                mWorld->mainStatistics.itemsCrafted += craftItemAm3;

                                CraftItem3x3();
                            }
                        }
                    }

                    if(mWorld->mId == -1)
                    {
                        for(int i = 0; i <= 8; i++)
                        {
                            craftSlotAm3[i] -= 1;
                            if(craftSlotAm3[i] == 0)
                            {
                                craftSlotId3[i] = -1;
                                craftSlotAm3[i] = -1;
                                craftSlotSt3[i] = 0;
                            }
                        }
                        mWorld->mId = craftItemId3;
                        mWorld->mAm = craftItemAm3;
                        mWorld->mSt = craftItemSt3;
                        mWorld->mainStatistics.itemsCrafted += craftItemAm3;

                        CraftItem3x3();
                    }
                }
            }
        }

        //switch right
        if(keyPressed(InputHelper::Instance()->getButtonToAction(9)))
        {
            if (upEn == 0) // if your mouse in neither of craft menus
            {
                invXPosition != 8 ? invXPosition ++ : invXPosition = 8;

                selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
            }
            else
            {
                if(invEn == 1)
                {
                    invXPosition != 1 ? invXPosition ++ : invXPosition = 1;
                    selectInvSprite->SetPosition(250 + (invXPosition * 27),78+(invYPosition * 27));
                }
                if(craft3xEn == 1)
                {
                    invXPosition != 2 ? invXPosition ++ : invXPosition = 2;
                    selectInvSprite->SetPosition(164 + (invXPosition * 27),65+(invYPosition * 27));
                }
                if(chestEn == 1) // if it is in chest
                {
                    invXPosition != 8 ? invXPosition ++ : invXPosition = 8;
                    selectInvSprite->SetPosition(131 + (invXPosition * 27),60+(invYPosition * 27));
                }
            }

        }

        //switch left
        if(keyPressed(InputHelper::Instance()->getButtonToAction(8)))
        {
            if (upEn == 0) // not only craft but chest too
            {
                invXPosition != 0 ? invXPosition -- : invXPosition = 0;

                selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
            }
            else
            {
                invXPosition != 0 ? invXPosition -- : invXPosition = 0;
                if(invEn == 1)
                {
                    selectInvSprite->SetPosition(250 + (invXPosition * 27),78+(invYPosition * 27));
                }
                if(craft3xEn == 1)
                {
                    selectInvSprite->SetPosition(164 + (invXPosition * 27),65+(invYPosition * 27));
                }
                if(chestEn == 1)
                {
                    selectInvSprite->SetPosition(131 + (invXPosition * 27),60+(invYPosition * 27));
                }
            }



        }

        //switch down
        if(keyPressed(InputHelper::Instance()->getButtonToAction(11)))
        {
            if (upEn == 0)
            {
                invYPosition != 3 ? invYPosition ++ : invYPosition = 3;
                selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
            }
            else
            {
                if (invEn == 1) //if mouse in the down of menu
                {
                    if (invYPosition == 1)
                    {
                        upEn = 0; // we go to standart inv menu
                        invYPosition = 0;
                        invXPosition = 5 + invXPosition;
                        selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
                        return;
                    }
                    invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                    selectInvSprite->SetPosition(250 + (invXPosition * 27),78+(invYPosition * 27));
                }

                if (craft3xEn == 1)
                {
                    if (invYPosition == 2)
                    {
                        upEn = 0;
                        invYPosition = 0;
                        invXPosition = 1 + invXPosition;
                        selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
                        return;
                    }
                    invYPosition != 2 ? invYPosition ++ : invYPosition = 2;
                    selectInvSprite->SetPosition(164 + (invXPosition * 27),65+(invYPosition * 27));
                }

                if (chestEn == 1)
                {
                    if (invYPosition == 2)
                    {
                        upEn = 0;
                        invYPosition = 0;
                        selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
                        return;
                    }
                    invYPosition != 1 ? invYPosition ++ : invYPosition = 2;
                    selectInvSprite->SetPosition(131 + (invXPosition * 27),60+(invYPosition * 27));
                }

                if (furnaceEn == 1)
                {
                    if (invYPosition == 1)
                    {
                        upEn = 0;
                        invYPosition = 0;
                        invXPosition = 2;
                        selectInvSprite->SetPosition(131 + (invXPosition * 27) ,165+(invYPosition * 27));
                        return;
                    }
                    invYPosition != 1 ? invYPosition ++ : invYPosition = 1;
                    selectInvSprite->SetPosition(201 ,61+(invYPosition * 54));
                }
            }
        }

        //switch up
        if(keyPressed(InputHelper::Instance()->getButtonToAction(10)))
        {
            if (upEn == 0)
            {

                if (invYPosition == 0)
                {
                    upEn = 1;
                    if(invEn == 1)
                    {
                        invXPosition = 0;
                        invYPosition = 0;
                        selectInvSprite->SetPosition(250 + (invXPosition * 27),78+(invYPosition * 27));
                    }
                    if(craft3xEn == 1)
                    {
                        invXPosition = 0;
                        invYPosition = 0;
                        selectInvSprite->SetPosition(164 + (invXPosition * 27),65+(invYPosition * 27));
                    }
                    if(chestEn == 1)
                    {
                        invYPosition = 2;
                        selectInvSprite->SetPosition(131 + (invXPosition * 27),60+(invYPosition * 27));
                    }
                    if(furnaceEn == 1)
                    {
                        invYPosition = 1;
                        selectInvSprite->SetPosition(201,61+(invYPosition * 54));
                    }
                    return;
                }
                invYPosition != 0 ? invYPosition -- : invYPosition = 0;
                selectInvSprite->SetPosition(131 + (invXPosition * 27),165+(invYPosition * 27));
            }
            else
            {
                invYPosition != 0 ? invYPosition -- : invYPosition = 0;

                if(invEn == 1)
                {
                    selectInvSprite->SetPosition(250 + (invXPosition * 27),78+(invYPosition * 27));
                }
                if(craft3xEn == 1)
                {
                    selectInvSprite->SetPosition(164 + (invXPosition * 27),65+(invYPosition * 27));
                }
                if(chestEn == 1)
                {
                    selectInvSprite->SetPosition(131 + (invXPosition * 27),60+(invYPosition * 27));
                }
                if(furnaceEn == 1)
                {
                    selectInvSprite->SetPosition(201,61+(invYPosition * 54));
                }
            }
        }


        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
            if (upEn == 0)
            {
                if (mWorld->mId == -1)
                {
                    if (mWorld->invId[invYPosition*9 + invXPosition] != -1)
                    {
                        mWorld->mId = mWorld->invId[invYPosition*9 + invXPosition];
                        mWorld->mAm = mWorld->invAm[invYPosition*9 + invXPosition];
                        mWorld->mSt = mWorld->invSt[invYPosition*9 + invXPosition];
                        mWorld->invId[invYPosition*9 + invXPosition] = -1;
                        mWorld->invAm[invYPosition*9 + invXPosition] = -1;
                        mWorld->invSt[invYPosition*9 + invXPosition] = 0;
                    }
                }
                else
                {
                    if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
                    {
                        mWorld->invId[invYPosition*9 + invXPosition]=mWorld->mId;
                        mWorld->invAm[invYPosition*9 + invXPosition]=mWorld->mAm;
                        mWorld->invSt[invYPosition*9 + invXPosition]=mWorld->mSt;
                        mWorld->mId = -1;
                        mWorld->mAm = -1;
                        mWorld->mSt = 0;
                    }

                    if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
                    {
                        if(mWorld->invSt[invYPosition*9 + invXPosition] == 1)
                        {
                            if (mWorld->invAm[invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                            {
                                mWorld->invAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
                                mWorld->mId = -1;
                                mWorld->mAm = -1;
                                mWorld->mSt = 0;
                            }
                            else
                            {
                                mWorld->mAm = (mWorld->invAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                                mWorld->invAm[invYPosition*9 + invXPosition]=64;

                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mAm = -1;
                                    mWorld->mId = -1;
                                    mWorld->mSt = 0;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                if (invEn == 1)
                {
                    if (mWorld->mId == -1)
                    {
                        if (craftSlotId[invYPosition*2 + invXPosition] != -1)
                        {
                            mWorld->mId = craftSlotId[invYPosition*2 + invXPosition];
                            mWorld->mAm = craftSlotAm[invYPosition*2 + invXPosition];
                            mWorld->mSt = craftSlotSt[invYPosition*2 + invXPosition];
                            craftSlotId[invYPosition*2 + invXPosition] = -1;
                            craftSlotAm[invYPosition*2 + invXPosition] = -1;
                            craftSlotSt[invYPosition*2 + invXPosition] = 0;
                        }
                    }
                    else
                    {
                        if (craftSlotId[invYPosition*2 + invXPosition] == -1)
                        {
                            craftSlotId[invYPosition*2 + invXPosition]=mWorld->mId;
                            craftSlotAm[invYPosition*2 + invXPosition]=mWorld->mAm;
                            craftSlotSt[invYPosition*2 + invXPosition]=mWorld->mSt;
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                            mWorld->mSt = 0;
                        }

                        if (craftSlotId[invYPosition*2 + invXPosition] == mWorld->mId)
                        {
                            if(craftSlotSt[invYPosition*2 + invXPosition] == 1)
                            {
                            if (craftSlotAm[invYPosition*2 + invXPosition]+mWorld->mAm < 64)
                            {
                                craftSlotAm[invYPosition*2 + invXPosition]+=mWorld->mAm;
                                mWorld->mId = -1;
                                mWorld->mAm = -1;
                                mWorld->mSt = 0;
                            }
                            else
                            {
                                mWorld->mAm = (craftSlotAm[invYPosition*2 + invXPosition] + mWorld->mAm) - 64;
                                craftSlotAm[invYPosition*2 + invXPosition]=64;

                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mAm = -1;
                                    mWorld->mId = -1;
                                    mWorld->mSt = 0;
                                }
                            }
                            }
                        }
                    }
                    CraftItem2x2();
                }

                if (craft3xEn == 1)
                {
                    if (mWorld->mId == -1)
                    {
                        if (craftSlotId3[invYPosition*3 + invXPosition] != -1)
                        {
                            mWorld->mId = craftSlotId3[invYPosition*3 + invXPosition];
                            mWorld->mAm = craftSlotAm3[invYPosition*3 + invXPosition];
                            mWorld->mSt = craftSlotSt3[invYPosition*3 + invXPosition];
                            craftSlotId3[invYPosition*3 + invXPosition] = -1;
                            craftSlotAm3[invYPosition*3 + invXPosition] = -1;
                            craftSlotSt3[invYPosition*3 + invXPosition] = 0;
                        }
                    }
                    else
                    {
                        if (craftSlotId3[invYPosition*3 + invXPosition] == -1)
                        {
                            craftSlotId3[invYPosition*3 + invXPosition]=mWorld->mId;
                            craftSlotAm3[invYPosition*3 + invXPosition]=mWorld->mAm;
                            craftSlotSt3[invYPosition*3 + invXPosition]=mWorld->mSt;
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                            mWorld->mSt = 0;
                        }

                        if (craftSlotId3[invYPosition*3 + invXPosition] == mWorld->mId)
                        {
                            if(craftSlotSt3[invYPosition*3 + invXPosition] == 1)
                            {
                                if (craftSlotAm3[invYPosition*3 + invXPosition]+mWorld->mAm < 64)
                                {
                                    craftSlotAm3[invYPosition*3 + invXPosition]+=mWorld->mAm;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
                                else
                                {
                                    mWorld->mAm = (craftSlotAm3[invYPosition*3 + invXPosition] + mWorld->mAm) - 64;
                                    craftSlotAm3[invYPosition*3 + invXPosition]=64;

                                    if(mWorld->mAm == 0)
                                    {
                                        mWorld->mAm = -1;
                                        mWorld->mId = -1;
                                        mWorld->mSt = 0;
                                    }
                                }
                            }
                        }
                    }
                    CraftItem3x3();
                }
                //Chest
                if (chestEn == 1)
                {
                    if (mWorld->mId == -1)
                    {
                        if (UseChest->chestSlotId[invYPosition*9 + invXPosition] != -1)
                        {
                            mWorld->mId = UseChest->chestSlotId[invYPosition*9 + invXPosition];
                            mWorld->mAm = UseChest->chestSlotAm[invYPosition*9 + invXPosition];
                            mWorld->mSt = UseChest->chestSlotSt[invYPosition*9 + invXPosition];
                            UseChest->chestSlotId[invYPosition*9 + invXPosition] = -1;
                            UseChest->chestSlotAm[invYPosition*9 + invXPosition] = -1;
                            UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 0;
                        }
                    }
                    else
                    {
                        if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == -1)
                        {
                            UseChest->chestSlotId[invYPosition*9 + invXPosition]=mWorld->mId;
                            UseChest->chestSlotAm[invYPosition*9 + invXPosition]=mWorld->mAm;
                            UseChest->chestSlotSt[invYPosition*9 + invXPosition]=mWorld->mSt;
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                            mWorld->mSt = 0;
                        }

                        if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == mWorld->mId)
                        {
                            if(UseChest->chestSlotSt[invYPosition*9 + invXPosition] == 1)
                            {
                                if (UseChest->chestSlotAm[+invYPosition*9 + invXPosition]+mWorld->mAm < 64)
                                {
                                    UseChest->chestSlotAm[invYPosition*9 + invXPosition]+=mWorld->mAm;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
                                else
                                {
                                    mWorld->mAm = (UseChest->chestSlotAm[invYPosition*9 + invXPosition] + mWorld->mAm) - 64;
                                    UseChest->chestSlotId[invYPosition*9 + invXPosition]=64;

                                    if(mWorld->mAm == 0)
                                    {
                                        mWorld->mAm = -1;
                                        mWorld->mId = -1;
                                        mWorld->mSt = 0;
                                    }
                                }
                            }
                        }
                    }
                }
                //furnace
                if(furnaceEn == true)
                {
                    if (mWorld->mId == -1)
                    {
                        if (UseFurnace->furnaceSlotId[invYPosition] != -1)
                        {
                            mWorld->mId = UseFurnace->furnaceSlotId[invYPosition];
                            mWorld->mAm = UseFurnace->furnaceSlotAm[invYPosition];
                            mWorld->mSt = UseFurnace->furnaceSlotSt[invYPosition];
                            UseFurnace->furnaceSlotId[invYPosition] = -1;
                            UseFurnace->furnaceSlotAm[invYPosition] = -1;
                            UseFurnace->furnaceSlotSt[invYPosition] = 0;
                        }
                    }
                    else
                    {
                        if (UseFurnace->furnaceSlotId[invYPosition] == -1)
                        {
                            UseFurnace->furnaceSlotId[invYPosition]=mWorld->mId;
                            UseFurnace->furnaceSlotAm[invYPosition]=mWorld->mAm;
                            UseFurnace->furnaceSlotSt[invYPosition]=mWorld->mSt;
                            mWorld->mId = -1;
                            mWorld->mAm = -1;
                            mWorld->mSt = 0;
                        }

                        if (UseFurnace->furnaceSlotId[invYPosition] == mWorld->mId)
                        {
                            if(UseFurnace->furnaceSlotSt[invYPosition] == 1)
                            {
                                if (UseFurnace->furnaceSlotAm[invYPosition]+mWorld->mAm < 64)
                                {
                                    UseFurnace->furnaceSlotAm[invYPosition]+=mWorld->mAm;
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
                                else
                                {
                                    mWorld->mAm = (UseFurnace->furnaceSlotAm[invYPosition] + mWorld->mAm) - 64;
                                    UseFurnace->furnaceSlotAm[invYPosition]=64;

                                    if(mWorld->mAm == 0)
                                    {
                                        mWorld->mAm = -1;
                                        mWorld->mId = -1;
                                        mWorld->mSt = 0;
                                    }
                                }
                            }
                        }
                    }
                    CheckForFurnFuel(UseFurnace);
                    CheckForFurnWorking(UseFurnace);
                }
            }
        }

        if(mSystemMgr->KeyPressed(PSP_CTRL_SQUARE))
        {
            if(mWorld->mSt == 1)
            {
                if (upEn == 0)
                {
                    if (mWorld->invId[invYPosition*9 + invXPosition] == mWorld->mId)
                    {
                        if (mWorld->invAm[invYPosition*9 + invXPosition] != 64)
                        {
                            mWorld->invAm[invYPosition*9 + invXPosition] += 1;

                            mWorld->mAm -= 1;

                            if(mWorld->mAm == 0)
                            {
                                mWorld->mId = -1;
                                mWorld->mAm = -1;
                            }
                        }

                    }

                    if (mWorld->mId != -1)
                    {
                       if (mWorld->invId[invYPosition*9 + invXPosition] == -1)
                       {
                            mWorld->invId[invYPosition*9 + invXPosition] = mWorld->mId;
                            mWorld->invAm[invYPosition*9 + invXPosition] = 1;
                            mWorld->invSt[invYPosition*9 + invXPosition] = 1;

                            mWorld->mAm -= 1;

                            if(mWorld->mAm == 0)
                            {
                                mWorld->mId = -1;
                                mWorld->mAm = -1;
                                mWorld->mSt = 0;
                            }
                        }
                    }
                }
                else
                {
                    ///2x CRAFT
                    if (invEn == 1)
                    {
                        if (craftSlotId[invYPosition*2 + invXPosition] == mWorld->mId)
                        {
                            if (craftSlotAm[invYPosition*2 + invXPosition] != 64)
                            {
                                craftSlotAm[invYPosition*2 + invXPosition] += 1;

                                mWorld->mAm -= 1;

                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                }
                            }
                        }

                        if (mWorld->mId != -1)
                        {
                           if (craftSlotId[invYPosition*2 + invXPosition] == -1)
                           {
                               craftSlotId[invYPosition*2 + invXPosition] = mWorld->mId;
                               craftSlotAm[invYPosition*2 + invXPosition] = 1;
                               craftSlotSt[invYPosition*2 + invXPosition] = 1;

                               mWorld->mAm -= 1;

                               if(mWorld->mAm == 0)
                               {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
                            }
                        }
                        CraftItem2x2();
                    }

                    ///CRAFT TABLE
                    if (craft3xEn == 1)
                    {
                        if (craftSlotId3[invYPosition*3 + invXPosition] == mWorld->mId)
                        {
                            if (craftSlotAm3[invYPosition*3 + invXPosition] != 64)
                            {
                                craftSlotAm3[invYPosition*3 + invXPosition] += 1;

                                mWorld->mAm -= 1;

                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                }
                            }
                        }

                        if (mWorld->mId != -1)
                        {
                           if (craftSlotId3[invYPosition*3 + invXPosition] == -1)
                           {
                               craftSlotId3[invYPosition*3 + invXPosition] = mWorld->mId;
                               craftSlotAm3[invYPosition*3 + invXPosition] = 1;
                               craftSlotSt3[invYPosition*3 + invXPosition] = 1;

                               mWorld->mAm -= 1;

                               if(mWorld->mAm == 0)
                               {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                               }
                           }
                       }
                       CraftItem3x3();
                    }

                    ///CHEST
                    if (chestEn == 1)
                    {
                        if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == mWorld->mId)
                        {
                            if (UseChest->chestSlotAm[invYPosition*9 + invXPosition] != 64)
                            {
                                UseChest->chestSlotAm[invYPosition*9 + invXPosition] += 1;

                                mWorld->mAm -= 1;
                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                }
                            }
                        }

                        if (mWorld->mId != -1)
                        {
                            if (UseChest->chestSlotId[invYPosition*9 + invXPosition] == -1)
                            {
                                UseChest->chestSlotId[invYPosition*9 + invXPosition] = mWorld->mId;
                                UseChest->chestSlotAm[invYPosition*9 + invXPosition] = 1;
                                UseChest->chestSlotSt[invYPosition*9 + invXPosition] = 1;

                                mWorld->mAm -= 1;

                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
                            }
                        }
                    }
                    ///FURNACE
                    if (furnaceEn == 1)
                    {
                        if (UseFurnace->furnaceSlotId[invYPosition] == mWorld->mId)
                        {
                            if (UseFurnace->furnaceSlotAm[invYPosition] != 64)
                            {
                                UseFurnace->furnaceSlotAm[invYPosition] += 1;

                                mWorld->mAm -= 1;
                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                }
                            }
                        }

                        if (mWorld->mId != -1)
                        {
                            if (UseFurnace->furnaceSlotId[invYPosition] == -1)
                            {
                                UseFurnace->furnaceSlotId[invYPosition] = mWorld->mId;
                                UseFurnace->furnaceSlotAm[invYPosition] = 1;
                                UseFurnace->furnaceSlotSt[invYPosition] = 1;

                                mWorld->mAm -= 1;

                                if(mWorld->mAm == 0)
                                {
                                    mWorld->mId = -1;
                                    mWorld->mAm = -1;
                                    mWorld->mSt = 0;
                                }
                            }
                        }
                        CheckForFurnFuel(UseFurnace);
                        CheckForFurnWorking(UseFurnace);
                    }
                }
            }
        }
    }
    }
    else if(menuState == 1) //menu state
    {
        //turn off menu with the same key
        if(keyPressed(InputHelper::Instance()->getButtonToAction(15)))
        {
            menuState = 0;
            menuOptions = false;
            optionsMenuPos = 0;
            selectPos = 0;
        }

        //menu keys
        if(menuOptions)
        {
            //up, down
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                if(optionsMenuPos == 8 || optionsMenuPos == 0)
                {
                    return;
                }
                optionsMenuPos--;
                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                if(optionsMenuPos == 7 || optionsMenuPos == 15)
                {
                    return;
                }
                optionsMenuPos++;
                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
            {
                if(optionsMenuPos + 8 > 15)
                {
                    return;
                }
                optionsMenuPos += 8;
                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
            {
                if(optionsMenuPos - 8 < 0)
                {
                    return;
                }
                optionsMenuPos -= 8;
                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_RIGHT))
            {
                if(optionsMenuPos == 0)
                {
                    if (mWorld->mainOptions.fov <= 95)
                    {
                        mWorld->mainOptions.fov += 5;
                        mSoundMgr->PlayMenuSound();
                        mRender->fovv = mWorld->mainOptions.fov;
                        RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
                        skyLight->UpdateLightSource(mWorld->skyTime);
                        skyMoonLight->UpdateLightSource(mWorld->skyTime);
                    }
                }
                if(optionsMenuPos == 1)
                {
                    if (mWorld->mainOptions.horizontalViewDistance != 4)
                    {
                        mWorld->mainOptions.horizontalViewDistance += 1;
                        mSoundMgr->PlayMenuSound();
                        mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                        fppCam->needUpdate = true;
                    }
                }
                if(optionsMenuPos == 8)
                {
                    if (mWorld->mainOptions.verticalViewDistance != 4)
                    {
                        mWorld->mainOptions.verticalViewDistance += 1;
                        mSoundMgr->PlayMenuSound();
                        mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                        fppCam->needUpdate = true;
                    }
                }
                if(optionsMenuPos == 9)
                {
                    if (mWorld->mainOptions.fogDistance != 30)
                    {
                        mWorld->mainOptions.fogDistance += 5;
                        mSoundMgr->PlayMenuSound();
                        fppCam->needUpdate = true;
                    }
                }
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_LEFT))
            {
                if(optionsMenuPos == 0)
                {
                    if (mWorld->mainOptions.fov >= 45)
                    {
                        mWorld->mainOptions.fov -= 5;
                        mSoundMgr->PlayMenuSound();
                        mRender->fovv = mWorld->mainOptions.fov;
                        RenderManager::InstancePtr()->SetPerspective(0, 480.0f / 272.0f, 0.18f, 1000.f);
                        skyLight->UpdateLightSource(mWorld->skyTime);
                        skyMoonLight->UpdateLightSource(mWorld->skyTime);
                    }
                }
                if(optionsMenuPos == 1)
                {
                    if (mWorld->mainOptions.horizontalViewDistance != 1)
                    {
                        mWorld->mainOptions.horizontalViewDistance -= 1;
                        mSoundMgr->PlayMenuSound();
                        mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                        fppCam->needUpdate = true;
                    }
                }
                if(optionsMenuPos == 8)
                {
                    if (mWorld->mainOptions.verticalViewDistance != 1)
                    {
                        mWorld->mainOptions.verticalViewDistance -= 1;
                        mSoundMgr->PlayMenuSound();
                        mWorld->playerZoneSize = Vector3(16*mWorld->mainOptions.horizontalViewDistance,16*mWorld->mainOptions.verticalViewDistance,16*mWorld->mainOptions.horizontalViewDistance);
                        fppCam->needUpdate = true;
                    }
                }
                if(optionsMenuPos == 9)
                {
                    if (mWorld->mainOptions.fogDistance != 0)
                    {
                        mWorld->mainOptions.fogDistance -= 5;
                        mSoundMgr->PlayMenuSound();
                        fppCam->needUpdate = true;
                    }
                }
            }

            //back
            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                selectPos = 0;
                menuOptions = false;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                //fog rendering
                if(optionsMenuPos == 2)
                {
                     mWorld->mainOptions.fogRendering = !mWorld->mainOptions.fogRendering;
                     mSoundMgr->PlayMenuSound();
                }

                //clouds rendering
                if(optionsMenuPos == 3)
                {
                     mWorld->mainOptions.cloudsRender = !mWorld->mainOptions.cloudsRender;
                     mSoundMgr->PlayMenuSound();
                }

                //fast rendering
                if(optionsMenuPos == 4)
                {
                     mWorld->mainOptions.fastRendering = !mWorld->mainOptions.fastRendering;
                     mSoundMgr->PlayMenuSound();

                     for(int i = 0; i < 512; i++)
                     {
                         mWorld->rebuildTransparentChunk(i);
                     }

                }

                //block animation
                if(optionsMenuPos == 5)
                {
                     mWorld->mainOptions.worldBlockAnimation = !mWorld->mainOptions.worldBlockAnimation;
                     mSoundMgr->PlayMenuSound();
                }

                //head bob
                if(optionsMenuPos == 6)
                {
                     mWorld->mainOptions.headBob = !mWorld->mainOptions.headBob;
                     bobCycle = 0.0f;
                     mSoundMgr->PlayMenuSound();
                }

                if(optionsMenuPos == 10)
                {
                     mWorld->mainOptions.sunMoodRendering = !mWorld->mainOptions.sunMoodRendering;
                     mSoundMgr->PlayMenuSound();
                }

                if(optionsMenuPos == 11)
                {
                     mWorld->mainOptions.guiDrawing = !mWorld->mainOptions.guiDrawing;
                     mSoundMgr->PlayMenuSound();
                }

                if(optionsMenuPos == 12)
                {
                     mWorld->mainOptions.sounds = !mWorld->mainOptions.sounds;
                     mSoundMgr->PlayMenuSound();
                     mSoundMgr->playerSounds = mWorld->mainOptions.sounds;
                }

                //take screenshot
                if(optionsMenuPos == 13)
                    makeScreen = true;

                //rename
                if(optionsMenuPos == 14)
                {
                    unsigned short test[128];
                    unsigned short opis[10] = {'W','o','r','l','d',' ','n','a','m','e'};
                    if(mSystemMgr->ShowOSK(opis,test,128) != -1)
                    {
                        std::string newWorldName = "";
                        for(int j = 0; test[j]; j++)
                        {
                            unsigned c = test[j];

                            if(32 <= c && c <= 127) // print ascii only
                                newWorldName += c;
                        }

                        sprintf(mWorld->worldName,"%s",newWorldName.c_str());
                    }
                }

                if(optionsMenuPos == 15)
                {
                    devMode = !devMode;
                }
            }
        }
        else
        {
            //up, down
            if(mSystemMgr->KeyPressed(PSP_CTRL_UP))
            {
                selectPos--;
                if(selectPos < 0)
                    selectPos = 5;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_DOWN))
            {
                selectPos++;
                if(selectPos > 5)
                    selectPos = 0;

                mSoundMgr->PlayMenuSound();
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
            {
                menuState = 0;
                selectPos = 0;
                optionsMenuPos = 0;
                menuOptions = false;
            }

            if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
            {
                if(selectPos == 0)//resume
                {
                    menuState = 0;
                }
                if(selectPos == 1)//options
                {
                    optionsMenuPos = 0;
                    menuOptions = true;
                }
                if(selectPos == 2)//options
                {
                    menuState = 3;
                    selectPos = 0;
                }
                if(selectPos == 3)//save
                {
                    mWorld->sunTime = sunTime;
                    mWorld->SaveCompressedWorld(saveFileName.c_str());
                    menuState = 0;
                }
                if(selectPos == 4)//save end exit
                {
                    //save
                    mWorld->sunTime = sunTime;
                    mWorld->SaveCompressedWorld(saveFileName.c_str());
                    //exit
                    sManager->PopState();
                }
                if(selectPos == 5)//exit
                {
                    //exit
                    sManager->PopState();
                }
            }
        }
    }
    if (menuState == 3)
    {
        if(mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE))
        {
            selectPos = 0;
            menuState = 1;
        }
        if(mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER))
        {
            statisticsPage += 1;
            if(statisticsPage == 2)
            {
                statisticsPage = 0;
            }
        }
        if(mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER))
        {
            statisticsPage -= 1;
            if(statisticsPage == -1)
            {
                statisticsPage = 1;
            }
        }
    }
    }
    else
    {
        if(dieFactor == 1)
        {
            mWorld->mainStatistics.dies += 1;
            dieFactor = 0;
        }
        if(mSystemMgr->KeyPressed(PSP_CTRL_CROSS))
        {
                playerPosition.x = newPlayerPos.x;
                playerPosition.y = newPlayerPos.y;
                playerPosition.z = newPlayerPos.z;

            mWorld->UpdatePlayerZoneBB(playerPosition);	//Move player back to original spawn point
            fppCam->m_vPosition = playerPosition; //important
            cameraSpeed = 2.0/ 60.0f;	//Possibly fix camera bug
            fppCam->RotateView(0,0,90,0);
            fppCam->upDownAngle = 0;
            mWorld->HP = 20;
            mWorld->HG = 20;
            dieFactor = 1;
        }
    }
}


void StatePlay::Update(StateManager* sManager)
{
    furnaceTimes += dt;
    if(furnaceTimes >= 1.0f)
    {
        if(mWorld->mFurnaces.size() > 0)
        {
            for(unsigned int i = 0; i < mWorld->mFurnaces.size(); i ++)
            {
                Furnace* WorkingFurance = mWorld->mFurnaces[i];

                if(WorkingFurance->fuelTime > 0)
                {
                    WorkingFurance->fuelTime -= 1;
                    if(mWorld->GetBlock(WorkingFurance->furnaceX, WorkingFurance->furnaceY, WorkingFurance->furnaceZ) == 106)
                    {
                        Vector3 testPos5 = Vector3(-1,-1,-1);
                        int chunkTarget2 = -1;

                        testPos5.x = WorkingFurance->furnaceX;
                        testPos5.y = WorkingFurance->furnaceY;
                        testPos5.z = WorkingFurance->furnaceZ;
                        chunkTarget2 = mWorld->getChunkId(testPos5);

                        mWorld->GetBlock(WorkingFurance->furnaceX, WorkingFurance->furnaceY, WorkingFurance->furnaceZ) = 107;

                        mWorld->SetLigtSourcePosition(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ,107);
                        mWorld->RebuildChunksLight(testPos5,chunkTarget2,107);
                        mWorld->UpdateLightAreaIn(testPos5);

                        mWorld->rebuildChunk(chunkTarget2);
                        mWorld->rebuildTransparentChunk(chunkTarget2);
                        mWorld->rebuildNearestChunks(chunkTarget2,testPos5);
                        fppCam->needUpdate = true;
                    }
                }

                if(WorkingFurance->fuelTime <= 0)
                {
                    WorkingFurance->fuelTime = 0.0f;
                    CheckForFurnFuel(WorkingFurance);
                }

                if(WorkingFurance->fuelTime <= 0)
                {
                    if(mWorld->GetBlock(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ) == 107)
                    {
                        Vector3 testPos5 = Vector3(-1,-1,-1);
                        int chunkTarget2 = -1;

                        testPos5.x = WorkingFurance->furnaceX;
                        testPos5.y = WorkingFurance->furnaceY;
                        testPos5.z = WorkingFurance->furnaceZ;
                        chunkTarget2 = mWorld->getChunkId(testPos5);

                        mWorld->GetBlock(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ) = 106;

                        mWorld->RemoveLigtSourceAtPosition(WorkingFurance->furnaceX,WorkingFurance->furnaceY,WorkingFurance->furnaceZ,107);
                        mWorld->RebuildChunksLight(testPos5,chunkTarget2,107);

                        mWorld->UpdateLightAreaIn(testPos5);
                        mWorld->rebuildChunk(chunkTarget2);
                        mWorld->rebuildTransparentChunk(chunkTarget2);
                        mWorld->rebuildNearestChunks(chunkTarget2,testPos5);
                        fppCam->needUpdate = true;
                    }
                }

                if(WorkingFurance->fuelTime > 0 && WorkingFurance->working == 1)
                {
                    WorkingFurance->meltingTime += 1;
                    if(WorkingFurance->meltingTime >= 10)
                    {
                        WorkingFurance->meltingTime = 0;
                        WorkingFurance->working = 0;

                        ReadyFurnSmelting(WorkingFurance);
                        CheckForFurnWorking(WorkingFurance);
                    }
                }
            }
        }
        furnaceTimes = 0.0f;
    }
        cloudsWay == 0 ? cloudsMove += 0.01 : cloudsMove -= 0.01;
        if(cloudsWay == 0)
        {
            if(cloudsMove > 150)
            {
                cloudsWay = 1;
            }
        }
        else
        {
            if(cloudsMove < -150)
            {
                cloudsWay = 0;
            }
        }

        if (mWorld->worldDayTime >= 6 && mWorld->worldDayTime <= 10)
        {
            if (mWorld->bright < 1)
            {
                mWorld->bright += 0.0001;
            }
        }

        if (mWorld->worldDayTime >= 15 && mWorld->worldDayTime <= 19)
        {
            if (mWorld->bright > 0)
            {
                mWorld->bright -= 0.0001;
            }
        }


    if(menuState == 0)//game state
    {
        if (anim[0] == 1)
        {
            if (changeY >= 0.0f)
            {
                anim[0] = 0;
                changeY = 0.0f;
            }
            if (changeY < 0.2f)
            {
                changeY += 0.02f;
            }
        }

        if (musicTime == 1000)
        {
            musicTimeGo = mSoundMgr->PlayRandomAmbient();
            musicTime = 0;
        }

        if (musicTime < musicTimeGo)
        {
            musicTime += dt;

        }
        else
        {
            if(musicTime != 1000)
            {
                musicTimeGo = mSoundMgr->PlayRandomAmbient();
                musicTime = 0;
            }
        }
        { //chunk updater
            tickChunk ++;
            if (tickChunk>=20)
            {
                for(int i = chunks*1; i < (chunks+1)*1; i++)
                {
                    mWorld->UpdateChunkBlocks2(chunks);
                    mWorld->rebuildChunk(chunks);
                    mWorld->rebuildTransparentChunk(chunks);
                }
                chunks += 1;
                if (chunks == 510)
                {
                    chunks = 0;
                }
                tickChunk = 0;
            }
        }
            //===Cave sounds===//
        {
            time_z < 1000 ? time_z += 1 : time_z = 0;

            if (time_z==600)
            {
                short r = rand() % 5;
                chunkId = mWorld->getChunkId(playerPosition);
                mWorld->UpdateChunkBlocks(chunkId);
                mWorld->rebuildChunk(chunkId);
                mWorld->rebuildTransparentChunk(chunkId);
                if (r==2)
                {
                    if (playerPosition.y < 50)
                    {
                        mSoundMgr->PlayCaveSound();
                    }
                }
            }
        }

        {
            tickHunger += dt;
            if(tickHunger >= 79)
            {
                HungerTime();
                tickHunger = 0;
            }

            tickHealth += dt;
            if(tickHealth >= 5)
            {
                HealthTime();
                tickHealth = 0;
            }


            if (hurt_time > 0)
            {
                hurt_time -= 0.1f;
            }
            if (hurt_time <= 0)
            {
                hurt = false;
            }

            if(tickOS >= 1 && headInWater == 1)
            {
                OxygenTime();
                tickOS = 0;
            }

            if (headInWater == 0)
            {
                if (mWorld->OS != 10)
                {
                    mWorld->OS = 10;
                }
                tickOS = 0;
            }
            else
            {
                tickOS += dt;
            }
        }

        if(fppCam->needUpdate)
        {
            showCube = false;

            //show pick cube
            Vector3 rayDir = fppCam->m_vView - fppCam->m_vPosition;
            rayDir.normalize();

            //we take position and view vector
            Vector3 testPos ;

            //moving slowly to the target
            for(float i = 0; i < 5.25f; i+=0.25f)
            {
                testPos = fppCam->m_vPosition + (rayDir * i);

                //check if we touching something
                if(mWorld->BlockEditable(testPos.x,testPos.y,testPos.z))
                {
                    //if yes then show pick cube
                    cubePos.x = (int)testPos.x + 0.5f;
                    cubePos.y = (int)testPos.y + 0.5f;
                    cubePos.z = (int)testPos.z + 0.5f;

                    showCube = true;
                    break;
                }
            }

        }

        int soundBlockType = -1;

        //RenderManager::InstancePtr()

        //update player position
        if(dt < 0.1f)
        {

            Vector3 delta = fppCam->m_vView - fppCam->m_vPosition;
            playerPosition = fppCam->m_vPosition;

            //gravity
            Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
            Vector3 legsPosition = playerPosition + Vector3(0.0f, -1.0f, 0.0f);
            Vector3 headPosition = playerPosition + Vector3(0.0f, 0.1f, 0.0f);

            //foot in water
            if(mWorld->PlayerInWater(legsPosition))
                footInWater = true;
            else
                footInWater = false;

            //check if head is is in the water
            if(mWorld->PlayerInWater(headPosition))
            {
                //change gravity
                if (playerVelocity.y > -3)
                {
                    playerVelocity.y += (GRAVITY/3.0f) * dt;
                }
                else
                {
                    playerVelocity.y = -3;
                }
                headInWater = true;
            }
            else
            {
                headInWater = false;
                playerVelocity.y += (GRAVITY*1.3 * dt) * 1.6f;
            }

            if(mWorld->PlayerInLava(legsPosition))
            {
                footInLava = true;
                mWorld->HP -= 0.25f;
            }
            else
            {
                footInLava = false;
            }

            //check if head is is in the Lava
            if(mWorld->PlayerInLava(headPosition))
            {
                //change gravity
                playerVelocity.y += (GRAVITY/3.0f) * dt;
                headInLava = true;
                mWorld->HP -= 0.5f;
            }
            else
            {
                headInLava = false;
                playerVelocity.y += GRAVITY * dt;
            }

            //check if we are standing on ground
            if(mWorld->SolidAtPointForPlayer(footPosition) || mWorld->SolidAtPointForPlayer(headPosition))
            {
                walkingOnGround = true;
                soundBlockType = mWorld->BlockSoundAtPos(footPosition);

                // If the player has their head stuck in a block, push them down.
                if (mWorld->SolidAtPointForPlayer(headPosition))
                {
                    int blockIn = (int)(headPosition.y);
                    playerPosition.y = (float)(blockIn - 0.15f);
                }

                // If the player is stuck in the ground, bring them out.
                // This happens because we're standing on a block at -1.5, but stuck in it at -1.4, so -1.45 is the sweet spot.
                if (mWorld->SolidAtPointForPlayer(footPosition))
                {
                    int blockOn = (int)(footPosition.y);
                    playerPosition.y = (float)(blockOn + 1 + 1.45f);
                }
                if(playerVelocity.y != 0.0f) /// FALL DAMAGE
                {
                    if (!mWorld->PlayerInWater(footPosition))
                    {
                        if(playerVelocity.y < -11 && playerVelocity.y > -19)
                        {
                            mSoundMgr->PlayFallSound(playerVelocity.y);
                            mSoundMgr->PlayHitSound();
                            mWorld->HP -= (int)((playerVelocity.y*-1) - 10) / 1.5;
                            mWorld->mainStatistics.damageRecieved += (int)((playerVelocity.y*-1) - 9) / 1.5;
                            hurt = true;
                            hurt_time = 1.0f;
                            if(mWorld->HG > 0.2)
                            {
                                mWorld->HG -= 0.2;
                            }
                            mWorld->mainStatistics.badlyFalls += 1;
                        }
                        if(playerVelocity.y < -19)
                        {
                            mSoundMgr->PlayFallSound(playerVelocity.y);
                            mSoundMgr->PlayHitSound();
                            mWorld->HP -= (int)((playerVelocity.y*-1) - 9) * 1.2f;
                            mWorld->mainStatistics.damageRecieved += (int)((playerVelocity.y*-1) - 9) * 1.2f;
                            hurt = true;
                            hurt_time = 1.0f;
                            if(mWorld->HG > 0.3)
                            {
                                mWorld->HG -= 0.3;
                            }
                            mWorld->mainStatistics.badlyFalls += 1;
                        }
                    }
                }
                playerVelocity.y = 0.0f;

                //dodatkowa logika podczas stania na klocku
                //jump
                if(jumping)
                {
                    playerVelocity.y = 1.45f * JUMPVELOCITY;
                    jumping = false;
                    walkingOnGround = false;
                }

            }
            else
            {

                walkingOnGround = false;
            }

            //update position
            if(!canFly)
                playerPosition += playerVelocity * dt;
            else
                playerVelocity.y = 0.0f;


            //collision with walls
            isWalking = false;
            Vector3 moveVector = fppCam->m_vVelocity;

            if(moveVector.x != 0.0f || moveVector.z != 0.0f)
            {
                if(TryToMove(moveVector,dt))
                {
                    isWalking = true;
                }
                else if(TryToMove(Vector3(0,0,moveVector.z),dt))
                {
                    isWalking = true;
                }
                else if(TryToMove(Vector3(moveVector.x,0,0),dt))
                {
                    isWalking = true;
                }
            }


            //update camera
            fppCam->m_vPosition = playerPosition;
            fppCam->m_vView = fppCam->m_vPosition + delta;
            fppCam->m_vVelocity = Vector3(0,0,0);
            fppCam->needUpdate = true;
        }

        if(fppCam->needUpdate)
        {
            mWorld->UpdatePlayerZoneBB(fppCam->m_vPosition);
        }

        //walking sound
       if(isWalking && walkingOnGround && (!footInWater || !footInLava))
		{
			if(walkSoundAccu > 0.5f || walkSoundAccu == 0.0f)
			{
				mSoundMgr->PlayWalkSound(soundBlockType);
				walkSoundAccu = 0.0f;
			}
			walkSoundAccu += dt;

			if(mWorld->mainOptions.headBob == 1)
			{
			    if(bobType == 0)
                {
                    if (bobCycle < 3.14)
                    {
                        bobCycle += 3.14/20;
                    }
                    else
                    {
                        bobType = 1;
                    }
                }
                else
                {
                    if (bobCycle > 0)
                    {
                        bobCycle -= 3.14/20;
                    }
                    else
                    {
                        bobType = 0;
                    }
                }

                float bobSine = sinf(bobCycle - (3.14/2) + 3.14)/3;
                float bobCose = cosf(bobCycle - (3.14/2) + 3.14)/3;

                fppCam->m_vOffset = Vector3(0.02f*bobSine,0.02f*bobCose,0.0f);

			}

		}
		else
		{
			walkSoundAccu = 0.0f;
			fppCam->m_vOffset = Vector3(0.0f,0.0f,0.0f);
            if(bobCycle > 3.14/2)
            {
                bobCycle -= (bobCycle-(3.14/2))/3;
            }
            else
            {
                bobCycle += ((3.14/2) - bobCycle) / 3;
            }

		}
    }

    mWorld->UpdateWorldTime(dt);
}


void StatePlay::Draw(StateManager* sManager)
{
    mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0,0x00000200);

	//start rendering*mWorld->bright
	bool needUpdate = fppCam->needUpdate;
	mRender->StartFrame(0.5*mWorld->bright,0.662*mWorld->bright,1*mWorld->bright);

    if(mWorld->mainOptions.sunMoodRendering == 1)
    {
		sceGumPushMatrix();
		ScePspFVector3 move = {fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z};
		sceGumTranslate(&move);

		dtt += dt;
        if(dtt > 0.05f)
        {
            dtt = 0;
            mWorld->skyTime += SKY_MOVE/20.0f;
            skyLight->UpdateLightSource(mWorld->skyTime);
        }

        TextureManager::Instance()->SetTextureModeulate(suntex);

		//draw skydome
        skyLight->Render();
		sceGumPopMatrix();
    }

    if(mWorld->mainOptions.sunMoodRendering == 1)
    {
		sceGumPushMatrix();
		ScePspFVector3 move = {fppCam->m_vPosition.x,fppCam->m_vPosition.y,fppCam->m_vPosition.z};
		sceGumTranslate(&move);

        skyMoonLight->UpdateLightSource(mWorld->skyTime+180.0f);
        TextureManager::Instance()->SetTextureModeulate(moontex);

		//draw skydome
        skyMoonLight->Render();
		sceGumPopMatrix();
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuFog(mWorld->mainOptions.fogDistance * 3.0, mWorld->mainOptions.horizontalViewDistance * 10 + 20.0f + 80.0f, GU_COLOR(0.5*mWorld->bright,0.662*mWorld->bright,1*mWorld->bright,1.0));	// Fog parameters 100.75
        sceGuEnable(GU_FOG );
    }

    if(mWorld->mainOptions.cloudsRender == 1)
    {//draw clouds
        TextureManager::Instance()->SetTextureModeulate(cloudsTex);

        sceGumPushMatrix();

		ScePspFVector3 move = {-180+cloudsMove,112,-180};
		sceGumTranslate(&move);
		mWorld->drawClouds();
		sceGumPopMatrix();
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuDisable(GU_FOG );
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuFog(mWorld->mainOptions.fogDistance*1.25, mWorld->mainOptions.horizontalViewDistance * 15 + 20.0f, GU_COLOR(0.5*mWorld->bright,0.662*mWorld->bright,1*mWorld->bright,1.0));	// Fog parameters 100.75
        sceGuEnable(GU_FOG );	// Enable fog
    }

    if(mWorld->mainOptions.worldBlockAnimation == 1)
    {
        timeTexture < 8 ? timeTexture ++ : timeTexture = 0; //infinity timer
        if (timeTexture == 7)
        {
            currentTexture < 15 ? currentTexture ++ : currentTexture = 0;
        }
    }
    else
    {
        currentTexture = 0;
    }

    {
        sceGuEnable(GU_TEXTURE_2D);
        TextureManager::Instance()->SetTextureModeulate(texture[currentTexture]);
        sceGumPushMatrix();
        mWorld->drawWorld(fppCam->mFrustum,needUpdate);
        sceGumPopMatrix();
        sceGuDisable(GU_TEXTURE_2D);
    }

    if(mWorld->mainOptions.fogRendering == 1)
    {
        sceGuDisable(GU_FOG );	// disable fog
    }

    if (mSnowBalls.empty() == 0)
    {
        TextureManager::Instance()->SetTextureModeulate(snowBall4);
        sceGumPushMatrix();
		ScePspFVector3 move = {0,0,0};
		sceGumTranslate(&move);
        for(unsigned int i = 0; i < mSnowBalls.size(); i++)
        {
            sceGuEnable(GU_DEPTH_TEST);
            sceGuEnable(GU_ALPHA_TEST);
            SnowBall2* UseSnowBall = mSnowBalls[i];
            UseSnowBall->Render();
            UseSnowBall->Update(mWorld);
            if(UseSnowBall->CheckCollision(mWorld) == 1)
            {
                delete mSnowBalls[i];
                mSnowBalls.erase(mSnowBalls.begin()+i);
            }
            sceGuDisable(GU_ALPHA_TEST);
            sceGuDisable(GU_DEPTH_TEST);
        }

        sceGumPopMatrix();
    }



    TextureManager::Instance()->SetTextureModeulate(texture[0]);

	if(makeScreen)
	{
		//end frame now to update frame buffer
		mRender->EndFrame();
		//make screenshot
		mRender->TakeNextScreenshot();
		makeScreen = false;
	}

	//render pick cube
	if(showCube)
	{
		//cubePos = fppCam->m_vPosition;
        sceGuEnable(GU_DEPTH_TEST);
        sceGuEnable(GU_ALPHA_TEST);
		sceGuEnable(GU_BLEND);
        mRender->DrawCube(cubePos.x,cubePos.y,cubePos.z);
		sceGuDisable(GU_BLEND);
        sceGuDisable(GU_ALPHA_TEST);
        sceGuDisable(GU_DEPTH_TEST);
	}

	if (startDt == 1 && dStd >= 0 && dStd <= 4)
	{
		sceGumPushMatrix();
        sceGuEnable(GU_DEPTH_TEST);
        sceGuEnable(GU_ALPHA_TEST);
		ScePspFVector3 move = {cubePos.x,cubePos.y,cubePos.z};
		sceGumTranslate(&move);

		sceGuEnable(GU_BLEND);
		sceGuColor(0xFFFFFFFF);
		//GU_COLOR()
        sceGuBlendFunc(GU_SUBTRACT, GU_FIX,GU_FIX, 0xFFFFFFFF, 0xFFFFFFFF);
		mRender->Draw(dModel[dStd]);
		sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
		sceGuDisable(GU_BLEND);
        sceGuDisable(GU_ALPHA_TEST);
        sceGuDisable(GU_DEPTH_TEST);
		sceGumPopMatrix();
	}

	if(mWorld->mainOptions.guiDrawing == 1)
	{
	    if(mWorld->invId[27+barPosition] != -1)
        {
        float cubeBob = sinf(bobCycle - (3.14/2) + 3.14)/16;
		float cubeBob2 =  cosf(bobCycle - (3.14/2) + 3.14)/18;
        if(mWorld->invId[27+barPosition] < 250)
        {
		TextureManager::Instance()->SetTextureModeulate(texture[0]);
		sceGumPushMatrix();

		//set view matrix to identity
		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		//translate

		ScePspFVector3 move = {0.596f+cubeBob+shift_x+(mWorld->mainOptions.fov-70)/200.0f,-0.3f+shift_y+cubeBob2+changeY,-0.7f+(mWorld->mainOptions.fov-70)/130.0f}; //446
		sceGumTranslate(&move);
		//rotate


		sceGumRotateX(0.169);
		sceGumRotateY(0.934); //3
		//scale
		ScePspFVector3 scale = {0.25f,0.25f,0.25f};
		sceGumScale(&scale);

		//draw cube
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		mWorld->drawCubes(mWorld->invId[27+barPosition]);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

		sceGumMatrixMode(GU_MODEL);
		sceGumPopMatrix();
        }

        if(mWorld->invId[27+barPosition] >= 250)
        {
		TextureManager::Instance()->SetTextureModeulate(texture[1]);
		sceGumPushMatrix();

		//set view matrix to identity
		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		//translate
		ScePspFVector3 move = {0.600f+cubeBob+shift_x+(mWorld->mainOptions.fov-70)/250.0f,-0.22f+cubeBob2+shift_y+changeY,-0.6f+(mWorld->mainOptions.fov-70)/180.0f};//-0.17
		sceGumTranslate(&move);
		//rotate
		sceGumRotateX(-0.24f);
		sceGumRotateY(-1.1f); //-1.1
		sceGumRotateZ(-3.8f); //-3.8
		//scale
		ScePspFVector3 scale = {0.25f,0.25f,0.25f};
		sceGumScale(&scale);

		//draw cube
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		mWorld->drawItems(mWorld->invId[27+barPosition]);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

		sceGumMatrixMode(GU_MODEL);
		sceGumPopMatrix();
        }

        }
	}

	//gui
	mRender->SetOrtho(0,0,0,0,0,0);


    if(mWorld->HP < 1)
	{
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,0.5f));
		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

	}


    if(hurt == true)
	{

		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,hurt_time));
		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);

	}

	if(headInWater)
	{
        if (GRAVITY != -4.0f)
        {
            GRAVITY = -4.0f;
        }
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
        sceGuColor(GU_COLOR(1,1,1,0.7));
		TextureManager::Instance()->SetTextureModeulate(blue);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);
	}
	else
    {
        if (GRAVITY != -6.8f)
        {
            GRAVITY = -6.8f;
        }
    }


	if(headInLava == 1 || footInLava == 1)
	{
		sceGuDisable(GU_DEPTH_TEST);
		sceGuDepthMask(1);
		sceGuEnable(GU_BLEND);
		sceGuEnable(GU_TEXTURE_2D);
		sceGuColor(GU_COLOR(1,1,1,0.7f));
		TextureManager::Instance()->SetTextureModeulate(red);
		advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
		sceGuDisable(GU_BLEND);
		sceGuDisable(GU_TEXTURE_2D);
		sceGuEnable(GU_DEPTH_TEST);
		sceGuDepthMask(0);
	}
    if(invEn == 1 || craft3xEn == 1 || chestEn == 1 || menuState != 0 || furnaceEn == 1)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuDepthMask(1);
        sceGuEnable(GU_BLEND);
        sceGuEnable(GU_TEXTURE_2D);
        sceGuColor(GU_COLOR(1,1,1,0.7));
        TextureManager::Instance()->SetTextureModeulate(black);
        advancedBlit(0,0,SCR_WIDTH,SCR_HEIGHT,0,0,32);
        sceGuDisable(GU_BLEND);
        sceGuDisable(GU_TEXTURE_2D);
        sceGuEnable(GU_DEPTH_TEST);
        sceGuDepthMask(0);
    }

	/// GUI
	sceGuDisable(GU_DEPTH_TEST);
	sceGuDepthMask(1);
	sceGuEnable(GU_BLEND);
	sceGuColor(GU_COLOR(1,1,1,1.0f));

	if (invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1)
    {
        barSprite->Draw();
        if (menuState != 1)
        {
            /// HP and HG RENDERING
            for(int i = 1; i <= 5; i++)
            {
                hpCellSprite->SetPosition(-4+i*16,10);

                hp44Sprite->SetPosition(-4+i*16,10);
                hp34Sprite->SetPosition(-4+i*16,10);
                hp24Sprite->SetPosition(-4+i*16,10);
                hp14Sprite->SetPosition(-4+i*16,10);

                hpCellSprite->Draw();
                if(i * 4 <= (int)mWorld->HP)
                {
                    hp44Sprite->Draw();
                }
                if((i * 4 - (int)mWorld->HP) == 1)
                {
                    hp34Sprite->Draw();
                }
                if((i * 4 - (int)mWorld->HP) == 2)
                {
                    hp24Sprite->Draw();
                }
                if((i * 4 - (int)mWorld->HP) == 3)
                {
                    hp14Sprite->Draw();
                }

                hgCellSprite->SetPosition(390+i*16,10);

                hg44Sprite->SetPosition(390+i*16,10);
                hg34Sprite->SetPosition(390+i*16,10);
                hg24Sprite->SetPosition(390+i*16,10);
                hg14Sprite->SetPosition(392+i*16,10);

                hgCellSprite->Draw();
                if(i * 4 <= (int)mWorld->HG)
                {
                    hg44Sprite->Draw();
                }
                if((i * 4 - (int)mWorld->HG) == 1)
                {
                    hg34Sprite->Draw();
                }
                if((i * 4 - (int)mWorld->HG) == 2)
                {
                    hg24Sprite->Draw();
                }
                if((i * 4 - (int)mWorld->HG) == 3)
                {
                    hg14Sprite->Draw();
                }

                if(headInWater)
                {
                    bubbleSprite->SetPosition(-4+i*16,28);
                    if(i * 2 <= mWorld->OS)
                    {
                        bubbleSprite->Draw();
                    }
                }
            }
            sceGuBlendFunc(GU_ABS, GU_ONE_MINUS_SRC_ALPHA, GU_SRC_ALPHA, 0, 0);
            crossSprite->Draw();
            sceGuBlendFunc(GU_ADD, GU_SRC_ALPHA, GU_ONE_MINUS_SRC_ALPHA, 0, 0);
            selectSprite->Draw();
        }
    }
    else
    {
        if (invEn == true)
        {
            invSprite->Draw();
        }
        if (craft3xEn == true)
        {
            crtSprite->Draw();
        }
        if (chestEn == true)
        {
            chtSprite->Draw();
        }
        if (furnaceEn == true)
        {
            furSprite->Draw();
            if(UseFurnace->fuelTime >= 10.0f)
            {
                furFireSprite->SetMapPos(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,0,14,14);
                furFireSprite->SetPosition(204,77);
            }
            if(UseFurnace->fuelTime < 10.0f)
            {
                furFireSprite->SetMapPos(TextureHelper::Instance()->GetTexture(TextureHelper::furFire),0,(10-UseFurnace->fuelTime)/10.0f*14.0f,14,(UseFurnace->fuelTime)/10.0f*14);
                furFireSprite->SetPosition(204,77+(10-UseFurnace->fuelTime)/10.0f*12.0f);
            }
            furFireSprite->Scale(1.5f,1.5f);
            furFireSprite->Draw();

            furArrowSprite->SetMapPos(TextureHelper::Instance()->GetTexture(TextureHelper::furArrow),0,0,(UseFurnace->meltingTime)/10.0f*22.0f,16);
            furArrowSprite->SetPosition(226+(UseFurnace->meltingTime)/10.0f*20.0f,76);
            furArrowSprite->Scale(1.5f,1.5f);
            furArrowSprite->Draw();
        }
    }
	sceGuDisable(GU_BLEND);

	/// 3D BLOCKS ON 2D PANEL
	TextureManager::Instance()->SetTextureModeulate(texture[0]);

        if (invEn == false && craft3xEn == false && chestEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1 && furnaceEn == false)
        {
            for(int k = 0; k <= 8; k++)
            {
                if(mWorld->invId[27+k] != -1)
                {
                    sceGumPushMatrix();
                    ScePspFVector3 loc = {100+k*35,253,0.0f};
                    sceGumTranslate(&loc);

                    if(mWorld->invId[27+k] < 250)
                    {
                        ScePspFVector3 sca = {17,17,17.0f};
                        sceGumScale(&sca);

                        //rotate
                        sceGumRotateX(2.5f);
                        sceGumRotateY(0.9f);

                        sceGuFrontFace(GU_CW);
                        mWorld->drawCubes(mWorld->invId[27+k]);
                        sceGuFrontFace(GU_CCW);
                    }

                    if(mWorld->invId[27+k] >= 250)
                    {
                        ScePspFVector3 sca = {32,32,32.0f};
                        sceGumScale(&sca);

                        //rotate
                        sceGumRotateX(0.0f);
                        sceGumRotateY(0.0f);
                        sceGumRotateZ(0.0f);

                        sceGuFrontFace(GU_CW);
                        mWorld->drawItems(mWorld->invId[27+k]);
                        sceGuFrontFace(GU_CCW);
                    }
                    sceGumPopMatrix();
                }
            }
        }

        /// INVENTORY CRAFT MENU
        if(invEn == true)
        {

            for(int i = 0; i <= 1; i++)
            {
                for(int j = 0; j <= 1; j++)
                {
                    if(craftSlotId[i*2+j] != -1)
                    {
                        sceGumPushMatrix();

                        ScePspFVector3 loc = {252+j*27,62+i*27,0.0f};
                        sceGumTranslate(&loc);

                        if(craftSlotId[i*2+j] < 250)
                        {
                            ScePspFVector3 sca = {15,15,15.0f};
                            sceGumScale(&sca);

                            //rotate
                            sceGumRotateX(2.5f);
                            sceGumRotateY(0.9f);

                            sceGuFrontFace(GU_CW);
                            mWorld->drawCubes(craftSlotId[i*2+j]);
                            sceGuFrontFace(GU_CCW);
                        }

                        if(craftSlotId[i*2+j] >= 250)
                        {
                            ScePspFVector3 sca = {26,26,26.0f};
                            sceGumScale(&sca);

                            //rotate
                            sceGumRotateX(0.0f);
                            sceGumRotateY(0.0f);

                            sceGuFrontFace(GU_CW);
                            mWorld->drawItems(craftSlotId[i*2+j]);
                            sceGuFrontFace(GU_CCW);
                        }

                        sceGumPopMatrix();
                    }

                }
            }

            //End

            //Item which we are crafting
            if (craftItemId != -1)
            {

                sceGumPushMatrix();

                ScePspFVector3 loc = {336,77,0.0f};
                sceGumTranslate(&loc);

                if(craftItemId < 250)
                {
                    ScePspFVector3 sca = {15,15,15.0f};
                    sceGumScale(&sca);

                    //rotate
                    sceGumRotateX(2.5f);
                    sceGumRotateY(0.9f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawCubes(craftItemId);
                    sceGuFrontFace(GU_CCW);
                }

                if(craftItemId >= 250)
                {
                    ScePspFVector3 sca = {26,26,26.0f};
                    sceGumScale(&sca);

                    //rotate
                    sceGumRotateX(0.0f);
                    sceGumRotateY(0.0f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawItems(craftItemId);
                    sceGuFrontFace(GU_CCW);
                }
                sceGumPopMatrix();
            }
        }


        ///CRAFTING TABLE
        if(craft3xEn == true)
        {
            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 2; j++)
                {
                if(craftSlotId3[i*3+j] != -1)
                {
                sceGumPushMatrix();

                ScePspFVector3 loc = {165+j*27,49+i*27,0.0f};
                sceGumTranslate(&loc);

                if(craftSlotId3[i*3+j] < 250)
                {
                ScePspFVector3 sca = {15,15,15.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);

                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(craftSlotId3[i*3+j]);
                sceGuFrontFace(GU_CCW);
                }

                if(craftSlotId3[i*3+j] >= 250)
                {
                ScePspFVector3 sca = {26,26,26.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);

                sceGuFrontFace(GU_CW);
                mWorld->drawItems(craftSlotId3[i*3+j]);
                sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
                }

                }


            }
            //End

            //Item which we are crafting 3x
            if (craftItemId3 != -1)
            {

                sceGumPushMatrix();

                ScePspFVector3 loc = {305,75,0.0f};
                sceGumTranslate(&loc);

                if(craftItemId3 < 250)
                {
                    ScePspFVector3 sca = {17,17,17.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(2.5f);
                    sceGumRotateY(0.9f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawCubes(craftItemId3);
                    sceGuFrontFace(GU_CCW);
                }

                if(craftItemId3 >= 250)
                {
                    ScePspFVector3 sca = {32,32,32.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(0.0f);
                    sceGumRotateY(0.0f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawItems(craftItemId3);
                    sceGuFrontFace(GU_CCW);
                }
                sceGumPopMatrix();
            }
            //End
        }

        ///CHEST
        if(chestEn == true)
        {
            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                    if(UseChest->chestSlotId[i*9+j] != -1)
                    {
                        sceGumPushMatrix();

                        ScePspFVector3 loc = {132+j*27,48+i*27,0.0f};
                        sceGumTranslate(&loc);

                        if(UseChest->chestSlotId[i*9+j] < 250)
                        {
                            ScePspFVector3 sca = {15,15,15.0f};
                            sceGumScale(&sca);
                            //rotate
                            sceGumRotateX(2.5f);
                            sceGumRotateY(0.9f);

                            sceGuFrontFace(GU_CW);
                            mWorld->drawCubes(UseChest->chestSlotId[i*9+j]);
                            sceGuFrontFace(GU_CCW);
                        }

                        if(UseChest->chestSlotId[i*9+j] >= 250)
                        {
                            ScePspFVector3 sca = {26,26,26.0f};
                            sceGumScale(&sca);

                            //rotate
                            sceGumRotateX(0.0f);
                            sceGumRotateY(0.0f);

                            sceGuFrontFace(GU_CW);
                            mWorld->drawItems(UseChest->chestSlotId[i*9+j]);
                            sceGuFrontFace(GU_CCW);
                        }
                        sceGumPopMatrix();
                    }
                }
            }
        }

        ///FURNACE
        if(furnaceEn == true)
        {
            if(UseFurnace->furnaceSlotId[0] != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc = {204,49,0.0f};
                sceGumTranslate(&loc);

                if(UseFurnace->furnaceSlotId[0] < 250)
                {
                    ScePspFVector3 sca = {15,15,15.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(2.5f);
                    sceGumRotateY(0.9f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawCubes(UseFurnace->furnaceSlotId[0]);
                    sceGuFrontFace(GU_CCW);
                }

                if(UseFurnace->furnaceSlotId[0] >= 250)
                {
                    ScePspFVector3 sca = {26,26,26.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(0.0f);
                    sceGumRotateY(0.0f);
                    sceGuFrontFace(GU_CW);
                    mWorld->drawItems(UseFurnace->furnaceSlotId[0]);
                    sceGuFrontFace(GU_CCW);
                }
                sceGumPopMatrix();
            }

            if(UseFurnace->furnaceSlotId[1] != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc = {204,103,0.0f};
                sceGumTranslate(&loc);

                if(UseFurnace->furnaceSlotId[1] < 250)
                {
                    ScePspFVector3 sca = {15,15,15.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(2.5f);
                    sceGumRotateY(0.9f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawCubes(UseFurnace->furnaceSlotId[1]);
                    sceGuFrontFace(GU_CCW);
                }

                if(UseFurnace->furnaceSlotId[1] >= 250)
                {
                    ScePspFVector3 sca = {26,26,26.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(0.0f);
                    sceGumRotateY(0.0f);
                    sceGuFrontFace(GU_CW);
                    mWorld->drawItems(UseFurnace->furnaceSlotId[1]);
                    sceGuFrontFace(GU_CCW);
                }
                sceGumPopMatrix();
            }

            if(UseFurnace->furnaceSlotId[2] != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc = {294,75,0.0f};
                sceGumTranslate(&loc);

                if(UseFurnace->furnaceSlotId[2] < 250)
                {
                    ScePspFVector3 sca = {17,17,17.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(2.5f);
                    sceGumRotateY(0.9f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawCubes(UseFurnace->furnaceSlotId[2]);
                    sceGuFrontFace(GU_CCW);
                }

                if(UseFurnace->furnaceSlotId[2] >= 250)
                {
                    ScePspFVector3 sca = {32,32,32.0f};
                    sceGumScale(&sca);
                    //rotate
                    sceGumRotateX(0.0f);
                    sceGumRotateY(0.0f);
                    sceGuFrontFace(GU_CW);
                    mWorld->drawItems(UseFurnace->furnaceSlotId[2]);
                    sceGuFrontFace(GU_CCW);
                }
                sceGumPopMatrix();
            }
        }

    if (invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
    {

        for(int k = 0; k <= 8; k++)
        {
            if(mWorld->invId[27+k] != -1)
            {
                sceGumPushMatrix();
                ScePspFVector3 loc = {132+k*27,236,0.0f};
                sceGumTranslate(&loc);

                if(mWorld->invId[27+k] < 250)
                {
                    ScePspFVector3 sca = {15,15,15.0f};
                    sceGumScale(&sca);

                    //rotate
                    sceGumRotateX(2.5f);
                    sceGumRotateY(0.9f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawCubes(mWorld->invId[27+k]);
                    sceGuFrontFace(GU_CCW);
                }

                if(mWorld->invId[27+k] >= 250)
                {
                    ScePspFVector3 sca = {26,26,26.0f};
                    sceGumScale(&sca);

                    //rotate
                    sceGumRotateX(0.0f);
                    sceGumRotateY(0.0f);
                    sceGumRotateZ(0.0f);

                    sceGuFrontFace(GU_CW);
                    mWorld->drawItems(mWorld->invId[27+k]);
                    sceGuFrontFace(GU_CCW);
                }

                sceGumPopMatrix();
            }
        }

            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                    if(mWorld->invId[i*9+j] != -1)
                    {
                        sceGumPushMatrix();

                        ScePspFVector3 loc = {132+j*27,150+i*27,0.0f};
                        sceGumTranslate(&loc);

                        if(mWorld->invId[i*9+j] < 250)
                        {
                            ScePspFVector3 sca = {15,15,15.0f};
                            sceGumScale(&sca);

                            //rotate
                            sceGumRotateX(2.5f);
                            sceGumRotateY(0.9f);

                            sceGuFrontFace(GU_CW);
                            mWorld->drawCubes(mWorld->invId[i*9+j]);
                            sceGuFrontFace(GU_CCW);
                        }

                        if(mWorld->invId[i*9+j] >= 250)
                        {
                            ScePspFVector3 sca = {26,26,26.0f};
                            sceGumScale(&sca);

                            //rotate
                            sceGumRotateX(0.0f);
                            sceGumRotateY(0.0f);

                            sceGuFrontFace(GU_CW);
                            mWorld->drawItems(mWorld->invId[i*9+j]);
                            sceGuFrontFace(GU_CCW);
                        }

                        sceGumPopMatrix();
                    }

                }
            }

            if (mWorld->mId != -1) //MOUSE ITEM
            {
                sceGumPushMatrix();
                if (upEn == 1)
                {
                    if (invEn == 1)
                    {
                        ScePspFVector3 loc = {252 + (invXPosition * 27),56+(invYPosition * 27),0.0f};
                        sceGumTranslate(&loc);
                    }
                    if (craft3xEn == 1)
                    {
                        ScePspFVector3 loc = {165 + (invXPosition * 27),43+(invYPosition * 27),0.0f};
                        sceGumTranslate(&loc);
                    }
                    if (chestEn == 1)
                    {
                        ScePspFVector3 loc = {132 + (invXPosition * 27),42+(invYPosition * 27),0.0f};
                        sceGumTranslate(&loc);
                    }
                    if (furnaceEn == 1)
                    {
                        ScePspFVector3 loc = {204,43+(invYPosition * 54),0.0f};
                        sceGumTranslate(&loc);
                    }
                }
                else
                {
                    if(invYPosition == 3)
                    {
                        ScePspFVector3 loc = {132 + (invXPosition * 27),150+(invYPosition * 27),0.0f};
                        sceGumTranslate(&loc);
                    }
                    else
                    {
                        ScePspFVector3 loc = {132 + (invXPosition * 27),144+(invYPosition * 27),0.0f};
                        sceGumTranslate(&loc);
                    }
                }

            if (mWorld->mId < 250)
            {
                ScePspFVector3 sca = {15,15,15.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(2.5f);
                sceGumRotateY(0.9f);
                sceGuFrontFace(GU_CW);
                mWorld->drawCubes(mWorld->mId);
                sceGuFrontFace(GU_CCW);
            }

            if (mWorld->mId >= 250)
            {
                ScePspFVector3 sca = {26,26,26.0f};
                sceGumScale(&sca);

                //rotate
                sceGumRotateX(0.0f);
                sceGumRotateY(0.0f);
                sceGuFrontFace(GU_CW);
                mWorld->drawItems(mWorld->mId);
                sceGuFrontFace(GU_CCW);
            }

            sceGumPopMatrix();

            }
    }

	sceGuEnable(GU_DEPTH_TEST);
	sceGuDepthMask(0);

    //text
    if(mWorld->HP <= 1)
    {
        sceGuDisable(GU_DEPTH_TEST);
        sceGuEnable(GU_BLEND);
        sceGuColor(GU_COLOR(1,1,1,1.0f));
        mRender->SetFontStyle(0.345f*2,GU_COLOR(0.6,0,0,1),0,0,0x00000200);
        mRender->DebugPrint(242,102,"YOU DIE. PRESS X TO RESPAWN");
        mRender->SetFontStyle(0.345f*2,GU_COLOR(1,0,0,1),0,0,0x00000200);
        mRender->DebugPrint(240,100,"YOU DIE. PRESS X TO RESPAWN");
        mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0,0x00000200);

    }
        if(invEn == true || craft3xEn == true || chestEn == true || furnaceEn == true)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            selectInvSprite->Draw();

            for(int i = 0; i <= 2; i++)
            {
                for(int j = 0; j <= 8; j++)
                {
                    if(mWorld->invId[i*9+j] != -1 && mWorld->invAm[i*9+j] > 1)
                    {
                        mRender->DebugPrint(131+j*27,161+i*27,"%i",mWorld->invAm[i*9+j]);
                    }
                }
            }

            if (mWorld->mId != -1)
            {
                if (upEn == 0)
                {
                    if(invYPosition == 3)
                    {
                        mRender->DebugPrint(131 + (invXPosition * 27),150+(invYPosition * 27),"%i",mWorld->mAm);
                    }
                    else
                    {
                        mRender->DebugPrint(131 + (invXPosition * 27),144+(invYPosition * 27),"%i",mWorld->mAm);
                    }
                }
                else
                {
                    if(invEn == 1)
                    {
                        mRender->DebugPrint(252 + (invXPosition * 27),56+(invYPosition * 27),"%i",mWorld->mAm);
                    }
                    if(craft3xEn == 1)
                    {
                        mRender->DebugPrint(165 + (invXPosition * 27),43+(invYPosition * 27),"%i",mWorld->mAm);
                    }
                    if(chestEn == 1)
                    {
                        mRender->DebugPrint(132 + (invXPosition * 27),42+(invYPosition * 27),"%i",mWorld->mAm);
                    }
                    if(furnaceEn == 1)
                    {
                        mRender->DebugPrint(204,44+(invYPosition * 54),"%i",mWorld->mAm);
                    }
                }
            }

            for(int k = 0; k <= 8; k++)
            {
                if (mWorld->invAm[27+k] > 1){mRender->DebugPrint(131+k*27,246,"%i",mWorld->invAm[27+k]);}
            }
        }

            if(invEn == false && craft3xEn == false && chestEn == false && furnaceEn == false && menuState == 0 && mWorld->mainOptions.guiDrawing == 1)
            {
                for(int k = 0; k <= 8; k++)
                {
                    if (mWorld->invAm[27+k] > 1){mRender->DebugPrint(100+k*35,268,"%i",mWorld->invAm[27+k]);}
                }
            }

            if(invEn == true)
            {
                for(int i = 0; i <= 1; i++)
                {
                    for(int j = 0; j <= 1; j++)
                    {
                        if(craftSlotId[i*2+j] != -1 && craftSlotAm[i*2+j] > 1)
                        {
                            mRender->DebugPrint(252+j*27,74+i*27,"%i",craftSlotAm[i*2+j]);
                        }
                    }
                }

                if(craftItemId != -1)
                {
                    mRender->DebugPrint(336,89,"%i",craftItemAm);
                }
            }

            if(craft3xEn == true)
            {
                for(int i = 0; i <= 2; i++)
                {
                    for(int j = 0; j <= 2; j++)
                    {
                        if(craftSlotId3[i*3+j] != -1 && craftSlotAm3[i*3+j] > 1)
                        {
                            mRender->DebugPrint(164+j*27,60+i*27,"%i",craftSlotAm3[i*3+j]);
                        }
                    }
                }

                if(craftItemId3 != -1)
                {
                    mRender->DebugPrint(305,93,"%i",craftItemAm3);
                }
            }

            if(chestEn == true)
            {
                for(int i = 0; i <= 2; i++)
                {
                    for(int j = 0; j <= 8; j++)
                    {
                        if(UseChest->chestSlotId[i*9+j] != -1 && UseChest->chestSlotAm[i*9+j] > 1)
                        {
                            mRender->DebugPrint(132+j*27,59+i*27,"%i",UseChest->chestSlotAm[i*9+j]);
                        }
                    }
                }
            }

            if(furnaceEn == true)
            {
                if(UseFurnace->furnaceSlotId[0] != -1 && UseFurnace->furnaceSlotAm[0] > 1)
                {
                    mRender->DebugPrint(204,56,"%i",UseFurnace->furnaceSlotAm[0]);
                }
                if(UseFurnace->furnaceSlotId[1] != -1 && UseFurnace->furnaceSlotAm[1] > 1)
                {
                    mRender->DebugPrint(204,110,"%i",UseFurnace->furnaceSlotAm[1]);
                }
                if(UseFurnace->furnaceSlotId[2] != -1 && UseFurnace->furnaceSlotAm[2] > 1)
                {
                    mRender->DebugPrint(294,82,"%i",UseFurnace->furnaceSlotAm[2]);
                }
            }
        sceGuDisable(GU_BLEND);
        sceGuEnable(GU_DEPTH_TEST);

    //menu buttons
    if(menuState == 1)
    {
        if(menuOptions)
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            nbuttonSprite->SetPosition(110,40);
            nbuttonSprite->Draw();

            nbuttonSprite->SetPosition(370,40);
            nbuttonSprite->Draw();

            nbuttonSprite->SetPosition(110,70);
            nbuttonSprite->Draw();

            nbuttonSprite->SetPosition(370,70);
            nbuttonSprite->Draw();

            buttonSprite->SetPosition(110,100);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,100);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,130);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,130);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,160);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,160);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,190);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,190);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,220);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,220);
            buttonSprite->Draw();

            buttonSprite->SetPosition(110,250);
            buttonSprite->Draw();

            buttonSprite->SetPosition(370,250);
            buttonSprite->Draw();

            if (optionsMenuPos < 8)
            {
                sbuttonSprite->SetPosition(110,(optionsMenuPos * 30) + 40);
            }
            if(optionsMenuPos >= 8)
            {
                sbuttonSprite->SetPosition(370,((optionsMenuPos-8) * 30) + 40);
            }
            sbuttonSprite->Draw();


            if(mWorld->mainOptions.fov == 40)
            {
                moverSprite->SetPosition(15,40);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.fov - 40)*3.33333f+5,40);
            }
            moverSprite->Draw();

            if(mWorld->mainOptions.horizontalViewDistance == 1)
            {
                moverSprite->SetPosition(15,70);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.horizontalViewDistance - 1)*66.666667f+5,70);
            }
            moverSprite->Draw();

            if(mWorld->mainOptions.verticalViewDistance == 1)
            {
                moverSprite->SetPosition(275,40);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.verticalViewDistance - 1)*66.666667f+265,40);
            }
            moverSprite->Draw();

            if(mWorld->mainOptions.fogDistance == 0)
            {
                moverSprite->SetPosition(275,70);
            }
            else
            {
                moverSprite->SetPosition((mWorld->mainOptions.fogDistance)*6.666667f+265,70);
            }
            moverSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            //draw subtitles on buttons
            if(mWorld->mainOptions.fov == 70)
            {
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(111,46,"FOV: Normal");
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(110,45,"FOV: Normal");
            }
            else
            {
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(111,46,"FOV: %f",mWorld->mainOptions.fov);
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(110,45,"FOV: %f",mWorld->mainOptions.fov);
            }

            if(mWorld->mainOptions.horizontalViewDistance == 1)
            {
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(111,76,"H Render Distance: %i chunk",mWorld->mainOptions.horizontalViewDistance);
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(110,75,"H Render Distance: %i chunk",mWorld->mainOptions.horizontalViewDistance);
            }
            else
            {
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(111,76,"H Render Distance: %i chunks",mWorld->mainOptions.horizontalViewDistance);
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(110,75,"H Render Distance: %i chunks",mWorld->mainOptions.horizontalViewDistance);
            }

            if(mWorld->mainOptions.verticalViewDistance == 1)
            {
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(371,46,"V Render Distance: %i chunk",mWorld->mainOptions.verticalViewDistance);
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(370,45,"V Render Distance: %i chunk",mWorld->mainOptions.verticalViewDistance);
            }
            else
            {
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(371,46,"V Render Distance: %i chunks",mWorld->mainOptions.verticalViewDistance);
                RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
                mRender->DebugPrint(370,45,"V Render Distance: %i chunks",mWorld->mainOptions.verticalViewDistance);
            }

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(371,76,"Fog Distance: %i",mWorld->mainOptions.fogDistance);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(370,75,"Fog Distance: %i",mWorld->mainOptions.fogDistance);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.fogRendering == true ? mRender->DebugPrint(111,106,"Fog Rendering: ON"): mRender->DebugPrint(111,106,"Fog Rendering: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.fogRendering == true ? mRender->DebugPrint(110,105,"Fog Rendering: ON"): mRender->DebugPrint(110,105,"Fog Rendering: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.cloudsRender == true ? mRender->DebugPrint(111,136,"Clouds Rendering: ON"): mRender->DebugPrint(111,136,"Clouds Rendering: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.cloudsRender == true ? mRender->DebugPrint(110,135,"Clouds Rendering: ON"): mRender->DebugPrint(110,135,"Clouds Rendering: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.fastRendering == true ? mRender->DebugPrint(111,166,"Graphics: Fast"): mRender->DebugPrint(111,166,"Graphics: Fancy");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.fastRendering == true ? mRender->DebugPrint(110,165,"Graphics: Fast"): mRender->DebugPrint(110,165,"Graphics: Fancy");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.worldBlockAnimation == true ? mRender->DebugPrint(111,196,"Block Animation: ON"): mRender->DebugPrint(111,196,"Block Animation: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.worldBlockAnimation == true ? mRender->DebugPrint(110,195,"Block Animation: ON"): mRender->DebugPrint(110,195,"Block Animation: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.headBob == true ? mRender->DebugPrint(111,226,"Head Bob: ON"): mRender->DebugPrint(111,226,"Head Bob: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.headBob == true ? mRender->DebugPrint(110,225,"Head Bob: ON"): mRender->DebugPrint(110,225,"Head Bob: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(111,256,"Don't Press This Button");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(110,255,"Don't Press This Button");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.sunMoodRendering == true ? mRender->DebugPrint(371,106,"Sun&Moon Rendering: ON"): mRender->DebugPrint(371,106,"Sun&Moon Rendering: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.sunMoodRendering == true ? mRender->DebugPrint(370,105,"Sun&Moon Rendering: ON"): mRender->DebugPrint(370,105,"Sun&Moon Rendering: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.guiDrawing == true ? mRender->DebugPrint(371,136,"GUI Rendering: ON"): mRender->DebugPrint(371,136,"GUI Rendering: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.guiDrawing == true ? mRender->DebugPrint(370,135,"GUI Rendering: ON"): mRender->DebugPrint(370,135,"GUI Rendering: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.sounds == true ? mRender->DebugPrint(371,166,"Sounds: ON"): mRender->DebugPrint(371,166,"Sounds: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mWorld->mainOptions.sounds == true ? mRender->DebugPrint(370,165,"Sounds: ON"): mRender->DebugPrint(370,165,"Sounds: OFF");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(371,196,"Take Screenshot");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(370,195,"Take Screenshot");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(371,226,"Rename Map");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            mRender->DebugPrint(370,225,"Rename Map");

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
            devMode == true ? mRender->DebugPrint(371,256,"Dev Mode: ON") : mRender->DebugPrint(371,256,"Dev Mode: OFF");
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
            devMode == true ? mRender->DebugPrint(370,255,"Dev Mode: ON") : mRender->DebugPrint(370,255,"Dev Mode: OFF");

            DrawText(240,20,GU_COLOR(1,1,1,1),0.35,"Options");
        }
        else
        {
            sceGuDisable(GU_DEPTH_TEST);
            sceGuEnable(GU_BLEND);
            sceGuColor(GU_COLOR(1,1,1,1.0f));

            buttonSprite->SetPosition(240,50);
            buttonSprite->Draw();

            //resume
            buttonSprite->SetPosition(240,80);
            buttonSprite->Draw();

            //options
            buttonSprite->SetPosition(240,110);
            buttonSprite->Draw();

            //save
            buttonSprite->SetPosition(240,160);
            buttonSprite->Draw();

            //quit
            buttonSprite->SetPosition(240,190);
            buttonSprite->Draw();

            //quit and save
            buttonSprite->SetPosition(240,220);
            buttonSprite->Draw();

            //selected button
            if(selectPos <= 2)
            {
                sbuttonSprite->SetPosition(240,(selectPos * 30) + 50);
            }
            if(selectPos > 2)
            {
                sbuttonSprite->SetPosition(240,(selectPos * 30) + 70);
            }
            sbuttonSprite->Draw();

            sceGuDisable(GU_BLEND);
            sceGuEnable(GU_DEPTH_TEST);

            mRender->SetFontStyle(0.35f ,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00000000|0x00004000);
            mRender->DebugPrint(3,11,"World seed is: %i",mWorld->worldSeed);

            mRender->SetFontStyle(0.35f ,GU_COLOR(1,1,1,1),0,0,0x00000000|0x00004000);
            mRender->DebugPrint(2,10,"World seed is: %i",mWorld->worldSeed);

            DrawText(240,55,GU_COLOR(1,1,1,1),0.35f,"Back to game");
            DrawText(240,85,GU_COLOR(1,1,1,1),0.35f,"Options...");
            DrawText(240,115,GU_COLOR(1,1,1,1),0.35f,"Statistics");
            DrawText(240,165,GU_COLOR(1,1,1,1),0.35f,"Save");
            DrawText(240,195,GU_COLOR(1,1,1,1),0.35f,"Save and exit");
            DrawText(240,225,GU_COLOR(1,1,1,1),0.35f,"Exit");

            DrawText(240,25,GU_COLOR(1,1,1,1),0.35f,"Game menu");
        }
    }
    if (menuState == 3)
    {
        if(statisticsPage == 0)
        {
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,51,"Blocks Placed: %i",mWorld->mainStatistics.blockPlaced);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,50,"Blocks Placed: %i",mWorld->mainStatistics.blockPlaced);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,71,"Blocks Destroyed: %i",mWorld->mainStatistics.blockDestroyed);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,70,"Blocks Destroyed: %i",mWorld->mainStatistics.blockDestroyed);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,91,"Age Of The World: %i d",mWorld->mainStatistics.daysInGame);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,90,"Age Of The World: %i d",mWorld->mainStatistics.daysInGame);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,111,"Minutes Played: %i m",mWorld->mainStatistics.minutesPlayed);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,110,"Minutes Played: %i m",mWorld->mainStatistics.minutesPlayed);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,131,"Items Crafted: %i",mWorld->mainStatistics.itemsCrafted);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,130,"Items Crafted: %i",mWorld->mainStatistics.itemsCrafted);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,151,"Items Smelted: %i",mWorld->mainStatistics.itemsSmelted);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,150,"Items Smelted: %i",mWorld->mainStatistics.itemsSmelted);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,171,"Soil Plowed: %i",mWorld->mainStatistics.soilPlowed);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,170,"Soil Plowed: %i",mWorld->mainStatistics.soilPlowed);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,191,"Crops Grown: %i",mWorld->mainStatistics.cropsGrowned);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,190,"Crops Grown: %i",mWorld->mainStatistics.cropsGrowned);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,211,"Trees Grown: %i",mWorld->mainStatistics.treesGrowned);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,210,"Trees Grown: %i",mWorld->mainStatistics.treesGrowned);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,231,"Damage Dealt: %i",mWorld->mainStatistics.damageRecieved);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,230,"Damage Dealt: %i",mWorld->mainStatistics.damageRecieved);
        }
        else
        {
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,51,"Badly falls: %i",mWorld->mainStatistics.badlyFalls);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,50,"Badly falls: %i",mWorld->mainStatistics.badlyFalls);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,71,"Food eaten: %i",mWorld->mainStatistics.foodEaten);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,70,"Food eaten: %i",mWorld->mainStatistics.foodEaten);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,91,"Jumps: %i",mWorld->mainStatistics.jumps);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,90,"Jumps: %i",mWorld->mainStatistics.jumps);

            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.14,0.14,0.14,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(201,111,"Dies: %i",mWorld->mainStatistics.dies);
            RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.8,0.8,0.8,1),0,0,0x00004000|0x00000000);
            RenderManager::InstancePtr()->DebugPrint(200,110,"Dies: %i",mWorld->mainStatistics.dies);
        }

        DrawText(240,20,GU_COLOR(1,1,1,1),0.35,"Statistics");

        RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000200);
        RenderManager::InstancePtr()->DebugPrint(241,251,"Page: %i / 2",statisticsPage+1);
        RenderManager::InstancePtr()->SetFontStyle(0.35,GU_COLOR(1,1,1,1),0,0,0x00004000|0x00000200);
        RenderManager::InstancePtr()->DebugPrint(240,250,"Page: %i / 2",statisticsPage+1);
    }

    //debug info
    if(devMode)
    {
        mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0,0x00000000);

        if(dt > 0.0f)
            mRender->DebugPrint(20,20,"fps: %4.2f",(1.0f/dt));
        mRender->DebugPrint(20,30,"cpu: %d%%",mRender->GetCpuUsage());
        mRender->DebugPrint(20,40,"gpu: %d%%",mRender->GetGpuUsage());
        mRender->DebugPrint(20,50,"memory: %d",freeMemory);
        mRender->DebugPrint(20,60,"poly: %d",(mWorld->GetDrawntTrianglesCount() / 3));
        mRender->DebugPrint(20,70,"verts: %d",mWorld->GetDrawntTrianglesCount());
        mRender->DebugPrint(20,80,"day time: %f",mWorld->worldDayTime);
        mRender->DebugPrint(20,90,"bright: %f",mWorld->bright);
        mRender->DebugPrint(20,100,"sun time: %f",sunTime);
        mRender->DebugPrint(20,110,"player.x: %f",playerPosition.x);
        mRender->DebugPrint(20,120,"player.y: %f",playerPosition.y);
        mRender->DebugPrint(20,130,"player.z: %f",playerPosition.z);
        mRender->DebugPrint(20,140,"angle: %f",mWorld->lightAngle);
        mRender->DebugPrint(20,180,"GetBlock(x, y, z) %f", (float)mWorld->GetBlock(cubePos.x, cubePos.y, cubePos.z));
        /*if(playSB != NULL)
        {
            mRender->DebugPrint(20,200,"pos.x %f", playSB->pos.x);
            mRender->DebugPrint(20,210,"pos.y %f", playSB->pos.y);
            mRender->DebugPrint(20,220,"pos.z %f", playSB->pos.z);
        }*/
        if(mSnowBalls.size() > 0)
        {
            mRender->DebugPrint(20,220," size of vector SnowBalls %i", mSnowBalls.size());
        }

        mRender->SetFontStyle(0.345f,0xFFFFFFFF,0,0,0x00000200);
    }

    //end frame
    mRender->EndFrame();
}

//additional functions
void StatePlay::advancedBlit(int sx, int sy, int sw, int sh, int dx, int dy, int slice)
{
    int start, end;

    // blit maximizing the use of the texture-cache

    for (start = sx, end = sx+sw; start < end; start += slice, dx += slice)
    {
        TexturesPSPVertex16* vertices = (TexturesPSPVertex16*)sceGuGetMemory(2 * sizeof(TexturesPSPVertex16));
        int width = (start + slice) < end ? slice : end-start;

        vertices[0].u = start;
        vertices[0].v = sy;
        vertices[0].x = dx;
        vertices[0].y = dy;
        vertices[0].z = 0;

        vertices[1].u = start + width;
        vertices[1].v = sy + sh;
        vertices[1].x = dx + width;
        vertices[1].y = dy + sh;
        vertices[1].z = 0;

        sceGuDrawArray(GU_SPRITES,GU_TEXTURE_16BIT|GU_VERTEX_16BIT|GU_TRANSFORM_2D,2,0,vertices);
    }
}

bool StatePlay::TryToMove(Vector3 moveVector,float dt)
{
    // Build a "test vector" that is a little longer than the move vector.
    float moveLength = moveVector.magnitude();
    Vector3 testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.2f);

    // Apply this test vector.
    Vector3 movePosition = playerPosition + testVector;
    Vector3 midBodyPoint = movePosition + Vector3(0, -0.7f, 0);
    Vector3 lowerBodyPoint = movePosition + Vector3(0, -1.4f, 0);

    if (!mWorld->SolidAtPointForPlayer(movePosition) && !mWorld->SolidAtPointForPlayer(lowerBodyPoint) && !mWorld->SolidAtPointForPlayer(midBodyPoint))
    {
        playerPosition = playerPosition + moveVector;
        return true;
    }

    //teraz mo¿na robiæ ciekawe rzeczy

    testVector = moveVector;
    testVector.normalize();
    testVector = testVector * (moveLength + 0.35f);
    movePosition = playerPosition + testVector;
    midBodyPoint = movePosition + Vector3(0, -0.7f, 0);
    lowerBodyPoint = movePosition + Vector3(0, -1.4f, 0);

    unsigned char lowerBlock = mWorld->BlockAtPoint(lowerBodyPoint);
    unsigned char midBlock = mWorld->BlockAtPoint(midBodyPoint);
    unsigned char upperBlock = mWorld->BlockAtPoint(movePosition);

    //kolizja z drabin¹ :>
    if (upperBlock == 6 || lowerBlock == 6 || midBlock == 6)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 82 || lowerBlock == 82 || midBlock == 82)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 83 || lowerBlock == 83 || midBlock == 83)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 84 || lowerBlock == 84 || midBlock == 84)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 85 || lowerBlock == 85 || midBlock == 85)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 86 || lowerBlock == 86 || midBlock == 86)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 87 || lowerBlock == 87 || midBlock == 87)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 88 || lowerBlock == 88 || midBlock == 88)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 89 || lowerBlock == 89 || midBlock == 89)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }

    if (upperBlock == 90 || lowerBlock == 90 || midBlock == 90)
    {
        playerVelocity.y = CLIMBVELOCITY;
        Vector3 footPosition = playerPosition + Vector3(0.0f, -1.5f, 0.0f);
        if (mWorld->SolidAtPointForPlayer(footPosition))
            playerPosition.y += 0.1f;
        return true;
    }



    return false;
}

bool StatePlay::keyPressed(int currentKey)
{
    //analog reset
    if(analogUp)
    {
        if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYup)
            analogUp = false;
    }
    if(analogDown)
    {
        if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYdown)
            analogDown = false;
    }
    if(analogLeft)
    {
        if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXleft)
            analogLeft = false;
    }
    if(analogRight)
    {
        if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXright)
            analogRight = false;
    }

    //keys
    if(currentKey == 0)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyPressed(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
    {
        if(!analogUp)
        {
            if(mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup)
            {
                analogUp = true;
                return true;//analog up
            }
        }
    }
    if(currentKey == 11)//cross
    {
        if(!analogDown)
        {
            if(mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown)
            {
                analogDown = true;
                return true;//analog down
            }
        }
    }
    if(currentKey == 13)//cross
    {
        if(!analogLeft)
        {
            if(mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft)
            {
                analogLeft = true;
                return true;//analog left
            }
        }
    }
    if(currentKey == 14)//cross
    {
        if(!analogRight)
        {
            if(mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright)
            {
                analogRight = true;
                return true;//analog right
            }
        }
    }

    return false;
}

bool StatePlay::keyHold(int currentKey)
{
    if(currentKey == 0)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_UP);
    if(currentKey == 1)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_DOWN);
    if(currentKey == 2)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LEFT);
    if(currentKey == 3)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RIGHT);

    if(currentKey == 4)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_TRIANGLE);
    if(currentKey == 5)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CROSS);
    if(currentKey == 6)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SQUARE);
    if(currentKey == 7)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_CIRCLE);

    if(currentKey == 8)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_LTRIGGER);
    if(currentKey == 9)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_RTRIGGER);
    if(currentKey == 10)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_SELECT);
    if(currentKey == 15)//cross
        return mSystemMgr->KeyHold(PSP_CTRL_START);

    //analog stick....
    if(currentKey == 12)//cross
        return (mSystemMgr->GetAnalogY() > InputHelper::Instance()->analogYup);//analog up
    if(currentKey == 11)//cross
        return (mSystemMgr->GetAnalogY() < InputHelper::Instance()->analogYdown);//analog down
    if(currentKey == 13)//cross
        return (mSystemMgr->GetAnalogX() < InputHelper::Instance()->analogXleft);//analog left
    if(currentKey == 14)//cross
        return (mSystemMgr->GetAnalogX() > InputHelper::Instance()->analogXright);//analog right

    return false;
}


void StatePlay::HungerTime()
{
    if(mWorld->HG >= 18)
    {
        if (rand() % 3 == 1)
        {
            mWorld->HG -= 1;
        }
    }
    else
    {
        mWorld->HG -= 1;
    }
    if(mWorld->HG < 0)
    {
        mWorld->HG = 0;
    }
}

void StatePlay::HealthTime()
{
    if(mWorld->HG < 1 && mWorld->HP > 0)
    {
        mSoundMgr->PlayHitSound();
        mWorld->HP -= 1;
        mWorld->mainStatistics.damageRecieved += 1;
        hurt = true;
        hurt_time = 1.0f;
    }

    if(mWorld->HG >= 18)
    {
        if(mWorld->HP > 0)
        {
            mWorld->HP += 1;
        }
    }

    if(mWorld->HP > 20)
    {
        mWorld->HP = 20;
    }
}

void StatePlay::OxygenTime()
{
    if(mWorld->OS <= 0)
    {
        mSoundMgr->PlayHitSound();
        mWorld->HP -= 1;
        mWorld->mainStatistics.damageRecieved += 1;
        if(mWorld->HP > 0)
        {
            hurt = true;
            hurt_time = 1.0f;
        }
    }
    if(mWorld->OS > 0)
    {
        mWorld->OS -= 1;
    }
}

void StatePlay::PutInInventory(int id, int num, bool st)
{
    for(int j = 35; j >= 0; j--)
    {
        if (mWorld->invSt[j]==1)
        {
            if (mWorld->invId[j]== id)
            {
                if(mWorld->invAm[j] + num <= 64)
                {
                    mWorld->invAm[j] += num;
                    chestId = -1;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (mWorld->invId[j]== -1)
        {
            mWorld->invSt[j] = st;
            mWorld->invId[j] = id;
            mWorld->invAm[j] = num;
            break;
        }
    }
}

void StatePlay::DrawText(int x,int y, unsigned int color, float size, const char *message, ...)
{
    RenderManager::InstancePtr()->SetFontStyle(size,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00000200|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x+(size/(float)0.35f),y+(size/(float)0.35f),message);
    RenderManager::InstancePtr()->SetFontStyle(size,color,0,0,0x00000200|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x,y,message);
}

void StatePlay::DrawText2(int x,int y, unsigned int color, float size, const char *message, ...)
{
    RenderManager::InstancePtr()->SetFontStyle(size,GU_COLOR(0.24,0.24,0.24,1),0,0,0x00004000|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x+(size/(float)0.35f),y+(size/(float)0.35f),message);
    RenderManager::InstancePtr()->SetFontStyle(size,color,0,0,0x00004000|0x00000000);
    RenderManager::InstancePtr()->DebugPrint(x,y,message);
}

