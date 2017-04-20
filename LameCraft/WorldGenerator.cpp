#include "WorldGenerator.h"
#include "CraftWorld2.h"
#include "LoadingScreen.h"

#define PI 3.1415926535897f
using namespace noisepp;

void WorldGenerator::initRandompMap(int worldSize,int chunkSize, CraftWorld *world,bool makeTrees,bool makePumpkins,bool makeTypes,bool makeWater,bool makeIron,bool makeCaves,bool makeCoal,bool makeGold,bool makeRedStone,bool makeDiamond,bool makeDirt,bool makeCanes,int seedII, int terrainBuilderI)
{
    LoadingScreen* loading = new LoadingScreen();
    //inicjuj mape
    int WORLD_SIZE = worldSize;
    int CHUNK_SIZE = chunkSize;


    if (seedII == 0)
    {
        seedII = rand() % 100000;
    }

    int seed = seedII;

    srand(seedII);

    world->worldSeed = seedII;


    //terrain settings for default terrain
    unsigned char grass = 1;
    unsigned char rock = 3;
    unsigned char dirt = 2;

    float x3 = 1 + (rand() % 28)*0.1f;
    float x4 = 0 + (rand() % 35)*0.1f;

    while (x3 == x4)
    {
        x3 = 0 + rand() % 3;
    }
    int Height = 64;

    PerlinModule* perlin = new PerlinModule();
    perlin->setSeed(seed);
    perlin->setQuality(noisepp::NOISE_QUALITY_FAST_STD);
    perlin->setOctaveCount(4);

    if(terrainBuilderI != 0)
    {
        float *data = new float[worldSize * worldSize];

        noisepp::utils::PlaneBuilder2D builder;
        builder.setModule(perlin);
        builder.setSize(worldSize, worldSize);


        builder.setBounds(0, 0, 1.5f-((rand() % 9)*0.1f), 1-((rand() % 4)*0.1f));

        builder.setDestination(data);
        builder.build ();

        //build map
        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                Height = data[x + z*WORLD_SIZE]* WORLD_SIZE/13 + WORLD_SIZE/2;
                //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

                for (int y = 0; y < Height; ++y)
                {
                    if(y == Height-1)
                        world->GetBlock(x, y, z) = grass;//grass
                    else if(y < Height-3)
                        world->GetBlock(x, y, z) = rock;
                    else
                        world->GetBlock(x, y, z) = dirt;
                }

            }
        }

        delete []data;

        if(terrainBuilderI == 2) // new ter builder
        {
        srand(seedII);

        float *data3 = new float[worldSize * worldSize];

        perlin->setSeed(seed + 1);
        perlin->setOctaveCount(2+rand() % 2);
        perlin->setPersistence(0.5 + (rand() % 60)*0.01f);
        //perlin.setLacunarity(3.5f);
        noisepp::utils::PlaneBuilder2D builder3;
        builder3.setModule(perlin);
        builder3.setSize(worldSize, worldSize);
        builder3.setBounds(0,0, x3, x3-0.5f);
        builder3.setDestination(data3);
        builder3.build ();

        int height1= 0;
        int heightDif = 0;

        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                height1 = data3[x + z*WORLD_SIZE]* 12 + WORLD_SIZE/2;
                heightDif = world->groundHeight(x,z) - height1;

                if (heightDif >= 0)
                    continue;

                //if (heightDif <= -4)
                    //continue;

                for (int y = height1; y > 0; --y)
                {
                    if(world->GetBlock(x, y-1, z) == rock)
                        break;


                    if(y == height1)
                        world->GetBlock(x, y, z) = grass;//grass
                    else if(y < height1-3)
                        world->GetBlock(x, y, z) = rock;
                    else
                        world->GetBlock(x, y, z) = dirt;
                }
            }
        }


        //delete tempdata
        delete []data3;
        }

    }
    else
    {
        float *data = new float[worldSize * worldSize];
        noisepp::PerlinModule perlin;
        perlin.setSeed(seed);
        perlin.setQuality(noisepp::NOISE_QUALITY_FAST_STD);

        //data = new float[worldSize * worldSize];



        noisepp::utils::PlaneBuilder2D builder;
        builder.setModule(perlin);
        builder.setSize(worldSize, worldSize);

            builder.setBounds(0.0, 0.0, 0.0, 0.0);
        builder.setDestination(data);
        builder.build ();

        int Height = 50;

        //build map
        for (int z = 0; z < WORLD_SIZE; ++z)
        {
            for (int x = 0; x < WORLD_SIZE; ++x)
            {
                Height = data[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
                //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

                for (int y = 0; y < Height; ++y)
                {
                        if(y == Height-1)
                            world->GetBlock(x, y, z) = grass;//grass
                        else if(y < Height-3)
                            world->GetBlock(x, y, z) = rock;
                        else
                            world->GetBlock(x, y, z) = dirt;
                }
            }
        }

        delete []data;
    }

	initBedrock(WORLD_SIZE, world);
	initBeachSand(WORLD_SIZE, world);

    if(terrainBuilderI != 0)
    {
        initWaterAndCanes(WORLD_SIZE, world);
    }

    if(makeTrees)
    {
        initGreatTrees(WORLD_SIZE, world);
        initTrees(WORLD_SIZE, world, perlin, seed);
    }

    initBiome(WORLD_SIZE, world, perlin, seed);

    initPumpkins(WORLD_SIZE, world);
    initIron(WORLD_SIZE, world);
    initCoal(WORLD_SIZE, world);
    initGold(WORLD_SIZE, world);
    initRedStone(WORLD_SIZE, world);
    initDiamond(WORLD_SIZE, world);
    initClay(WORLD_SIZE, world);
    initTypes(WORLD_SIZE, world);

    if(makeCaves) //worm cave generator
	{
        int x = 10 + rand() % 117;
        int z = 10 + rand() % 117;
        int y = world->groundHeight(x,z);

        int direct = rand() % 4;
        bool verDirect = 1;

        int numCaves = 4 + rand() % 3;
        int numSphere = 64 + rand() % 32;

        int rFactor;

        for(int i = 0; i <= numCaves; i++)
        {
            x = 10 + rand() % 117;
            z = 10 + rand() % 117;
            y = world->groundHeight(x,z);
            rFactor = 3 + rand() % 5;
            verDirect = 1;
            numSphere = 64 + rand() % 32;

            for(int j = 0; j <= numSphere; j++)
            {
                if(j % 10 == 0)
                {
                    rFactor = 2 + rand() % 5;
                }
                world->BuildBlockSphere(2,0,x,y,z);

                if (j == numSphere)
                {
                    int radius = 3+rand()%2;
                    world->BuildBlockSphere(radius, 0, x ,y, z);
                }

                if(rand() % rFactor == 0)
                {
                    direct = rand() % 4;
                }

                if(j > numSphere / 2)
                {
                    if(rand() % numSphere/20)
                    {
                        verDirect = rand() % 2;
                    }
                }

                if(y < 6)
                {
                    verDirect = 0;
                }

                if(verDirect == 1)
                {
                    y -= 2;
                }
                else
                {
                    y += 2;
                }

                switch(direct)
                {
                    case 0: x += 2; z += 2; break;
                    case 1: x -= 2; z -= 2; break;
                    case 2: z += 2; x -= 2; break;
                    case 3: z -= 2; x += 2; break;
                }
            }
        }
	}

    initLava(WORLD_SIZE, world);
    initDirt(WORLD_SIZE, world);

    loading->KillLoadingScreen();

        //caves?
    delete loading;
    delete perlin;

}

