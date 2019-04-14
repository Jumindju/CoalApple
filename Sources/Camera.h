#pragma once

#include "libs/glm/glm.hpp"
#include "libs/glm/ext/matrix_transform.hpp";
#include "Config.h"
class Camera {
public:
	Camera(const Config config);
	glm::mat4 getViewProj();
	virtual void update();
	virtual void translate(glm::vec3 v);
protected:
	glm::vec3 position;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 viewProjektion;
};