#include "CraftWorld2.h"
#include <Aurora/Graphics/RenderManager.h>
#include <Aurora/Utils/Logger.h>

#include <string.h>
#include <zlib.h>
#define PI 3.1415926535897f


//percent / texturechunk = 1 pixel ; percent = 1 block

//down - верхн€€ граница текстуры
//up - нижн€€


CraftWorld::CraftWorld()
{
    WORLD_SIZE = 0;
    CHUNK_SIZE = 0;

    mainStatistics.blockPlaced = 0;
    mainStatistics.blockDestroyed = 0;
    mainStatistics.daysInGame = 0;
    mainStatistics.minutesPlayed = 0;
    mainStatistics.itemsCrafted = 0;
    mainStatistics.itemsSmelted = 0;
    mainStatistics.jumps = 0;
    mainStatistics.dies = 0;
    mainStatistics.foodEaten = 0;
    mainStatistics.badlyFalls = 0;
    mainStatistics.blocksWalked = 0;
    mainStatistics.treesGrowned = 0;
    mainStatistics.cropsGrowned = 0;
    mainStatistics.soilPlowed = 0;
    mainStatistics.timeInAir = 0;
    mainStatistics.timeInWater = 0;
    mainStatistics.damageRecieved = 0;

    mainOptions.cloudsRender = 1;
    mainOptions.fakeShadowsRendering = 1;
    mainOptions.sounds = 1;
    mainOptions.music = 1;
    mainOptions.fogRendering = 1;
    mainOptions.fastRendering = 0;
    mainOptions.headBob = 1;
    mainOptions.fov = 70;
    mainOptions.sunMoodRendering = 1;
    mainOptions.worldBlockAnimation = 1;
    mainOptions.particles = 0;
    mainOptions.fogDistance = 20;
    mainOptions.horizontalViewDistance = 3;
    mainOptions.verticalViewDistance = 2;
    mainOptions.guiDrawing = 1;

    waterY = 0;

    bright = 0;
    worldTime = 0.0f;
    skyTime = 112.0f;

    playerZoneSize = Vector3(48,16,48);
    updateChunksSwitch = false;
    updateChunkTimer = 0.0f;
    chunksCreatedInFrameCount = 0;
    transparentchunksCreatedInFrameCount = 0;

    mId = -1;
    mAm = -1;
    mSt = 0;//percent / texturechunk = 1 pixel ; percent = 1 block

    worldSeed = 0;

    HP = 20;
    HG = 20;
    OS = 10;

    worldTime = 0.0f;

    worldDayTime = 12.0f;
    worldHour = 0.0f;

    freezeDayTime = false;
    worldVersion = 3;


    mDirectsize = 0;

    //air
    blockTypes.push_back(BaseBlock());
    //normal blocks
    blockTypes.push_back(GrassBlock());
    blockTypes.push_back(DirtBlock());
    blockTypes.push_back(RockBlock());
    blockTypes.push_back(WaterBlock());
    blockTypes.push_back(GoldBlock());
    blockTypes.push_back(LadderBlock());
    blockTypes.push_back(SandBlock());
    blockTypes.push_back(WoodBlock());
    blockTypes.push_back(LeavesBlock());

    blockTypes.push_back(GrayWoolBlock());
    blockTypes.push_back(BlackWoolBlock());
    blockTypes.push_back(RedWoolBlock());
    blockTypes.push_back(DarkGreyWoolBlock());
    blockTypes.push_back(BrownWoolBlock());
    blockTypes.push_back(LightBlackWoolBlock());
    blockTypes.push_back(PinkWoolBlock());
    blockTypes.push_back(LightGreenWoolBlock());
    blockTypes.push_back(YellowWoolBlock());

    blockTypes.push_back(BlueWoolBlock());
    blockTypes.push_back(LightBlueWoolBlock());
    blockTypes.push_back(FioletWoolBlock());
    blockTypes.push_back(PastelWoolBlock());
    blockTypes.push_back(LightFioletWoolBlock());
    blockTypes.push_back(OrangeWoolBlock());
    blockTypes.push_back(CactusBlock());
    blockTypes.push_back(AllSnowBlock());
    blockTypes.push_back(BrickBlock());

    blockTypes.push_back(CageBlock());
    blockTypes.push_back(SnowBlock());
    blockTypes.push_back(DarkWoodBlock());
    blockTypes.push_back(WhiteWoodBlock());
    blockTypes.push_back(IceBlock());
    blockTypes.push_back(CaneBlock());
    blockTypes.push_back(BoxBlock());
    blockTypes.push_back(ShelfBlock());
    blockTypes.push_back(CobbleStone());

    blockTypes.push_back(DrySandBlock());
    blockTypes.push_back(SnowLewesBlock());
    blockTypes.push_back(Sponge());
    blockTypes.push_back(GlassBlock());
    blockTypes.push_back(IronOre());
    blockTypes.push_back(CoalOre());
    blockTypes.push_back(DiamondOre());
    blockTypes.push_back(RedstoneOre());
    blockTypes.push_back(SlamRockBlock());

    blockTypes.push_back(Obsidian());
    blockTypes.push_back(JackOLantern());
    blockTypes.push_back(Torch());
    blockTypes.push_back(Door1());
    blockTypes.push_back(Door2());
    blockTypes.push_back(Door3());
    blockTypes.push_back(Door4());
    blockTypes.push_back(Door5());
    blockTypes.push_back(Door6());

    blockTypes.push_back(Door7());
    blockTypes.push_back(Door8());
    blockTypes.push_back(Door9());
    blockTypes.push_back(Door10());
    blockTypes.push_back(WoodenFence());
    blockTypes.push_back(CobbleStair1());
    blockTypes.push_back(CobbleStair2());
    blockTypes.push_back(CobbleStair3());
    blockTypes.push_back(CobbleStair4());

    blockTypes.push_back(Diamond());
    blockTypes.push_back(Gold());
    blockTypes.push_back(Iron());
    blockTypes.push_back(BrickStair1());
    blockTypes.push_back(BrickStair2());
    blockTypes.push_back(BrickStair3());
    blockTypes.push_back(BrickStair4());
    blockTypes.push_back(MelonBlock());
    blockTypes.push_back(JukeBox());

    blockTypes.push_back(EndStone());
    blockTypes.push_back(Pumpkin());
    blockTypes.push_back(GlowStone());
    blockTypes.push_back(HayBale());
    blockTypes.push_back(Mooshroom1());
    blockTypes.push_back(Mooshroom2());
    blockTypes.push_back(Soil());
    blockTypes.push_back(WateredSoil());
    blockTypes.push_back(MooshroomWood());

    blockTypes.push_back(HalfBlock8());
    blockTypes.push_back(HalfBlock0());
    blockTypes.push_back(HalfBlock1());
    blockTypes.push_back(HalfBlock2());
    blockTypes.push_back(HalfBlock3());
    blockTypes.push_back(HalfBlock4());
    blockTypes.push_back(HalfBlock5());
    blockTypes.push_back(HalfBlock6());
    blockTypes.push_back(HalfBlock7());

    blockTypes.push_back(Cake());
    blockTypes.push_back(TrapDoor());
    blockTypes.push_back(Snow2());
    blockTypes.push_back(Table());
    blockTypes.push_back(AetherStone());
    blockTypes.push_back(MushRoomLeave());
    blockTypes.push_back(MossAetherStone());
    blockTypes.push_back(AetherBlock1());
    blockTypes.push_back(ClayBlock());

    blockTypes.push_back(Chest5());
    blockTypes.push_back(BasaltCobble());
    blockTypes.push_back(GabbroCobble());
    blockTypes.push_back(DaciteCobble());
    blockTypes.push_back(Furnace2());
    blockTypes.push_back(Crafting());
    blockTypes.push_back(FurnaceOff());
    blockTypes.push_back(FurnaceOn());
    blockTypes.push_back(Furnace5());

    blockTypes.push_back(Furnace6());
    blockTypes.push_back(TNT());
    blockTypes.push_back(Nuclear());
    blockTypes.push_back(Lava());
    blockTypes.push_back(Gravel());
    blockTypes.push_back(LavaStone());
    blockTypes.push_back(LavaObsidian());
    blockTypes.push_back(BlackStone());
    blockTypes.push_back(CryObsidian());

    blockTypes.push_back(MossBlack());
    blockTypes.push_back(Flower1());
    blockTypes.push_back(Flower2());
    blockTypes.push_back(Sapling());
    blockTypes.push_back(Pumpkin2());
    blockTypes.push_back(Pumpkin3());
    blockTypes.push_back(Pumpkin4());
    blockTypes.push_back(WoodenStair1());
    blockTypes.push_back(WoodenStair2());

    blockTypes.push_back(WoodenStair3());
    blockTypes.push_back(WoodenStair4());
    blockTypes.push_back(Marble());
    blockTypes.push_back(Cube());
    blockTypes.push_back(Chest2());
    blockTypes.push_back(Chest3());
    blockTypes.push_back(Chest4());

    blockTypes.push_back(WheatBlock1());
    blockTypes.push_back(WheatBlock2());
    blockTypes.push_back(WheatBlock3());
    blockTypes.push_back(WheatBlock4());

    blockTypes.push_back(FreeBlock3());
    blockTypes.push_back(FreeBlock4());
    blockTypes.push_back(WorldSky());
    blockTypes.push_back(Cloud());
    blockTypes.push_back(IronBlock());

    itemTypes.push_back(WoodenPickaxe());
    itemTypes.push_back(StonePickaxe());
    itemTypes.push_back(IronPickaxe());
    itemTypes.push_back(DiamondPickaxe());
    itemTypes.push_back(GoldenPickaxe());

    itemTypes.push_back(WoodenSword());
    itemTypes.push_back(StoneSword());
    itemTypes.push_back(IronSword());
    itemTypes.push_back(DiamondSword());
    itemTypes.push_back(GoldenSword());

    itemTypes.push_back(WoodenShovel());
    itemTypes.push_back(StoneShovel());
    itemTypes.push_back(IronShovel());
    itemTypes.push_back(DiamondShovel());
    itemTypes.push_back(GoldenShovel());

    itemTypes.push_back(WoodenAxe());
    itemTypes.push_back(StoneAxe());
    itemTypes.push_back(IronAxe());
    itemTypes.push_back(DiamondAxe());
    itemTypes.push_back(GoldenAxe());

    itemTypes.push_back(WoodenHoe());
    itemTypes.push_back(StoneHoe());
    itemTypes.push_back(IronHoe());
    itemTypes.push_back(DiamondHoe());
    itemTypes.push_back(GoldenHoe());

    itemTypes.push_back(Scissors());
    itemTypes.push_back(Stick());
    itemTypes.push_back(Coal());
    itemTypes.push_back(IronBar());
    itemTypes.push_back(DiamondItem());

    itemTypes.push_back(GoldenBar());
    itemTypes.push_back(FireItem());
    itemTypes.push_back(LigniteCoal());
    itemTypes.push_back(Clay());
    itemTypes.push_back(Apple());
    itemTypes.push_back(GoldenApple());

    itemTypes.push_back(WheatSeeds());
    itemTypes.push_back(Wheat());
    itemTypes.push_back(WhiteBread());
    itemTypes.push_back(Brick());
    itemTypes.push_back(Busket());
    itemTypes.push_back(WaterBusket());
    itemTypes.push_back(LavaBusket());

    itemTypes.push_back(CaneItem());
    itemTypes.push_back(Flower1Item());
    itemTypes.push_back(Flower2Item());
    itemTypes.push_back(SaplingItem());
    itemTypes.push_back(Paper());
    itemTypes.push_back(Book());
    itemTypes.push_back(SnowBallItem());

    itemTypes.push_back(MooshroomItem1());
    itemTypes.push_back(MooshroomItem2());
    itemTypes.push_back(Bowl());
    itemTypes.push_back(MooshroomBowl());

    itemTypes.push_back(IronWateringCan());
    itemTypes.push_back(DiamondWateringCan());
    itemTypes.push_back(DoorItem());

    for(int o = 0; o <= 35; o += 1)
    {
        invAm[o] = -1;
        invId[o] = -1;
        invSt[o] = 0;
    }

    timee = 0.0f;
    lightShadowFactor = 0.2f;
    lightFactor = Vector3(1.0f,1.0f,1.0f);
}

CraftWorld::~CraftWorld()
{
    //delete arrays
    delete [] m_Blocks;
    delete [] m_BlockLight;

    //delete chests
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        delete mChunks[i];
    }
    mChunks.clear();

    //water chunks
    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        delete mTransparentChunks[i];
    }
    mTransparentChunks.clear();

    for(unsigned int i = 0; i < mChests.size(); i++)
    {
        delete mChests[i];
    }
    mChests.clear();

        //delete furnace
    for(unsigned int i = 0; i < mFurnaces.size(); i++)
    {
        delete mFurnaces[i];
    }
    mFurnaces.clear();

    //delete all direction mind blocks
    for(unsigned int i = 0; i < mDirects.size(); i++)
    {
        delete mDirects[i];
    }
    mDirects.clear();

    //delete block vertices
    blockTypes.clear();
    itemTypes.clear();

}

