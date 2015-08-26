#pragma once
#include <map>
#include <string>

//origin = Mr. Marco

class Asset
{
	struct TextureData { unsigned  m_handle, m_width, m_height; };

	static std::map<std::string, TextureData> s_textures;

	Asset() {}

public:
	static Asset &getInstance()
	{
		static Asset instance;
		return instance;
	}

	void Draw(const char *name, int x, int y);
	void Draw(const char *name, int x, int y, int w, int h);
	void Load(const char *name, const char *path, int w, int h);

	int GetHeight(const char *name);
	int GetWidth(const char *name);

	void FreeAll();
};