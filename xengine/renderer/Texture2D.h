#pragma once

#include <string>
#include <GL/glew.h>

namespace xe {

class Texture2D {
public:
	Texture2D(const std::string &filename);
	virtual ~Texture2D();

	GLuint getTextureId() const { return textureId; }
	std::string getFileName() const { return fileName; }
	int getWidth() const { return w; }
	int getHeight() const { return h; }
private:
	Texture2D() {}
private:
	void loadPicture();
private:
	int w, h, nrComponents;
	std::string fileName;
	GLuint textureId;
};

}
