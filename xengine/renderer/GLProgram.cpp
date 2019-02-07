#include <iostream>
#include "GLProgram.h"

namespace xe {

char GLProgram::_errLog[4096] = { 0 };

const std::string GLProgram::defaultVert = std::string() +
"#version 330 core\n" +
"layout(location = 0) in vec3 aPos;\n" +
"layout(location = 1) in vec4 aColor;\n" +
"layout(location = 2) in vec2 aTexCoord;\n" +
"out vec4 outColor;\n" +
"out vec2 TexCoord;\n" +
"uniform mat4 PVM;\n" +
"void main() {\n" +
"	gl_Position = PVM * vec4(aPos, 1.0);\n" +
"	outColor = aColor;\n" +
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n" +
"}\n";
const std::string GLProgram::defaultFrag = std::string() +
"#version 330 core\n"+
"out vec4 FragColor;\n"+
"in vec4 outColor;\n"+
"in vec2 TexCoord;\n"+
"uniform sampler2D texture1;\n"+
"void main() {\n"+
"FragColor = texture(texture1, TexCoord) * outColor;\n" +
"}\n";


GLProgram::GLProgram(const std::string & vert, const std::string & frag) 
	: _programId(0) {
	initWithVertFrag(vert, frag);
}

GLProgram::~GLProgram() {
	if (0 != _programId) { glDeleteProgram(_programId); }
}

void GLProgram::use() {
	glUseProgram(_programId);
}

GLuint GLProgram::getProgramId() const {
	return _programId;
}

void GLProgram::initWithVertFrag(const std::string & vert, const std::string & frag) {
	GLuint vertId = loadShader(vert, GL_VERTEX_SHADER);
	GLuint fragId = loadShader(frag, GL_FRAGMENT_SHADER);

	_programId = glCreateProgram();
	/** attache shader to program **/
	glAttachShader(_programId, vertId);
	glAttachShader(_programId, fragId);
	/** link shader **/
	glLinkProgram(_programId);
	/** error Log **/
	GLint linkStatus = GL_FALSE;
	glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);
	if (GL_FALSE == linkStatus) {
		GLint maxLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);
		glGetProgramInfoLog(_programId, sizeof(_errLog), &maxLength, _errLog);
		std::cerr << "Error: Link Program error." << "\n"
			<< vert << "\n" 
			<< frag << "\n"
			<< _errLog << "\n";
		throw new std::runtime_error("shader link failed.");
	}
	/** release shader object **/
	glDetachShader(_programId, vertId);
	glDetachShader(_programId, fragId);
	glDeleteShader(vertId);
	glDeleteShader(fragId);
}

GLuint GLProgram::loadShader(const std::string & source, GLenum shaderType) {
	if (source.empty()) { throw new std::runtime_error("shader is empty"); }

	GLuint shaderId = glCreateShader(shaderType);
	const char *str = source.c_str();
	glShaderSource(shaderId, 1, &str, NULL);
	/** Compile shader **/
	glCompileShader(shaderId);
	GLint compileStatus = GL_FALSE;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	/** error log **/
	if (GL_FALSE == compileStatus) {
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		glGetShaderInfoLog(shaderId, sizeof(_errLog), &maxLength, _errLog);
		std::cerr << "Error: Shader [\n" << source << "\n] compile error\n"
			<< _errLog << "\n";
		throw new std::runtime_error("shader compile error");
	}
	return shaderId;
}

void GLProgram::setInt(const std::string &name, int value) {
	glUniform1i(glGetUniformLocation(_programId, name.c_str()), value);
}
void GLProgram::setFloat(const std::string &name, float value) {
	glUniform1f(glGetUniformLocation(_programId, name.c_str()), value);
}
void GLProgram::setMat4(const std::string &name, const Matrix &mat) const {
	glUniformMatrix4fv(glGetUniformLocation(_programId, name.c_str()), 1, GL_FALSE, &mat.m[0][0]);
}

void GLProgram::setVec3(const std::string &name, float x, float y, float z) {
	glUniform3f(glGetUniformLocation(_programId, name.c_str()), x, y, z);
}
void GLProgram::setVec3(const std::string &name, const Vector3 &value) {
	glUniform3fv(glGetUniformLocation(_programId, name.c_str()), 1, &value.X);
}

}