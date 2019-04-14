#pragma once

#include <GL/glew.h>
#include <SDL.h>
#include "Config.h";

class Context
{
public:
	Context(const Config config);
	SDL_Window* getWindow();
private:
	SDL_Window* window;
};