void WorldGenerator::initLava(int WORLD_SIZE, CraftWorld *world)
{
    char Num = 10 + rand() % 8;

    for(int i = 0; i <= Num; i++)
    {
        int x = 16 + rand() % 110;
        int z = 16 + rand() % 110;
        int y = 32 - rand() % 16;

        int w;


        w = 2 + rand() % 2;

        for(int X = x - w; X < x + w; X++)
        {
            for(int Z = z - w; Z < z + w; Z++)
            {

                    if(X > 0 && X < 127 && Z > 0 && Z < 127 && y > 0 && y < 127)
                     world->GetBlock(X,y,Z) = 112;

            }
        }
        for(int X = x - w-1; X < x + w+1; X++)
        {
            for(int Z = z - w-1; Z < z + w+1; Z++)
            {
                    if(X > 0 && X < 127 && Z > 0 && Z < 127 && y+1 > 0 && y+1 < 127)
                     world->GetBlock(X,y+1,Z) = 0;
            }
        }
        for(int X = x - w; X < x + w; X++)
        {
            for(int Z = z - w; Z < z + w; Z++)
            {
                    if(X > 0 && X < 127 && Z > 0 && Z < 127 && y+2 > 0 && y+2 < 127)
                     world->GetBlock(X,y+2,Z) = 0;
            }
        }
    }
}