void CraftWorld::SaveCompressedWorld(std::string  filename)
{
    //first save version and name on normal file
    FILE * pFile;
    pFile = fopen(filename.c_str(),"wb");

    if(pFile == NULL)
        return;

    //version
    fwrite(&worldVersion,sizeof(int),1,pFile);

    //name
    fwrite(worldName,sizeof(char),50,pFile);

    //close file
    fclose(pFile);

    //now save compressed map info
    filename = filename + "c";

    //open file
    gzFile saveFile;
    saveFile = gzopen(filename.c_str(),"wb");
    if(saveFile == 0)
        return;

    //player pos
    gzwrite(saveFile, &playerPos.x,sizeof(float));
    gzwrite(saveFile, &playerPos.y,sizeof(float));
    gzwrite(saveFile, &playerPos.z,sizeof(float));

    //size
    gzwrite(saveFile, &WORLD_SIZE,sizeof(int));

    //chunksize
    gzwrite(saveFile, &CHUNK_SIZE,sizeof(int));

    //cubes
    gzwrite(saveFile, m_Blocks,sizeof(unsigned char)*(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE));

    //light
    gzwrite(saveFile, m_BlockLight,sizeof(unsigned char)*(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE));

    //settings
    gzwrite(saveFile, m_BlockSettings,sizeof(unsigned char)*(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE));

    //world time
    gzwrite(saveFile, &worldDayTime,sizeof(float));
    //sun time
    gzwrite(saveFile, &sunTime,sizeof(float));

    gzwrite(saveFile, &mainStatistics,sizeof(st));

    gzwrite(saveFile, &mainOptions,sizeof(opt));

    gzwrite(saveFile, &invId,sizeof(int)*(36));

    gzwrite(saveFile, &invAm,sizeof(int)*(36));

    gzwrite(saveFile, &invSt,sizeof(bool)*(36));

    gzwrite(saveFile, &HP,sizeof(unsigned int));

    gzwrite(saveFile, &HG,sizeof(unsigned int));

    gzwrite(saveFile, &OS,sizeof(unsigned int));

    gzwrite(saveFile, &bright,sizeof(float));

    gzwrite(saveFile, &worldSeed,sizeof(int));

    gzwrite(saveFile, &skyTime,sizeof(float));

    mChestsize = mChests.size();
    gzwrite(saveFile, &mChestsize,sizeof(int));

    if(mChestsize != 0)
    {
    int* data1 = new int[27*mChestsize];
    int* data2 = new int[27*mChestsize];
    bool* data3 = new bool[27*mChestsize];

    int* data4 = new int[mChestsize];
    int* data5 = new int[mChestsize];
    int* data6 = new int[mChestsize];

    for(int k = 0; k < mChestsize; k++)
    {
        Chest* SaveChest = mChests[k];
        for(int l = 0; l <= 26; l++)
        {
            data1[k*27+l] = SaveChest->chestSlotId[l];
            data2[k*27+l] = SaveChest->chestSlotAm[l];
            data3[k*27+l] = SaveChest->chestSlotSt[l];
        }

        data4[k] = SaveChest->chestX;
        data5[k] = SaveChest->chestY;
        data6[k] = SaveChest->chestZ;
    }

    gzwrite(saveFile, data1,sizeof(int) * (mChestsize*27));
    gzwrite(saveFile, data2,sizeof(int) * (mChestsize*27));
    gzwrite(saveFile, data3,sizeof(bool) * (mChestsize*27));

    gzwrite(saveFile, data4,sizeof(int)*(mChestsize));
    gzwrite(saveFile, data5,sizeof(int)*(mChestsize));
    gzwrite(saveFile, data6,sizeof(int)*(mChestsize));

    delete[] data1;
    delete[] data2;
    delete[] data3;
    delete[] data4;
    delete[] data5;
    delete[] data6;
    }

    mFurnacesize = mFurnaces.size();
    gzwrite(saveFile, &mFurnacesize,sizeof(int));

    if(mFurnacesize != 0)
    {
        int* data1 = new int[3*mFurnacesize];
        int* data2 = new int[3*mFurnacesize];
        bool* data3 = new bool[3*mFurnacesize];

        int* data4 = new int[mFurnacesize];
        int* data5 = new int[mFurnacesize];
        int* data6 = new int[mFurnacesize];

        float* data7 = new float[mFurnacesize];
        float* data8 = new float[mFurnacesize];

        bool* data9 = new bool[mFurnacesize];

        int* data10 = new int[mFurnacesize];

        for(int k = 0; k < mFurnacesize; k++)
        {
            Furnace* SaveFurnace = mFurnaces[k];
            for(int l = 0; l <= 2; l++)
            {
                data1[k*3+l] = SaveFurnace->furnaceSlotId[l];
                data2[k*3+l] = SaveFurnace->furnaceSlotAm[l];
                data3[k*3+l] = SaveFurnace->furnaceSlotSt[l];
            }
            data4[k] = SaveFurnace->furnaceX;
            data5[k] = SaveFurnace->furnaceY;
            data6[k] = SaveFurnace->furnaceZ;

            data7[k] = SaveFurnace->fuelTime;
            data8[k] = SaveFurnace->meltingTime;
            data9[k] = SaveFurnace->working;
            data10[k] = SaveFurnace->smeltItemTemp;
        }

        gzwrite(saveFile, data1,sizeof(int) * (mFurnacesize*3));
        gzwrite(saveFile, data2,sizeof(int) * (mFurnacesize*3));
        gzwrite(saveFile, data3,sizeof(bool) *(mFurnacesize*3));

        gzwrite(saveFile, data4,sizeof(int)*(mFurnacesize));
        gzwrite(saveFile, data5,sizeof(int)*(mFurnacesize));
        gzwrite(saveFile, data6,sizeof(int)*(mFurnacesize));

        gzwrite(saveFile, data7,sizeof(float)*(mFurnacesize));
        gzwrite(saveFile, data8,sizeof(float)*(mFurnacesize));
        gzwrite(saveFile, data9,sizeof(bool)*(mFurnacesize));

        gzwrite(saveFile, data10,sizeof(float)*(mFurnacesize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        delete[] data5;
        delete[] data6;
        delete[] data7;
        delete[] data8;
        delete[] data9;
        delete[] data10;
    }


    mDirectsize = mDirects.size();
    gzwrite(saveFile, &mDirectsize,sizeof(int));

    if(mDirectsize != 0)
    {
        int* data1 = new int[mDirectsize];
        int* data2 = new int[mDirectsize];
        int* data3 = new int[mDirectsize];

        char* data4 = new char[mDirectsize];

        for(int k = 0; k < mDirectsize; k++)
        {
            DirectionBlock* SaveDirectionBlock = mDirects[k];

            data1[k] = SaveDirectionBlock->X;
            data2[k] = SaveDirectionBlock->Y;
            data3[k] = SaveDirectionBlock->Z;
            data4[k] = SaveDirectionBlock->direction;
        }

        gzwrite(saveFile, data1,sizeof(int) * (mDirectsize));
        gzwrite(saveFile, data2,sizeof(int) * (mDirectsize));
        gzwrite(saveFile, data3,sizeof(int) * (mDirectsize));
        gzwrite(saveFile, data4,sizeof(char)* (mDirectsize));

        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
    }
    //close file
    gzclose(saveFile);
    saveFile=0;
}

void CraftWorld::LoadWorld(const char *filename)
{
    FILE * pFile;
    pFile = fopen(filename,"rb");

    if(pFile == NULL)
        return;

    //version
    fread(&worldVersion,sizeof(int),1,pFile);

    //name
    fread(worldName,sizeof(char),50,pFile);

    //size
    fread(&WORLD_SIZE,sizeof(int),1,pFile);

    //chunksize
    fread(&CHUNK_SIZE,sizeof(int),1,pFile);

    //cubes
    m_Blocks = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    fread(m_Blocks,sizeof(unsigned char),(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE),pFile);

    //light
    m_BlockLight = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    fread(m_BlockLight,sizeof(unsigned char),(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE),pFile);

    m_BlockSettings = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    memset(m_BlockSettings, 0, sizeof(block_t) * WORLD_SIZE * WORLD_SIZE * WORLD_SIZE);

    //close file
    fclose(pFile);
}

void CraftWorld::LoadCompressedWorld(std::string  filename)
{
    //load normal save info
    FILE * pFile;
    pFile = fopen(filename.c_str(),"rb");

    if(pFile == NULL)
        return;

    //version
    fread(&worldVersion,sizeof(int),1,pFile);

    //name
    fread(worldName,sizeof(char),50,pFile);
    //close file
    fclose(pFile);

    //load compressed map data
    filename = filename + "c";

    //open file
    gzFile saveFile;
    saveFile = gzopen(filename.c_str(),"rb");
    if(saveFile == 0)
        return;

    //player pos
    gzread(saveFile, &playerPos.x,sizeof(float));
    gzread(saveFile, &playerPos.y,sizeof(float));
    gzread(saveFile, &playerPos.z,sizeof(float));

    //size
    gzread(saveFile, &WORLD_SIZE,sizeof(int));

    //chunksize
    gzread(saveFile, &CHUNK_SIZE,sizeof(int));

    //cubes
    m_Blocks = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    gzread(saveFile, m_Blocks,sizeof(unsigned char)*(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE));

    //light
    m_BlockLight = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    gzread(saveFile, m_BlockLight,sizeof(unsigned char)*(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE));

    //settings
    m_BlockSettings = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    if(worldVersion >= 3)
    {
        //settings
        gzread(saveFile, m_BlockSettings,sizeof(unsigned char)*(WORLD_SIZE * WORLD_SIZE * WORLD_SIZE));

        //world time
        gzread(saveFile, &worldDayTime,sizeof(float));

        //sun time
        gzread(saveFile, &sunTime,sizeof(float));

        gzread(saveFile, &mainStatistics,sizeof(st));

        gzread(saveFile, &mainOptions,sizeof(opt));

        gzread(saveFile, &invId,sizeof(int)*(36));

        gzread(saveFile, &invAm,sizeof(int)*(36));

        gzread(saveFile, &invSt,sizeof(bool)*(36));

        gzread(saveFile, &HP,sizeof(unsigned int));

        gzread(saveFile, &HG,sizeof(unsigned int));

        gzread(saveFile, &OS,sizeof(unsigned int));

        gzread(saveFile, &bright,sizeof(float));

        gzread(saveFile, &worldSeed,sizeof(int));

        gzread(saveFile, &skyTime,sizeof(float));

        gzread(saveFile, &mChestsize,sizeof(int));


        mChests.clear();

        if(mChestsize != 0)
        {
        int* data1 = new int[27*mChestsize];
        int* data2 = new int[27*mChestsize];
        bool* data3 = new bool[27*mChestsize];

        int* data4 = new int[mChestsize];
        int* data5 = new int[mChestsize];
        int* data6 = new int[mChestsize];

        gzread(saveFile, data1,sizeof(int)*(mChestsize*27));
        gzread(saveFile, data2,sizeof(int)*(mChestsize*27));
        gzread(saveFile, data3,sizeof(bool)*(mChestsize*27));

        gzread(saveFile, data4,sizeof(int)*(mChestsize));
        gzread(saveFile, data5,sizeof(int)*(mChestsize));
        gzread(saveFile, data6,sizeof(int)*(mChestsize));

        for(int k = 0; k < mChestsize; k++)
        {
            Chest* SaveChest = new Chest(-1,-1,-1);

            for(int l = 0; l <= 26; l++)
            {
                SaveChest->chestSlotId[l] = data1[k * 27 + l];
                SaveChest->chestSlotAm[l] = data2[k * 27 + l];
                SaveChest->chestSlotSt[l] = data3[k * 27 + l];
            }
            SaveChest->chestX = data4[k];
            SaveChest->chestY = data5[k];
            SaveChest->chestZ = data6[k];
            mChests.push_back(SaveChest);

            //delete SaveChest;
        }
        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        delete[] data5;
        delete[] data6;
        }


        gzread(saveFile, &mFurnacesize,sizeof(int));
        mFurnaces.clear();

        if(mFurnacesize != 0)
        {
        int* data1 = new int[3*mFurnacesize];
        int* data2 = new int[3*mFurnacesize];
        bool* data3 = new bool[3*mFurnacesize];

        int* data4 = new int[mFurnacesize];
        int* data5 = new int[mFurnacesize];
        int* data6 = new int[mFurnacesize];

        float* data7 = new float[mFurnacesize];
        float* data8 = new float[mFurnacesize];

        bool* data9 = new bool[mFurnacesize];

        int* data10 = new int[mFurnacesize];

        gzread(saveFile, data1,sizeof(int)*(mFurnacesize*3));
        gzread(saveFile, data2,sizeof(int)*(mFurnacesize*3));
        gzread(saveFile, data3,sizeof(bool)*(mFurnacesize*3));

        gzread(saveFile, data4,sizeof(int)*(mFurnacesize));
        gzread(saveFile, data5,sizeof(int)*(mFurnacesize));
        gzread(saveFile, data6,sizeof(int)*(mFurnacesize));

        gzread(saveFile, data7,sizeof(float)*(mFurnacesize));
        gzread(saveFile, data8,sizeof(float)*(mFurnacesize));

        gzread(saveFile, data10,sizeof(int)*(mFurnacesize));

        for(int k = 0; k < mFurnacesize; k++)
        {
            Furnace* SaveFurnace = new Furnace(-1,-1,-1);

            for(int l = 0; l <= 2; l++)
            {
                SaveFurnace->furnaceSlotId[l] = data1[k * 3 + l];
                SaveFurnace->furnaceSlotAm[l] = data2[k * 3 + l];
                SaveFurnace->furnaceSlotSt[l] = data3[k * 3 + l];
            }
            SaveFurnace->furnaceX = data4[k];
            SaveFurnace->furnaceY = data5[k];
            SaveFurnace->furnaceZ = data6[k];
            SaveFurnace->fuelTime = data7[k];
            SaveFurnace->meltingTime = data8[k];
            SaveFurnace->working = data9[k];
            SaveFurnace->smeltItemTemp = data10[k];
            mFurnaces.push_back(SaveFurnace);

            //delete SaveChest;
        }
        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        delete[] data5;
        delete[] data6;
        delete[] data7;
        delete[] data8;
        delete[] data9;
        delete[] data10;
        }

        gzread(saveFile, &mDirectsize,sizeof(int));
        mDirects.clear();

        if(mDirectsize != 0)
        {
        int* data1 = new int[mDirectsize];
        int* data2 = new int[mDirectsize];
        int* data3 = new int[mDirectsize];
        char* data4 = new char[mDirectsize];

        gzread(saveFile, data1,sizeof(int)*(mDirectsize));
        gzread(saveFile, data2,sizeof(int)*(mDirectsize));
        gzread(saveFile, data3,sizeof(int)*(mDirectsize));
        gzread(saveFile, data4,sizeof(char)*(mDirectsize));

        for(int k = 0; k < mDirectsize; k++)
        {
            DirectionBlock* SaveDirectionBlock = new DirectionBlock(-1,-1,-1,-1);

            SaveDirectionBlock->X = data1[k];
            SaveDirectionBlock->Y = data2[k];
            SaveDirectionBlock->Z = data3[k];
            SaveDirectionBlock->direction = data4[k];
            mDirects.push_back(SaveDirectionBlock);

            //delete SaveChest;
        }
        delete[] data1;
        delete[] data2;
        delete[] data3;
        delete[] data4;
        }


    }
    else
    {
        memset(m_BlockSettings, 0, sizeof(block_t) * WORLD_SIZE * WORLD_SIZE * WORLD_SIZE);
    }

    //close file
    gzclose(saveFile);
    saveFile=0;
}

void CraftWorld::initWorld(int worldSize,int chunkSize)
{
    //inicjuj mape
    WORLD_SIZE = worldSize;
    CHUNK_SIZE = chunkSize;

    m_Blocks = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    memset(m_Blocks, 0, sizeof(block_t) * WORLD_SIZE * WORLD_SIZE * WORLD_SIZE);

    m_BlockLight = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    memset(m_BlockLight, 255, sizeof(block_t) * WORLD_SIZE * WORLD_SIZE * WORLD_SIZE);

    m_BlockSettings = new block_t[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];
    memset(m_BlockSettings, 0, sizeof(block_t) * WORLD_SIZE * WORLD_SIZE * WORLD_SIZE);
}

void CraftWorld::initWorldBlocksLight()
{
    int x, y, z;
    block_t Light;
    block_t DeltaLight = 16;

    for (z = 0; z < WORLD_SIZE; ++z)
    {
        for (x = 0; x < WORLD_SIZE; ++x)
        {
            Light = 255;
            for (y = WORLD_SIZE - 1; y >= 0; --y)
            {
                if (Light < 16)
                {
                    Light = 16;
                }

                if (GetBlock(x, y, z) != 0)
                {
                    if (Light >= DeltaLight)
                    {
                        Light -= DeltaLight;
                    }

                if (BlockSolid(x+1, y, z) == 1 && GetBlock(x+1,y,z) == 4)
                {
                    Light -= DeltaLight*2;
                }
                if (BlockSolid(x-1, y, z) == 1 && GetBlock(x-1,y,z) == 4)
                {

                    Light -= DeltaLight*2;
                }
                if (BlockSolid(x, y, z+1) == 1 && GetBlock(x,y,z+1) == 4)
                {
                    Light -= DeltaLight*2;
                }
                if (BlockSolid(x, y, z-1) == 1 && GetBlock(x,y,z-1) == 4)
                {
                    Light -= DeltaLight*2;
                }

                if (Light < 16)
                {
                    Light = 16;
                }

                }
            GetBlockLight(x, y, z) = Light;
            }
        }
    }
}

void CraftWorld::initPutBlocksLight(const int x, const int z)
{
    int y;
    block_t Light;
    block_t DeltaLight = 16;

    Light = 255;
    for (y = WORLD_SIZE - 1; y >= 0; --y)
    {
        if (Light < 16)
        {
            Light = 16;
        }

        if (GetBlock(x, y, z) != 0)
        {
            if (Light >= DeltaLight)
            {
                Light -= DeltaLight;
            }
            if (BlockSolid(x+1, y, z) == 1 && GetBlock(x+1,y,z) == 4)
            {
                Light -= DeltaLight*2;
            }
            if (BlockSolid(x-1, y, z) == 1 && GetBlock(x-1,y,z) == 4)
            {
                Light -= DeltaLight*2;
            }
            if (BlockSolid(x, y, z+1) == 1 && GetBlock(x,y,z+1) == 4)
            {
                Light -= DeltaLight*2;
            }
            if (BlockSolid(x, y, z-1) == 1 && GetBlock(x,y,z-1) == 4)
            {
                Light -= DeltaLight*2;
            }

            if (Light < 16)
            {
                Light = 16;
            }
        }
        GetBlockLight(x, y, z) = Light;
    }
}

void CraftWorld::InitLightValues()
{
    lightAngle = 10;
    lightColor = Vector3(1, 1, 1);
    fogColor = lightColor * 0.8f;
    ambientColor = Vector3(0, 0, 0);

    //light face factors
    buildcloudsVerts();
}

void CraftWorld::SetWolrdTime(float time)
{
    //6am = SunRise
    //Light is symmetric about noon
    //4am-8am = dawn
    //4am color = (0.1, 0.1, 0.1)
    //6am color = (1, 0.6, 0.04)
    //8am color = (1, 1, 1)

    worldDayTime = time;//std::fmod(time, 24);

    lightAngle = worldDayTime / 24.0f * 360.0f - 90.0f;
    if (lightAngle < 0)lightAngle += 360.0f;

    if (worldDayTime <= 4 || worldDayTime >= 22)
    {
        lightColor = Vector3(0.1f, 0.1f, 0.1f);
    }
    else if (worldDayTime == 5)
    {
        lightColor = Vector3(0.1, 0.1, 0.1);
    }
    else if (worldDayTime == 6)
    {
        lightColor = Vector3(0.19, 0.19, 0.19);
    }
    else if (worldDayTime == 7)
    {
        lightColor = Vector3(0.35, 0.35, 0.35);
    }
    else if (worldDayTime == 8)
    {
        lightColor = Vector3(0.5, 0.5, 0.5);
    }
    else if (worldDayTime == 9)
    {
        lightColor = Vector3(0.7, 0.7, 0.7);
    }
    else if (worldDayTime == 10)
    {
        lightColor = Vector3(0.9, 0.9, 0.9);
    }
    else if (worldDayTime >= 11 && worldDayTime <= 13)
    {
        lightColor = Vector3(0.97, 0.97, 0.97);
    }
    else if (worldDayTime == 14)
    {
        lightColor = Vector3(0.97, 0.97, 0.97);
    }
    else if (worldDayTime == 15)
    {
        lightColor = Vector3(0.7, 0.7, 0.7);
    }
    else if (worldDayTime == 16)
    {
        lightColor = Vector3(0.4, 0.4, 0.4);
    }
    else if (worldDayTime == 17)
    {
        lightColor = Vector3(0.2, 0.2, 0.2);
    }
    else if (worldDayTime == 18)
    {
        lightColor = Vector3(0.15, 0.15, 0.15);
    }
    else if (worldDayTime == 19)
    {
        lightColor = Vector3(0.1, 0.1, 0.1);
    }
    else if (worldDayTime >= 20)
    {
        lightColor = Vector3(0.1, 0.1, 0.1);
    }
    else	//Shouldn't get here
    {
        lightColor = Vector3(1, 1, 1);
    }

    //ambientColor = lightColor / 3.0f;
    ambientColor = Vector3(0,0,0);
    buildcloudsVerts();
    //light face factors
}

void CraftWorld::buildMap()
{
    createWorldChunkss();
}

void CraftWorld::destroyMap()
{
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        mChunks[i]->reset();
    }

    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        mTransparentChunks[i]->reset();
    }
}

void CraftWorld::setTextureSize(int texture,int chunk)
{
    texutreSize = texture;
    textureChunk = chunk;

    percent = (float)textureChunk / (float)texutreSize;
}

block_t& CraftWorld::GetBlock (const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE];
    }
    return m_Blocks[0 + 0 * WORLD_SIZE + 0 * WORLD_SIZE * WORLD_SIZE];
}

block_t& CraftWorld::GetBlockLight (const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return m_BlockLight[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE];
    }
    return m_BlockLight[0 + 0 * WORLD_SIZE + 0 * WORLD_SIZE * WORLD_SIZE];
}

block_t& CraftWorld::GetBlockSettings(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return m_BlockSettings[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE];
    }
    return m_BlockSettings[0 + 0 * WORLD_SIZE + 0 * WORLD_SIZE * WORLD_SIZE];
}

void CraftWorld::CheckForTorchSupport(const int x, const int y, const int z,int blockID)
{
    for(int zz = z-1; zz < z+2; zz++)
    {
        for(int xx = x-1; xx < x+2; xx++)
        {
            for(int yy = y-1; yy < y+2; yy++)
            {
                if(GetBlock(xx,yy,zz) == Torch::getID())
                {
                    if(!CanPutBlockHere(xx,yy,zz,Torch::getID()))
                    {
                        GetBlock(xx,yy,zz) = 0;
                        RemoveLigtSourceAtPosition(xx,yy,zz,Torch::getID());
                    }
                }
            }
        }
    }
}

void CraftWorld::RemoveLigtSourceAtPosition(const int x, const int y, const int z,int blockID)
{
    if(blockID == JackOLantern::getID() || blockID == Torch::getID() || blockID == 112 || blockID == 107)
    {
        int current = 0;

        for(int zz = z-10; zz < z+10; zz++)
        {
            for(int xx = x-10; xx < x+10; xx++)
            {
                for(int yy = y-10; yy < y+10; yy++)
                {
                    if (xx >= 0 || yy >= 0 || zz >= 0  || xx < WORLD_SIZE || yy < WORLD_SIZE || zz < WORLD_SIZE)
                    {
                        if((GetBlockSettings(xx,yy,zz) & OpLighSource) != 0)
                        {
                            current = GetBlockSettings(xx,yy,zz) & 0xF;
                            GetBlockSettings(xx,yy,zz) ^= current & 0xF;
                            GetBlockSettings(xx,yy,zz) ^= 0 & 0xF;
                            //turn off light here
                            GetBlockSettings(xx,yy,zz) ^= OpLighSource;
                        }
                    }
                }
            }
        }

        BoundingBox lBox = BoundingBox(Vector3(x - 10,y - 10,z - 10),Vector3(x + 10,y + 10,z + 10));
        for(unsigned int i = 0; i < mChunks.size(); i++)
        {
            if(lBox.intersect(mChunks[i]->bBox))
                UpdateWorldLightForChunk(i);
        }

    }
}
bool CraftWorld::CanPutBlockHere(const int x, const int y, const int z,int blockID)
{
    if(blockID == Torch::getID())
    {
        bool canPlaseTorch = false;

        if(GetBlock(x,y-1,z) != 0 && GetBlock(x,y-1,z) != Torch::getID())
        {
            canPlaseTorch = true;
        }
        else if(GetBlock(x-1,y,z) != 0 && GetBlock(x-1,y,z) != Torch::getID())
        {
            canPlaseTorch = true;
        }
        else if(GetBlock(x+1,y,z) != 0 && GetBlock(x+1,y,z) != Torch::getID())
        {
            canPlaseTorch = true;
        }
        else if(GetBlock(x,y,z-1) != 0 && GetBlock(x,y,z-1) != Torch::getID())
        {
            canPlaseTorch = true;
        }
        else if(GetBlock(x,y,z+1) != 0 && GetBlock(x,y,z+1) != Torch::getID())
        {
            canPlaseTorch = true;
        }

        return canPlaseTorch;
    }

    return true;
}

void CraftWorld::LightTravel(int x,int y,int z,int steps,int lightLevel)
{
    if (x >= 0 && y >= 0 && z >= 0  && x < WORLD_SIZE && y < WORLD_SIZE && z < WORLD_SIZE && steps > 0 && lightLevel >= 0)
    {
        bool canGofuther = false;

        if(BlockSolid(x,y,z) == 1 && BlockTransparent(x,y,z) == false && GetBlock(x,y,z) != 107 && GetBlock(x,y,z) != 93 && GetBlock(x,y,z) != 59)
        {
            return;
        }

        //if((GetBlockSettings(x,y,z) & OpLightTraveled) == 0)//not traveled
        //{
        //mark traveled
        //GetBlockSettings(x,y,z) ^= OpLightTraveled;

        //if it's transparent block or light source...
        if(BlockTransparent(x,y,z) == true || GetBlock(x,y,z) == Torch::getID() || GetBlock(x,y,z) == Cake::getID() || GetBlock(x,y,z) == Lava::getID() || GetBlock(x,y,z) == 93 || (GetBlock(x,y,z) >= 125 && GetBlock(x,y,z) <= 128) || GetBlock(x,y,z) == 59 || GetBlock(x,y,z) == 107)
        {
            bool canGofuther = false;
            //check if it's lightened
            if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//lightened
            {
                //get current value
                int current = GetBlockSettings(x,y,z) & 0xF;
                //set new only if it's brighter
                if(current < lightLevel)
                {
                    //clear this value
                    GetBlockSettings(x,y,z) ^= current & 0xF;
                    //set new value
                    GetBlockSettings(x,y,z) ^= lightLevel & 0xF;

                    canGofuther = true;
                }
            }
            else
            {
                int current = GetBlockSettings(x,y,z) & 0xF;
                //clear thisBlockSolid(x,y,z) == 1 value
                GetBlockSettings(x,y,z) ^= current & 0xF;
                //set new value
                GetBlockSettings(x,y,z) ^= lightLevel & 0xF;
                //mark as lightened
                GetBlockSettings(x,y,z) ^= OpLighSource;

                canGofuther = true;
            }


            //go futher
            if(canGofuther)
            {
                LightTravel(x+1,y,z,steps-1,lightLevel-1);
                LightTravel(x-1,y,z,steps-1,lightLevel-1);
                LightTravel(x,y+1,z,steps-1,lightLevel-1);
                LightTravel(x,y-1,z,steps-1,lightLevel-1);
                LightTravel(x,y,z+1,steps-1,lightLevel-1);
                LightTravel(x,y,z-1,steps-1,lightLevel-1);
            }
        }
        //}
    }
}

