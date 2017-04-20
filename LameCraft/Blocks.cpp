#include "Blocks.h"



GrassBlock::GrassBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 0;
	downPlane = 2;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 0;

	loot = 2;
	material = 3;
	update = 1;
	solid = true;

}

block_t GrassBlock::getID(){ return 1;}

DirtBlock::DirtBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 1;

	loot = 2;
	material = 3;
	update = 1;
	solid = true;

}

block_t DirtBlock::getID(){ return 2;}


RockBlock::RockBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 36;
	material = 2;
	update = 0;
	solid = true;

}

block_t RockBlock::getID(){ return 3;}


WaterBlock::WaterBlock():BaseBlock()
{
	textureRow = 3;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
	editable = false;
	transparent = true;
	soundType = -1;
    blockSpecial = true;
    solid = false;


}

block_t WaterBlock::getID(){ return 4;}

GoldBlock::GoldBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 5;
	material = 2;
	solid = true;

	furnItem = 280;

}

block_t GoldBlock::getID(){ return 5;}

LadderBlock::LadderBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = true;
	soundType = 3;

	loot = 6;
	material = 1;
	solid = true;

}
block_t LadderBlock::getID(){ return 6;}


SandBlock::SandBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 5;

	loot = 7;
	material = 3;
	update = 1;
	solid = true;

	furnItem = 40;

}
block_t SandBlock::getID(){ return 7;}


WoodBlock::WoodBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 8;
	material = 1;
	solid = true;

	furnItem = 277;

}
block_t WoodBlock::getID(){ return 8;}

LeavesBlock::LeavesBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = 1;
	soundType = 0;
	blockSpecial = 1;

	loot = 9;
	material = 4;
	solid = true;

}
block_t LeavesBlock::getID(){ return 9;}


GrayWoolBlock::GrayWoolBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 10;
	material = 4;
	solid = true;

}
block_t GrayWoolBlock::getID(){ return 10;}


BlackWoolBlock::BlackWoolBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 11;
	solid = true;

}
block_t BlackWoolBlock::getID(){ return 11;}


RedWoolBlock::RedWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 12;
	solid = true;

}
block_t RedWoolBlock::getID(){ return 12;}


DarkGreyWoolBlock::DarkGreyWoolBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 13;
	solid = true;

}
block_t DarkGreyWoolBlock::getID(){ return 13;}



BrownWoolBlock::BrownWoolBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 14;
	solid = true;

}
block_t BrownWoolBlock::getID(){ return 14;}


LightBlackWoolBlock::LightBlackWoolBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 15;
	solid = true;

}
block_t LightBlackWoolBlock::getID(){ return 15;}



PinkWoolBlock::PinkWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 16;
	solid = true;

}
block_t PinkWoolBlock::getID(){ return 16;}


LightGreenWoolBlock::LightGreenWoolBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 17;
	solid = true;

}
block_t LightGreenWoolBlock::getID(){ return 17;}

YellowWoolBlock::YellowWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 18;
	solid = true;

}
block_t YellowWoolBlock::getID(){ return 18;}

BlueWoolBlock::BlueWoolBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 19;
	solid = true;

}
block_t BlueWoolBlock::getID(){ return 19;}

LightBlueWoolBlock::LightBlueWoolBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 20;
	solid = true;

}
block_t LightBlueWoolBlock::getID(){ return 20;}

FioletWoolBlock::FioletWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;
	loot = 21;
	solid = true;

}
block_t FioletWoolBlock::getID(){ return 21;}

PastelWoolBlock::PastelWoolBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 22;
	solid = true;

}
block_t PastelWoolBlock::getID(){ return 22;}

LightFioletWoolBlock::LightFioletWoolBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;


	loot = 23;
	solid = true;

}
block_t LightFioletWoolBlock::getID(){ return 23;}

OrangeWoolBlock::OrangeWoolBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 24;
	solid = true;

}
block_t OrangeWoolBlock::getID(){ return 24;}

