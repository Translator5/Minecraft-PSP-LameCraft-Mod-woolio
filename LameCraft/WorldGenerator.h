#ifndef WorldGenerator_H
#define WorldGenerator_H

#include <Aurora/Math/Frustum.h>
#include <math.h>
#include <psptypes.h>

#include <noisepp/Noise.h>
#include <noisepp/NoiseUtils.h>
#include <noisepp/NoiseBuilders.h>

class CraftWorld;
using namespace noisepp;

class WorldGenerator
{
	public:
		void initRandompMap(int worldSize,int chunkSize, CraftWorld *world, bool makeTrees,bool makePumpkins,bool makeTypes,bool makeWater,bool makeIron,bool makeCaves,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seedII, int terrainBuilderI);
		void initTrees(int WORLD_SIZE,  CraftWorld *world, PerlinModule* perlin, int seed);
		void initGreatTrees(int WORLD_SIZE,  CraftWorld *world);
		void initPumpkins(int WORLD_SIZE,  CraftWorld *world);

		void initTypes(int WORLD_SIZE, CraftWorld *world);
		void initLavaPools(int WORLD_SIZE, CraftWorld *world);
		void initBiome(int WORLD_SIZE, CraftWorld *world, PerlinModule* perlin, int seed);

		void initWaterAndCanes(int WORLD_SIZE, CraftWorld *world);
		void initBedrock(int WORLD_SIZE, CraftWorld *world);
        void initBeachSand(int WORLD_SIZE, CraftWorld *world);

        void initIron(int WORLD_SIZE, CraftWorld *world);
		void initCoal(int WORLD_SIZE, CraftWorld *world);
		void initGold(int WORLD_SIZE, CraftWorld *world);
		void initRedStone(int WORLD_SIZE, CraftWorld *world);
		void initDiamond(int WORLD_SIZE, CraftWorld *world);

        void initClay(int WORLD_SIZE, CraftWorld *world);
		void initDirt(int WORLD_SIZE, CraftWorld *world);
		void initLava(int WORLD_SIZE, CraftWorld *world);
};

#endif
