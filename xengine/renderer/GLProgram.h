#ifndef __XE_GLProgram_H__
#define __XE_GLProgram_H__

#include <string>
#include <GL/glew.h>
#include "math/XEMath.h"

namespace xe {

class GLProgram {
public:
	GLProgram(const std::string &vert, const std::string &frag);
	~GLProgram();
	void use();
	GLuint getProgramId() const;

	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
	void setMat4(const std::string &name, const Matrix &mat) const;
	void setVec3(const std::string &name, float x, float y, float z);
	void setVec3(const std::string &name, const Vector3 &value);

	const static std::string defaultVert;
	const static std::string defaultFrag;
private:
	static char _errLog[4096];
	void initWithVertFrag(const std::string &vert, const std::string &frag);
	GLuint loadShader(const std::string &source, GLenum shaderType);
	GLProgram() {}
	GLuint _programId;
};

}

#endif // !__XE_GLProgram_H__