CactusBlock::CactusBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 0;
	downPlane = 2;
	sidePlane = 1;
	editable = true;
	transparent = true;
    blockSpecial = true;
	soundType = 3;

	loot = 25;
	material = 1;
	update = 1;
	solid = true;

}
block_t CactusBlock::getID(){ return 25;}

AllSnowBlock::AllSnowBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 6;

	loot = 26;
	solid = true;

}
block_t AllSnowBlock::getID(){ return 26;}

BrickBlock::BrickBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;

	loot = 27;
	material = 2;
	solid = true;

}
block_t BrickBlock::getID(){ return 27;}

CageBlock::CageBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;
	transparent = true;
	soundType = 2;

	loot = 28;
	material = 2;
	solid = true;

}
block_t CageBlock::getID(){ return 28;}

SnowBlock::SnowBlock():BaseBlock()
{
	textureRow = 0;

	upPlane = 4;
	downPlane = 2;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 6;

	loot = 2;
	material = 3;
	solid = true;

}
block_t SnowBlock::getID(){ return 29;}

DarkWoodBlock::DarkWoodBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 30;
	material = 1;
	solid = true;

}
block_t DarkWoodBlock::getID(){ return 30;}

WhiteWoodBlock::WhiteWoodBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 3;

	loot = 31;
	material = 1;
	solid = true;

	furnItem = 277;

}
block_t WhiteWoodBlock::getID(){ return 31;}

IceBlock::IceBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = -1;
	solid = true;

}
block_t IceBlock::getID(){ return 32;}

CaneBlock::CaneBlock():BaseBlock()
{
	textureRow = 5;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 3;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 293;
    update = 1;
    solid = false;

}
block_t CaneBlock::getID(){ return 33;}

BoxBlock::BoxBlock():BaseBlock() // planks
{
	textureRow = 4;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 3;

    loot = 34;
    material = 1;
    solid = true;

}
block_t BoxBlock::getID(){ return 34;}

ShelfBlock::ShelfBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 1;
	editable = true;
	transparent = false;
	soundType = 3;

    loot = 35;
    solid = true;

}
block_t ShelfBlock::getID(){ return 35;}

CobbleStone::CobbleStone():BaseBlock()
{
	textureRow = 4;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 2;

    loot = 36;
    material = 2;
    solid = true;

    furnItem = 3;

}
block_t CobbleStone::getID(){ return 36;}

DrySandBlock::DrySandBlock():BaseBlock()
{
	textureRow = 4;

	upPlane = 8;
	downPlane = 8;
	sidePlane = 8;
	editable = true;
	transparent = false;
	soundType = 1;

    loot = 36;
    solid = true;

}
block_t DrySandBlock::getID(){ return 37;}

SnowLewesBlock::SnowLewesBlock():BaseBlock()
{
	textureRow = 2;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 0;

    loot = 37;
    solid = true;

}
block_t SnowLewesBlock::getID(){ return 38;}

Sponge::Sponge():BaseBlock()
{
	textureRow = 3;

	upPlane = 10;
	downPlane = 10;
	sidePlane = 10;
	editable = true;
	transparent = false;
	soundType = 1;

    loot = 38;
    solid = true;

}
block_t Sponge::getID(){ return 39;}

GlassBlock::GlassBlock():BaseBlock()
{
	textureRow = 3;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;
	transparent = true;
	soundType = 2;

    loot = -1;
    solid = true;

}
block_t GlassBlock::getID(){ return 40;}

IronOre::IronOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 2;

    loot = 41;
    material = 2;
    solid = true;

    furnItem = 278;
}
block_t IronOre::getID(){ return 41;}

CoalOre::CoalOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 4;
	downPlane = 4;
	sidePlane = 4;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 277;
	material = 2;
	solid = true;

	furnItem = 277;

}
block_t CoalOre::getID(){ return 42;}