void WorldGenerator::initGreatTrees(int WORLD_SIZE, CraftWorld *world)
{
    int NumTrees = 3 + rand() % 4;
    bool flag = 1;

    for(int i = 0; i <= NumTrees; i++)
    {
        flag = 1;

        int x = 10 + rand() % 108;
        int z = 10 + rand() % 108;
        int y = world->groundHeight(x,z) + 1;

        int treeHeight = 8;

        for(int X = x-1; X <= x+1; X++)
        {
            for(int Z = z-1; Z <= z+1; Z++)
            {
                for(int Y = y; Y < y + treeHeight; Y++)
                {
                    if(world->GetBlock(X,Y,Z) != 0)
                    {
                        flag = 0;
                        break;
                    }
                }
            }
        }
        if(world->GetBlock(x,y-1,z) != 1)
        {
            flag = 0;
        }

        if(flag == 1)
        {
            for(int X = x-1; X <= x+1; X++)
            {
                for(int Z = z-1; Z <= z+1; Z++)
                {
                    switch(rand()%7)
                    {
                    case 1:
                    if(world->GetBlock(X,world->groundHeight(X,Z)+1,Z) == 0 && world->GetBlock(X,world->groundHeight(X,Z),Z) != 0)
                    {
                        world->GetBlock(X,world->groundHeight(X,Z)+1,Z) = 77;
                    }
                    break;
                    case 2:
                    if(world->GetBlock(X,world->groundHeight(X,Z)+1,Z) == 0 && world->GetBlock(X,world->groundHeight(X,Z),Z) != 0)
                    {
                        world->GetBlock(X,world->groundHeight(X,Z)+1,Z) = 77;
                    }
                    break;
                    case 3:
                    if(world->GetBlock(X,world->groundHeight(X,Z)+1,Z) == 0 && world->GetBlock(X,world->groundHeight(X,Z),Z) != 0)
                    {
                        world->GetBlock(X,world->groundHeight(X,Z)+1,Z) = 78;
                    }
                    break;
                    }
                }
            }
            for(int y1 = y; y1 < y + treeHeight; y1 ++)
            {
                world->GetBlock(x,y1,z) = 8;
                if(y1 - y > treeHeight/3)
                {
                    if(rand() % 3 == 2)
                    {
                        switch(rand() % 4)
                        {
                        case 0:
                        for(int X = x; X <= x + 3; X++)
                        {
                            world->GetBlock(X,y1,z) = 8;
                            if(X == x+3)
                            {
                                world->BuildBlockSphere(2,9,X,y1,z,0);
                            }
                        }
                        break;
                        case 1:
                        for(int X = x-3; X <= x; X++)
                        {
                            world->GetBlock(X,y1,z) = 8;
                            if(X == x-3)
                            {
                                world->BuildBlockSphere(2,9,X,y1,z,0);
                            }
                        }
                        break;
                        case 2:
                        for(int Z = z; Z <= z + 3; Z++)
                        {
                            world->GetBlock(x,y1,Z) = 8;
                            if(Z == z+3)
                            {
                                world->BuildBlockSphere(2,9,x,y1,Z,0);
                            }
                        }
                        break;
                        case 3:
                        for(int Z = z-3; Z <= z; Z++)
                        {
                            world->GetBlock(x,y1,Z) = 8;
                            if(Z == z-3)
                            {
                                world->BuildBlockSphere(2,9,x,y1,Z,0);
                            }
                        }
                        break;
                        }
                    }
                }
                if(y1 - y == treeHeight - 2)
                {
                    world->BuildBlockSphere(3,9,x,y1,z,0);
                }
            }
        }
    }
}

