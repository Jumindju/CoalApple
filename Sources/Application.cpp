#include "Application.h";
#include "defines.h";
#include <SDL.h>
#include "GL/glew.h";

Application::Application(const Config config)
	:camera(config)
	,context(config)
{
	model = glm::mat4(1.0f);
	camera.translate(glm::vec3(0.0f, 0.0f, 5.0f));
	camera.update();
	modelViewProj = camera.getViewProj() * model;
	SDL_SetRelativeMouseMode(SDL_TRUE);
}
bool escapeBlocked = false;
bool closed = false;

bool cameraW = false;
bool cameraA = false;
bool cameraS = false;
bool cameraD = false;
bool cameraSpace = false;
bool cameraShift = false;

void Application::runLoop() {
	uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64 lastCounter = SDL_GetPerformanceCounter();

	while (!closed) {
		handleEvents();
		glClearColor(0.1f, 0.6f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		time += delta;
		context.swapWindow();
		uint64 endCounter = SDL_GetPerformanceCounter();
		uint64 elapsed = endCounter - lastCounter;
		delta = ((float)elapsed) / (float)perfCounterFrequency;
		uint32 FPS = (uint32)((float)perfCounterFrequency / (float)elapsed);
		//std::cout << "FPS: "<< FPS << std::endl;
		lastCounter = endCounter;
	}
}
void Application::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		bool keyUp = event.type == SDL_KEYDOWN;
		if (event.type == SDL_QUIT) {
			closed = true;
		}
		else if (keyUp || event.type == SDL_KEYUP) {
			SDL_Keycode btnPressed = event.key.keysym.sym;
			switch (btnPressed) {
			case SDLK_ESCAPE: {
				if (escapeBlocked) {
					escapeBlocked = false;
				}
				else
				{
					escapeBlocked = true;
					SDL_bool mouseMode = SDL_TRUE;
					if (SDL_GetRelativeMouseMode()) {
						mouseMode = SDL_FALSE;
					}
					SDL_SetRelativeMouseMode(mouseMode);
				}
			}break;
			case SDLK_w:
				cameraW = keyUp;
				break;
			case SDLK_a:
				cameraA = keyUp;
				break;
			case SDLK_s:
				cameraS = keyUp;
				break;
			case SDLK_d:
				cameraD = keyUp;
				break;
			case SDLK_SPACE:
				cameraSpace = keyUp;
				break;
			case SDLK_LSHIFT:
				cameraShift = keyUp;
				break;
			}
		}
		else if (event.type == SDL_MOUSEMOTION) {
			if (SDL_GetRelativeMouseMode())
				camera.onMouseMove(event.motion.xrel, event.motion.yrel);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT)
				SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		if (SDL_GetRelativeMouseMode()) {
			float currSpeed = cameraVel * delta;
			if (cameraW)
				camera.moveFront(currSpeed);
			if (cameraS)
				camera.moveFront(-currSpeed);
			if (cameraD) 
				camera.moveSideways(currSpeed);
			if (cameraA)
				camera.moveSideways(-currSpeed);
			if (cameraSpace)
				camera.moveUp(currSpeed);
			if (cameraShift)
				camera.moveUp(-currSpeed);
			model = glm::rotate(model, 1.0f*delta, glm::vec3(0, 1, 0));
			modelViewProj = camera.getViewProj()*model;
		}
		camera.update();
	}
}