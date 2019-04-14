#pragma once

#include <GL/glew.h>
#include "../defines.h"

class Shader {
public:
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	~Shader();
	void bind();
	void unbind();
	GLuint getShaderId();
private:
	GLuint compile(std::string shaderSource, GLenum type);
	GLuint createShader(const char* vertexShaderFileName, const char* fragmentShaderFileName);

	GLuint shaderId;
};