DiamondOre::DiamondOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 5;
	downPlane = 5;
	sidePlane = 5;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 279;
	material = 2;
	solid = true;

	furnItem = 279;

}
block_t DiamondOre::getID(){ return 43;}

RedstoneOre::RedstoneOre():BaseBlock()
{
	textureRow = 6;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 44;
	material = 2;
	solid = true;

	furnItem = 44;

}
block_t RedstoneOre::getID(){ return 44;}

SlamRockBlock::SlamRockBlock():BaseBlock()
{
	textureRow = 6;

	upPlane = 7;
	downPlane = 7;
	sidePlane = 7;
	editable = true;
	transparent = false;
	soundType = 2;

	material = 2;
	solid = true;

}
block_t SlamRockBlock::getID(){ return 45;}

Obsidian::Obsidian():BaseBlock()
{
	textureRow = 5;

	upPlane = 6;
	downPlane = 6;
	sidePlane = 6;
	editable = true;
	transparent = false;
	soundType = 2;

	loot = 46;
	material = 5;
	solid = true;

}
block_t Obsidian::getID(){ return 46;}

JackOLantern::JackOLantern():BaseBlock()
{
	textureRow = 7;

	upPlane = 0;
	downPlane = 1;
	sidePlane = 2;
	editable = true;
	transparent = false;
	soundType = 3;
	lightSource = true;
	solid = true;

}
block_t JackOLantern::getID(){ return 47;}

Torch::Torch():BaseBlock()
{
	textureRow = 7;

	upPlane = 3;
	downPlane = 3;
	sidePlane = 3;
	editable = true;
	transparent = false;
	soundType = 2;
	lightSource = true;
	blockSpecial = true;

    loot = 48;
    solid = false;

}
block_t Torch::getID(){ return 48;}

Door1::Door1():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = true;
    material = 1;

}
block_t Door1::getID(){ return 49;}

Door2::Door2():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = true;
    material = 1;
}
block_t Door2::getID(){ return 50;}

Door3::Door3():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = true;
    material = 1;

}
block_t Door3::getID(){ return 51;}

Door4::Door4():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = true;
    material = 1;

}
block_t Door4::getID(){ return 52;}

Door5::Door5():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = false;
    material = 1;

}
block_t Door5::getID(){ return 53;}

Door6::Door6():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = false;
    material = 1;
}
block_t Door6::getID(){ return 54;}

Door7::Door7():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = false;
    material = 1;
}
block_t Door7::getID(){ return 55;}

Door8::Door8():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = false;
    material = 1;
}
block_t Door8::getID(){ return 56;}

Door9::Door9():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = true;
    material = 1;
}
block_t Door9::getID(){ return 57;}

Door10::Door10():BaseBlock()
{
	textureRow = 3;

	upPlane = 11;
	downPlane = 11;
	sidePlane = 11;
	editable = true;
	transparent = true;
	soundType = 2;
	blockSpecial = true;

    loot = 306;
    solid = false;
    material = 1;
}
block_t Door10::getID(){ return 58;}

WoodenFence::WoodenFence():BaseBlock()
{
	textureRow = 4;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
    blockSpecial = true;

	solid = true;
	loot = 59;
	material = 1;

}
block_t WoodenFence::getID(){ return 59;}

CobbleStair1::CobbleStair1():BaseBlock()
{
    textureRow = 4;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 60;
    material = 1;
    solid = true;
    points = 60;

}
block_t CobbleStair1::getID(){ return 60;}

CobbleStair2::CobbleStair2():BaseBlock()
{
    textureRow = 4;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 60;
    material = 1;
    solid = true;
    points = 60;

}
block_t CobbleStair2::getID(){ return 61;}

CobbleStair3::CobbleStair3():BaseBlock()
{
    textureRow = 4;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 60;
    material = 1;
    solid = true;
    points = 60;

}
block_t CobbleStair3::getID(){ return 62;}

CobbleStair4::CobbleStair4():BaseBlock()
{
    textureRow = 4;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 60;
    material = 1;
    solid = true;
    points = 60;
}
block_t CobbleStair4::getID(){ return 63;}