void WorldGenerator::initBiome(int WORLD_SIZE, CraftWorld *world, PerlinModule* perlin, int seed)
{
    float *dataBiomes = new float[WORLD_SIZE * WORLD_SIZE];
    char frequency = 20 + rand() % 20; //0 - 100%

    perlin->setSeed(seed+5);
    perlin->setOctaveCount(6);
    perlin->setPersistence(0.5f);
    noisepp::utils::PlaneBuilder2D builderBiomes;
    builderBiomes.setModule(perlin);
    builderBiomes.setSize(WORLD_SIZE, WORLD_SIZE);
    builderBiomes.setBounds(2, 2, 6, 4);
    builderBiomes.setDestination(dataBiomes);
    builderBiomes.build ();

    char perlinHeight;

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            perlinHeight = dataBiomes[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
            //int Height = m_HeightMap.GetValue(x, z) * WORLD_SIZE/12 + WORLD_SIZE/2;

            if (perlinHeight > 80 - frequency*0.4)
            {
                if(world->GetBlock(x, world->groundHeight(x, z), z) == 0) continue;

                if(world->GetBlock(x, world->groundHeightExcept(x, z, 9), z) == 1)
                {
                    world->GetBlock(x, world->groundHeightExcept(x, z, 9), z) = 29; // snow
                }
                else if(world->GetBlock(x, world->groundHeightWater(x, z), z) == 4)
                {
                    world->GetBlock(x, world->groundHeightWater(x, z), z) = 32; // ice
                    continue;
                }

                if(world->GetBlock(x, world->groundHeight(x, z), z) != 93 && world->GetBlock(x, world->groundHeight(x, z), z) != 32)
                {
                    if(world->GetBlock(x, world->groundHeight(x, z)+1, z) == 0)
                    {
                        world->GetBlock(x, world->groundHeight(x, z)+1, z) = 93;
                    }
                }
            }
        }
    }
    delete [] dataBiomes;
}

void WorldGenerator::initWaterAndCanes(int WORLD_SIZE, CraftWorld *world)
{

        for (int z = 0; z < WORLD_SIZE; z++)
        {
            for (int x = 0; x < WORLD_SIZE; x++)
            {
                if (world->GetBlock(x,62,z) == 0)
                {
                    world->GetBlock(x,62,z) = 4;
                    if (world->GetBlock(x+1,62,z) == 7) //placing canes
                    {
                        if(rand()% 45 == 1)
                        {
                            char height = rand() % 3;
                            for(int k = 1; k < 2+height; k++)
                            {
                                world->GetBlock(x+1,62+k,z) = 33;
                            }
                        }
                    }
                    if (world->GetBlock(x-1,62,z) == 7) //placing canes
                    {
                        if(rand()% 45 == 1)
                        {
                            char height = 1+ rand() % 2;
                            for(int k = 1; k < 2+height; k++)
                            {
                                world->GetBlock(x-1,62+k,z) = 33;
                            }
                        }
                    }
                    if (world->GetBlock(x,61,z) == 1)
                    {
                        world->GetBlock(x,61,z) = 2;
                        continue;
                    }
                    for(int y = 61; y >= 50; y--)
                    {
                        if (world->GetBlock(x,y,z) != 0)
                            break;


                        if (world->GetBlock(x,y+1,z) == 4)
                        {
                            world->GetBlock(x,y,z) = 4;
                        }
                        if (world->GetBlock(x,y-1,z) == 1)
                        {
                            world->GetBlock(x,y-1,z) = 2;
                        }
                    }
                }
            }
        }

}

