#include <iostream>
#define GLEW_STATIC
#define SDL_MAIN_HANDLED
#include "Config.h"
//#include "Application.h"
#include "Application.h"
using namespace std;

int main()
{
	const Config config;
	//config.isFullScreen = true;
	Application applitcation(config);

	return 0;
}