Diamond::Diamond():BaseBlock()
{
	textureRow = 8;

	upPlane = 2;
	downPlane = 2;
	sidePlane = 2;
	editable = true;
	transparent = false;

    loot = 64;
    material = 2;
    solid = true;

}
block_t Diamond::getID(){ return 64;}

Gold::Gold():BaseBlock()
{
	textureRow = 8;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;
	transparent = false;

    loot = 65;
    material = 2;
    solid = true;

}
block_t Gold::getID(){ return 65;}


Iron::Iron():BaseBlock()
{
	textureRow = 8;

	upPlane = 0;
	downPlane = 0;
	sidePlane = 0;
	editable = true;
	transparent = false;
	soundType = 2;

    loot = 66;
    material = 2;
    solid = true;

}
block_t Iron::getID(){ return 66;}

BrickStair1::BrickStair1():BaseBlock()
{
    textureRow = 4;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 67;
    material = 1;
    solid = true;
    points = 60;

}
block_t BrickStair1::getID(){ return 67;}

BrickStair2::BrickStair2():BaseBlock()
{
    textureRow = 4;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 67;
    material = 1;
    solid = true;
    points = 60;

}
block_t BrickStair2::getID(){ return 68;}

BrickStair3::BrickStair3():BaseBlock()
{
    textureRow = 4;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 67;
    material = 1;
    solid = true;
    points = 60;

}
block_t BrickStair3::getID(){ return 69;}

BrickStair4::BrickStair4():BaseBlock()
{
    textureRow = 4;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 67;
    material = 1;
    solid = true;
    points = 60;
}
block_t BrickStair4::getID(){ return 70;}

MelonBlock::MelonBlock():BaseBlock()
{
    textureRow = 8;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 3;
    editable = true;
    transparent = false;
    soundType = 3;

    loot = 71;
    solid = true;

}
block_t MelonBlock::getID(){ return 71;}

JukeBox::JukeBox():BaseBlock()
{
    textureRow = 8;

    upPlane = 6;
    downPlane = 5;
    sidePlane = 5;
    editable = true;
    transparent = false;
    solid = true;

}
block_t JukeBox::getID(){ return 72;}


EndStone::EndStone():BaseBlock()
{
    textureRow = 0;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 10;
    editable = true;
    transparent = false;
    solid = true;

}
block_t EndStone::getID(){ return 73;}

Pumpkin::Pumpkin():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 0;
    sidePlane2 = 12;
    sidePlane3 = 12;
    sidePlane4 = 12;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    loot = 74;
    material = 1;
    solid = true;

}
block_t Pumpkin::getID(){ return 74;}

GlowStone::GlowStone():BaseBlock()
{
    textureRow = 3;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 8;
    editable = true;
    transparent = true;
    lightSource = true;

    solid = true;

}
block_t GlowStone::getID(){ return 75;}

HayBale::HayBale():BaseBlock()
{
    textureRow = 9;

    upPlane = 3;
    downPlane = 3;
    sidePlane = 2;
    editable = true;
    transparent = false;

    loot =  76;
    material = 4;
    solid = true;

}
block_t HayBale::getID(){ return 76;}

Mooshroom1::Mooshroom1():BaseBlock()
{
    textureRow = 5;

    sidePlane = 12;
    downPlane = 12;
    upPlane = 12;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 300;
    solid = false;
    update = 1;

}
block_t Mooshroom1::getID(){ return 77;}

Mooshroom2::Mooshroom2():BaseBlock()
{
    textureRow = 5;

    sidePlane = 13;
    downPlane = 13;
    upPlane = 13;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 301;
    solid = false;
    update = 1;

}
block_t Mooshroom2::getID(){ return 78;}

Soil::Soil():BaseBlock()
{
    textureRow = 9;

    upPlane = 13;
    downPlane = 13;
    sidePlane = 13;
    editable = true;
    transparent = false;
    soundType = 1;

    loot = 2;
    material = 3;
    update = 1;
    solid = true;

}
block_t Soil::getID(){ return 79;}

