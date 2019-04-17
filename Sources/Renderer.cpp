#include "Renderer.h"
#include "defines.h"
#include <iostream>

Renderer::Renderer(Vertex* pVertecies,uint32* pIndices)
	:vertexBuffer(pVertecies, 3)
	,indexBuffer(pIndices, 3,sizeof(pIndices[0]))
{
}
void Renderer::bindBuffers() {
	vertexBuffer.bind();
	indexBuffer.bind();
}
void Renderer::unbindBuffers() {
	vertexBuffer.unBind();
	indexBuffer.unbind();
}