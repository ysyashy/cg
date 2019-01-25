#include <fstream>
#include <stb_image.h>
#include "Texture2D.h"
#include "TexturePool.h"

namespace xe {

void Texture2D::loadPicture() {
	unsigned char *data = stbi_load(fileName.c_str(), &w, &h, &nrComponents, 0);
	if (nullptr != data) {
		GLenum format;
		if (1 <= nrComponents && nrComponents <= 4) {
			format = GL_RED + nrComponents - 1;
		} else {
			stbi_image_free(data);
			throw std::runtime_error("unknow picture format");
		}
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINE);
		
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);

	} else {
		throw std::runtime_error("file not found: " + fileName + ".");
	}
}

Texture2D::Texture2D() {}

Texture2D::Texture2D(const std::string & filename) 
	: fileName(filename), textureId(0) {
	loadPicture();
}

Texture2D::~Texture2D() {
	glDeleteTextures(1, &textureId);
}

inline GLuint Texture2D::getTextureId() const {
	return textureId;
}
inline std::string Texture2D::getFileName() const {
	return fileName;
}
inline int Texture2D::getWidth() const {
	return w;
}
inline int Texture2D::getHeight() const {
	return h;
}

}