WateredSoil::WateredSoil():BaseBlock()
{
    textureRow = 9;

    upPlane = 14;
    downPlane = 14;
    sidePlane = 14;
    editable = true;
    transparent = false;
    soundType = 1;

    loot = 2;
    material = 3;
    update = 1;
    solid = true;

}
block_t WateredSoil::getID(){ return 80;}

MooshroomWood::MooshroomWood():BaseBlock()
{
    textureRow = 8;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 7;
    editable = true;
    transparent = false;

    solid = true;

}
block_t MooshroomWood::getID(){ return 81;}

HalfBlock8::HalfBlock8():BaseBlock()
{
    textureRow = 4;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 82;
    material = 1;

    solid = true;

}
block_t HalfBlock8::getID(){ return 82;}

HalfBlock0::HalfBlock0():BaseBlock()
{
    textureRow = 4;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;
    blockSpecial = true;

    solid = true;
    loot = 83;
    material = 1;

}
block_t HalfBlock0::getID(){ return 83;}

HalfBlock1::HalfBlock1():BaseBlock()
{
    textureRow = 1;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 9;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    loot = 84;
    material = 1;
    solid = true;

}
block_t HalfBlock1::getID(){ return 84;}

HalfBlock2::HalfBlock2():BaseBlock()
{
    textureRow = 7;

    upPlane = 4;
    downPlane = 5;
    sidePlane = 4;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    loot = 85;
    material = 1;
    solid = true;

}
block_t HalfBlock2::getID(){ return 85;}

HalfBlock3::HalfBlock3():BaseBlock()
{
    textureRow = 4;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    loot = 86;
    material = 1;
    solid = true;
}
block_t HalfBlock3::getID(){ return 86;}

HalfBlock4::HalfBlock4():BaseBlock()
{
    textureRow = 5;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    loot = 87;
    material = 1;
    solid = true;

}
block_t HalfBlock4::getID(){ return 87;}

HalfBlock5::HalfBlock5():BaseBlock()
{
    textureRow = 5;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 8;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    solid = true;

}
block_t HalfBlock5::getID(){ return 88;}

HalfBlock6::HalfBlock6():BaseBlock()
{
    textureRow = 6;

    upPlane = 8;
    downPlane = 8;
    sidePlane = 8;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    solid = true;

}
block_t HalfBlock6::getID(){ return 89;}

HalfBlock7::HalfBlock7():BaseBlock()
{
    textureRow = 6;

    upPlane = 9;
    downPlane = 9;
    sidePlane = 9;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    solid = true;

}
block_t HalfBlock7::getID(){ return 90;}

Cake::Cake():BaseBlock()
{
    textureRow = 0;

    upPlane = 11;
    downPlane = 12;
    sidePlane = 13;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    solid = true;

}
block_t Cake::getID(){ return 91;}

TrapDoor::TrapDoor():BaseBlock()
{
    textureRow = 8;

    upPlane = 11;
    downPlane = 11;
    sidePlane = 11;
    editable = true;
    transparent = true;
    blockSpecial = true;
    lightSource = false;

    solid = true;

}
block_t TrapDoor::getID(){ return 92;}

Snow2::Snow2():BaseBlock()
{
    textureRow = 0;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    loot = 1;
    solid = false;

}
block_t Snow2::getID(){ return 93;}

Table::Table():BaseBlock()
{
    textureRow = 9;

    upPlane = 10;
    downPlane = 8;
    sidePlane = 9;
    editable = true;
    transparent = false;
    blockSpecial = true;
    lightSource = false;

    solid = true;

}
block_t Table::getID(){ return 94;}

AetherStone::AetherStone():BaseBlock()
{
    textureRow = 9;

    upPlane = 11;
    downPlane = 11;
    sidePlane = 11;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;

}
block_t AetherStone::getID(){ return 95;}

