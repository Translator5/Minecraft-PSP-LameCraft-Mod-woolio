#ifndef CraftWorld_H
#define CraftWorld_H

#include <string>

#include <Aurora/Math/Frustum.h>

#include "Blocks.h"
#include "Items.h"
#include "SimpleMeshChunk2.h"
#include "Furnace2.h"
#include "Chest2.h"
#include "DirectionBlock.h"

class CraftWorld
{
public:

	enum BlockSettings
	{
		 OpLighSource = 0x10, //16
		 OpSideRender = 0x20,
		 OpActAsLadder = 0x40,
		 OpLightTraveled = 0x80
	};

	CraftWorld();
	~CraftWorld();

    typedef struct Statistics
    {
        unsigned int blockPlaced;
        unsigned int blockDestroyed;
        unsigned int daysInGame;
        unsigned int minutesPlayed;
        unsigned int itemsCrafted;
        unsigned int itemsSmelted;
        unsigned int jumps;
        unsigned int dies;
        unsigned int foodEaten;
        unsigned int badlyFalls;
        unsigned int blocksWalked;
        unsigned int treesGrowned;
        unsigned int cropsGrowned;
        unsigned int soilPlowed;
        unsigned int timeInWater;
        unsigned int timeInAir;
        unsigned int damageRecieved;
    } st;

    typedef struct Options
    {
        bool cloudsRender;
        bool fastRendering;
        bool sunMoodRendering;
        bool sounds;
        bool music;
        bool headBob;
        bool worldBlockAnimation;
        bool fogRendering;
        bool fakeShadowsRendering;
        bool particles;
        bool guiDrawing;

        float fov;
        int horizontalViewDistance;
        int verticalViewDistance;
        int fogDistance;
    } opt;

    st mainStatistics;
    opt mainOptions;

	block_t& GetBlock (const int x, const int y, const int z) ;
	block_t& GetBlockLight (const int x, const int y, const int z);
	block_t& GetBlockSettings (const int x, const int y, const int z);
	block_t BlockAtPoint(Vector3 pos);

	//map creation
	void initWorld(int worldSize,int chunkSize);
	void initWorldBlocksLight();
	void initPutBlocksLight(const int x, const int z);

	void GetSpecialBlockVerts(int i,BaseBlock *blockType);
	void GetNormalBlockVerts(int i,BaseBlock *blockType);
	void GetItemVerts(int i,BaseItem *itemType);
	void GetCloudsVerts(BaseBlock *blockType);
	void buildblocksVerts();
	void buildcloudsVerts();
	void buildskyVerts();
    void setTextureSize(int texture,int chunk);

    void PutInInventory(int id, int num, bool st);

	//chunks handling
	void createChunks(const int StartX, const int StartY, const int StartZ);
	void createTransparentChunks(const int StartX, const int StartY, const int StartZ);
	void rebuildChunk(int id);
	void rebuildTransparentChunk(int id);
	void rebuildNearestChunks(int id,Vector3 pos);
	void createWorldChunkss();
	void SetAllChunksToUpdate();

