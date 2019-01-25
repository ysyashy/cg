#include <iostream>
#include "TexturePool.h"
#include "Texture2D.h"

namespace xe {

TexturePool * TexturePool::getInstance() {
	if (instance == nullptr) {
		instance = new TexturePool();
	}
	return instance;
}

void TexturePool::destroyInstance() {
	for (auto entry : instance->texMap) {
		delete entry.second;
		entry.second = nullptr;
	}
	instance->texMap.clear();
}

void TexturePool::addTexture(const std::string & filename, Texture2D * tex) {
	if (texMap.count(filename) > 0) {
		throw std::runtime_error("error: texture has exists.");
	} else {
		texMap.emplace(filename, tex);
	}
}

Texture2D * TexturePool::getTexture(const std::string & filename) {
	if (0 == texMap.count(filename)) {
		return nullptr;
	} else {
		return texMap.at(filename);
	}
}

void TexturePool::removeTexture(const std::string & filename) {
	if (texMap.count(filename) != 0) {
		delete texMap.at(filename);
		texMap.erase(filename);
	}
}

TexturePool::TexturePool() {}

}