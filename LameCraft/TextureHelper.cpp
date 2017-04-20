#include "TextureHelper.h"
#include <Aurora/Graphics/RenderManager.h>

TextureHelper::TextureHelper()
{
	defaulPatch = "Assets/";
	defaultFolder = "Lamecraft/";
	texturePatch = "Assets/Lamecraft/";
}

TextureHelper::~TextureHelper()
{

}

int TextureHelper::GetTexture(Textures texture)
{
	switch(texture)
	{
		case Genesis:
		{
			fileName = texturePatch + "title/genesis.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case PspTeam:
		{
			fileName = texturePatch + "title/pspteam.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Logo:
		{
			fileName = texturePatch + "environment/moon.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Utils:
		{
			fileName = texturePatch + "hud/utils.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Dirt:
		{
			fileName = texturePatch + "title/dirt.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Glass:
		{
			fileName = texturePatch + "models/glass.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Terrain1:
		{
			fileName = texturePatch + "terrains/terrain1.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain2:
		{
			fileName = texturePatch + "terrains/terrain2.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain3:
		{
			fileName = texturePatch + "terrains/terrain3.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain4:
		{
			fileName = texturePatch + "terrains/terrain4.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain5:
		{
			fileName = texturePatch + "terrains/terrain5.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain6:
		{
			fileName = texturePatch + "terrains/terrain6.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain7:
		{
			fileName = texturePatch + "terrains/terrain7.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case Terrain8:
		{
			fileName = texturePatch + "terrains/terrain8.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain9:
		{
			fileName = texturePatch + "terrains/terrain9.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain10:
		{
			fileName = texturePatch + "terrains/terrain10.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain11:
		{
			fileName = texturePatch + "terrains/terrain11.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain12:
		{
			fileName = texturePatch + "terrains/terrain12.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain13:
		{
			fileName = texturePatch + "terrains/terrain13.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain14:
		{
			fileName = texturePatch + "terrains/terrain14.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain15:
		{
			fileName = texturePatch + "terrains/terrain15.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
				case Terrain16:
		{
			fileName = texturePatch + "terrains/terrain16.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Blue:
		{
			fileName = texturePatch + "hud/blue.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case Vignet:
		{
			fileName = texturePatch + "hud/vignet.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Sun:
		{
			fileName = texturePatch + "environment/sun.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case SnowBall3:
		{
			fileName = texturePatch + "entity/snowball.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Moon:
		{
			fileName = texturePatch + "environment/moon.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case lameCraft:
		{
			fileName = texturePatch + "title/logo.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Red:
		{
			fileName = texturePatch + "hud/red.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case Black:
		{
			fileName = texturePatch + "hud/black.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case screen1:
		{
			fileName = texturePatch + "title/screen0.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case screen2:
		{
			fileName = texturePatch + "title/screen1.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case screen4:
		{
			fileName = texturePatch + "title/screen3.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
		case screen3:
		{
			fileName = texturePatch + "title/screen2.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case clouds1:
		{
			fileName = texturePatch + "environment/clouds.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case inv:
		{
			fileName = texturePatch + "gui/inventory1.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case crt:
		{
			fileName = texturePatch + "gui/crafting_table.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case cht:
		{
			fileName = texturePatch + "gui/chest.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case fur:
		{
			fileName = texturePatch + "gui/furnace.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case cursor:
		{
			fileName = texturePatch + "gui/cursor.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case furFire:
		{
			fileName = texturePatch + "gui/fire.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
        case furArrow:
		{
			fileName = texturePatch + "gui/arrow.png";
			TextureManager::Instance()->LoadTexture(fileName);
			return TextureManager::Instance()->GetTextureNumber(fileName);
		}
		break;
	}

	return 0;
}

void TextureHelper::SetTextureFolderName(std::string name)
{
	defaultFolder = name;
	texturePatch = defaulPatch + defaultFolder;
}

TextureHelper TextureHelper::m_TextureHelper;

TextureHelper* TextureHelper::Instance()
{
	return &m_TextureHelper;
}
