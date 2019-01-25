#pragma once

#include <string>
#include <GL/glew.h>

namespace xe {

class Texture2D {
public:
	Texture2D(const std::string &filename);
	virtual ~Texture2D();

	GLuint getTextureId() const;
	std::string getFileName() const;
	int getWidth() const;
	int getHeight() const;
private:
	void loadPicture();
	Texture2D();
private:
	int w, h, nrComponents;
	std::string fileName;
	GLuint textureId;
};

}
