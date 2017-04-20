#ifndef TEXTUREHELPER_H_
#define TEXTUREHELPER_H_

#include <string>

class TextureHelper
{
private:

	std::string defaulPatch;
	std::string defaultFolder;
	std::string texturePatch;
	std::string fileName;

public:

	enum Textures
	{
		Genesis,
		PspTeam,
		Logo,
		Utils,
		Dirt,
		Glass,
		Terrain1,Terrain2,Terrain3,Terrain4,Terrain5,Terrain6,Terrain7,Terrain8,Terrain9,Terrain10,Terrain11,Terrain12,Terrain13,Terrain14,Terrain15,Terrain16,
		Blue,
		Sun,
		SnowBall3,
		Moon,
		lameCraft,
		Red,
		Black,
		screen1,
		screen2,
		screen3,
		screen4,
		clouds1,
		inv,
		crt, // craft
		cht, // chest
		fur, // furnace
		cursor,
		furArrow,
		furFire,
		Vignet,
	};

	static TextureHelper m_TextureHelper;
	static TextureHelper* Instance();


	TextureHelper();
	~TextureHelper();

	int GetTexture(Textures texture);

	void SetTextureFolderName(std::string name);
};

#endif
