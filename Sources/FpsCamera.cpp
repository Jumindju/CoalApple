#include "FpsCamera.h"
#include <iostream>
#include "Config.h"

FpsCamera::FpsCamera(const Config config)
	:Camera(config)
{
	mouseSensetivity = config.mouseSensitivity;
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	onMouseMove(0.0f, 0.0f);
	update();
}
void FpsCamera::onMouseMove(float xRel, float yRel) {
	yaw += xRel * mouseSensetivity;
	pitch -= yRel * mouseSensetivity;
	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch < -89.0f) {
		pitch = -89.0f;
	}
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	lookAt = glm::normalize(front);
	update();
}
void FpsCamera::update() {
	view = glm::lookAt(position, position + lookAt, up);
	viewProjektion = projection * view;
}
void FpsCamera::moveFront(float amount) {
	translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f)*lookAt)*amount);
	update();
}
void FpsCamera::moveSideways(float amount) {
	translate(glm::normalize(glm::cross(lookAt, up))*amount);
	update();
}
void FpsCamera::moveUp(float amount) {
	translate(up*amount);
}
