#pragma once

#include <unordered_map>
#include <string>

namespace xe {

class Texture2D;

class TexturePool {
public:
	static TexturePool * getInstance();
	static void destroyInstance();
	void addTexture(const std::string &filename, Texture2D *tex);
	Texture2D *getTexture(const std::string &filename);
	void removeTexture(const std::string &filename);
private:
	static TexturePool *instance;

	std::unordered_map<std::string, Texture2D*> texMap;
	TexturePool();
};

}