void WorldGenerator::initBedrock(int WORLD_SIZE, CraftWorld *world)
{
        for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            world->GetBlock(x, 0, z) = IronBlock::getID();//last one in set
        }
    }

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            short r = rand() % 2;
            if (r == 1)
            {
            world->GetBlock(x, 1, z) = IronBlock::getID();//last one in set
            }
        }
    }

    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            short r = rand() % 3;
            if (r == 1)
            {
            world->GetBlock(x, 2, z) = IronBlock::getID();//last one in set
            }
        }
    }
}

void WorldGenerator::initBeachSand(int WORLD_SIZE, CraftWorld *world)
{
    for (int z = 0; z < WORLD_SIZE; ++z)
    {
        for (int x = 0; x < WORLD_SIZE; ++x)
        {
            if (world->GetBlock(x,63,z) != 0 && world->GetBlock(x,64,z) == 0)
            {
                world->GetBlock(x,63,z) = 7;
                world->GetBlock(x,62,z) = 7;
            }
            if (world->GetBlock(x,62,z) != 0 && world->GetBlock(x,63,z) == 0)
            {
                world->GetBlock(x,62,z) = 7;
                world->GetBlock(x,61,z) = 7;
            }
        }
    }
}

void WorldGenerator::initTrees(int WORLD_SIZE, CraftWorld *world, PerlinModule* perlin, int seed)
{
    float *dataTrees = new float[WORLD_SIZE * WORLD_SIZE];
    perlin->setSeed(seed+4);
    perlin->setOctaveCount(2 + rand() % 6);
    perlin->setPersistence(0.5f + (rand() % 10 *0.1f));
    noisepp::utils::PlaneBuilder2D builderTrees;
    builderTrees.setModule(perlin);
    builderTrees.setSize(WORLD_SIZE, WORLD_SIZE);
    builderTrees.setBounds(1 + rand() % 3, 1, 6, 1 + rand() % 3);
    builderTrees.setDestination(dataTrees);
    builderTrees.build ();

    char perlinHeight;
    char woodBlock;

    for (int Z = 0; Z < WORLD_SIZE; Z += 4 +rand()%4)
    {
        for (int x = 0; x < WORLD_SIZE; x += 4 +rand()%4)
        {
            int z = Z + (-2 + rand() % 3);

            if(x < 0 || x > 127 || z < 0 || z > 127)
            {
                continue;
            }
            perlinHeight = dataTrees[x + z*WORLD_SIZE]* WORLD_SIZE/12 + WORLD_SIZE/2;
            if(perlinHeight >  70)
            {
                char y = world->groundHeight(x,z);
                char TrunkHeight = 5;//rand() % 5 + 4;


                //check if there is an water on there or another tree
                bool flag = 1;
                for (int y1 = y+1; y1 < y + 1 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
                {
                    if(world->GetBlock(x, y1, z) != 0)
                    {
                        flag = 0;
                        break;
                    }
                }
                if(world->GetBlock(x, y, z) != 1)
                {
                    flag = 0;
                }

                if(flag == 0)continue;

                if(rand() % 8 == 1)
                {
                    woodBlock = 31;
                    TrunkHeight = 4 + rand() % 2;
                }
                else
                {
                    woodBlock = 8;
                    TrunkHeight = 3 + rand() % 2;
                }
                //Create the tree trunk
                for (int y1 = y + 1; y1 < y + 2 + TrunkHeight && y1 < WORLD_SIZE; ++y1)
                {
                    block_t& Block = world->GetBlock(x, y1, z);
                    if (Block == 0) Block = woodBlock;
                }

                //create my leaves
                for(int yy = 0; yy < 2; yy++)
                {
                    for(int xx = 0; xx < 5; xx++)
                    {
                        for(int zz = 0; zz < 3; zz++)
                        {
                            int x1 = xx + x - 2;// :D - what a shitty code
                            int y1 = yy + y + TrunkHeight - 1;
                            int z1 = zz + z - 1;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 9;
                        }
                    }
                }


                for(int yy = 0; yy < 2; yy++)
                {
                    for(int xx = 0; xx < 3; xx++)
                    {

                            int x1 = xx + x - 1;// :D - what a shitty code
                            int y1 = yy + y + TrunkHeight + 1;
                            int z1 = z;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 9;
                    }
                }


                for(int xx = 0; xx < 3; xx++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {

                        int x1 = xx + x - 1;// :D - what a shitty code
                        int y1 = y + TrunkHeight + 1;
                        int z1 = zz + z - 1;
                        int rand1 = rand() % 8;

                        if (rand1 > 6)
                        {
                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 9;
                        }
                    }
                }

                for(int yy = 0; yy < 2; yy++)
                {
                    for(int zz = 0; zz < 3; zz++)
                    {

                            int x1 = x;// :D - what a shitty code
                            int y1 = yy + y + TrunkHeight + 1;
                            int z1 = zz + z - 1;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 9;
                    }
                }

                for(int yy = 0; yy < 2; yy++)
                {
                    for(int xx = 0; xx < 3; xx++)
                    {
                        for(int zz = 0; zz < 5; zz++)
                        {
                            int x1 = xx + x - 1;// :D - what a shitty code
                            int y1 = yy + y + TrunkHeight - 1;
                            int z1 = zz + z - 2;

                            if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                            if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                            block_t& Block = world->GetBlock(x1, y1, z1);
                            if (Block == 0) Block = 9;
                        }
                    }
                }

                for(int yy = 0; yy < 2; yy++)
                {
                    int x1 = x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight - 1;
                    int z1 = z - 2;
                    int rand1 = rand() % 3;

                    if (rand1 != 1)
                    {
                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }

                for(int yy = 0; yy < 2; yy++)
                {
                    int x1 = x + 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight - 1;
                    int z1 = z - 2;
                    int rand1 = rand() % 3;

                    if (rand1 != 1)
                    {
                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }

                for(int yy = 0; yy < 2; yy++)
                {
                    int x1 = x - 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight - 1;
                    int z1 = z + 2;
                    int rand1 = rand() % 3;

                    if (rand1 != 1)
                    {
                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }

                for(int yy = 0; yy < 2; yy++)
                {
                    int x1 = x + 2;// :D - what a shitty code
                    int y1 = yy + y + TrunkHeight - 1;
                    int z1 = z + 2;
                    int rand1 = rand() % 3;

                    if (rand1 != 1)
                    {
                        if (x1 < 0 || y1 < 0 || z1 < 0) continue;
                        if (x1 >= WORLD_SIZE || y1 >= WORLD_SIZE || z1 >= WORLD_SIZE) continue;

                        block_t& Block = world->GetBlock(x1, y1, z1);
                        if (Block == 0) Block = 9;
                    }
                }
            }
        }
    }

    delete[] dataTrees;
}

void WorldGenerator::initPumpkins(int WORLD_SIZE, CraftWorld *world)
{
    char NumPumpkinsSpawns = 3 + rand() % 6;
    char Frequency = 7; // 1 - 100

    for (int i = 0; i < NumPumpkinsSpawns; ++i)
    {
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        //check if there is an water on there or another tree
        unsigned short rad = 0;


                for(int x2 = x-3; x2 < x+3; ++x2)
                {
                    for(int z2 = z-3; z2 < z+3; ++z2)
                    {
                        if (x2 > 0 && x2 < WORLD_SIZE && z2 > 0 && z2 < WORLD_SIZE)
                        {

                            rad = rand() % 100;

                            if (rad > Frequency)
                                continue;

                            if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1 || world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 2)
                            {
                                if(world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) == 0)
                                {
                                    short rad2 = rand() % 4;

                                    switch(rad2)
                                    {
                                    case 0: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=74; break;
                                    case 1: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=122; break;
                                    case 2: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=123; break;
                                    case 3: world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)=124; break;
                                    }
                                }
                            }
                        }
                    }



        }


    }
}

void WorldGenerator::initTypes(int WORLD_SIZE, CraftWorld *world) //generate flowers
{

    char NumTypes = 70+rand() % 100; // 255 - max

    unsigned char NumSpecies = 2;
    short Species[NumSpecies];

    Species[0] = 119; //yellow flower
    Species[1] = 120; //red flower

    for (char i = 0; i < NumTypes; ++i)
    {
        //Choose the tpumpkin position
        int x2 = rand() % WORLD_SIZE;
        int z2 = rand() % WORLD_SIZE;

        char rad2 = rand() % NumSpecies;

        if(world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 1 || world->GetBlock(x2, world->groundHeight(x2, z2), z2 ) == 2)
        {
            if(world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2 ) == 0)
            {
                world->GetBlock(x2, world->groundHeight(x2, z2)+1, z2)= Species[rad2];
            }
        }

    }
}

