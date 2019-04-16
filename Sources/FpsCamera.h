#pragma once
#include "Camera.h"
class FpsCamera : public Camera
{
public:
	FpsCamera(const Config config);
	void update() override;
	void onMouseMove(float xRel, float yRel);
	void moveFront(float amount);
	void moveSideways(float amount);
	void moveUp(float amount);
private:
	float yaw;
	float pitch;
	glm::vec3 lookAt;
	float mouseSensetivity;
	glm::vec3 up;
};