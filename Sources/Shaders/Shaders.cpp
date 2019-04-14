#include <iostream>
#include <GL/glew.h>

#include "Shaders.h"
#include "../defines.h"
#include "../utils.h"

Shader::Shader(const char* vertexShadeFileName, const char* fragmentShaderFileName) {
	shaderId = createShader(vertexShadeFileName, fragmentShaderFileName);
}
Shader::~Shader() {
	glDeleteProgram(shaderId);
}
void Shader::bind() {
	glUseProgram(shaderId);
}
void Shader::unbind() {
	glUseProgram(0);
}
GLuint Shader::compile(std::string shaderSourceCode, GLenum type) {
	GLuint id = glCreateShader(type);
	const char* src = shaderSourceCode.c_str();
	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result != GL_TRUE) {
		int length = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length + 1];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Shader compilation error: " << message << std::endl;
		delete[] message;
		return 0;
	}
	return id;
}
GLuint Shader::getShaderId() {
	return shaderId;
}
GLuint Shader::createShader(const char* vertexShaderFileName, const char* fragmentShaderFileName) {
	std::string vertexShaderSource = utils::readFile(vertexShaderFileName);
	std::string fragmentShaderSource = utils::readFile(fragmentShaderFileName);

	GLuint program = glCreateProgram();
	GLuint vs = compile(vertexShaderSource, GL_VERTEX_SHADER);
	GLuint fs = compile(fragmentShaderSource, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

#ifdef _RELEASE
	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);
#endif
	return program;
}