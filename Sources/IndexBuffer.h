#pragma once
#include <GL/glew.h>
#include "defines.h"

class IndexBuffer
{
public:
	IndexBuffer(void* data, uint32 countIndices, uint8 elementSite);
	virtual ~IndexBuffer();
	void bind();
	void unbind();
private:
	GLuint bufferId;
};
