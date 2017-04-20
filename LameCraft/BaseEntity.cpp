#include "BaseEntity.h"


BaseEntity::BaseEntity()
{
	vertices = NULL;
}

BaseEntity::~BaseEntity()
{
	if(vertices != NULL)
	{
		free(vertices);
	}
}

entity_t BaseEntity::getBaseID(){	return 0;}
