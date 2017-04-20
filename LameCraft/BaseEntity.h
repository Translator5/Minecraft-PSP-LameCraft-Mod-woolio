#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <Aurora/Graphics/Vertex.h>

using namespace Aurora::Graphics;

typedef unsigned short entity_t;

class BaseEntity
{
public:
	//vertices to show in bar or in hand
	CraftPSPVertex *vertices;

	BaseEntity();
	virtual ~BaseEntity();

	static entity_t getBaseID();

};

#endif
