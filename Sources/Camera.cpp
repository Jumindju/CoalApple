#include "Camera.h"

#include "libs/glm/glm.hpp";
#include "libs/glm/ext/matrix_transform.hpp";
#include "libs/glm/gtc/matrix_transform.hpp";

Camera::Camera(const Config config) {
	projection = glm::perspective(config.fov / 2.0f, (float)config.width / (float)config.height, 0.1f, 1000.0f);
	view = glm::mat4(1.0f);
	position = glm::vec3(0.0f);
	update();
}
glm::mat4 Camera::getViewProj() {
	return viewProjektion;
}
void Camera::update() {
	viewProjektion = projection * view;
}
void Camera::translate(glm::vec3 v) {
	position += v;
	view = glm::translate(view, v*-1.0f);
}