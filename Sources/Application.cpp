#include "Application.h"

#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include "Shaders/Shaders.h"


Vertex vertices[] = {
Vertex{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
},
Vertex{
	glm::vec3(5.0f, 0.0f, 0.0f),
	glm::vec4(0.0, 1.0f, 0.0f, 1.0f)
},
Vertex{
	glm::vec3(0.0f, 5.0f, 0.0f),
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
},
Vertex{
	glm::vec3(5.0f, 5.0f, 0.0f),
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
},
Vertex{
	glm::vec3(0.0f, 0.0f, 5.0f),
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
},
Vertex{
	glm::vec3(5.0f, 0.0f, 5.0f),
	glm::vec4(0.0, 1.0f, 0.0f, 1.0f)
},
Vertex{
	glm::vec3(0.0f, 5.0f, 5.0f),
	glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
},
Vertex{
	glm::vec3(5.0f, 5.0f, 5.0f),
	glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
},
};
uint32 indices[] = {
	0,1,2,3,
	1,3,5,7,
	4,5,6,7,
	0,2,4,6,
	2,3,6,7,
	0,1,4,5
};

uint32 numVertecies = sizeof(vertices) / sizeof(vertices[0]);
uint32 numIndices = sizeof(indices) / sizeof(indices[0]);

Application::Application(const Config config)
	:camera(config)
	, context(config)
	, renderer(vertices, indices,numVertecies,numIndices)
{
	Shader shader("D:/Programmier-Projekte/C++/CoalApple/Shaders/basic.vert", "D:/Programmier-Projekte/C++/CoalApple/Shaders/basic.frag");
	shader.bind();
	modelViewProjMatrixLoc = glGetUniformLocation(shader.getShaderId(), "u_modelViewProj");
}
void Application::runLoop() {
	uint64 perfCounterFrequency = SDL_GetPerformanceFrequency();
	uint64 lastCounter = SDL_GetPerformanceCounter();

	delta = 0.0f;
	cameraSpeed = 6.0f;
	time = 0.0f;

	model = glm::rotate(model, 1.0f*delta, glm::vec3(0, 1, 0));
	modelViewProj = camera.getViewProj() * model;

	SDL_SetRelativeMouseMode(SDL_TRUE);
	//glEnable(GL_CULL_FACE)
	//glEnable(GL_DEPTH_TEST);
	while (!closed) {
		handleEvents();
		glClearColor(0.04f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		time += delta;
		if (cameraW)
			camera.moveFront(delta * cameraSpeed);
		if (cameraS) {
			camera.moveFront(-delta * cameraSpeed);
		}if (cameraA) {
			camera.moveSideways(-delta * cameraSpeed);
		}if (cameraD) {
			camera.moveSideways(delta * cameraSpeed);
		}if (cameraSpace) {
			camera.moveUp(delta * cameraSpeed);
		}if (cameraShift) {
			camera.moveUp(-delta * cameraSpeed);
		}

		modelViewProj = camera.getViewProj() * model;
		camera.update();

		renderer.bindBuffers();

		glUniformMatrix4fv(modelViewProjMatrixLoc, 1, GL_FALSE, &modelViewProj[0][0]);
		glDrawElements(GL_TRIANGLE_STRIP, numIndices, GL_UNSIGNED_INT, 0);

		renderer.unbindBuffers();

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
	}
}