void WorldGenerator::initIron(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 700;
    short Ore = 41;
    char HighestLayer = 64;
    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 3 + rand() % 3;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = HighestLayer - rand() % HighestLayer-3;

        for(int j = 0; j < NumOreBlocks; j++)
        {
            if(x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
            {
                if(world->GetBlock(x,y,z) == 3)
                world->GetBlock(x,y,z) = Ore;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}

void WorldGenerator::initCoal(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 950;
    short Ore = 42;
    char HighestLayer = 100;
    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 4 + rand() % 3;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = HighestLayer - rand() % HighestLayer-3;

        for(int j = 0; j < NumOreBlocks; j++)
        {
            if(x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
            {
                if(world->GetBlock(x,y,z) == 3)
                world->GetBlock(x,y,z) = Ore;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}

void WorldGenerator::initGold(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 128;
    short Ore = 5;
    char HighestLayer = 32;
    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 2 + rand() % 7;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = HighestLayer - rand() % HighestLayer-3;

        for(int j = 0; j < NumOreBlocks; j++)
        {
            if(x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
            {
                if(world->GetBlock(x,y,z) == 3)
                world->GetBlock(x,y,z) = Ore;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}

void WorldGenerator::initRedStone(int WORLD_SIZE, CraftWorld *world)//44
{
    int NumOres = 160;
    short Ore = 44;
    char HighestLayer = 19;
    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 1 + rand() % 10;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = HighestLayer - rand() % HighestLayer-3;

        for(int j = 0; j <= NumOreBlocks; j++)
        {
            if(x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
            {
                if(world->GetBlock(x,y,z) == 3)
                world->GetBlock(x,y,z) = Ore;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}

void WorldGenerator::initDiamond(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 60;
    short Ore = 43;
    char HighestLayer = 13;
    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 3 + rand() % 3;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = HighestLayer - rand() % HighestLayer-3;

        for(int j = 0; j <= NumOreBlocks; j++)
        {
            if(x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
            {
                if(world->GetBlock(x,y,z) == 3)
                world->GetBlock(x,y,z) = Ore;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}


void WorldGenerator::initClay(int WORLD_SIZE, CraftWorld *world)
{
    int NumOres = 40 + rand() % 30;

    char NumOreBlocks;

    for (int i = 0; i < NumOres; ++i)
    {
        NumOreBlocks = 8 + rand() % 8;
        //Choose the tpumpkin position
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 64 - rand() % 16;

        for(int j = 0; j <= NumOreBlocks; j++)
        {
            if(x > 0 && x < 127 && z > 0 && z < 127 && y > 0 && y < 127)
            {
                if(world->GetBlock(x,y,z) == 7 || ((world->GetBlock(x,y,z) == 2 && world->GetBlock(x,y+1,z) == 4)))
                world->GetBlock(x,y,z) = 99;
            }
            switch(rand() % 6)
            {
                case 0: x += 1; break;
                case 1: x -= 1; break;
                case 2: z += 1; break;
                case 3: z -= 1; break;
                case 4: y += 1; break;
                case 5: y -= 1; break;
            }
        }
    }
}


void WorldGenerator::initDirt(int WORLD_SIZE, CraftWorld *world)
{
    int NumBlocks = 500;
    char radius = 2 + rand() % 3;

    short PlaceBlock = 2;

    for (int i = 0; i < NumBlocks; ++i)
    {
        int x = rand() % WORLD_SIZE;
        int z = rand() % WORLD_SIZE;
        int y = 80 - rand() % 78;

        world->BuildBlockSphere(radius, PlaceBlock, x, y, z, RockBlock::getID());

    }
}