void CraftWorld::SetLigtSourcePosition(const int x, const int y, const int z,int blockID)
{
    //put correct light based on lightsource type
    if(blockID == JackOLantern::getID() || blockID == Torch::getID() || blockID == 112 || blockID == 107)
    {
        LightTravel(x,y,z,10,11);
    }
}


bool CraftWorld::BlockTransparentOrSpecial(const int x, const int y, const int z)
{
    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE || y >= WORLD_SIZE || z >= WORLD_SIZE) return true;

    if(blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].transparent || blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].blockSpecial)
        return true;

    return false;
}

bool CraftWorld::BlockTransparentOrLightSource(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return (blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].transparent || blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].lightSource);
    }
}

bool CraftWorld::BlockTransparent(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].transparent;
    }
}

bool CraftWorld::BlockSpecial(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].blockSpecial;
    }
}

bool CraftWorld::BlockUpdate2(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].update;
    }
}

bool CraftWorld::BlockSolid(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].solid;
    }
}

short CraftWorld::BlockLoot(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].loot;
    }
}

short CraftWorld::BlockMaterial(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].material;
    }
}

bool CraftWorld::BlockEditable(const int x, const int y, const int z)
{
    if (x >= 0 && x < 128 && z >= 0 && z < 128 && y >= 0 && y < 128)
    {
        return blockTypes[m_Blocks[x + y * WORLD_SIZE + z * WORLD_SIZE * WORLD_SIZE]].editable;
    }
    return 0;
}

bool CraftWorld::LightSourceBlock(int id)
{
    return blockTypes[id].lightSource;
}

void CraftWorld::GetSpecialBlockVerts(int i,BaseBlock* blockType)
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector3*> mColour;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;

    if(i == 6 || i == 134 || i == 135 || i == 136) //Ladders
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+1, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == TrapDoor::getID())
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + ((percent / (float)textureChunk) * 3);


        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.2, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.2, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 3);

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.2, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.2, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;
        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+0.2, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.2, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.2, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+0.2, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 3);

        mPosition.push_back(new Vector3(x,   y+0.2, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.2, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 3);

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.2, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+0.2, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == Cake::getID())
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces

        //x
            up = down + ((percent / (float)textureChunk) * 8);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x, y, z+0.9));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5, z+0.9));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x
            down = 1.0f - percent * (blockType->textureRow + 1);


            up = down + ((percent / (float)textureChunk) * 8);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x+0.9, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.9, y+0.5, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.9, y+0.5, z+0.9));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.9, y,   z+0.9));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->downPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y, z+0.9));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+0.9));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->upPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x,   y+0.5, z+0.9));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y+0.5, z+0.9));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y+0.5, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+0.5, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

            down = 1.0f - percent * (blockType->textureRow + 1);


            up = down + ((percent / (float)textureChunk) * 8);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x,   y+0.5, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+0.9, y+0.5, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+0.9, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

            up = down + ((percent / (float)textureChunk) * 8);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x,   y,   z+0.9));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+0.9, y,   z+0.9));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+0.9, y+0.5, z+0.9));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+0.5, z+0.9));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == WoodenFence::getID())
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        float pixel = 1 / 16.0f;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces

        //x
        left = percent * blockType->sidePlane;
        right = left + ((percent / (float)textureChunk) * 4);
        up = down + percent;

        mPosition.push_back(new Vector3(x+pixel*6, y, z+pixel*10));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+pixel*6, y+1, z+pixel*10));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+pixel*6, y+1, z+pixel*6));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+pixel*6, y,   z+pixel*6));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + ((percent / (float)textureChunk) * 4);
        up = down + percent;

        mPosition.push_back(new Vector3(x+pixel*10, y,   z+pixel*6));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+pixel*10, y+1, z+pixel*6));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+pixel*10, y+1, z+pixel*10));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+pixel*10, y,   z+pixel*10));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;

        left = percent * blockType->sidePlane;
        right = left + ((percent / (float)textureChunk) * 4);
        up = down + ((percent / (float)textureChunk) * 4);

        mPosition.push_back(new Vector3(x+pixel*6,   y, z+pixel*6));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+pixel*10, y, z+pixel*6));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+pixel*10, y, z+pixel*10));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+pixel*6,   y, z+pixel*10));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->sidePlane;
        right = left + ((percent / (float)textureChunk) * 4);
        up = down + ((percent / (float)textureChunk) * 4);

        mPosition.push_back(new Vector3(x+pixel*6,   y+1, z+pixel*10));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+pixel*10, y+1, z+pixel*10));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+pixel*10, y+1, z+pixel*6));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+pixel*6,   y+1, z+pixel*6));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + ((percent / (float)textureChunk) * 4);
        up = down + percent;

        mPosition.push_back(new Vector3(x+pixel*6,   y+1, z+pixel*6));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+pixel*10, y+1, z+pixel*6));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+pixel*10, y,   z+pixel*6));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+pixel*6,   y,   z+pixel*6));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + ((percent / (float)textureChunk) * 4);
        up = down + percent;

        mPosition.push_back(new Vector3(x+pixel*6,   y,   z+pixel*10));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+pixel*10, y,   z+pixel*10));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+pixel*10, y+1, z+pixel*10));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+pixel*6,   y+1, z+pixel*10));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }



    if(i == Table::getID())
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces

        //x
        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 12);

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.65, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.65, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 12);

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.65, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.65, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;

        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+0.65, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.65, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.65, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+0.65, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 12);

        mPosition.push_back(new Vector3(x,   y+0.65, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.65, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 12);

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.65, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+0.65, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == Snow2::getID())
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 15);

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.05, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.05, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 15);

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.05, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.05, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;

        left = percent * blockType->downPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down

        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;

        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+0.05, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.05, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.05, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+0.05, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 15);

        mPosition.push_back(new Vector3(x,   y+0.05, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.05, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;
        up = down + ((percent / (float)textureChunk) * 15);

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.05, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+0.05, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == 25) //cacti
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+0.1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.1, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+0.9, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.9, y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.9, y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+0.9, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->downPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x+0.1,   y, z+0.1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y, z+0.1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y, z+0.9));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.1, y, z+0.9));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->upPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

        mPosition.push_back(new Vector3(x+0.1,   y+1, z+0.9));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y+1, z+0.9));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.9, y+1, z+0.1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+0.1,   y+1, z+0.1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z+0.1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+0.1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+0.1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z+0.1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y,   z+0.9));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+0.9));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+0.9));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+1, z+0.9));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == 74 || i == 122 || i == 123 || i == 124 || i == 100 || i == 131 || i == 132 || i == 133)
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane2;
        right = left + percent;

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+1, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane3;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane4;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }



    if(i == HalfBlock1::getID() || i == HalfBlock2::getID() || i == HalfBlock3::getID() || i == HalfBlock4::getID() || i == HalfBlock5::getID() || i == HalfBlock6::getID() || i == HalfBlock7::getID() || i == HalfBlock0::getID() || i == HalfBlock8::getID())
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + percent - ((percent / (float)textureChunk) * 8);

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.5, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.5, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        up = down + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+0.5, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.5, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.5, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+0.5, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + percent - ((percent / (float)textureChunk) * 8);

        mPosition.push_back(new Vector3(x,   y+0.5, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.5, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.5, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+0.5, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == 112 || i == 9)
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
            float BlockLight  = 0.5f;  //For the two x faces
            float BlockLight1 = 0.8f;		//For the two z faces
            float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        up = down + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+1, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }


    if(i == 125 || i == 60 || i == 67)
    {

        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent;

        float left = percent * blockType->upPlane;
        float right = left + percent;

        iVertex = 0;

        //light
        float BlockLight  = 0.5f;  //For the two x faces
        float BlockLight1 = 0.8f;		//For the two z faces
        float BlockLight2 = 1.0f;		//For the two y faces


        //x
        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + percent - ((percent / (float)textureChunk) * 8);

        mPosition.push_back(new Vector3(x, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.5, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.5, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        up = down + percent;

        mPosition.push_back(new Vector3(x,   y, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y, z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y, z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+0.5, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.5, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+0.5, z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+0.5, z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + percent - ((percent / (float)textureChunk) * 8);

        mPosition.push_back(new Vector3(x,   y+0.5, z));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.5, z));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y,   z));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + percent;

        mPosition.push_back(new Vector3(x,   y,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y,   z+1));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->upPlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z+1));
        mtextures.push_back(new Vector2(left, up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(right, up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x+1, y+1, z+0.5));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
        mPosition.push_back(new Vector3(x,   y+1, z+0.5));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x,   y+1, z+0.5));
        mtextures.push_back(new Vector2(right, up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+1, z+0.5));
        mtextures.push_back(new Vector2(left, up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x+1, y+0.5,   z+0.5));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
        mPosition.push_back(new Vector3(x,   y+0.5,   z+0.5));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x, y+0.5, z+1));
        mtextures.push_back(new Vector2(right - ((percent / (float)textureChunk) * 8), down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z+1));
        mtextures.push_back(new Vector2(right - ((percent / (float)textureChunk) * 8), up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+1, z+0.5));
        mtextures.push_back(new Vector2(left, up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x, y+0.5,z+0.5));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x

        left = percent * blockType->sidePlane;
        right = left + percent;

        mPosition.push_back(new Vector3(x+1, y+0.5,   z+0.5));
        mtextures.push_back(new Vector2(right - ((percent / (float)textureChunk) * 8), down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z+0.5));
        mtextures.push_back(new Vector2(right - ((percent / (float)textureChunk) * 8) , up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+1, z+1));
        mtextures.push_back(new Vector2(left, up - ((percent / (float)textureChunk) * 8)));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
        mPosition.push_back(new Vector3(x+1, y+0.5,   z+1));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;


        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }

    if(i == Torch::getID())
    {
        float down = 1.0f - percent * (blockType->textureRow + 1);
        float up = down + percent - ((percent / (float)textureChunk) * 6);

        float left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
        float right = left + ((percent / (float)textureChunk) * 2);

        //x-1
        mPosition.push_back(new Vector3(x + 0.45f,y			,z + 0.45f + 0.1f	));
        mtextures.push_back(new Vector2(right	, down));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f,y + 0.6f	,z + 0.45f + 0.1f	));
        mtextures.push_back(new Vector2(right	, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f,y + 0.6f	,z + 0.45f			));
        mtextures.push_back(new Vector2(left	, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f,y			,z + 0.45f			));
        mtextures.push_back(new Vector2(left	, down));
        mColour.push_back(new Vector3(1,1,1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //x+1
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y		,z + 0.45f));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y+ 0.6f,z + 0.45f));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y+ 0.6f,z + 0.45f + 0.1f));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y		,z + 0.45f + 0.1f));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(1,1,1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //z-1
        mPosition.push_back(new Vector3(x + 0.45f		, y + 0.6f	, z + 0.45f));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f, y + 0.6f	, z + 0.45f));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f, y			, z + 0.45f));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f		, y			, z + 0.45f));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(1,1,1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //z+1
        mPosition.push_back(new Vector3(x + 0.45f		, y			, z + 0.45f + 0.1f));
        mtextures.push_back(new Vector2(left, down));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f, y			, z + 0.45f + 0.1f));
        mtextures.push_back(new Vector2(right, down));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f + 0.1f, y + 0.6f	, z + 0.45f + 0.1f));
        mtextures.push_back(new Vector2(right, up));
        mColour.push_back(new Vector3(1,1,1));
        mPosition.push_back(new Vector3(x + 0.45f		, y + 0.6f	, z + 0.45f + 0.1f));
        mtextures.push_back(new Vector2(left, up));
        mColour.push_back(new Vector3(1,1,1));

        mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
        mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        left = percent * blockType->downPlane;
        right = left + percent;

            mPosition.push_back(new Vector3(x + 0.45f		,y,z + 0.45f + 0.1f));
            mtextures.push_back(new Vector2(left, up));
            mColour.push_back(new Vector3(1,1,1));
            mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y,z + 0.45f + 0.1f));
            mtextures.push_back(new Vector2(right, up));
            mColour.push_back(new Vector3(1,1,1));
            mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y,z + 0.45f));
            mtextures.push_back(new Vector2(right, down));
            mColour.push_back(new Vector3(1,1,1));
            mPosition.push_back(new Vector3(x + 0.45f		,y,z + 0.45f));
            mtextures.push_back(new Vector2(left, down));
            mColour.push_back(new Vector3(1,1,1));

            mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
            mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

        iVertex += 4;

        //y+1
        {
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 8);
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

            mPosition.push_back(new Vector3(x + 0.45f		,y + 0.6f,z + 0.45f + 0.1f));
            mtextures.push_back(new Vector2(left, up));
            mColour.push_back(new Vector3(1,1,1));
            mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y + 0.6f,z + 0.45f + 0.1f));
            mtextures.push_back(new Vector2(right, up));
            mColour.push_back(new Vector3(1,1,1));
            mPosition.push_back(new Vector3(x + 0.45f + 0.1f,y + 0.6f,z + 0.45f));
            mtextures.push_back(new Vector2(right, down));
            mColour.push_back(new Vector3(1,1,1));
            mPosition.push_back(new Vector3(x + 0.45f		,y + 0.6f,z + 0.45f));
            mtextures.push_back(new Vector2(left, down));
            mColour.push_back(new Vector3(1,1,1));

            mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
            mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

            iVertex += 4;
        }

        blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
            delete 		mTriangle[aa];
        mTriangle.clear();
    }
}

void CraftWorld::GetCloudsVerts(BaseBlock *blockType)
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector3*> mColour;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;

        iVertex = 0;

    if(blockTypes[141].vertices != NULL)
	{
	    free(blockTypes[141].vertices);
	}


        float BlockLight2 = 0.1;		//For the two y faces
        if (worldDayTime == 5)
        {
            BlockLight2 = 0.18;
        }
        if (worldDayTime == 6)
        {
            BlockLight2 = 0.3;
        }
        if (worldDayTime == 7)
        {
            BlockLight2 = 0.45;
        }
        if (worldDayTime == 8)
        {
            BlockLight2 = 0.65;
        }
        if (worldDayTime == 9)
        {
            BlockLight2 = 0.85;
        }
        if (worldDayTime >= 10 && worldDayTime <= 13)
        {
            BlockLight2 = 1;
        }
        if (worldDayTime == 14)
        {
            BlockLight2 = 0.87;
        }
        if (worldDayTime == 15)
        {
            BlockLight2 = 0.72;
        }
        if (worldDayTime == 16)
        {
            BlockLight2 = 0.46;
        }
        if (worldDayTime == 17)
        {
            BlockLight2 = 0.25;
        }
        if (worldDayTime == 18)
        {
            BlockLight2 = 0.18;
        }
        if (worldDayTime >= 19)
        {
            BlockLight2 = 0.1;
        }
        //ѕо часовой стрелке
        for(float l = 1; l <= 10; l += 1)
        {
            for(float j = 1; j <= 10; j += 1)//0-|-
            {
                mPosition.push_back(new Vector3(x+((l-1)*48),   y, z+((j-1)*48)));
                mtextures.push_back(new Vector2(0+(l-1)/64, 0+(j-1)/64));
                mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
                mPosition.push_back(new Vector3(x+(l*48), y, z+((j-1)*48)));
                mtextures.push_back(new Vector2(l/64, 0+(j-1)/64));
                mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
                mPosition.push_back(new Vector3(x+(l*48), y, z+(j*48)));
                mtextures.push_back(new Vector2(l/64, j/64));
                mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
                mPosition.push_back(new Vector3(x+((l-1)*48),   y, z+(j*48)));
                mtextures.push_back(new Vector2(0+(l-1)/64, j/64));
                mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

                mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
                mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

                iVertex += 4;
            }
        }




        blockTypes[141].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //build verts
        //vertices
        int vert = 0;
        unsigned int size =  mTriangle.size();
        for(unsigned int j = 0; j < size; j++)
        {
            blockTypes[141].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
            blockTypes[141].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
            blockTypes[141].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
            blockTypes[141].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
            blockTypes[141].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
            blockTypes[141].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
            vert++;

            blockTypes[141].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
            blockTypes[141].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
            blockTypes[141].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
            blockTypes[141].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
            blockTypes[141].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
            blockTypes[141].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
            vert++;

            blockTypes[141].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
            blockTypes[141].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
            blockTypes[141].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
            blockTypes[141].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
            blockTypes[141].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
            blockTypes[141].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
            vert++;
        }

        //clear the cache or there will be some errors
        sceKernelDcacheWritebackInvalidateRange(blockTypes[141].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
        //sceKernelDcacheWritebackInvalidateAll();

        for(unsigned int aa = 0; aa < mPosition.size(); aa++)
        {
            delete mPosition[aa];
            delete mtextures[aa];
            delete mColour[aa];
        }
        mPosition.clear();
        mtextures.clear();
        mColour.clear();

        for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
        {
            delete 	mTriangle[aa];
        }
        mTriangle.clear();
}


void CraftWorld::GetNormalBlockVerts(int i,BaseBlock *blockType)
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector3*> mColour;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;


    float down = 1.0f - percent * (blockType->textureRow + 1);
    float up = down + percent;

    float left = percent * blockType->upPlane;
    float right = left + percent;

    iVertex = 0;

    //light
    float BlockLight  = 0.5f;  //For the two x faces
    float BlockLight1 = 0.8f;		//For the two z faces
    float BlockLight2 = 1.0f;		//For the two y faces

    //x
    left = percent * blockType->sidePlane;
    right = left + percent;

    mPosition.push_back(new Vector3(x, y, z+1));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x, y+1, z+1));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x, y+1, z));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    //x

    left = percent * blockType->sidePlane;
    right = left + percent;

    mPosition.push_back(new Vector3(x+1, y,   z));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x+1, y+1, z));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x+1, y+1, z+1));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x+1, y,   z+1));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    //up
    left = percent * blockType->downPlane;
    right = left + percent;

    mPosition.push_back(new Vector3(x,   y, z));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
    mPosition.push_back(new Vector3(x+1, y, z));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
    mPosition.push_back(new Vector3(x+1, y, z+1));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
    mPosition.push_back(new Vector3(x,   y, z+1));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    //down
    left = percent * blockType->upPlane;
    right = left + percent;

    mPosition.push_back(new Vector3(x,   y+1, z+1));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
    mPosition.push_back(new Vector3(x+1, y+1, z+1));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
    mPosition.push_back(new Vector3(x+1, y+1, z));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));
    mPosition.push_back(new Vector3(x,   y+1, z));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight2,BlockLight2,BlockLight2));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    left = percent * blockType->sidePlane;
    right = left + percent;

    mPosition.push_back(new Vector3(x,   y+1, z));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
    mPosition.push_back(new Vector3(x+1, y+1, z));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
    mPosition.push_back(new Vector3(x+1, y,   z));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
    mPosition.push_back(new Vector3(x,   y,   z));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    left = percent * blockType->sidePlane;
    right = left + percent;

    mPosition.push_back(new Vector3(x,   y,   z+1));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
    mPosition.push_back(new Vector3(x+1, y,   z+1));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
    mPosition.push_back(new Vector3(x+1, y+1, z+1));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));
    mPosition.push_back(new Vector3(x,   y+1, z+1));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight1,BlockLight1,BlockLight1));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;


    blockTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
    //build verts
    //vertices
    int vert = 0;
    unsigned int size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
        blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
        blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
        blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
        blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
        blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
        blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
        blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
        blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
        blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
        blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        blockTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
        blockTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
        blockTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
        blockTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
        blockTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
        blockTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(blockTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
        delete mColour[aa];
    }
    mPosition.clear();
    mtextures.clear();
    mColour.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
        delete 		mTriangle[aa];
    mTriangle.clear();
}

