#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <vector>

class Renderer {
public:
	Renderer(Vertex* pVertecies, uint32* pIndices, uint32 numVert, uint32 numIndices);
	void bindBuffers();
	void unbindBuffers();
private:
	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
};