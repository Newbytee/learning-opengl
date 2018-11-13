#pragma once
#include <string>
#include <GL/glew.h>

class GLSLProgram {

public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
	void linkShaders();
	void addAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);

	void use();
	void unuse();
private:
	void compileShader(const std::string& filepath, GLuint id);

	int _numAttributes;

	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