void CraftWorld::GetItemVerts(int i,BaseItem *itemType)
{
    std::vector<Vector3*> mPosition;
    std::vector<Vector3*> mColour;
    std::vector<Vector2*> mtextures;
    std::vector<Vector3*> mTriangle;

    int iVertex = 0;

    float x = -0.5f;
    float y = -0.5f;
    float z = -0.5f;


    float down = 1.0f - percent * (itemType->textureRow + 1);
    float up = down + percent;

    float left = percent * itemType->plane;
    float right = left + percent;

    iVertex = 0;

    //light
    float BlockLight  = 1.0f;  //For the two x faces

    mPosition.push_back(new Vector3(x,   y,   z+1));
    mtextures.push_back(new Vector2(left, down));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x+1, y,   z+1));
    mtextures.push_back(new Vector2(right, down));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x+1, y+1, z+1));
    mtextures.push_back(new Vector2(right, up));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));
    mPosition.push_back(new Vector3(x,   y+1, z+1));
    mtextures.push_back(new Vector2(left, up));
    mColour.push_back(new Vector3(BlockLight,BlockLight,BlockLight));

    mTriangle.push_back(new Vector3(iVertex, iVertex+1, iVertex+2));
    mTriangle.push_back(new Vector3(iVertex+2, iVertex+3, iVertex));

    iVertex += 4;

    itemTypes[i].vertices = (CraftPSPVertex*)memalign(16,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
    //build verts
    //vertices
    int vert = 0;
    unsigned int size =  mTriangle.size();
    for(unsigned int j = 0; j < size; j++)
    {
        itemTypes[i].vertices[vert].u = mtextures[mTriangle[j]->x]->x;
        itemTypes[i].vertices[vert].v = mtextures[mTriangle[j]->x]->y;
        itemTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->x]->x,mColour[mTriangle[j]->x]->y,mColour[mTriangle[j]->x]->z,1.0f);
        itemTypes[i].vertices[vert].x = mPosition[mTriangle[j]->x]->x;
        itemTypes[i].vertices[vert].y = mPosition[mTriangle[j]->x]->y;
        itemTypes[i].vertices[vert].z = mPosition[mTriangle[j]->x]->z;
        vert++;

        itemTypes[i].vertices[vert].u = mtextures[mTriangle[j]->y]->x;
        itemTypes[i].vertices[vert].v = mtextures[mTriangle[j]->y]->y;
        itemTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->y]->x,mColour[mTriangle[j]->y]->y,mColour[mTriangle[j]->y]->z,1.0f);
        itemTypes[i].vertices[vert].x = mPosition[mTriangle[j]->y]->x;
        itemTypes[i].vertices[vert].y = mPosition[mTriangle[j]->y]->y;
        itemTypes[i].vertices[vert].z = mPosition[mTriangle[j]->y]->z;
        vert++;

        itemTypes[i].vertices[vert].u = mtextures[mTriangle[j]->z]->x;
        itemTypes[i].vertices[vert].v = mtextures[mTriangle[j]->z]->y;
        itemTypes[i].vertices[vert].color = GU_COLOR( mColour[mTriangle[j]->z]->x,mColour[mTriangle[j]->z]->y,mColour[mTriangle[j]->z]->z,1.0f);
        itemTypes[i].vertices[vert].x = mPosition[mTriangle[j]->z]->x;
        itemTypes[i].vertices[vert].y = mPosition[mTriangle[j]->z]->y;
        itemTypes[i].vertices[vert].z = mPosition[mTriangle[j]->z]->z;
        vert++;
    }

    //clear the cache or there will be some errors
    sceKernelDcacheWritebackInvalidateRange(itemTypes[i].vertices,( mTriangle.size() * 3) * sizeof(CraftPSPVertex));
    //sceKernelDcacheWritebackInvalidateAll();

    for(unsigned int aa = 0; aa < mPosition.size(); aa++)
    {
        delete mPosition[aa];
        delete mtextures[aa];
        delete mColour[aa];
    }
    mPosition.clear();
    mtextures.clear();
    mColour.clear();

    for(unsigned int aa = 0; aa < mTriangle.size(); aa++)
        delete 		mTriangle[aa];
    mTriangle.clear();
}

void CraftWorld::buildblocksVerts()
{
    for(unsigned int i = 0; i < itemTypes.size(); i++)
    {
        BaseItem *itemType = &itemTypes[i];
        GetItemVerts(i,itemType);
    }
    //create vertices for each block type
    for(unsigned int i = 1; i < blockTypes.size(); i++)
    {
        BaseBlock *blockType = &blockTypes[i];
        if(blockType->blockSpecial)
            GetSpecialBlockVerts(i,blockType);
        else
            GetNormalBlockVerts(i,blockType);
    }

}

void CraftWorld::buildcloudsVerts()
{
    BaseBlock *blockType = &blockTypes[141];
    GetCloudsVerts(blockType);
}

void CraftWorld::createChunks(const int StartX, const int StartY, const int StartZ)
{
    SimpleMeshChunk* MeshChunk = new SimpleMeshChunk();

    int iVertex = 0;
    block_t Block;

    /* Only create visible faces of each chunk */
    MeshChunk->chunkStartZ = StartZ;
    MeshChunk->chunkStartY = StartY;
    MeshChunk->chunkStartX = StartX;

    MeshChunk->bBox = BoundingBox(Vector3(StartX,StartY,StartZ),Vector3(StartX + CHUNK_SIZE,StartY + CHUNK_SIZE,StartZ + CHUNK_SIZE));

    //if we are in player zone on the start then build map
    if(playerZoneBB.intersect(MeshChunk->bBox))
    {
        createdChunksCount++;
        //light
        for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
        {
            for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
            {
                for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
                {
                    Block = GetBlock(x,y,z);
                    if(BlockTransparent(x,y,z) == true)continue;//if block is transparent don't continue

                    if(!BlockSpecial(x,y,z))
                        GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,false);
                    else
                        GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,false);
                }
            }
        }

        MeshChunk->end();
    }
    else
    {
        MeshChunk->end();
        MeshChunk->created = false;
    }

    MeshChunk->id = mChunks.size();
    mChunks.push_back(MeshChunk);
}


void CraftWorld::createTransparentChunks(const int StartX, const int StartY, const int StartZ)
{
    SimpleMeshChunk* MeshChunk = new SimpleMeshChunk();

    int iVertex = 0;
    block_t Block;

    MeshChunk->chunkStartZ = StartZ;
    MeshChunk->chunkStartY = StartY;
    MeshChunk->chunkStartX = StartX;

    MeshChunk->bBox = BoundingBox(Vector3(StartX,StartY,StartZ),Vector3(StartX + CHUNK_SIZE,StartY + CHUNK_SIZE,StartZ + CHUNK_SIZE));

    //if we are in player zone on the start then build map
    if(playerZoneBB.intersect(MeshChunk->bBox))
    {
        for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
        {
            for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
            {
                for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
                {
                    Block = GetBlock(x,y,z);
                    if (BlockTransparent(x,y,z) == false || Block == 0) continue;

                    if(!BlockSpecial(x,y,z))
                        GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,true);
                    else
                        GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,true);
                }
            }
        }
        MeshChunk->end();
    }
    else
    {
        MeshChunk->end();
        MeshChunk->created = false;
    }

    //MeshChunk->end();
    MeshChunk->id = mChunks.size();
    mTransparentChunks.push_back(MeshChunk);
}

void CraftWorld::rebuildChunk(int id)
{
    SimpleMeshChunk* MeshChunk = mChunks[id];

    int iVertex = 0;
    block_t Block;

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    MeshChunk->reset();

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                Block = GetBlock(x,y,z);
                if(BlockTransparent(x,y,z) == true)continue;//if block is transparent don't continue

                if(!BlockSpecial(x,y,z))
                {
                    GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,false);
                }
                else
                {
                    GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,false);
                }
            }
        }
    }

    MeshChunk->end();
}

void CraftWorld::rebuildTransparentChunk(int id)
{
    SimpleMeshChunk* MeshChunk = mTransparentChunks[id];

    int iVertex = 0;
    block_t Block;

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    MeshChunk->reset();

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                Block = GetBlock(x,y,z);
                if (BlockTransparent(x,y,z) == false || Block == 0) continue;

                if(!BlockSpecial(x,y,z))
                    GetNormalBlock(x,y,z,iVertex,MeshChunk,Block,true);
                else
                    GetSpecialBlock(x,y,z,iVertex,MeshChunk,Block,true);
            }
        }
    }

    MeshChunk->end();
}

