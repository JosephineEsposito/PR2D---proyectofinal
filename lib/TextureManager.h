#pragma once

#include <litegfx.h>

#include <unordered_map>
#include <string>

class TextureManager
{
private:
	std::unordered_map<std::string, ltex_t*> textures;

public:
	~TextureManager();

	ltex_t* loadTexture(const std::string& key, const char* filename);
	ltex_t* getTexture(const std::string& key);

};