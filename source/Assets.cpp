#include "Assets.h"
#include "Aie.h"

//origin = Mr.Marco

std::map<std::string, Asset::TextureData> Asset::s_textures;

//draws asset "name" at position "x" and "y"
void Asset::Draw(const char *name, int x, int y)
{
	if (s_textures.count(name) > 0)
	{
		MoveSprite(s_textures[name].m_handle, x, y);
		DrawSprite(s_textures[name].m_handle);
	}
}

//loads asset data into memory
void Asset::Load(const char *name, const char *path, int w, int h)
{
	if (s_textures.count(name) > 0)
		DestroySprite(s_textures[name].m_handle);

	TextureData t;
	t.m_handle = CreateSprite(path, w, h, true);
	t.m_width = w;
	t.m_height = h;
	s_textures[name] = t;
}

//get the height of an asset
int Asset::GetHeight(const char *name)
{
	if (s_textures.count(name) > 0)
		return s_textures[name].m_height;
	else return -1;
}

//get the width of an asset
int Asset::GetWidth(const char *name)
{
	if (s_textures.count(name) > 0)
		return s_textures[name].m_width;
	else return -1;
}

//deletes all assets from memory to free it up
void Asset::FreeAll()
{
	for each(auto t in s_textures)
		DestroySprite(t.second.m_handle);
}