void CraftWorld::GetSpecialBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent)
{

        /* Only create visible faces of each chunk */
    bool DefaultBlock = false;
    bool transparentBlock;

    block_t Block1 = 0;

    Vector3 light1,light2,light3,light4;
    float BaseLight = 1.0f;

    Vector3 BlockColory1;    //Top face
    Vector3 BlockColory2;    //Bottom face
    Vector3 BlockColorx1;    //Sunset face
    Vector3 BlockColorx2;    //Sunrise face
    Vector3 BlockColorz1;     //Front/back faces
    Vector3 BlockColorz2;     //Front/back faces

    //texture stuff
    BaseBlock *blockType = &blockTypes[Block];

    float down = 1.0f - percent * (blockType->textureRow + 1);
    float up = down + percent;

    float left = percent * blockType->upPlane;
    float right = left + percent;

    bool canCreate = false;

        //lightened
        //if time is between 21-4 use settings table for lightening
        //if time is between 5-20 use normal light table but compare it with settings table
    if(worldDayTime >= 21 || worldDayTime <= 4)//night
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            BaseLight  = (float)(GetBlockSettings(x, y, z) & 0xF)/16.0f; // 255.0f;  //For the two x faces

            BlockColorx1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.95f;
            BlockColorz1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.70f;
            BlockColory1 = BlockColory2 = Vector3(BaseLight,BaseLight,BaseLight);
        }
        else //normal light
        {
            //light
            BaseLight  = GetBlockLight(x, y, z) / 255.0f;  //For the two x faces
            //float BlockLight1 = BlockLight * 0.9f;		//For the two z faces
            //float BlockLight2 = BlockLight * 0.8f;		//For the two y faces

            BlockColory1 = lightColor * BaseLight;
            BlockColory2 = lightColor * BaseLight * 0.5f;

            BlockColorz1  = lightColor * BaseLight;
            BlockColorz1 *= 0.70f;

            BlockColorx1 = lightColor * BaseLight;
            BlockColorx1 *= 0.95f;
        }
    }
    else //day
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            //int normal = GetBlockLight(x, y, z);
            //int lightened = (GetBlockSettings(x, y, z) & 0xF) * 16;

            float normal = lightColor.x + ambientColor.x;
            float lightened = (GetBlockSettings(x, y, z) & 0xF) / 15.0f;

            if(lightened > normal)
            {
                BaseLight = lightened; // 255.0f;
                BlockColorx1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.95f;
                BlockColorz1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.75f;
                BlockColory1 = BlockColory2 = Vector3(BaseLight,BaseLight,BaseLight);
            }
            else
            {
                BaseLight  = GetBlockLight(x, y, z) / 255.0f;

                BlockColory1 = lightColor * BaseLight;
                BlockColory2 = lightColor  * BaseLight * 0.5;

                BlockColorz1  = lightColor * BaseLight;
                BlockColorz1 *= 0.70f;

                BlockColorx1 = lightColor * BaseLight;
                BlockColorx1 *= 0.95f;

            }

        }
        else
        {
            BaseLight  = (float)GetBlockLight(x, y, z) / 255.0f;

            BlockColory1 = lightColor * BaseLight;
            BlockColory2 = lightColor * 0.5f * BaseLight;

            BlockColorz1  = lightColor * BaseLight;
            BlockColorz1 *= 0.70f;

            BlockColorx1 = lightColor * BaseLight;
            BlockColorx1 *= 0.95f;

        }
    }

    BlockColorz2 = BlockColorz1;
    BlockColorx2 = BlockColorx1;

    if( Block == Cake::getID())
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up

            MeshChunk->position(x+0.0625, y,   z+0.9375);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.0625, y+0.5, z+0.9375);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.0625, y+0.5, z+0.0625);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.0625, y,   z+0.0625);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = true;


        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+0.9, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+0.9375, y,   z+0.0625);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.9375, y+0.5, z+0.0625);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.9375, y+0.5, z+0.9375);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9375, y,   z+0.9375);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->downPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            if((GetBlockSettings(x,y-0.5,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x+0.0625,   y, z+0.0625);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.9375, y, z+0.0625);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9375, y, z+0.9375);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.0625,   y, z+0.9375);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;
            //down
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->upPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            MeshChunk->position(x+0.0625,   y+0.5, z+0.9375);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.9375, y+0.5, z+0.9375);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9375, y+0.5, z+0.0625);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.0625,   y+0.5, z+0.0625);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-0.9);
                Block1 = GetBlock(x,y,z-0.9);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-0.9);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            down = 1.0f - percent * (blockType->textureRow + 1);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            up = down + percent - ((percent / (float)textureChunk) * 8);


            if((GetBlockSettings(x,y,z-0.9) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            //up

            MeshChunk->position(x+0.0625,   y+0.5, z+0.0625);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9375, y+0.5, z+0.0625);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.9375, y,   z+0.0625);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.0625,   y,   z+0.0625);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+0.9);
                Block1 = GetBlock(x,y,z+0.9);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+0.9);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            down = 1.0f - percent * (blockType->textureRow + 1);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            up = down + percent - ((percent / (float)textureChunk) * 8);


            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x+0.0625,   y,   z+0.9375);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.9375, y,   z+0.9375);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.9375, y+0.5, z+0.9375);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.0625,   y+0.5, z+0.9375);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// WATER & LAVA
    if( Block == 4 || Block == 112)
    {
        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if (x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
        {
            if (GetBlock(x-1,y,z) == 0)
            {
                canCreate = true;
            }
        }


        if (canCreate)
        {
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->sidePlane;
            right = left + percent;

            //up = down + percent - ((percent / (float)textureChunk) * 1);
            //down = 1.0f - percent * (blockType->textureRow + 1);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            if(GetBlock(x,y,z) == 4)
            {
                if(GetBlock(x,y+1,z) != 4)
                {
                    MeshChunk->position(x, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x, y+0.875, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x, y+0.875, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                }
                else
                {
                    MeshChunk->position(x, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x, y+1, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x, y+1, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);

                }
            }


            if(GetBlock(x,y,z) == 112)
            {
                if(GetBlock(x,y+1,z) != 112)
                {
                    MeshChunk->position(x, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x, y+0.875, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x, y+0.875, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                }
                else
                {
                    MeshChunk->position(x, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x, y+1, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x, y+1, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);

                }
            }

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;

        if (x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
        {
            if (GetBlock(x+1,y,z) == 0)
            {
                canCreate = true;
            }
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 14);

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;

            if(GetBlock(x,y,z) == 4)
            {
                if(GetBlock(x,y+1,z) != 4)
                {
                MeshChunk->position(x+1, y,   z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+1, y+0.875, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+1, y+0.875, z+1);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+1, y,   z+1);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                }
                else
                {
                MeshChunk->position(x+1, y,   z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+1, y+1, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+1, y+1, z+1);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+1, y,   z+1);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                }
            }

            if(GetBlock(x,y,z) == 112)
            {
                if(GetBlock(x,y+1,z) != 112)
                {
                MeshChunk->position(x+1, y,   z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+1, y+0.875, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+1, y+0.875, z+1);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+1, y,   z+1);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                }
                else
                {
                MeshChunk->position(x+1, y,   z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+1, y+1, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+1, y+1, z+1);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+1, y,   z+1);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                }
            }

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if (x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
        {
            if (GetBlock(x,y-1,z) == 0)
            {
                canCreate = true;
            }
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;

            if((GetBlockSettings(x,y-0.05,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if(GetBlock(x,y,z) == 4)
        {
        if(GetBlock(x,y+1,z) != 4)
        {
        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;

        if (x >= 0 && x <= 127 && z >= 0 && z <= 127 && y >= 0 && y <= 127)
        {
            if (GetBlock(x,y+1,z) == 0)
            {
                canCreate = true;
            }
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;
            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;


                MeshChunk->position(x,   y+0.875f, z+1);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+1, y+0.875f, z+1);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+1, y+0.875f, z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+0.875f, z);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
        }
        }

        if(GetBlock(x,y,z) == 112)
        {
        if(GetBlock(x,y+1,z) != 112)
        {
        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if (x >= 0 && x <= 127 && z >= 0 && z <= 127 && y >= 0 && y <= 127)
        {
            if (GetBlock(x,y+1,z) == 0)
            {
                canCreate = true;
            }
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;


                MeshChunk->position(x,   y+0.875f, z+1);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+1, y+0.875f, z+1);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+1, y+0.875f, z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+0.875f, z);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
        }

        }




        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if (x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
        {
            if (GetBlock(x,y,z-1) == 0)
            {
                canCreate = true;
            }
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 14);

            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;
            //up
            if(GetBlock(x,y,z) == 4)
            {
                if(GetBlock(x,y+1,z) != 4)
                {
                    MeshChunk->position(x,   y+0.875, z);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x+1, y+0.875, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x+1, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x,   y,   z);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                }
                else
                {
                    MeshChunk->position(x,   y+1, z);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x+1, y+1, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x+1, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x,   y,   z);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                }
            }

                        //up
            if(GetBlock(x,y,z) == 112)
            {
                if(GetBlock(x,y+1,z) != 112)
                {
                    MeshChunk->position(x,   y+0.875, z);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x+1, y+0.875, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x+1, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x,   y,   z);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                }
                else
                {
                    MeshChunk->position(x,   y+1, z);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                    MeshChunk->position(x+1, y+1, z);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x+1, y,   z);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x,   y,   z);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                }
            }



            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;

        if (x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
        {
            if (GetBlock(x,y,z+1) == 0)
            {
                canCreate = true;
            }
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 14);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up
            if(GetBlock(x,y,z) == 4)
            {
                if(GetBlock(x,y+1,z) != 4)
                {
                    MeshChunk->position(x,   y,   z+1);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x+1, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x+1, y+0.875, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x,   y+0.875, z+1);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                }
                else
                {
                    MeshChunk->position(x,   y,   z+1);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x+1, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x+1, y+1, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x,   y+1, z+1);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                }
            }


            if(GetBlock(x,y,z) == 112)
            {
                if(GetBlock(x,y+1,z) != 112)
                {
                    MeshChunk->position(x,   y,   z+1);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x+1, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x+1, y+0.875, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x,   y+0.875, z+1);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                }
                else
                {
                    MeshChunk->position(x,   y,   z+1);
                    MeshChunk->textureCoord(left, down);
                    MeshChunk->colour(light1.x,light1.y,light1.z);
                    MeshChunk->position(x+1, y,   z+1);
                    MeshChunk->textureCoord(right, down);
                    MeshChunk->colour(light3.x,light3.y,light3.z);
                    MeshChunk->position(x+1, y+1, z+1);
                    MeshChunk->textureCoord(right, up);
                    MeshChunk->colour(light4.x,light4.y,light4.z);
                    MeshChunk->position(x,   y+1, z+1);
                    MeshChunk->textureCoord(left, up);
                    MeshChunk->colour(light2.x,light2.y,light2.z);
                }
            }

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }


    /// SNOW COVER
    if( Block == Snow2::getID())
    {

    if(worldDayTime >= 21 || worldDayTime <= 4)//night
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            BaseLight  = (float)(GetBlockSettings(x, y, z) & 0xF)/16.0f; // 255.0f;  //For the two x faces

            BlockColorx1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.95f;
            BlockColorz1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.70f;
            BlockColory1 = BlockColory2 = Vector3(BaseLight,BaseLight,BaseLight);
        }
        else //normal light
        {
            //light
            BaseLight  = GetBlockLight(x, y, z) / 255.0f;  //For the two x faces
            //float BlockLight1 = BlockLight * 0.9f;		//For the two z faces
            //float BlockLight2 = BlockLight * 0.8f;		//For the two y faces

            BlockColory1 = lightColor * (BaseLight);
            BlockColory2 = lightColor * (BaseLight) * 0.5f;

            BlockColorz1  = lightColor * (BaseLight);
            BlockColorz1 *= 0.70f;

            BlockColorx1 = lightColor * (BaseLight);
            BlockColorx1 *= 0.95f;
        }
    }
    else //day
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            //int normal = GetBlockLight(x, y, z);
            //int lightened = (GetBlockSettings(x, y, z) & 0xF) * 16;

            float normal = lightColor.x  + ambientColor.x;
            float lightened = (GetBlockSettings(x, y, z) & 0xF) / 15.0f;

            if(lightened > normal)
            {
                BaseLight = lightened; // 255.0f;
                BlockColorx1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.95f;
                BlockColorz1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.75f;
                BlockColory1 = BlockColory2 = Vector3(BaseLight,BaseLight,BaseLight);
            }
            else
            {
                BaseLight  = GetBlockLight(x, y, z) / 255.0f;

                BlockColory1 = lightColor * BaseLight;
                BlockColory2 = lightColor  * BaseLight * 0.5;

                BlockColorz1  = lightColor * BaseLight;
                BlockColorz1 *= 0.70f;

                BlockColorx1 = lightColor * BaseLight;
                BlockColorx1 *= 0.95f;

            }

        }
        else
        {
            BaseLight  = GetBlockLight(x, y, z) / 255.0f;

            BlockColory1 = lightColor * BaseLight;
            BlockColory2 = lightColor * 0.5 * BaseLight;

            BlockColorz1  = lightColor * BaseLight;
            BlockColorz1 *= 0.70f;

            BlockColorx1 = lightColor * BaseLight;
            BlockColorx1 *= 0.95f;

        }
    }

    BlockColorz2 = BlockColorz1;
    BlockColorx2 = BlockColorx1;

        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;

        if (x > 0)transparentBlock = BlockTransparent(x-1,y,z);
        if (transparentBlock == true)
        {
            canCreate = true;
        }


        if (canCreate)
        {
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane;
            right = left + percent;

            //up = down + percent - ((percent / (float)textureChunk) * 1);
            //down = 1.0f - percent * (blockType->textureRow + 1);

        if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+0.125, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+0.125, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;

        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparent(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 2);

        if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //simple shadows
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.125, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.125, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        canCreate = false;
        transparentBlock = BlockTransparent(x,y-1,z);
        if (y > 0)
        {
            if (transparentBlock == true && GetBlock(x,y-1,z) != 9)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;

            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;
            //simple shadows

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;
            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;

            MeshChunk->position(x,   y+0.125, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.125, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.125, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.125, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;

        {
            if (z > 0)transparentBlock = BlockTransparent(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 2); //percent / texturechunk = 1 pixel ; percent = 1 block

        if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;

            //up

            MeshChunk->position(x,   y+0.125, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.125, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;

        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparent(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 2);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;
            //up

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.125, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+0.125, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }


    if( Block == Table::getID())
    {
        up = down + percent;
        down = 1.0f - percent * (blockType->textureRow + 1);
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 4);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up

            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+0.75, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+0.75, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 4);

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.75, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.75, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-1,z);
                Block1 = GetBlock(x,y-1,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.65,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;

            if((GetBlockSettings(x,y-0.65,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-0.65, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.75,z);
                Block1 = GetBlock(x,y+0.75,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+1,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;
            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;

            MeshChunk->position(x,   y+0.75, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.75, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.75, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.75, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            down = 1.0f - percent * (blockType->textureRow + 1);

            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 4);

            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+0.75, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.75, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            down = 1.0f - percent * (blockType->textureRow + 1);
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 4);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.75, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+0.75, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// MULTI-TILED BLOCKS (CHESTS, PUMPKINS, FURNACES)
    if(Block == 74 || Block == 122 || Block == 123 || Block == 124 || Block == 100 || Block == 131 || Block == 132 || Block == 133 || (Block >= 106 && Block <= 109))
    {
        down = 1.0f - percent * (blockType->textureRow + 1);
        up = down + percent;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane2;
            right = left + percent;

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-0.5, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory2 * lightShadowFactor;

                //simple shadows
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
                {
                    light4-=lightFactor;
                }
            }

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory1 * lightShadowFactor;
                //simple shadows
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light4-=lightFactor;
                }
            }
            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            MeshChunk->position(x,   y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+1, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane3;
            right = left + percent;

            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            MeshChunk->position(x,   y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane4;
            right = left + percent;

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;

                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light3-=lightFactor;
                }
            }

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// HALF BLOCKS
    if(Block == HalfBlock1::getID() || Block == HalfBlock2::getID() || Block == HalfBlock3::getID() || Block == HalfBlock4::getID() || Block == HalfBlock5::getID() || Block == HalfBlock6::getID() || Block == HalfBlock7::getID() || Block == HalfBlock0::getID() || Block == HalfBlock8::getID())
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }
            //up
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorx1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            up = down + percent;


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory2 * lightShadowFactor;

                //simple shadows
                if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
                {
                    light4-=lightFactor;
                }
            }

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColory1 * lightShadowFactor;
                //simple shadows
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
                {
                    light3-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
                {
                    light4-=lightFactor;
                }
            }

            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;
                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
                {
                    light2-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
                {
                    light3-=lightFactor;
                }
            }

            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up
            if(mainOptions.fakeShadowsRendering == true)
            {
                lightFactor = BlockColorz1 * lightShadowFactor;

                //simple shadows
                //up
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
                {
                    light2-=lightFactor;
                }
                if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
                {
                    light4-=lightFactor;
                }

                //down
                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
                {
                    light1-=lightFactor;
                }

                if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
                {
                    light3-=lightFactor;
                }
            }

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }


    /// FENCE
    if(Block == WoodenFence::getID())
    {
        float pixel = 1/16.0f;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + ((percent / (float)textureChunk) * 4);

            up = down + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x+pixel*6, y,   z+pixel*10);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*6, y+1, z+pixel*10);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*6, y+1, z+pixel*6);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*6, y,   z+pixel*6);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + ((percent / (float)textureChunk) * 4);

            up = down + percent;
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+pixel*10, y,   z+pixel*6);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*10, y+1, z+pixel*6);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*10, y+1, z+pixel*10);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*10, y,   z+pixel*10);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->sidePlane;
            right = left + ((percent / (float)textureChunk) * 4);

            up = down + ((percent / (float)textureChunk) * 4);


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x+pixel*6,   y, z+pixel*6);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*10, y, z+pixel*6);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*10, y, z+pixel*10);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*6,   y, z+pixel*10);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->sidePlane;
            right = left + ((percent / (float)textureChunk) * 4);

            up = down + ((percent / (float)textureChunk) * 4);

            MeshChunk->position(x+pixel*6,   y+1, z+pixel*10);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*10, y+1, z+pixel*10);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*10, y+1, z+pixel*6);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*6,   y+1, z+pixel*6);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + ((percent / (float)textureChunk) * 4);

            up = down + percent;
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x+pixel*6,   y+1, z+pixel*6);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*10, y+1, z+pixel*6);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*10, y,   z+pixel*6);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*6,   y,   z+pixel*6);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + ((percent / (float)textureChunk) * 4);

            up = down + percent;

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x+pixel*6,   y,   z+pixel*10);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*10, y,   z+pixel*10);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*10, y+1, z+pixel*10);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*6,   y+1, z+pixel*10);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if(BlockSolid(x,y,z-1) == true)
        {
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx2;
                //up
                MeshChunk->position(x+pixel*7, y+pixel*12,   z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*7, y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*7, y+pixel*15, z);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*7, y+pixel*12,   z);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx2;
                //up
                MeshChunk->position(x+pixel*7, y+pixel*6,   z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*7, y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*7, y+pixel*9, z);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*7, y+pixel*6,   z);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //x+1
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx1;
                //up

                MeshChunk->position(x+pixel*9, y+pixel*12,   z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*12,   z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

                        //x+1
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx1;
                //up

                MeshChunk->position(x+pixel*9, y+pixel*6,   z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*6,   z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);


                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x+pixel*7,   y+pixel*12, z);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*12, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*12, z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*12, z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);


                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x+pixel*7,   y+pixel*6, z);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*6, z);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*6, z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*6, z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //top face
            //y+1
            transparentBlock = DefaultBlock;

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);

                MeshChunk->position(x+pixel*7,   y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*15, z);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);

                MeshChunk->position(x+pixel*7,   y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*9, z);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }
        }

        if(BlockSolid(x,y,z+1) == true)
        {
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx2;
                //up
                MeshChunk->position(x+pixel*7, y+pixel*12,   z+pixel*16);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*7, y+pixel*15, z+pixel*16);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*7, y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*7, y+pixel*12,   z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx2;
                //up
                MeshChunk->position(x+pixel*7, y+pixel*6,   z+pixel*16);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*7, y+pixel*9, z+pixel*16);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*7, y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*7, y+pixel*6,   z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //x+1
            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx1;
                //up

                MeshChunk->position(x+pixel*9, y+pixel*12,   z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z+pixel*16);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*12,   z+pixel*16);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

                        //x+1

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                    if(lightened > BlockColorx2.x)
                        BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorx1;
                //up

                MeshChunk->position(x+pixel*9, y+pixel*6,   z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z+pixel*16);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*6,   z+pixel*16);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //y-1

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);

                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x+pixel*7,   y+pixel*12, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*12, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*12, z+pixel*16);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*12, z+pixel*16);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

                        //y-1

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);

                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x+pixel*7,   y+pixel*6, z+pixel*8);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*6, z+pixel*8);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*6, z+pixel*16);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*6, z+pixel*16);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //top face
            //y+1

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);


                MeshChunk->position(x+pixel*7,   y+pixel*15, z+pixel*16);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z+pixel*16);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*15, z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 2);

                up = down + ((percent / (float)textureChunk) * 8);

                MeshChunk->position(x+pixel*7,   y+pixel*9, z+pixel*16);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z+pixel*16);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*9, y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*7,   y+pixel*9, z+pixel*8);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }
        }

        if(BlockSolid(x-1,y,z) == true)
        {

            //y-1
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);


                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x,   y+pixel*12, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*8, y+pixel*12, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*8, y+pixel*12, z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+pixel*12, z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //y-1
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);

                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x,   y+pixel*6, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*8, y+pixel*6, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*8, y+pixel*6, z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+pixel*6, z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //top face
            //y+1

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);

                MeshChunk->position(x,   y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*8, y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*8, y+pixel*15, z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+pixel*15, z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //top face
            //y+1

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);


                MeshChunk->position(x,   y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*8, y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*8, y+pixel*9, z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+pixel*9, z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //z-1


            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz1.x)
                        BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz1;

                MeshChunk->position(x,   y+pixel *15, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*8, y+pixel *15, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*8, y+pixel *12,   z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+pixel *12,   z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //z-1
            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz1.x)
                        BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz1;

                MeshChunk->position(x,   y+pixel *9, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*8, y+pixel *9, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*8, y+pixel *6,   z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x,   y+pixel *6,   z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //z+1

            if (canCreate == true)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz2.x)
                        BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz2;
                //up

                MeshChunk->position(x,   y+pixel*12,   z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*8, y+pixel*12,   z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8, y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x,   y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //z+1

            if (canCreate == true)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz2.x)
                        BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz2;
                //up

                MeshChunk->position(x,   y+pixel*6,   z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*8, y+pixel*6,   z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8, y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x,   y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }
        }

        if(BlockSolid(x+1,y,z) == true)
        {

            //y-1
            canCreate = true;

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);


                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x+pixel*8,   y+pixel*12, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*16, y+pixel*12, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*16, y+pixel*12, z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8,   y+pixel*12, z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //y-1
            transparentBlock = DefaultBlock;
            canCreate = true;

            if (canCreate)
            {
                //up
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);

                if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory2.x)
                        BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory2;

                MeshChunk->position(x+pixel*8,   y+pixel*6, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*16, y+pixel*6, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*16, y+pixel*6, z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8,   y+pixel*6, z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }


            //top face
            //y+1

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);

                MeshChunk->position(x+pixel*8,   y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*16, y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*16, y+pixel*15, z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8,   y+pixel*15, z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //top face
            //y+1

            if (canCreate)
            {
                if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                    if(lightened > BlockColory1.x)
                        BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColory1;

                //down
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 2);

                MeshChunk->position(x+pixel*8,   y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*16, y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*16, y+pixel*9, z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8,   y+pixel*9, z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light4.x,light4.y,light4.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //z-1
            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);
                if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz1.x)
                        BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz1;

                MeshChunk->position(x+pixel*8,   y+pixel *15, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*16, y+pixel *15, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*16, y+pixel *12,   z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8,   y+pixel *12,   z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

                    //z-1

            if (canCreate)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);
                if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz1.x)
                        BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz1;

                MeshChunk->position(x+pixel*8,   y+pixel *9, z+pixel*7);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);
                MeshChunk->position(x+pixel*16, y+pixel *9, z+pixel*7);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*16, y+pixel *6,   z+pixel*7);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*8,   y+pixel *6,   z+pixel*7);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //z+1
            if (canCreate == true)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz2.x)
                        BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz2;
                //up

                MeshChunk->position(x+pixel*8,   y+pixel*12,   z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*16, y+pixel*12,   z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*16, y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*8,   y+pixel*15, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            //z+1

            if (canCreate == true)
            {
                left = percent * blockType->sidePlane;
                right = left + ((percent / (float)textureChunk) * 8);

                up = down + ((percent / (float)textureChunk) * 3);

                if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
                {
                    float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                    if(lightened > BlockColorz2.x)
                        BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
                }

                light1 = light2 = light3 = light4 = BlockColorz2;
                //up

                MeshChunk->position(x+pixel*8,   y+pixel*6,   z+pixel*9);
                MeshChunk->textureCoord(left, down);
                MeshChunk->colour(light1.x,light1.y,light1.z);
                MeshChunk->position(x+pixel*16, y+pixel*6,   z+pixel*9);
                MeshChunk->textureCoord(right, down);
                MeshChunk->colour(light3.x,light3.y,light3.z);
                MeshChunk->position(x+pixel*16, y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(right, up);
                MeshChunk->colour(light4.x,light4.y,light4.z);
                MeshChunk->position(x+pixel*8,   y+pixel*9, z+pixel*9);
                MeshChunk->textureCoord(left, up);
                MeshChunk->colour(light2.x,light2.y,light2.z);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }
        }
    }

    /// DOOR 1 Z--
    if(Block == 49 || Block == 56)
    {
        float pixel = 1 / (float)16;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+pixel*3);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+2, z+pixel*3);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+2, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+2, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+2, z+pixel*3);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+pixel*3);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {

            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 3);


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+pixel*3);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+pixel*3);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 2)
            {
                transparentBlock = BlockTransparent(x,y+2,z);
                Block1 = GetBlock(x,y+2,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 2)transparentBlock = BlockTransparentOrSpecial(x,y+2,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+2,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+2, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 3);

            MeshChunk->position(x,   y+2, z+pixel*3);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+2, z+pixel*3);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+2, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+2, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+2, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+2, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+pixel*3);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+pixel*3);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+2, z+pixel*3);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+2, z+pixel*3);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// DOOR Z++
    if(Block == 50 || Block == 55)
    {
        float pixel = 1 / (float)16;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+2, z+pixel*13);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z+pixel*13);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y,   z+pixel*13);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+2, z+pixel*13);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 3);


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z+pixel*13);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z+pixel*13);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 2)
            {
                transparentBlock = BlockTransparent(x,y+2,z);
                Block1 = GetBlock(x,y+2,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 2)transparentBlock = BlockTransparentOrSpecial(x,y+2,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+2,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+2, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + ((percent / (float)textureChunk) * 3);


            MeshChunk->position(x,   y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+2, z+pixel*13);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+2, z+pixel*13);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+2, z+pixel*13);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+2, z+pixel*13);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z+pixel*13);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z+pixel*13);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// DOOR X--
    if(Block == 51 || Block == 53)
    {
        float pixel = 1 / (float)16;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+2, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+pixel*3, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*3, y+2, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*3, y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*3, y,   z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 1)
            {
                transparentBlock = BlockTransparent(x,y-2,z);
                Block1 = GetBlock(x,y-2,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 1)transparentBlock = BlockTransparentOrSpecial(x,y-2,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->upPlane;
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent;


            if((GetBlockSettings(x,y-2,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-2, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*3, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*3, y, z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 2)
            {
                transparentBlock = BlockTransparent(x,y+2,z);
                Block1 = GetBlock(x,y+2,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 2)transparentBlock = BlockTransparentOrSpecial(x,y+2,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+2,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+2, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent;

            MeshChunk->position(x,   y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*3, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*3, y+2, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+2, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+2, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*3, y+2, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*3, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*3, y,   z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*3, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// DOOR X++
    if(Block == 52 || Block == 54)
    {
        float pixel = 1 / (float)16;
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x+pixel*13, y,   z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*13, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*13, y+2, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*13, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+pixel*16, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*16, y+2, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*16, y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*16, y,   z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 1)
            {
                transparentBlock = BlockTransparent(x,y-2,z);
                Block1 = GetBlock(x,y-2,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 1)transparentBlock = BlockTransparentOrSpecial(x,y-2,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->upPlane;
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent;

            if((GetBlockSettings(x,y-2,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-2, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x+pixel*13,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*16, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*16, y, z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*13,   y, z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+2,z);
                Block1 = GetBlock(x,y+2,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+2,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+2,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+2, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent;

            MeshChunk->position(x+pixel*13,   y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*16, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*16, y+2, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*13,   y+2, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x+pixel*13,   y+2, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*16, y+2, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*16, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*13,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 13);
            right = left + ((percent / (float)textureChunk) * 3);

            up = down + percent + ((percent / (float)textureChunk) * 16);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x+pixel*13,   y,   z+pixel*16);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*16, y,   z+pixel*16);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*16, y+2, z+pixel*16);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*13,   y+2, z+pixel*16);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// STAIRS
    if(Block == 125 || Block == 60 || Block == 67)
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //faces
        //x x -1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y+0.5,z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+1, z+0.5);
            MeshChunk->textureCoord(left, up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y+0.5,z+0.5);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //xx1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y+0.5,   z+0.5);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+0.5);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(left, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            up = down + percent;


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //top top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+1,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,   y+1, z+1);
            MeshChunk->textureCoord(left, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+0.5);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+1, z+0.5);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z z -1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+1, z+0.5);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+0.5);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.5,   z+0.5);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.5,   z+0.5);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(Block == 126 || Block == 61 || Block == 68)
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //faces
        //x x -1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y+0.5,z+0.5);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+1, z+0.5);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+1, z);
            MeshChunk->textureCoord(left, up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y+0.5,z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //xx1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y+0.5,z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+1, z+0.5);
            MeshChunk->textureCoord(left, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5,z+0.5);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            up = down + percent;


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //top top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+1,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1*0.9f;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,   y+1, z+0.5);
            MeshChunk->textureCoord(left, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+1, z+0.5);
            MeshChunk->textureCoord(right, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+1, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z z+1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y+0.5,   z+0.5);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5,   z+0.5);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+0.5);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+0.5);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }


    if(Block == 127 || Block == 62 || Block == 69)
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x x-1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x+0.5, y+0.5,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.5, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.5, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.5, y+0.5,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            up = down + percent;


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //top face
        //y y +1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x+0.5,y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.5,y+1, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //zz-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x+0.5,y+1, z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(left, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.5,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.5,y+0.5,   z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x+0.5,   y+0.5,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5,   z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.5,   y+1, z+1);
            MeshChunk->textureCoord(left, up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    if(Block == 128 || Block == 63 || Block == 70)
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent  - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //x x+1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent  - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+0.5, y+0.5,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.5, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.5, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.5, y+0.5,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up
            left = percent * blockType->downPlane;
            right = left + percent;

            up = down + percent;


            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x,   y, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y, z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y, z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //top face
        //y y +1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y+0.5,z);
                Block1 = GetBlock(x,y+0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y+0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened*0.9f;
            }

            light1 = light2 = light3 = light4 = BlockColory1;

            //down
            left = percent * blockType->upPlane;
            right = left + percent;

            up = down + percent;

            MeshChunk->position(x,y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.5, y+1, z+1);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.5, y+1, z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,y+1, z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+0.5, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+0.5, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //zz-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,y+1, z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.5, y+1, z);
            MeshChunk->textureCoord(left, up - ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.5, y+0.5,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,y+0.5,   z);
            MeshChunk->textureCoord(right - ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent - ((percent / (float)textureChunk) * 8);

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+0.5, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+0.5, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            up = down + percent;

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y+0.5,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.5, y+0.5,   z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.5, y+1, z+1);
            MeshChunk->textureCoord(right- ((percent / (float)textureChunk) * 8), up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+1);
            MeshChunk->textureCoord(left, up- ((percent / (float)textureChunk) * 8));
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// CACTI
    if(Block == 25)
    {
        up = down + percent;

        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x > 0)
            {
                transparentBlock = BlockTransparent(x-1,y,z);
                Block1 = GetBlock(x-1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+0.1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.1, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.1, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (x < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x+1,y,z);
                Block1 = GetBlock(x+1,y,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x+0.9, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.9, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+0.9, y+1, z+1 );
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //y-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (y > 0)
            {
                transparentBlock = BlockTransparent(x,y-0.5,z);
                Block1 = GetBlock(x,y-0.5,z);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-0.5,z);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            //up

            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->downPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y-0.5, z) & 0xF) / 15.0f;
                if(lightened > BlockColory2.x)
                    BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory2;

            MeshChunk->position(x+0.1,   y, z+0.1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.9, y, z+0.1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9, y, z+0.9);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.1,   y, z+0.9);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //top face
        //y+1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            if((GetBlockSettings(x,y+0.5,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y+0.5, z) & 0xF) / 15.0f;
                if(lightened > BlockColory1.x)
                    BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColory1;
            //up
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 1);
            up = down + ((percent / (float)textureChunk) * 14);

            left = percent * blockType->upPlane + ((percent / (float)textureChunk) * 1);
            right = left + ((percent / (float)textureChunk) * 14);

            MeshChunk->position(x+0.1,   y+1, z+0.9);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+0.9, y+1, z+0.9);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+0.9, y+1, z+0.1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+0.1,   y+1, z+0.1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light4.x,light4.y,light4.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        //z-1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z > 0)
            {
                transparentBlock = BlockTransparent(x,y,z-1);
                Block1 = GetBlock(x,y,z-1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate)
        {
            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;


            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;
            //up
            MeshChunk->position(x,   y+1, z+0.1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+0.1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z+0.1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z+0.1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //z+1
        transparentBlock = DefaultBlock;
        canCreate = false;
        if(transparent)
        {
            Block1 = 1;
            if (z < WORLD_SIZE - 1)
            {
                transparentBlock = BlockTransparent(x,y,z+1);
                Block1 = GetBlock(x,y,z+1);
            }

            if (transparentBlock == false || Block1 == 0)
                canCreate = true;
        }
        else
        {
            if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
            if (transparentBlock == true)
                canCreate = true;
        }

        if (canCreate == true)
        {
            down = 1.0f - percent * (blockType->textureRow + 1);
            up = down + percent;
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //simple shadows
            //up

            MeshChunk->position(x,   y,   z+0.9);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+0.9);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+0.9);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+0.9);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// LEAVES
    if(Block == 9)
    {
    if(mainOptions.fastRendering == 0)
    {
               //faces
    //x-1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (x > 0)
        {
            transparentBlock = BlockTransparent(x-1,y,z);
            Block1 = GetBlock(x-1,y,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;

        MeshChunk->position(x, y,   z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x, y+1, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x, y,   z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //x+1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (x < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x+1,y,z);
            Block1 = GetBlock(x+1,y,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;
        //up

        MeshChunk->position(x+1, y,   z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y,   z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }

    //y-1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (y > 0)
        {
            transparentBlock = BlockTransparent(x,y-1,z);
            Block1 = GetBlock(x,y-1,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-1,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
            if(lightened > BlockColory2.x)
                BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColory2;

        MeshChunk->position(x,   y, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y, z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y, z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //top face
    //y+1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (y < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x,y+1,z);
            Block1 = GetBlock(x,y+1,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (BlockTransparentOrSpecial(x,y+1,z) == true && GetBlock(x,y+1,z) != 93)
            canCreate = true;
    }

    if (canCreate)
    {
        if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
            if(lightened > BlockColory1.x)
                BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColory1;
        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        MeshChunk->position(x,   y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y+1, z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }

    //z-1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (z > 0)
        {
            transparentBlock = BlockTransparent(x,y,z-1);
            Block1 = GetBlock(x,y,z-1);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;
        //up
        MeshChunk->position(x,   y+1, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+1, y,   z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y,   z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //z+1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (z < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x,y,z+1);
            Block1 = GetBlock(x,y,z+1);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate == true)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;

        MeshChunk->position(x,   y,   z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y,   z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x,   y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
        }
        }
    else
    {
               //faces
    //x-1
    transparentBlock = 0;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (x > 0)
        {
            transparentBlock = BlockTransparent(x-1,y,z);
            Block1 = GetBlock(x-1,y,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * 13;
        right = left + percent;

        if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

        MeshChunk->position(x, y,   z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x, y+1, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x, y,   z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //x+1
    transparentBlock = 0;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (x < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x+1,y,z);
            Block1 = GetBlock(x+1,y,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * 13;
        right = left + percent;

        if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;
        //up
        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

        MeshChunk->position(x+1, y,   z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y,   z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }

    //y-1
    transparentBlock = 0;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (y > 0)
        {
            transparentBlock = BlockTransparent(x,y-1,z);
            Block1 = GetBlock(x,y-1,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-1,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        //up
        left = percent * 13;
        right = left + percent;

        if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
            if(lightened > BlockColory2.x)
                BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColory2;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColory2 * lightShadowFactor;

            //simple shadows
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
            {
                light3-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
            {
                light4-=lightFactor;
            }
        }

        MeshChunk->position(x,   y, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y, z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y, z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //top face
    //y+1
    transparentBlock = 0;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (y < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x,y+1,z);
            Block1 = GetBlock(x,y+1,z);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (BlockTransparentOrSpecial(x,y+1,z) == true && GetBlock(x,y+1,z) != 93)
            canCreate = true;
    }

    if (canCreate)
    {
        if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
            if(lightened > BlockColory1.x)
                BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColory1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColory1 * lightShadowFactor;
            //simple shadows
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
            {
                light3-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
            {
                light4-=lightFactor;
            }
        }
        //down
        left = percent * 13;
        right = left + percent;

        MeshChunk->position(x,   y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y+1, z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }

    //z-1
    transparentBlock = 0;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (z > 0)
        {
            transparentBlock = BlockTransparent(x,y,z-1);
            Block1 = GetBlock(x,y,z-1);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * 13;
        right = left + percent;

        if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorz1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }
        //up
        MeshChunk->position(x,   y+1, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+1, y,   z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y,   z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //z+1
    transparentBlock = 0;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (z < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x,y,z+1);
            Block1 = GetBlock(x,y,z+1);
        }

        if (Block1 == 0 || Block1 == 93)
            canCreate = true;
    }
    else
    {
        if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate == true)
    {
        left = percent * 13;
        right = left + percent;

        if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorz1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
            {
                light3-=lightFactor;
            }
        }

        MeshChunk->position(x,   y,   z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y,   z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x,   y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
        }
        }
    }


    /// FLOWERS & CANES & MOOSHROOMS
    if(Block == 33 || Block == 119 || Block == 120 || Block == 121 || Block == 77 || Block == 78)
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            //simple shadows
            //up

            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }


        //x+1
        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            //simple shadows
            //up

            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y+1, z+1 );
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

         transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            //simple shadows
            //up

            MeshChunk->position(x+1, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y+1, z );
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        transparentBlock = DefaultBlock;
        canCreate = true;

        if (canCreate)
        {
            left = percent * blockType->sidePlane;
            right = left + percent;

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx1.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;

            //simple shadows
            //up

            MeshChunk->position(x+1, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// WHEAT
    if(Block >= 134 && Block <= 137)
    {
        //faces
        //x-1
        transparentBlock = DefaultBlock;
        canCreate = true;

        left = percent * blockType->sidePlane;
        right = left + percent;

        up = down + percent;

        float pixel = 1.0f / 16.0f;

        if (canCreate)
        {

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x+pixel*4, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*4, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*4, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*4, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+pixel*4, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*4, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*4, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*4, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx1;
            //up

            MeshChunk->position(x+pixel*12, y,   z);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+pixel*12, y+1, z);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*12, y+1, z+1);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*12, y,   z+1);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {

            if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
                if(lightened > BlockColorx2.x)
                    BlockColorx2.x = BlockColorx2.y = BlockColorx2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorx2;
            //up
            MeshChunk->position(x+pixel*12, y,   z+1);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+pixel*12, y+1, z+1);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+pixel*12, y+1, z);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+pixel*12, y,   z);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+1, z+pixel*4);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+pixel*4);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z+pixel*4);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z+pixel*4);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate == true)
        {
            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+pixel*4);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+pixel*4);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+pixel*4);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+pixel*4);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate == true)
        {
            if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
                if(lightened > BlockColorz2.x)
                    BlockColorz2.x = BlockColorz2.y = BlockColorz2.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz2;
            //up

            MeshChunk->position(x,   y,   z+pixel*12);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);
            MeshChunk->position(x+1, y,   z+pixel*12);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x+1, y+1, z+pixel*12);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x,   y+1, z+pixel*12);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        if (canCreate)
        {
            if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
            {
                float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
                if(lightened > BlockColorz1.x)
                    BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
            }

            light1 = light2 = light3 = light4 = BlockColorz1;

            MeshChunk->position(x,   y+1, z+pixel*12);
            MeshChunk->textureCoord(right, up);
            MeshChunk->colour(light2.x,light2.y,light2.z);
            MeshChunk->position(x+1, y+1, z+pixel*12);
            MeshChunk->textureCoord(left, up);
            MeshChunk->colour(light4.x,light4.y,light4.z);
            MeshChunk->position(x+1, y,   z+pixel*12);
            MeshChunk->textureCoord(left, down);
            MeshChunk->colour(light3.x,light3.y,light3.z);
            MeshChunk->position(x,   y,   z+pixel*12);
            MeshChunk->textureCoord(right, down);
            MeshChunk->colour(light1.x,light1.y,light1.z);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }

    /// TORCH
    if(Block == Torch::getID())
    {
    //texture stuff
    BaseBlock *blockType = &blockTypes[Block];
    float down = 1.0f - percent * (blockType->textureRow + 1);
    float up = down + percent - ((percent / (float)textureChunk) * 6);

    float left = percent * blockType->upPlane;
    float right = left + percent;

    float pixel = 1 / (float)16;

    //standing torch
    block_t Block1 = GetBlock(x,y-1,z);

    if(Block1 != 0 && Block1 != Torch::getID())
    {
        left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
        right = left + ((percent / (float)textureChunk) * 2);

        //x-1
        MeshChunk->info(x + 0.4375f,y			,z + 0.4375f + 0.0625*2	,right	, down	,1,1,1);
        MeshChunk->info(x + 0.4375f,y + 0.0625*10,z + 0.4375f + 0.0625*2	,right	, up	,1,1,1);
        MeshChunk->info(x + 0.4375f,y + 0.0625*10,z + 0.4375f			,left	, up	,1,1,1);
        MeshChunk->info(x + 0.4375f,y			,z + 0.4375f			,left	, down	,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //x+1
        MeshChunk->info(x + 0.4375f + pixel*2,y		        ,z + 0.4375f            ,right, down,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2,y + pixel*10  ,z + 0.4375f            ,right, up,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2,y + pixel*10  ,z + 0.4375f + pixel*2  ,left, up,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2,y		        ,z + 0.4375f + pixel*2  ,left, down,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //z-1
        MeshChunk->info(x + 0.4375f		        ,y + pixel*10   ,z + 0.4375f,right, up,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10   ,z + 0.4375f,left, up,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2   ,y			    ,z + 0.4375f,left, down,1,1,1);
        MeshChunk->info(x + 0.4375f		        ,y			    ,z + 0.4375f,right, down,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //z+1
        MeshChunk->info(x + 0.4375f		        ,y			    ,z + 0.4375f + pixel*2,left, down,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2   ,y			    ,z + 0.4375f + pixel*2,right, down,1,1,1);
        MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10	,z + 0.4375f + pixel*2,right, up,1,1,1);
        MeshChunk->info(x + 0.4375f		        ,y + pixel*10	,z + 0.4375f + pixel*2,left, up,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //y+1
        {
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 8);
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

            MeshChunk->info(x + 0.4375f		        ,y + pixel*10   ,z + 0.4375f + pixel*2  ,left, up,1,1,1);
            MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10   ,z + 0.4375f + pixel*2  ,right, up,1,1,1);
            MeshChunk->info(x + 0.4375f + pixel*2   ,y + pixel*10   ,z + 0.4375f            ,right, down,1,1,1);
            MeshChunk->info(x + 0.4375f		        ,y + pixel*10   ,z + 0.4375f            ,left, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
    }
    else
    {
        bool canPlaseTorch = false;

        if(GetBlock(x-1,y,z) != 0 && GetBlock(x-1,y,z) != Torch::getID())
        {
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

                    //x-1
            MeshChunk->info(x - pixel   ,y + pixel*3    ,z + 0.4375f + pixel*2	,right	, down	,1,1,1);
            MeshChunk->info(x + pixel*4 ,y + pixel*13   ,z + 0.4375f + pixel*2	,right	, up	,1,1,1);
            MeshChunk->info(x + pixel*4 ,y + pixel*13   ,z + 0.4375f			,left	, up	,1,1,1);
            MeshChunk->info(x - pixel   ,y + pixel*3    ,z + 0.4375f			,left	, down	,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            //x+1
            MeshChunk->info(x + pixel    ,y	+ pixel*3	,z + 0.4375f            ,right, down,1,1,1);
            MeshChunk->info(x + pixel*6  ,y + pixel*13  ,z + 0.4375f            ,right, up  ,1,1,1);
            MeshChunk->info(x + pixel*6  ,y + pixel*13  ,z + 0.4375f + pixel*2  ,left, up   ,1,1,1);
            MeshChunk->info(x + pixel    ,y + pixel*3   ,z + 0.4375f + pixel*2  ,left, down ,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            //z-1
            MeshChunk->info(x + pixel*4		,y + pixel*13   ,z + pixel*7,right, up  ,1,1,1);
            MeshChunk->info(x + pixel*6     ,y + pixel*13   ,z + pixel*7,left, up   ,1,1,1);
            MeshChunk->info(x + pixel       ,y + pixel*3	,z + pixel*7,left, down ,1,1,1);
            MeshChunk->info(x - pixel	    ,y + pixel*3	,z + pixel*7,right, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            //z+1
            MeshChunk->info(x - pixel	        ,y + pixel*3    ,z + pixel*9,left, down,1,1,1);
            MeshChunk->info(x + pixel           ,y + pixel*3	,z + pixel*9,right, down,1,1,1);
            MeshChunk->info(x + pixel*6         ,y + pixel*13	,z + pixel*9,right, up,1,1,1);
            MeshChunk->info(x + pixel*4		    ,y + pixel*13	,z + pixel*9,left, up,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            canPlaseTorch = true;
                    //y+1
            {
                down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 8);
                up = down + ((percent / (float)textureChunk) * 2);

                left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
                right = left + ((percent / (float)textureChunk) * 2);

                MeshChunk->info(x + pixel*4		        ,y + pixel*13   ,z + pixel*7 + pixel*2  ,left, up,1,1,1);
                MeshChunk->info(x + pixel*4 + pixel*2   ,y + pixel*13   ,z + pixel*7 + pixel*2  ,right, up,1,1,1);
                MeshChunk->info(x + pixel*4 + pixel*2   ,y + pixel*13   ,z + pixel*7            ,right, down,1,1,1);
                MeshChunk->info(x + pixel*4		        ,y + pixel*13   ,z + pixel*7            ,left, down,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            {
                down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 6);
                up = down + ((percent / (float)textureChunk) * 2);

                left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
                right = left + ((percent / (float)textureChunk) * 2);

                MeshChunk->info(x - pixel   ,y + pixel*3   ,z + pixel*7            ,left, up,1,1,1);
                MeshChunk->info(x + pixel   ,y + pixel*3   ,z + pixel*7            ,right, up,1,1,1);
                MeshChunk->info(x + pixel   ,y + pixel*3   ,z + pixel*7 + pixel*2  ,right, down,1,1,1);
                MeshChunk->info(x - pixel	,y + pixel*3   ,z + pixel*7 + pixel*2  ,left, down,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }
        }
        else if(GetBlock(x+1,y,z) != 0 && GetBlock(x+1,y,z) != Torch::getID())
        {

            canPlaseTorch = true;
            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

                    //x-1
            MeshChunk->info(x + pixel*15   ,y + pixel*3    ,z + 0.4375f + pixel*2	,right	, down	,1,1,1);
            MeshChunk->info(x + pixel*10 ,y + pixel*13   ,z + 0.4375f + pixel*2	,right	, up	,1,1,1);
            MeshChunk->info(x + pixel*10 ,y + pixel*13   ,z + 0.4375f			,left	, up	,1,1,1);
            MeshChunk->info(x + pixel*15  ,y + pixel*3    ,z + 0.4375f			,left	, down	,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            //x+1
            MeshChunk->info(x + pixel*17    ,y	+ pixel*3	,z + 0.4375f            ,right, down,1,1,1);
            MeshChunk->info(x + pixel*12  ,y + pixel*13  ,z + 0.4375f            ,right, up  ,1,1,1);
            MeshChunk->info(x + pixel*12  ,y + pixel*13  ,z + 0.4375f + pixel*2  ,left, up   ,1,1,1);
            MeshChunk->info(x + pixel*17    ,y + pixel*3   ,z + 0.4375f + pixel*2  ,left, down ,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            //z-1
            MeshChunk->info(x + pixel*12		,y + pixel*13   ,z + pixel*9,right, up  ,1,1,1);
            MeshChunk->info(x + pixel*10     ,y + pixel*13   ,z + pixel*9,left, up   ,1,1,1);
            MeshChunk->info(x + pixel*15       ,y + pixel*3	,z + pixel*9,left, down ,1,1,1);
            MeshChunk->info(x + pixel*17	    ,y + pixel*3	,z + pixel*9,right, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            //z+1
            MeshChunk->info(x + pixel*17	        ,y + pixel*3    ,z + pixel*7,left, down,1,1,1);
            MeshChunk->info(x + pixel*15           ,y + pixel*3	,z + pixel*7,right, down,1,1,1);
            MeshChunk->info(x + pixel*10         ,y + pixel*13	,z + pixel*7,right, up,1,1,1);
            MeshChunk->info(x + pixel*12		    ,y + pixel*13	,z + pixel*7,left, up,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;

            canPlaseTorch = true;
                    //y+1
            {
                down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 8);
                up = down + ((percent / (float)textureChunk) * 2);

                left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
                right = left + ((percent / (float)textureChunk) * 2);

                MeshChunk->info(x + pixel*10		        ,y + pixel*13   ,z + pixel*7 + pixel*2  ,left, up,1,1,1);
                MeshChunk->info(x + pixel*12                ,y + pixel*13   ,z + pixel*7 + pixel*2  ,right, up,1,1,1);
                MeshChunk->info(x + pixel*12                ,y + pixel*13   ,z + pixel*7            ,right, down,1,1,1);
                MeshChunk->info(x + pixel*10		        ,y + pixel*13   ,z + pixel*7            ,left, down,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }

            {
                down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 6);
                up = down + ((percent / (float)textureChunk) * 2);

                left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
                right = left + ((percent / (float)textureChunk) * 2);

                MeshChunk->info(x + pixel * 15  ,y + pixel*3   ,z + pixel*7            ,left, up,1,1,1);
                MeshChunk->info(x + pixel * 17  ,y + pixel*3   ,z + pixel*7            ,right, up,1,1,1);
                MeshChunk->info(x + pixel * 17  ,y + pixel*3   ,z + pixel*7 + pixel*2  ,right, down,1,1,1);
                MeshChunk->info(x + pixel * 15 	,y + pixel*3   ,z + pixel*7 + pixel*2  ,left, down,1,1,1);

                MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
                MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

                iVertex += 4;
            }
        }
        else if(GetBlock(x,y,z-1) != 0 && GetBlock(x,y,z-1) != Torch::getID())
        {

            canPlaseTorch = true;
        left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
        right = left + ((percent / (float)textureChunk) * 2);

        //x-1
        MeshChunk->info(x + pixel*9,y + pixel*3		,z - pixel	    ,right	, down	,1,1,1);
        MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*4	,right	, up	,1,1,1);
        MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*6	,left	, up	,1,1,1);
        MeshChunk->info(x + pixel*9,y + pixel*3		,z + pixel	    ,left	, down	,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //x+1
        MeshChunk->info(x + pixel*7,y + pixel*3     ,z + pixel          ,right, down,1,1,1);
        MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*6           ,right, up,1,1,1);
        MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*4  ,left, up,1,1,1);
        MeshChunk->info(x + pixel*7,y + pixel*3	    ,z - pixel ,left, down,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //z-1
        MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*4,right, up,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*4,left, up,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3    ,z - pixel,left, down,1,1,1);
        MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z - pixel,right, down,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //z+1
        MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z + pixel,left, down,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3	,z + pixel,right, down,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13	,z + pixel*6,right, up,1,1,1);
        MeshChunk->info(x + pixel*7		        ,y + pixel*13	,z + pixel*6,left, up,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //y+1
        {
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 8);
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

            MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*6  ,left, up,1,1,1);
            MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*6  ,right, up,1,1,1);
            MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*4            ,right, down,1,1,1);
            MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*4          ,left, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

                //y+1
        {
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 6);
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

            MeshChunk->info(x + pixel*7		        ,y + pixel*3   ,z + pixel  ,left, up,1,1,1);
            MeshChunk->info(x + pixel*7             ,y + pixel*3   ,z - pixel  ,right, up,1,1,1);
            MeshChunk->info(x + pixel*9             ,y + pixel*3   ,z - pixel  ,right, down,1,1,1);
            MeshChunk->info(x + pixel*9		        ,y + pixel*3   ,z + pixel  ,left, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

        }
        else if(GetBlock(x,y,z+1) != 0 && GetBlock(x,y,z+1) != Torch::getID())
        {

        canPlaseTorch = true;
        left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
        right = left + ((percent / (float)textureChunk) * 2);

        //x-1
        MeshChunk->info(x + pixel*9,y + pixel*3		,z + pixel*15	    ,right	, down	,1,1,1);
        MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*10	,right	, up	,1,1,1);
        MeshChunk->info(x + pixel*9,y + pixel*13    ,z + pixel*12	,left	, up	,1,1,1);
        MeshChunk->info(x + pixel*9,y + pixel*3		,z + pixel*17	    ,left	, down	,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //x+1
        MeshChunk->info(x + pixel*7,y + pixel*3     ,z + pixel*17         ,right, down,1,1,1);
        MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*12           ,right, up,1,1,1);
        MeshChunk->info(x + pixel*7,y + pixel*13    ,z + pixel*10  ,left, up,1,1,1);
        MeshChunk->info(x + pixel*7,y + pixel*3	    ,z + pixel*15 ,left, down,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //z-1
        MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*10,right, up,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*10,left, up,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3    ,z + pixel*15,left, down,1,1,1);
        MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z + pixel*15,right, down,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //z+1
        MeshChunk->info(x + pixel*7		        ,y + pixel*3    ,z + pixel*17,left, down,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*3	,z + pixel*17,right, down,1,1,1);
        MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13	,z + pixel*12,right, up,1,1,1);
        MeshChunk->info(x + pixel*7		        ,y + pixel*13	,z + pixel*12,left, up,1,1,1);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;

        //y+1
        {
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 8);
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

            MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*10  ,left, up,1,1,1);
            MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*10  ,right, up,1,1,1);
            MeshChunk->info(x + pixel*7 + pixel*2   ,y + pixel*13   ,z + pixel*12           ,right, down,1,1,1);
            MeshChunk->info(x + pixel*7		        ,y + pixel*13   ,z + pixel*12          ,left, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }

                //y+1
        {
            down = 1.0f - percent * (blockType->textureRow + 1) + ((percent / (float)textureChunk) * 6);
            up = down + ((percent / (float)textureChunk) * 2);

            left = percent * blockType->sidePlane + ((percent / (float)textureChunk) * 7);
            right = left + ((percent / (float)textureChunk) * 2);

            MeshChunk->info(x + pixel*7		        ,y + pixel*3   ,z + pixel *17  ,left, up,1,1,1);
            MeshChunk->info(x + pixel*7             ,y + pixel*3   ,z + pixel *15 ,right, up,1,1,1);
            MeshChunk->info(x + pixel*9             ,y + pixel*3   ,z + pixel *15 ,right, down,1,1,1);
            MeshChunk->info(x + pixel*9		        ,y + pixel*3   ,z + pixel *17 ,left, down,1,1,1);

            MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
            MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

            iVertex += 4;
        }
        }
    }
}
}

void CraftWorld::GetNormalBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent)
{
    /* Only create visible faces of each chunk */
    bool DefaultBlock = false;
    bool transparentBlock;

    block_t Block1 = 0;

    Vector3 light1,light2,light3,light4;
    float BaseLight = 1.0f;

    Vector3 BlockColory1;    //Top face
    Vector3 BlockColory2;    //Bottom face
    Vector3 BlockColorx1;    //Sunset face
    Vector3 BlockColorz1;     //Front/back faces
    //texture stuff
    BaseBlock *blockType = &blockTypes[Block];

    float down = 1.0f - percent * (blockType->textureRow + 1);
    float up = down + percent;

    float left = percent * blockType->upPlane;
    float right = left + percent;

    bool canCreate = false;

    //lightened
    //if time is between 21-4 use settings table for lightening
    //if time is between 5-20 use normal light table but compare it with settings table
    //	if setting is brighter then use it
    if(worldDayTime >= 21 || worldDayTime <= 4)//night
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            BaseLight  = (float)(GetBlockSettings(x, y, z) & 0xF)/16.0f; // 255.0f;  //For the two x faces

            BlockColorx1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.95f;
            BlockColorz1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.70f;
            BlockColory1 = BlockColory2 = Vector3(BaseLight,BaseLight,BaseLight);
        }
        else //normal light
        {
            //light
            BaseLight  = GetBlockLight(x, y, z) / 255.0f;  //For the two x faces
            //float BlockLight1 = BlockLight * 0.9f;		//For the two z faces
            //float BlockLight2 = BlockLight * 0.8f;		//For the two y faces

            BlockColory1 = lightColor * (BaseLight);
            BlockColory2 = lightColor * (BaseLight) * 0.5f;

            BlockColorz1  = lightColor * (BaseLight);
            BlockColorz1 *= 0.70f;

            BlockColorx1 = lightColor * (BaseLight);
            BlockColorx1 *= 0.95f;
        }
    }
    else //day
    {
        if((GetBlockSettings(x,y,z) & OpLighSource) != 0)//block is lightened
        {
            //int normal = GetBlockLight(x, y, z);
            //int lightened = (GetBlockSettings(x, y, z) & 0xF) * 16;

            float normal = lightColor.x;
            float lightened = (GetBlockSettings(x, y, z) & 0xF) / 15.0f;

            if(lightened > normal)
            {
                BaseLight = lightened; // 255.0f;
                BlockColorx1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.95f;
                BlockColorz1 = Vector3(BaseLight,BaseLight,BaseLight) * 0.75f;
                BlockColory1 = BlockColory2 = Vector3(BaseLight,BaseLight,BaseLight);
            }
            else
            {
                BaseLight  = GetBlockLight(x, y, z) / 255.0f;

                BlockColory1 = lightColor * BaseLight;
                BlockColory2 = lightColor  * BaseLight * 0.5;

                BlockColorz1  = lightColor * BaseLight;
                BlockColorz1 *= 0.70f;

                BlockColorx1 = lightColor * BaseLight;
                BlockColorx1 *= 0.95f;

            }

        }
        else
        {
            BaseLight  = GetBlockLight(x, y, z) / 255.0f;

            BlockColory1 = lightColor * BaseLight;
            BlockColory2 = lightColor * 0.5 * BaseLight;

            BlockColorz1  = lightColor * BaseLight;
            BlockColorz1 *= 0.70f;

            BlockColorx1 = lightColor * BaseLight;
            BlockColorx1 *= 0.95f;

        }
    }

    //faces
    //x-1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (x > 0)
        {
            transparentBlock = BlockTransparent(x-1,y,z);
            Block1 = GetBlock(x-1,y,z);
        }

        if (transparentBlock == false || Block1 == 0)
            canCreate = true;
    }
    else
    {
        if (x > 0)transparentBlock = BlockTransparentOrSpecial(x-1,y,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x-1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x-1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y+1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }

        MeshChunk->position(x, y,   z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x, y+1, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x, y,   z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //x+1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (x < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x+1,y,z);
            Block1 = GetBlock(x+1,y,z);
        }

        if (transparentBlock == false || Block1 == 0)
            canCreate = true;
    }
    else
    {
        if (x < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x+1,y,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x+1,y,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x+1, y, z) & 0xF) / 15.0f;
            if(lightened > BlockColorx1.x)
                BlockColorx1.x = BlockColorx1.y = BlockColorx1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorx1;
        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorx1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }
        //up

        MeshChunk->position(x+1, y,   z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y,   z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }

    //y-1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (y > 0)
        {
            transparentBlock = BlockTransparent(x,y-1,z);
            Block1 = GetBlock(x,y-1,z);
        }

        if (transparentBlock == false || Block1 == 0)
            canCreate = true;
    }
    else
    {
        if (y > 0)transparentBlock = BlockTransparentOrSpecial(x,y-1,z);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        //up
        left = percent * blockType->downPlane;
        right = left + percent;

        if((GetBlockSettings(x,y-1,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y-1, z) & 0xF) / 15.0f;
            if(lightened > BlockColory2.x)
                BlockColory2.x = BlockColory2.y = BlockColory2.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColory2;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColory2 * lightShadowFactor;

            //simple shadows
            if(!BlockTransparentOrLightSource(x-1,y-1,z) || !BlockTransparentOrLightSource(x-1,y-1,z-1) || !BlockTransparentOrLightSource(x,y-1,z-1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y-1,z) || !BlockTransparentOrLightSource(x+1,y-1,z+1) || !BlockTransparentOrLightSource(x,y-1,z+1))
            {
                light3-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z))
            {
                light4-=lightFactor;
            }
        }

        MeshChunk->position(x,   y, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y, z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y, z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //top face
    //y+1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (y < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x,y+1,z);
            Block1 = GetBlock(x,y+1,z);
        }

        if (transparentBlock == false || Block1 == 0)
            canCreate = true;
    }
    else
    {
        if (BlockTransparentOrSpecial(x,y+1,z) == true && GetBlock(x,y+1,z) != 93)
            canCreate = true;
    }

    if (canCreate)
    {
        if((GetBlockSettings(x,y+1,z) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y+1, z) & 0xF) / 15.0f;
            if(lightened > BlockColory1.x)
                BlockColory1.x = BlockColory1.y = BlockColory1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColory1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColory1 * lightShadowFactor;
            //simple shadows
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x+1,y+1,z) || !BlockTransparentOrLightSource(x+1,y+1,z-1) || !BlockTransparentOrLightSource(x,y+1,z-1))
            {
                light3-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z))
            {
                light4-=lightFactor;
            }
        }

        //down
        left = percent * blockType->upPlane;
        right = left + percent;

        MeshChunk->position(x,   y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y+1, z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light4.x,light4.y,light4.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }

    //z-1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (z > 0)
        {
            transparentBlock = BlockTransparent(x,y,z-1);
            Block1 = GetBlock(x,y,z-1);
        }

        if (transparentBlock == false || Block1 == 0)
            canCreate = true;
    }
    else
    {
        if (z > 0)transparentBlock = BlockTransparentOrSpecial(x,y,z-1);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x,y,z-1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z-1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorz1 * lightShadowFactor;
            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y+1,z-1))
            {
                light2-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y+1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y+1,z-1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x-1,y,z-1) || !BlockTransparentOrLightSource(x-1,y-1,z-1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z-1) || !BlockTransparentOrLightSource(x+1,y,z-1) || !BlockTransparentOrLightSource(x+1,y-1,z-1))
            {
                light3-=lightFactor;
            }
        }
        //up
        MeshChunk->position(x,   y+1, z);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);
        MeshChunk->position(x+1, y+1, z);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x+1, y,   z);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x,   y,   z);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }


    //z+1
    transparentBlock = DefaultBlock;
    canCreate = false;
    if(transparent)
    {
        Block1 = 1;
        if (z < WORLD_SIZE - 1)
        {
            transparentBlock = BlockTransparent(x,y,z+1);
            Block1 = GetBlock(x,y,z+1);
        }

        if (transparentBlock == false || Block1 == 0)
            canCreate = true;
    }
    else
    {
        if (z < WORLD_SIZE - 1)transparentBlock = BlockTransparentOrSpecial(x,y,z+1);
        if (transparentBlock == true)
            canCreate = true;
    }

    if (canCreate == true)
    {
        left = percent * blockType->sidePlane;
        right = left + percent;

        if((GetBlockSettings(x,y,z+1) & OpLighSource) != 0)//block is lightened
        {
            float lightened = (GetBlockSettings(x, y, z+1) & 0xF) / 15.0f;
            if(lightened > BlockColorz1.x)
                BlockColorz1.x = BlockColorz1.y = BlockColorz1.z = lightened;
        }

        light1 = light2 = light3 = light4 = BlockColorz1;

        if(mainOptions.fakeShadowsRendering == true)
        {
            lightFactor = BlockColorz1 * lightShadowFactor;

            //simple shadows
            //up
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y+1,z+1))
            {
                light2-=lightFactor;
            }
            if(!BlockTransparentOrLightSource(x,y+1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y+1,z+1))
            {
                light4-=lightFactor;
            }

            //down
            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x-1,y,z+1) || !BlockTransparentOrLightSource(x-1,y-1,z+1))
            {
                light1-=lightFactor;
            }

            if(!BlockTransparentOrLightSource(x,y-1,z+1) || !BlockTransparentOrLightSource(x+1,y,z+1) || !BlockTransparentOrLightSource(x+1,y-1,z+1))
            {
                light3-=lightFactor;
            }
        }

        MeshChunk->position(x,   y,   z+1);
        MeshChunk->textureCoord(left, down);
        MeshChunk->colour(light1.x,light1.y,light1.z);
        MeshChunk->position(x+1, y,   z+1);
        MeshChunk->textureCoord(right, down);
        MeshChunk->colour(light3.x,light3.y,light3.z);
        MeshChunk->position(x+1, y+1, z+1);
        MeshChunk->textureCoord(right, up);
        MeshChunk->colour(light4.x,light4.y,light4.z);
        MeshChunk->position(x,   y+1, z+1);
        MeshChunk->textureCoord(left, up);
        MeshChunk->colour(light2.x,light2.y,light2.z);

        MeshChunk->triangle(iVertex, iVertex+1, iVertex+2);
        MeshChunk->triangle(iVertex+2, iVertex+3, iVertex);

        iVertex += 4;
    }
}

