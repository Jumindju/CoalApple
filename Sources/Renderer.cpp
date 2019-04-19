#include "Renderer.h"
#include "defines.h"
#include <iostream>

Renderer::Renderer(Vertex* pVertecies,uint32* pIndices, uint32 numVert, uint32 numIndices)
	:vertexBuffer(pVertecies, numVert)
	,indexBuffer(pIndices, numIndices,sizeof(pIndices[0]))
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