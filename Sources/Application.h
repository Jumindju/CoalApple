#pragma once

#include "Context.h"
#include "FpsCamera.h"
#include "Config.h"
#include "libs/glm/glm.hpp";

class Application {
public:
	Application(const Config config);
	void runLoop();

private:
	Context context;
	FpsCamera camera;
	glm::mat4 model;
	glm::mat4 modelViewProj;
	float delta = 0.0f;
	float time = 0.0f;
	float cameraVel = 6.0f;
	void handleEvents();
	void turnOffMouse();
	void turnOnMouse();
};
