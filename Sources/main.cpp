#include <iostream>
#define GLEW_STATIC
#define SDL_MAIN_HANDLED
#include "Context.h"
#include "Config.h"
using namespace std;

int main()
{
	Config config;
	//config.isFullScreen = true;
	Context context(config);

	return 0;
}
