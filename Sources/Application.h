#pragma once

#include "defines.h"
#include "Context.h"
#include "Config.h"
#include "libs/glm/glm.hpp";
#include "FpsCamera.h"
#include "Renderer.h"

class Application {
public:
	Application(const Config config);
	void runLoop();

private:
	Context context;
	FpsCamera camera;
	Renderer renderer;
	glm::mat4 model=glm::mat4(1.0f);
	glm::mat4 modelViewProj;
	int modelViewProjMatrixLoc;
	uint32 numVertecies;
	uint32 numIndices;
	float delta = 0.0f;
	float time = 0.0f;
	float cameraVel = 6.0f;
	void handleEvents();
	bool closed = false;
	bool escapeBlocked = false;
	bool cameraW = false;
	bool cameraA = false;
	bool cameraS = false;
	bool cameraD = false;
	bool cameraSpace = false;
	bool cameraShift = false;
};