MushRoomLeave::MushRoomLeave():BaseBlock()
{
    textureRow = 8;

    upPlane = 10;
    downPlane = 8;
    sidePlane = 10;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;

}
block_t MushRoomLeave::getID(){ return 96;}

MossAetherStone::MossAetherStone():BaseBlock()
{
    textureRow = 10;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t MossAetherStone::getID(){ return 97;}

AetherBlock1::AetherBlock1():BaseBlock()
{
    textureRow = 10;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 1;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t AetherBlock1::getID(){ return 98;}

ClayBlock::ClayBlock():BaseBlock()
{
    textureRow = 1;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 10;
    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 1;

    loot = 283;
    material = 3;
    solid = true;

}
block_t ClayBlock::getID(){ return 99;}

Chest5::Chest5():BaseBlock()
{
    textureRow = 10;
    upPlane = 4;
    downPlane = 4;
    sidePlane = 3;
    sidePlane2 = 5;
    sidePlane3 = 5;
    sidePlane4 = 5;
    editable = true;
    transparent = false;
    solid = true;
    blockSpecial = true;

    loot = 100;
    material = 1;

}
block_t Chest5::getID(){ return 100;}

BasaltCobble::BasaltCobble():BaseBlock()
{
    textureRow = 9;

    upPlane = 3;
    downPlane = 3;
    sidePlane = 3;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 101;
    material = 2;

}
block_t BasaltCobble::getID(){ return 101;}

GabbroCobble::GabbroCobble():BaseBlock()
{
    textureRow = 9;

    upPlane = 5;
    downPlane = 5;
    sidePlane = 5;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 102;
    material = 2;

}
block_t GabbroCobble::getID(){ return 102;}

DaciteCobble::DaciteCobble():BaseBlock()
{
    textureRow = 9;

    upPlane = 7;
    downPlane = 7;
    sidePlane = 7;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 103;
    material = 2;

}
block_t DaciteCobble::getID(){ return 103;}

Furnace2::Furnace2():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 8;
    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 2;

    loot = 104;
    material = 2;
    solid = true;

}
block_t Furnace2::getID(){ return 104;}

Crafting::Crafting():BaseBlock()
{
    textureRow = 10;

    upPlane = 10;
    downPlane = 10;
    sidePlane = 11;
    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 3;

    loot = 105;
    material = 1;
    solid = true;

}
block_t Crafting::getID(){ return 105;}

FurnaceOff::FurnaceOff():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 8;
    editable = true;
    transparent = false;
    lightSource = false;

    loot = 106;
    material = 2;
    solid = true;

}
block_t FurnaceOff::getID(){ return 106;}

FurnaceOn::FurnaceOn():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 9;
    editable = true;
    transparent = false;
    lightSource = true;

    solid = true;
    loot = 106;
    material = 2;

}
block_t FurnaceOn::getID(){ return 107;}

Furnace5::Furnace5():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 7;
    sidePlane2 = 7;
    sidePlane3 = 8;
    sidePlane4 = 7;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 106;
    material = 2;

}
block_t Furnace5::getID(){ return 108;}

Furnace6::Furnace6():BaseBlock()
{
    textureRow = 10;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 7;
    sidePlane2 = 7;
    sidePlane3 = 7;
    sidePlane4 = 8;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
    loot = 106;
    material = 2;

}
block_t Furnace6::getID(){ return 109;}

TNT::TNT():BaseBlock()
{
    textureRow = 1;

    upPlane = 13;
    downPlane = 12;
    sidePlane = 14;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;

}
block_t TNT::getID(){ return 110;}

Nuclear::Nuclear():BaseBlock()
{
    textureRow = 1;

    upPlane = 15;
    downPlane = 15;
    sidePlane = 15;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;

}
block_t Nuclear::getID(){ return 111;}

Lava::Lava():BaseBlock()
{
    textureRow = 11;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = false;
	transparent = false;
	soundType = 2;
	lightSource = true;
	blockSpecial = true;

	update = 1;
    solid = false;

}
block_t Lava::getID(){ return 112;}