void CraftWorld::UpdateWorldLightForChunk(int chunkID)
{
    int StartZ = mChunks[chunkID]->chunkStartZ;
    int StartY = mChunks[chunkID]->chunkStartY;
    int StartX = mChunks[chunkID]->chunkStartX;

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {

                block_t Block = GetBlock(x,y,z);
                if(BlockTransparent(x,y,z) == true)continue;//if block is transparent don't continue

                //light source?
                if(Block == 48 || Block == 112 || Block == 107)
                {
                    SetLigtSourcePosition(x,y,z,Block);
                }

            }
        }
    }
}

void CraftWorld::UpdateLightAreaIn(Vector3 pos)
{
    int biggestLight = 9;

    int startx = pos.x - biggestLight > 0 ? pos.x - biggestLight : 0;
    int starty = pos.y - biggestLight > 0 ? pos.y - biggestLight : 0;
    int startz = pos.z - biggestLight > 0 ? pos.z - biggestLight : 0;

    int endx = pos.x + biggestLight < WORLD_SIZE ? pos.x + biggestLight : WORLD_SIZE;
    int endy = pos.y + biggestLight < WORLD_SIZE ? pos.y + biggestLight : WORLD_SIZE;
    int endz = pos.z + biggestLight < WORLD_SIZE ? pos.z + biggestLight : WORLD_SIZE;

    for (int z = startz; z < endz; ++z)
    {
        for (int y = starty; y < endy; ++y)
        {
            for (int x = startx; x < endx; ++x)
            {
                block_t Block = GetBlock(x,y,z);
                if(Block == 48 || Block == 112)
                {
                    RemoveLigtSourceAtPosition(x,y,z,Block);
                    SetLigtSourcePosition(x,y,z,Block);
                    AddChunkToUpdate(x,y,z);
                }
            }
        }
    }
}

