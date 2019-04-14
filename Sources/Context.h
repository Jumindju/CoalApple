#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include "Config.h";

class Context
{
public:
	Context(const Config config);
	void swapWindow();
private:
	SDL_Window* window;
};