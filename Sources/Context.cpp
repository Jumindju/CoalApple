#include "Context.h"
#include "defines.h"

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>

void GLAPIENTRY openGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

Context::Context(const Config config) {
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);

#ifdef _DEBUG
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

	uint32 flags = SDL_WINDOW_OPENGL;
	if (config.isFullScreen)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

	window = SDL_CreateWindow("Testing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, config.width, config.height, flags);
	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "Error: " << glewGetErrorString(glewError) << std::endl;
		std::cin.get();
		return;
	}
#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(openGLCallback, 0);
#endif
}
void Context::swapWindow() {
	SDL_GL_SwapWindow(window);
}

void GLAPIENTRY openGLCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cout << "[OpenGL Log]: " << message << " " << severity << std::endl;
}