Gravel::Gravel():BaseBlock()
{
    textureRow = 11;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 1;
    editable = true;
    transparent = false;
    lightSource = false;
    soundType = 1;

    update = 1;
    solid = true;

}
block_t Gravel::getID(){ return 113;}

LavaStone::LavaStone():BaseBlock()
{
    textureRow = 11;

    upPlane = 2;
    downPlane = 2;
    sidePlane = 2;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t LavaStone::getID(){ return 114;}

LavaObsidian::LavaObsidian():BaseBlock()
{
    textureRow = 11;

    upPlane = 3;
    downPlane = 3;
    sidePlane = 3;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t LavaObsidian::getID(){ return 115;}

BlackStone::BlackStone():BaseBlock()
{
    textureRow = 11;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 4;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t BlackStone::getID(){ return 116;}

CryObsidian::CryObsidian():BaseBlock()
{
    textureRow = 11;

    upPlane = 5;
    downPlane = 5;
    sidePlane = 5;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t CryObsidian::getID(){ return 117;}

MossBlack::MossBlack():BaseBlock()
{
    textureRow = 11;

    upPlane = 6;
    downPlane = 6;
    sidePlane = 6;
    editable = true;
    transparent = false;
    lightSource = false;

    solid = true;
}
block_t MossBlack::getID(){ return 118;}

Flower1::Flower1():BaseBlock()
{
    textureRow = 5;

    sidePlane = 10;
    downPlane = 10;
    upPlane = 10;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 294;
    solid = false;

}
block_t Flower1::getID(){ return 119;}

Flower2::Flower2():BaseBlock()
{
    textureRow = 5;

    sidePlane = 11;
    downPlane = 11;
    upPlane = 11;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 295;
    solid = false;

}
block_t Flower2::getID(){ return 120;}



Sapling::Sapling():BaseBlock()
{
    textureRow = 5;

    upPlane = 14;
    downPlane = 14;
    sidePlane = 14;
    editable = true;
    transparent = true;
    blockSpecial = true;

    loot = 296;
    update = 1;
    solid = false;

}
block_t Sapling::getID(){ return 121;}

Pumpkin2::Pumpkin2():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 12;
    sidePlane2 = 0;
    sidePlane3 = 12;
    sidePlane4 = 12;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    material = 1;
    loot = 74;
    solid = true;
}
block_t Pumpkin2::getID(){ return 122;}

Pumpkin3::Pumpkin3():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 12;
    sidePlane2 = 12;
    sidePlane3 = 0;
    sidePlane4 = 12;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    material = 1;
    loot = 74;
    solid = true;

}
block_t Pumpkin3::getID(){ return 123;}


Pumpkin4::Pumpkin4():BaseBlock()
{
    textureRow = 9;

    upPlane = 1;
    downPlane = 1;
    sidePlane = 12;
    sidePlane2 = 12;
    sidePlane3 = 12;
    sidePlane4 = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    material = 1;
    loot = 74;
    solid = true;

}
block_t Pumpkin4::getID(){ return 124;}

WoodenStair1::WoodenStair1():BaseBlock()
{
    textureRow = 4;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 125;
    material = 1;
    solid = true;
    points = 60;
}
block_t WoodenStair1::getID(){ return 125;}

WoodenStair2::WoodenStair2():BaseBlock()
{
    textureRow = 4;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 125;
    material = 1;
    solid = true;
    points = 60;
}
block_t WoodenStair2::getID(){ return 126;}

WoodenStair3::WoodenStair3():BaseBlock()
{
    textureRow = 4;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 125;
    material = 1;
    solid = true;
    points = 60;
}
block_t WoodenStair3::getID(){ return 127;}

WoodenStair4::WoodenStair4():BaseBlock()
{
    textureRow = 4;

    upPlane = 0;
    downPlane = 0;
    sidePlane = 0;
    editable = true;
    transparent = false;
    blockSpecial = true;

    loot = 125;
    material = 1;
    solid = true;
    points = 60;
}
block_t WoodenStair4::getID(){ return 128;}

Marble::Marble():BaseBlock()
{
    textureRow = 9;

    upPlane = 14;
    downPlane = 14;
    sidePlane = 14;
    editable = true;
    transparent = false;

    loot = 128;
    material = 2;
    solid = true;

}
block_t Marble::getID(){ return 129;}

Cube::Cube():BaseBlock()
{
    transparent = false;
    blockSpecial = true;
}
block_t Cube::getID(){ return 130;}

Chest2::Chest2():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 5;
    sidePlane2 = 3;
    sidePlane3 = 5;
    sidePlane4 = 5;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    loot = 100;
    material = 1;
    solid = true;


}
block_t Chest2::getID(){ return 131;}

Chest3::Chest3():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 5;
    sidePlane2 = 5;
    sidePlane3 = 3;
    sidePlane4 = 5;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    loot = 100;
    material = 1;
    solid = true;


}
block_t Chest3::getID(){ return 132;}