	void GetSpecialBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent);
	void GetNormalBlock(int x,int y, int z,int &iVertex,SimpleMeshChunk* MeshChunk,block_t Block,bool transparent);

	//load/save options
	void SaveCompressedWorld(std::string filename);
	void LoadWorld(const char *filename);
	void LoadCompressedWorld(std::string filename);

	//lightening
	void InitLightValues();
	void SetWolrdTime(float time);
	void LightTravel(int x,int y,int z,int steps,int lightLevel);

	//
	void buildMap();
	void destroyMap();

	//rendering
	void drawWorld(Frustum &camFrustum,bool camUpdate);
	void drawCubes(int i);
	void drawClouds();
	void drawItems(int i);

	//pickin,collision etc
	int groundHeight (const int x, const int z);
	int groundHeightWater (const int x, const int z);
	int groundHeightExcept (const int x, const int z, int bl);
	int getChunkId(Vector3 pos);
	int BlockSoundAtPos(Vector3 pos);

	bool SolidAtPointForPlayer(Vector3 pos);
	bool SolidAtPoint(Vector3 pos);
	bool PlayerInWater(Vector3 pos);
	bool PlayerInLava(Vector3 pos);
	bool PlayerInBlock(Vector3 pos);

	bool BlockTransparentOrSpecial(const int x, const int y, const int z);
	bool BlockTransparentOrLightSource(const int x, const int y, const int z);
	bool BlockTransparent(const int x, const int y, const int z);
	bool BlockSpecial(const int x, const int y, const int z);
	bool BlockEditable(const int x, const int y, const int z);
	short BlockLoot(const int x, const int y, const int z);
	short BlockMaterial(const int x, const int y, const int z);
	bool BlockUpdate2(const int x, const int y, const int z);
	bool BlockSolid(const int x, const int y, const int z);

	bool LightSourceBlock(int id);
	bool CanPutBlockHere(const int x, const int y, const int z,int blockID);
	void SetLigtSourcePosition(const int x, const int y, const int z,int blockID);
	void CheckForTorchSupport(const int x, const int y, const int z,int blockID);
	void RemoveLigtSourceAtPosition(const int x, const int y, const int z,int blockID);
	void AddChunkToUpdate(const int x, const int y, const int z);
	void RebuildChunksLight(Vector3 pos,int currentChunk,int blockID);
	void UpdateLightAreaIn(Vector3 pos);
	void UpdateWorldLightForChunk(int chunkID);

	int GetDrawntTrianglesCount() { return drawnTriangles; }

	Vector3 GetPlayerPos();
	void UpdatePlayerZoneBB(Vector3 playerPosition);
	void UpdateWorldTime(float dt);
	int GetBlockTypesCount();
	int GetItemTypesCount();
	void UpdateChunkBlocks(int id);
	void UpdateChunkBlocks2(int id); //for chunk updater
	int FindDirId(int x, int y, int z);

    int invId[36];
    int invAm[36];
    bool invSt[36];
    int mId;
    int mAm;
    bool mSt;

    std::vector<BaseBlock> blockTypes;
	std::vector<BaseItem> itemTypes;

    float bright;

    int worldSeed;
    float HP; //health
    float HG; //hunger
    char OS; //oxygen supply
    char waterY;

	char worldName[50];
	int createdChunksCount;
	Vector3	fogColor;
	float worldDayTime;
	float worldTime;

	bool freezeDayTime;
	bool skyRender;
	unsigned short fogLevel;

	float sunTime;
	int worldVersion;
	float lightAngle;

	Vector3 playerZoneSize;

    std::vector<Chest*> mChests;
    std::vector<Furnace*> mFurnaces;
    std::vector<DirectionBlock*> mDirects;

    char mChestsize;
    char mFurnacesize;
    int mDirectsize;

    Vector3 lightColor;
    float skyTime;

    void BuildBlockSphere(int radius, block_t block, char X, char Y, char Z);
    void BuildBlockSphere(int radius, block_t block, char X, char Y, char Z, block_t blockToChange);

private:

	int WORLD_SIZE;
	int CHUNK_SIZE;

	int texutreSize;
	int textureChunk;
	float percent;

	std::vector<SimpleMeshChunk*> mChunks;
	std::vector<SimpleMeshChunk*> mTransparentChunks;

	block_t* m_Blocks;
	block_t* m_BlockLight;

	block_t* m_BlockSettings;

	float *data;

	//player zone aabb
	BoundingBox playerZoneBB;
	Vector3 playerPos;
	int chunksCreatedInFrameCount;
	int transparentchunksCreatedInFrameCount;
	float updateChunkTimer;
	bool updateChunksSwitch;

	//world time

	float worldHour;//1 game hour = 50 real seconds = 24 game hours = 20 real minutes

	//information
	int drawnTriangles;

	//transparent order rendering
	float lightShadowFactor;

	char cloudTexX;
	char cloudTexY;
	float timee;

	//lightining
	Vector3	ambientColor;
};


#endif