void CraftWorld::AddChunkToUpdate(const int x, const int y, const int z)
{
    int chunkTarget = getChunkId(Vector3(x,y,z));
    if(chunkTarget != -1)
        mChunks[chunkTarget]->needUpdate = true;
}

void CraftWorld::RebuildChunksLight(Vector3 pos,int currentChunk,int blockID)
{
    if(blockID == 112 || blockID == JackOLantern::getID() || blockID == Torch::getID() || blockID == GlowStone::getID() || blockID == 107)
    {
        BoundingBox lBox = BoundingBox(Vector3(pos.x - 10,pos.y - 10,pos.z - 10),Vector3(pos.x + 10,pos.y + 10,pos.z + 10));
        for(unsigned int i = 0; i < mChunks.size(); i++)
        {
            if(lBox.intersect(mChunks[i]->bBox))
            {
                rebuildChunk(i);
                rebuildTransparentChunk(i);
            }
        }
    }
}

void CraftWorld::rebuildNearestChunks(int id,Vector3 pos)
{
    Vector3 test = mChunks[id]->bBox.onBorder(pos);
    Vector3 temp = pos;
    int chunkNumber = -1;

    if(test.x != 0)
    {
        temp.x +=test.x;

        chunkNumber = getChunkId(temp);
        if(chunkNumber != -1)
        {
            rebuildChunk(chunkNumber);
            rebuildTransparentChunk(chunkNumber);
        }


        //now check for other with this... //needed by shadows
        if(test.y != 0)
        {
            temp.y +=test.y;
            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }

        if(test.z != 0)
        {
            temp.z +=test.z;
            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }
    }


    if(test.y != 0)
    {
        temp = pos;
        temp.y +=test.y;

        chunkNumber = getChunkId(temp);
        if(chunkNumber != -1)
        {
            rebuildChunk(chunkNumber);
            rebuildTransparentChunk(chunkNumber);
        }

        if(test.z != 0)
        {
            temp.z +=test.z;
            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }
    }

    if(test.z != 0)
    {
        temp = pos;
        temp.z +=test.z;

        chunkNumber = getChunkId(temp);
        if(chunkNumber != -1)
        {
            rebuildChunk(chunkNumber);
            rebuildTransparentChunk(chunkNumber);
        }

        if(test.x != 0)
        {
            temp.x +=test.x;

            chunkNumber = getChunkId(temp);
            if(chunkNumber != -1)
            {
                rebuildChunk(chunkNumber);
                rebuildTransparentChunk(chunkNumber);
            }
        }
    }

}

void CraftWorld::createWorldChunkss()
{
    createdChunksCount = 0;

    for (int z = 0; z < WORLD_SIZE; z += CHUNK_SIZE)
    {
        for (int y = 0; y < WORLD_SIZE; y += CHUNK_SIZE)
        {
            for (int x = 0; x < WORLD_SIZE; x += CHUNK_SIZE)
            {
                createChunks(x,y,z);
                createTransparentChunks(x,y,z);
            }
        }
    }
}

void CraftWorld::UpdateChunkBlocks(int id)
{


    SimpleMeshChunk* MeshChunk = mChunks[id];

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                if (BlockUpdate2(x,y,z) == 0)
                {
                    continue;
                }
                if(GetBlock(x,y,z) == 0)
                {
                    continue;
                }
                if(x > 0 && x < WORLD_SIZE && y > 0 && y < WORLD_SIZE && z > 0 && z < WORLD_SIZE)
                {
                    if(GetBlock(x,y,z) == 2 && (GetBlock(x,y+1,z) == 0 || GetBlock(x,y+1,z) == 48 || GetBlock(x,y+1,z) == 119 || GetBlock(x,y+1,z) == 120 || GetBlock(x,y+1,z) == 77 || GetBlock(x,y+1,z) == 78 || GetBlock(x,y+1,z) == 59) && GetBlockLight(x,y,z) > 128)
                    {
                        GetBlock(x,y,z) = 1;
                        continue;
                    }
                    if(GetBlock(x,y,z) == 1 && GetBlock(x,y+1,z) != 0 && GetBlock(x,y+1,z) != 119 && GetBlock(x,y+1,z) != 120 && GetBlock(x,y+1,z) != 48 && GetBlock(x,y+1,z) != 77 && GetBlock(x,y+1,z) != 78 && GetBlock(x,y+1,z) != 59)
                    {
                        GetBlock(x,y,z) = 2;
                        continue;

                    }

                    if(GetBlock(x,y,z) == 134)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 135;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 135;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 135 && GetBlock(x,y-1,z) == 79)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                GetBlock(x,y,z) = 136;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                GetBlock(x,y,z) = 136;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 136 && GetBlock(x,y-1,z) == 79)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 16)
                            {
                                mainStatistics.cropsGrowned += 1;
                                GetBlock(x,y,z) = 137;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 25)
                            {
                                mainStatistics.cropsGrowned += 1;
                                GetBlock(x,y,z) = 137;
                                GetBlock(x,y-1,z) = 79;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 77)
                    {
                        if(rand() % 180 < 3)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 77;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 78)
                    {
                        if(rand() % 180 < 3)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 78;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 79 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 8 == 1)
                        {
                            GetBlock(x,y,z) = 2;
                            continue;
                        }
                    }
                    if(GetBlock(x,y,z) == 80 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 12 == 1)
                        {
                            GetBlock(x,y,z) = 79;
                            continue;
                        }
                    }

                    if(GetBlock(x,y,z) == 33 && GetBlock(x,y+1,z) == 0 && GetBlock(x,y-3,z) != 33 && GetBlock(x,y-3,z) != 0)
                    {
                        if(rand() % 4 == 1)
                        {
                            GetBlock(x,y+1,z) = 33;
                            continue;
                        }
                    }

                    if(GetBlock(x,y,z) == 112 && GetBlock(x,y+2,z) == 4 && GetBlock(x,y+1,z) == 0)
                    {
                        GetBlock(x,y+1,z) = 36; //make coblestone
                        continue;
                    }

                    if(GetBlock(x,y,z) == 112 && GetBlock(x,y-2,z) == 4 && GetBlock(x,y-1,z) == 0)
                    {
                        GetBlock(x,y-1,z) = 46; //make obsidian
                        continue;
                    }


                    if(GetBlock(x,y,z) == 121 && GetBlock(x,y-1,z) != 0 && GetBlock(x,y-1,z) != 4)
                    {
                        if(rand() % 7 == 1)
                        {
                            mainStatistics.treesGrowned += 1;
                            int height = 2 + rand() % 2;

                            for(int x2 = x - 2; x2 <= x + 2; x2 ++)
                            {
                                for(int z2 = z - 2; z2 <= z + 2; z2 ++)
                                {
                                    for(int y2 = y+height; y2 <= y+height+1; y2 ++)
                                    {
                                        if(x2 >= 0 && x2 <= 127 && z2 >= 0 && z2 <= 127)
                                        {
                                            GetBlock(x2,y2,z2) = 9;
                                        }
                                    }
                                }
                            }

                            for(int x2 = x - 1; x2 <= x + 1; x2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x2 >= 0 && x2 <= 127 && z >= 0 && z <= 127)
                                    {
                                        GetBlock(x2,y2,z) = 9;
                                    }
                                }
                            }

                            for(int z2 = z - 1; z2 <= z + 1; z2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x >= 0 && x <= 127 && z2 >= 0 && z2 <= 127)
                                    {
                                        GetBlock(x,y2,z2) = 9;
                                    }
                                }
                            }

                            for(int yy1 = y; yy1 <= y+height+2; yy1++)
                            {
                               GetBlock(x,yy1,z) = 8;
                            }
                        }
                    }
                }
            }
        }
    }
}