Chest4::Chest4():BaseBlock()
{
    textureRow = 10;

    upPlane = 4;
    downPlane = 4;
    sidePlane = 5;
    sidePlane2 = 5;
    sidePlane3 = 5;
    sidePlane4 = 3;
    editable = true;
    transparent = false;
    blockSpecial = true;
    soundType = 3;

    loot = 100;
    material = 1;
    solid = true;


}
block_t Chest4::getID(){ return 133;}


WheatBlock1::WheatBlock1():BaseBlock()
{
    textureRow = 7;

    sidePlane = 11;
    downPlane = 11;
    upPlane = 11;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 286;
    update = 1;
    solid = false;

}
block_t WheatBlock1::getID(){ return 134;}

WheatBlock2::WheatBlock2():BaseBlock()
{
    textureRow = 7;

    sidePlane = 12;
    downPlane = 12;
    upPlane = 12;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 286;
    update = 1;
    solid = false;

}
block_t WheatBlock2::getID(){ return 135;}

WheatBlock3::WheatBlock3():BaseBlock()
{
    textureRow = 7;

    sidePlane = 13;
    downPlane = 13;
    upPlane = 13;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 286;
    update = 1;
    solid = false;

}
block_t WheatBlock3::getID(){ return 136;}

WheatBlock4::WheatBlock4():BaseBlock()
{
    textureRow = 7;

    sidePlane = 14;
    downPlane = 14;
    upPlane = 14;
	editable = true;
	transparent = true;
    blockSpecial = true;

    loot = 287;
    update = 1;
    solid = false;
}
block_t WheatBlock4::getID(){ return 137;}

FreeBlock3::FreeBlock3():BaseBlock()
{
    textureRow = 8;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 11;
    editable = true;
    transparent = true;
    lightSource = false;
    blockSpecial = true;solid = true;
}
block_t FreeBlock3::getID(){ return 138;}

FreeBlock4::FreeBlock4():BaseBlock()
{
    textureRow = 8;

    upPlane = 12;
    downPlane = 12;
    sidePlane = 11;
    editable = true;
    transparent = true;
    lightSource = false;
    blockSpecial = true;solid = true;
}
block_t FreeBlock4::getID(){ return 139;}

WorldSky::WorldSky():BaseBlock()
{
    transparent = false;
    blockSpecial = true;

}
block_t WorldSky::getID(){ return 140;}

Cloud::Cloud():BaseBlock()
{

    transparent = true;
    blockSpecial = true;

}
block_t Cloud::getID(){ return 141;}

IronBlock::IronBlock():BaseBlock()
{
	textureRow = 1;

	upPlane = 1;
	downPlane = 1;
	sidePlane = 1;
	editable = true;;
	transparent = false;
	soundType = 2;
	solid = true;
	material = 6;

}
block_t IronBlock::getID(){ return 142;}
