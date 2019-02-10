#ifndef __GL_Shader_H__
#define __GL_Shader_H__
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"

class Shader {
public:
	Shader(const std::string &vertexFile, const std::string &fragmentFile, const std::string &gemotryFile = "");
	~Shader() {
		if (0 != _programId)	glDeleteProgram(_programId);
	}
	void use() {
		glUseProgram(_programId);
	}
	GLuint getProgramId() const { return _programId; }
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setVec3(const std::string &name, float x, float y, float z);
	void setVec3(const std::string &name, const glm::vec3 &value);
private:
	Shader() {}
	GLint loadShader(const std::string &filename, GLenum shaderType);
	bool readFile(const std::string &filename, std::string &result);
private:
	GLuint _programId;
	std::string _buff;
};

Shader::Shader(const std::string & vertexFile
			   , const std::string & fragmentFile
			   , const std::string & gemotryFile)
	: _programId(0)
{
	_buff.reserve(4096);
	GLuint vertexShaderId = loadShader(vertexFile, GL_VERTEX_SHADER);
	GLuint fragmentShaderId = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	GLuint gemotryShaderId = loadShader(gemotryFile, GL_GEOMETRY_SHADER);

	_programId = glCreateProgram();
	/* attache shader to program */
	if (0 != vertexShaderId && 0 != fragmentShaderId) {
		glAttachShader(_programId, vertexShaderId);
		glAttachShader(_programId, fragmentShaderId);
		if (0 != gemotryShaderId) {
			glAttachShader(_programId, gemotryShaderId);
		}
	}
	/* link shader */
	glLinkProgram(_programId);
	/* error log */
	GLint linkStatus = 0;
	glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);
	if (GL_FALSE == linkStatus) {
		GLint maxLength = 0;
		glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar *errLog = new GLchar[maxLength + 1];
		glGetProgramInfoLog(_programId, maxLength, &maxLength, errLog);
		std::cerr << "Error: Link Shader error. "
			<< errLog << std::endl;
		delete[] errLog;
	}
	/* release shader object */
	glDetachShader(_programId, vertexShaderId);
	glDetachShader(_programId, fragmentShaderId);
	glDetachShader(_programId, gemotryShaderId);
	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);
	glDeleteShader(gemotryShaderId);
}
GLint Shader::loadShader(const std::string & filename, GLenum shaderType)
{
	if (filename.empty()) { return 0; }
	/* read from file */
	_buff.clear();
	if (!readFile(filename, _buff)) {
		throw std::runtime_error("read file error");
		return 0;
	}
	GLuint shaderId = glCreateShader(shaderType);
	const char *str = _buff.c_str();
	glShaderSource(shaderId, 1, &str, NULL);
	/* compile shader */
	glCompileShader(shaderId);
	GLint compileStatus = 0;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
	/* error log */
	if (compileStatus == GL_FALSE) {
		GLint maxLength = 0;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar *errLog = new GLchar[maxLength + 1];
		glGetShaderInfoLog(shaderId, maxLength, &maxLength, errLog);
		std::cerr << "Error: Shader file [" << filename << "] compile error. " 
			<< errLog << std::endl;
		delete[] errLog;
		return 0;
	}
	return shaderId;
}
bool Shader::readFile(const std::string & filename, std::string & result)
{
	result.clear();
	std::ifstream in_stream(filename);
	if (!in_stream)	return false;
	result.assign(std::istreambuf_iterator<char>(in_stream),
				  std::istreambuf_iterator<char>());
	return true;
}
void Shader::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(_programId, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(_programId, name.c_str()), value);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(_programId, name.c_str()), x, y, z);
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value)
{
	glUniform3fv(glGetUniformLocation(_programId, name.c_str()), 1, &value[0]);
}


#endif