void CraftWorld::UpdateChunkBlocks2(int id)
{


    SimpleMeshChunk* MeshChunk = mChunks[id];

    int StartZ = MeshChunk->chunkStartZ;
    int StartY = MeshChunk->chunkStartY;
    int StartX = MeshChunk->chunkStartX;

    for (int z = StartZ; z < CHUNK_SIZE + StartZ; ++z)
    {
        for (int y = StartY; y < CHUNK_SIZE + StartY; ++y)
        {
            for (int x = StartX; x < CHUNK_SIZE + StartX; ++x)
            {
                if (BlockUpdate2(x,y,z) == 0)
                {
                    continue;
                }
                if(x > 0 && x < WORLD_SIZE && y > 0 && y < WORLD_SIZE && z > 0 && z < WORLD_SIZE)
                {
                    if(GetBlock(x,y,z) == 0)
                    {
                       continue;
                    }


                    if(GetBlock(x,y,z) == 2 && (GetBlock(x,y+1,z) == 0 || GetBlock(x,y+1,z) == 48 || GetBlock(x,y+1,z) == 119 || GetBlock(x,y+1,z) == 120 || GetBlock(x,y+1,z) == 77 || GetBlock(x,y+1,z) == 78) && GetBlockLight(x,y,z) > 172)
                    {
                        GetBlock(x,y,z) = 1;
                        continue;
                    }
                    if(GetBlock(x,y,z) == 1 && GetBlock(x,y+1,z) != 0 && GetBlock(x,y+1,z) != 119 && GetBlock(x,y+1,z) != 120 && GetBlock(x,y+1,z) != 48 && GetBlock(x,y+1,z) != 77 && GetBlock(x,y+1,z) != 78)
                    {
                        GetBlock(x,y,z) = 2;
                        continue;
                    }

                    if(GetBlock(x,y,z) == 134)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 32)
                            {
                                GetBlock(x,y,z) = 135;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 50)
                            {
                                GetBlock(x,y,z) = 135;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 135 && GetBlock(x,y-1,z) == 79)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 32)
                            {
                                GetBlock(x,y,z) = 136;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 50)
                            {
                                GetBlock(x,y,z) = 136;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 136 && GetBlock(x,y-1,z) == 79)
                    {
                        if(GetBlock(x,y-1,z) == 79)
                        {
                            if(rand() % 100 < 32)
                            {
                                mainStatistics.cropsGrowned += 1;
                                GetBlock(x,y,z) = 137;
                                continue;
                            }
                        }
                        if(GetBlock(x,y-1,z) == 80)
                        {
                            if(rand() % 100 < 50)
                            {
                                mainStatistics.cropsGrowned += 1;
                                GetBlock(x,y,z) = 137;
                                GetBlock(x,y-1,z) = 79;
                                continue;
                            }
                        }
                    }

                    if(GetBlock(x,y,z) == 79 && GetBlock(x,y+1,z) == 0)
                    {
                        if(rand() % 6 == 1)
                        {
                            GetBlock(x,y,z) = 2;
                            continue;
                        }
                    }
                    if(GetBlock(x,y,z) == 77)
                    {
                        if(rand() % 180 < 4)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 77;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 77;
                                }
                            }
                        }
                        continue;
                    }

                    if(GetBlock(x,y,z) == 78)
                    {
                        if(rand() % 180 < 4)
                        {
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x+1,y-1,z) != 0 && GetBlock(x+1,y,z) == 0)
                                {
                                    GetBlock(x+1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x-1,y-1,z) != 0 && GetBlock(x-1,y,z) == 0)
                                {
                                    GetBlock(x-1,y,z) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z-1) != 0 && GetBlock(x,y,z-1) == 0)
                                {
                                    GetBlock(x,y,z-1) = 78;
                                }
                            }
                            if(rand() % 2 == 1)
                            {
                                if(GetBlock(x,y-1,z+1) != 0 && GetBlock(x,y,z+1) == 0)
                                {
                                    GetBlock(x,y,z+1) = 78;
                                }
                            }
                        }
                        continue;
                    }


                    if(GetBlock(x,y,z) == 33 && GetBlock(x,y+1,z) == 0 && GetBlock(x,y-3,z) != 33 && GetBlock(x,y-3,z) != 0)
                    {
                        if(rand() % 2 == 1)
                        {
                            GetBlock(x,y+1,z) = 33;
                            continue;
                        }
                    }

                    if(GetBlock(x,y,z) == 112 && GetBlock(x,y+2,z) == 4 && GetBlock(x,y+1,z) == 0)
                    {
                        GetBlock(x,y+1,z) = 36; //make cobblestone
                        continue;
                    }

                    if(GetBlock(x,y,z) == 112 && GetBlock(x,y-2,z) == 4 && GetBlock(x,y-1,z) == 0)
                    {
                        GetBlock(x,y-1,z) = 46; //make obsidian
                        continue;
                    }

                    if(GetBlock(x,y,z) == 121 && GetBlock(x,y-1,z) != 0 && GetBlock(x,y-1,z) != 4)
                    {
                        if(rand() % 3 == 1)
                        {
                            mainStatistics.treesGrowned += 1;
                            int height = 2 + rand() % 2;

                            for(int x2 = x - 2; x2 <= x + 2; x2 ++)
                            {
                                for(int z2 = z - 2; z2 <= z + 2; z2 ++)
                                {
                                    for(int y2 = y+height; y2 <= y+height+1; y2 ++)
                                    {
                                        if(x2 >= 0 && x2 <= 127 && z2 >= 0 && z2 <= 127)
                                        {
                                            GetBlock(x2,y2,z2) = 9;
                                        }
                                    }
                                }
                            }

                            for(int x2 = x - 1; x2 <= x + 1; x2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x2 >= 0 && x2 <= 127 && z >= 0 && z <= 127)
                                    {
                                        GetBlock(x2,y2,z) = 9;
                                    }
                                }
                            }

                            for(int z2 = z - 1; z2 <= z + 1; z2 ++)
                            {
                                for(int y2 = y+height+2; y2 <= y+height+3; y2 ++)
                                {
                                    if(x >= 0 && x <= 127 && z2 >= 0 && z2 <= 127)
                                    {
                                        GetBlock(x,y2,z2) = 9;
                                    }
                                }
                            }

                            for(int yy1 = y; yy1 <= y+height+2; yy1++)
                            {
                               GetBlock(x,yy1,z) = 8;
                            }
                        }
                    }
                }
            }
        }
    }
}

void CraftWorld::SetAllChunksToUpdate()
{
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        mChunks[i]->needUpdate = true;
    }

    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        mTransparentChunks[i]->needUpdate = true;
    }
}

void CraftWorld::drawCubes(int i)
{

    sceGuEnable(GU_TEXTURE_2D);
    if(blockTypes[i].transparent)
        sceGuEnable(GU_BLEND);
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF |GU_COLOR_8888| GU_VERTEX_32BITF | GU_TRANSFORM_3D, blockTypes[i].points, 0, blockTypes[i].vertices);
    if(blockTypes[i].transparent)
        sceGuDisable(GU_BLEND);
    sceGuDisable(GU_TEXTURE_2D);
}


void CraftWorld::drawClouds()
{
    sceGuEnable(GU_TEXTURE_2D);
    sceGuEnable(GU_BLEND);
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF |GU_COLOR_8888| GU_VERTEX_32BITF | GU_TRANSFORM_3D, 600, 0, blockTypes[141].vertices);
    sceGuDisable(GU_BLEND);
    sceGuDisable(GU_TEXTURE_2D);

}


void CraftWorld::drawItems(int i)
{
    sceGuColor(0xFFFFFFFF);
    sceGuEnable(GU_TEXTURE_2D);
    sceGuEnable(GU_BLEND);
    sceGumDrawArray(GU_TRIANGLES, GU_TEXTURE_32BITF |GU_COLOR_8888| GU_VERTEX_32BITF | GU_TRANSFORM_3D, 6, 0, itemTypes[i-250].vertices);
        sceGuDisable(GU_BLEND);
        sceGuDisable(GU_TEXTURE_2D);
}

void CraftWorld::drawWorld(Frustum &camFrustum,bool camUpdate)
{
    drawnTriangles = 0;

    //normal not transparend chunks
    sceGuColor(0xFFFFFFFF);
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        if(mChunks[i]->trienglesCount > 0 || !mChunks[i]->created)
        {
            if(playerZoneBB.intersect(mChunks[i]->bBox))
            {
                if(camFrustum.BoxInFrustum(mChunks[i]->bBox) == Frustum::Intersects)
                {
                    //check if wee need to build vertices of this chunk
                    if((!mChunks[i]->created || mChunks[i]->needUpdate) && chunksCreatedInFrameCount == 0)
                    {
                        rebuildChunk(i);
                        chunksCreatedInFrameCount++;
                    }

                    mChunks[i]->drawChunk();
                    drawnTriangles += mChunks[i]->trienglesCount;
                }
            }
            else if(mChunks[i]->created)
            {
                mChunks[i]->reset();
            }
        }
    }

    for(unsigned int i = 0; i < mTransparentChunks.size(); i++)
    {
        if(mTransparentChunks[i]->trienglesCount > 0 || !mTransparentChunks[i]->created)
        {
            if(playerZoneBB.intersect(mTransparentChunks[i]->bBox))
            {
                if(camFrustum.BoxInFrustum(mTransparentChunks[i]->bBox) == Frustum::Intersects)
                {
                    //check if wee need to build vertices of this chunk
                    if((!mTransparentChunks[i]->created || mTransparentChunks[i]->needUpdate) && transparentchunksCreatedInFrameCount == 0)
                    {
                        rebuildTransparentChunk(i);
                        transparentchunksCreatedInFrameCount++;
                    }
                    sceGuEnable(GU_DEPTH_TEST);
                    sceGuEnable(GU_ALPHA_TEST);
                    sceGuEnable(GU_BLEND);

                    mTransparentChunks[i]->drawChunk();
                    drawnTriangles += mTransparentChunks[i]->trienglesCount;

                    sceGuDisable(GU_BLEND);
                    sceGuDisable(GU_ALPHA_TEST);
                    sceGuDisable(GU_DEPTH_TEST);
                }

            }
            else if(mTransparentChunks[i]->created)
            {
                mTransparentChunks[i]->reset();
            }
        }
    }
}

void CraftWorld::UpdatePlayerZoneBB(Vector3 playerPosition)
{
    playerPos = playerPosition;
    playerZoneBB = BoundingBox(Vector3(playerPosition.x - playerZoneSize.x,playerPosition.y - playerZoneSize.y,playerPosition.z - playerZoneSize.z),Vector3(playerPosition.x + playerZoneSize.x,playerPosition.y + playerZoneSize.y,playerPosition.z + playerZoneSize.z));
}

Vector3 CraftWorld::GetPlayerPos()
{
    return playerPos;
}

void CraftWorld::UpdateWorldTime(float dt)
{

    timee += dt;
    if(timee > 60.0f)
    {
        mainStatistics.minutesPlayed += 1;
        timee = 0;
    }

    worldTime += dt;

    //stuff that goes on tick
    //1 tick = 1 second

    //rebuilding chunks
    updateChunkTimer += dt;
    if(updateChunkTimer > 0.3f)//update time 1/4 second
    {
        chunksCreatedInFrameCount = 0;
        transparentchunksCreatedInFrameCount = 0;
        updateChunkTimer = 0.0f;
    }

    if(worldTime > 1.0f)
    {
        worldTime = 0.0f;
    }

    if(!freezeDayTime)
    {
        //world day/night time
        worldHour += dt;


        if(worldHour > 50.0f)//one game hour = 50 sec
        {
            worldHour = 0.0f;
            worldDayTime += 1.0f;
            if(worldDayTime > 23.0f)
            {
                worldDayTime = 0.0f;
                mainStatistics.daysInGame += 1;
            }

            SetWolrdTime(worldDayTime);
            SetAllChunksToUpdate();
        }
    }
}

int CraftWorld::GetBlockTypesCount()
{
    return blockTypes.size();
}

int CraftWorld::GetItemTypesCount()
{
    return itemTypes.size();
}

int CraftWorld::groundHeight(const int x, const int z)
{
    if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE) return -1;

    for (int y = WORLD_SIZE - 1; y >= 0; --y)
    {
        block_t Block = GetBlock(x, y, z);
        if (Block != 0 && Block != 4) return (y);
    }

    return -1;
}

int CraftWorld::groundHeightExcept(const int x, const int z, int bl)
{
    if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE) return -1;


    for (int y = WORLD_SIZE - 1; y >= 0; --y)
    {
        block_t Block = GetBlock(x, y, z);
        if(Block == bl)
        {
            continue;
        }
        if (Block != 0) return (y);
    }

    return -1;
}

int CraftWorld::groundHeightWater(const int x, const int z)
{
    if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE) return -1;

    for (int y = WORLD_SIZE - 1; y >= 0; --y)
    {
        block_t Block = GetBlock(x, y, z);
        if (Block != 0) return (y);
    }

    return -1;
}

int CraftWorld::getChunkId(Vector3 pos)
{
    for(unsigned int i = 0; i < mChunks.size(); i++)
    {
        if(mChunks[i]->bBox.contains(pos))
            return mChunks[i]->id;
    }

    return -1;
}

bool CraftWorld::SolidAtPoint(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_SIZE-1 || z >= WORLD_SIZE-1) return true;

    //don't collide with water and air
    if(BlockSolid(x,y,z) == 0)
    {
        //
        return false;
    }

    //collision
    return true;
}

int CraftWorld::BlockSoundAtPos(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_SIZE-1 || z >= WORLD_SIZE-1) return -1;

    return blockTypes[GetBlock(x,y,z)].soundType;
}

bool CraftWorld::SolidAtPointForPlayer(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    //outside the world so collision
    if (x <= 0 || y <= 0 || z <= 0  || x >= WORLD_SIZE-1 || y >= WORLD_SIZE-1 || z >= WORLD_SIZE-1) return true;

    //don't collide with water and air
    if(BlockSolid(x,y,z) == 0)
    {
        //4 corners
        if(SolidAtPoint(Vector3(pos.x-0.15f,pos.y,pos.z-0.15f))) return true;
        if(SolidAtPoint(Vector3(pos.x+0.15f,pos.y,pos.z+0.15f))) return true;
        if(SolidAtPoint(Vector3(pos.x+0.15f,pos.y,pos.z-0.15f))) return true;
        if(SolidAtPoint(Vector3(pos.x-0.15f,pos.y,pos.z+0.15f))) return true;
        //
        return false;
    }

    //collision
    return true;
}

bool CraftWorld::PlayerInWater(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE-1 || y >= WORLD_SIZE-1 || z >= WORLD_SIZE-1) return false;

    if(GetBlock(x,y,z) == 4 || GetBlock(x,y,z) == 32)
        return true;

    return false;
}

bool CraftWorld::PlayerInLava(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE-1 || y >= WORLD_SIZE-1 || z >= WORLD_SIZE-1) return false;

    if(GetBlock(x,y,z) == Lava::getID())
        return true;

    return false;
}

bool CraftWorld::PlayerInBlock(Vector3 pos)
{
    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE-1 || y >= WORLD_SIZE-1 || z >= WORLD_SIZE-1) return false;

    if(GetBlock(x,y,z) != Lava::getID() || GetBlock(x,y,z) != 4 || GetBlock(x,y,z) != 0)
        return true;

    return false;
}

block_t CraftWorld::BlockAtPoint(Vector3 pos)
{


    int x = pos.x;
    int y = pos.y;
    int z = pos.z;

    if (x < 0 || y < 0 || z < 0  || x >= WORLD_SIZE || y >= WORLD_SIZE || z >= WORLD_SIZE) return -1;

    return GetBlock(x,y,z);

}


void CraftWorld::BuildBlockSphere(int radius, block_t block, char X, char Y, char Z)
{
    float reference = 125 / 20.0f;

    int latitudes = (int)(radius * reference);
    int longitudes = (int)(latitudes/2);

    float latitude_increment = PI*2 / latitudes;
    float longitude_increment = PI / longitudes;

    for (float u = 0; u < PI*2; u += latitude_increment)
    {
        for (float t = 0; t < PI; t += longitude_increment)
        {

            float rad = radius;

            int x = X + (rad * sinf(t) * sinf(u));
            int y = Y + (rad * cosf(t));
            int z = Z + (rad * sinf(t) * cosf(u));

            if(x > X)
            {
                for(int x2 = x; x2 >= X - (x2-X); x2 --)
                {
                    if(x2 > 0 && x2 < 127 && z > 0 && z < 127 && y > 0 && y <127)
                    {
                        GetBlock(x2,y,z) = block;
                    }
                }
            }

            if(x < X)
            {
                for(int x2 = x; x2 <= X + (X-x2); x2 ++)
                {
                    if(x2 > 0 && x2 < 127 && z > 0 && z < 127 && y > 0 && y <127)
                    {
                        GetBlock(x2,y,z) = block;
                    }
                }
            }
        }
    }
}

void CraftWorld::BuildBlockSphere(int radius, block_t block, char X, char Y, char Z, block_t blockToChange)
{
    float reference = 125 / 20.0f;

    int latitudes = (int)(radius * reference);
    int longitudes = (int)(latitudes/2);

    float latitude_increment = PI*2 / latitudes;
    float longitude_increment = PI / longitudes;

    for (float u = 0; u < PI*2; u += latitude_increment)
    {
        for (float t = 0; t < PI; t += longitude_increment)
        {

            float rad = radius;

            int x = X + (rad * sinf(t) * sinf(u));
            int y = Y + (rad * cosf(t));
            int z = Z + (rad * sinf(t) * cosf(u));

            if(x > X)
            {
                for(int x2 = x; x2 >= X - (x2-X); x2 --)
                {
                    if(x2 > 0 && x2 < 127 && z > 0 && z < 127 && y > 0 && y <127)
                    {
                        if (GetBlock(x2,y,z) == blockToChange)
                        {
                            GetBlock(x2,y,z) = block;
                        }
                    }
                }
            }

            if(x < X)
            {
                for(int x2 = x; x2 <= X + (X-x2); x2 ++)
                {
                    if(x2 > 0 && x2 < 127 && z > 0 && z < 127 && y > 0 && y <127)
                    {
                        if (GetBlock(x2,y,z) == blockToChange)
                        {
                            GetBlock(x2,y,z) = block;
                        }
                    }
                }
            }
        }
    }
}


void CraftWorld::PutInInventory(int id, int num, bool st)
{
    for(int j = 35; j >= 0; j--)
    {
        if (invSt[j]==1)
        {
            if (invId[j]== id)
            {
                if(invAm[j] + num <= 64)
                {
                    invAm[j] += num;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        if (invId[j]== -1)
        {
            invSt[j] = st;
            invId[j] = id;
            invAm[j] = num;
            break;
        }
    }
}

int CraftWorld::FindDirId(int x, int y, int z)
{
    int o;
    o = -1;
    for(unsigned int i = 0; i < mDirects.size(); i++)
    {
        DirectionBlock* NewDirectionBlock = mDirects[i];
        if(NewDirectionBlock->X == x && NewDirectionBlock->Y == y && NewDirectionBlock->Z == z)
        {
            o = i;
            break;
        }
    }

    return o;
}
