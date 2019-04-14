#pragma once

#include <GL/glew.h>

#include "defines.h"

class VertexBuffer {
public:
	VertexBuffer(void* data, uint32 numVertices);
	virtual ~VertexBuffer();
	void bind();
	void unBind();
private:
	GLuint bufferId;
	GLuint vao;
};