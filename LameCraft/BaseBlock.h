#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <Aurora/Graphics/Vertex.h>

using namespace Aurora::Graphics;

typedef unsigned char block_t;

class BaseBlock
{
public:
	//texture info
	char textureRow;
	char upPlane;
	char downPlane;
	char sidePlane;
	char sidePlane2;
    char sidePlane3;
    char sidePlane4;
    int loot;
	//vertices to show in bar or in hand
	CraftPSPVertex *vertices;
	char points;

	//sound type
	char soundType;//0 grass,1 gravel,2 stone,3 wood

	//other properties
	bool editable;
	bool transparent;
	bool lightSource;
	bool blockSpecial;
	char material;
	bool update;
	bool solid;

	int furnItem;

	BaseBlock();
	virtual ~BaseBlock();

	static block_t getBaseID();

};

#endif
