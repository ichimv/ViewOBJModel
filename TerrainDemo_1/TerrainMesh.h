#pragma once

#include <Types.h>

class TerrainMesh
{
public:
   TerrainMesh(int cols, int rows, float worldScale, const class HeightMap* pHeightMap);

   void Render();

private:
	struct Vertex {
		glm::vec3 Pos;

		void InitVertex(float worldScale, const HeightMap* pHeightMap, int x, int z);
	};

	void CreateGLState();

	void PopulateBuffers(const HeightMap* pHeightMap);
	void InitVertices(const HeightMap* pHeightMap, std::vector<Vertex>& Vertices);
	void InitIndices(std::vector<uint>& Indices);

	int m_cols = 0;
	int m_rows = 0;

	float m_worldScale;

	uint m_vao;
	uint m_vb;
	uint m_ib;
};

