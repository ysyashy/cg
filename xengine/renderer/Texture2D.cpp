#include <fstream>
#include <stb_image.h>
#include "Texture2D.h"
#include "TexturePool.h"
#include <iostream>

namespace xe {

void Texture2D::loadPicture() {
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(fileName.c_str(), &w, &h, &nrComponents, 0);
	if (nullptr != data) {
		GLenum format;
		switch (nrComponents) {
		case 1:	format = GL_RED;	break;
		case 3: format = GL_RGB;	break;
		case 4: format = GL_RGBA;	break;
		default:
			stbi_image_free(data);
			throw std::runtime_error("unknow picture format");
			break;
		}

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);

	} else {
		throw std::runtime_error("file not found: " + fileName + ".");
	}
}

Texture2D::Texture2D(const std::string & filename) 
	: fileName(filename), textureId(0) {
	loadPicture();
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &textureId);
}

}