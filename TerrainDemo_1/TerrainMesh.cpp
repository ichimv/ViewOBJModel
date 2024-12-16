#include "pch.h"
#include "HeightMap.h"
#include "TerrainMesh.h"


TerrainMesh::TerrainMesh(int cols, int rows, float worldScale,
	const HeightMap* pHeightMap)
{
	m_cols = cols;
	m_rows = rows;

	m_worldScale = worldScale;

	CreateGLState();

	PopulateBuffers(pHeightMap);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void TerrainMesh::CreateGLState()
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vb);

	glBindBuffer(GL_ARRAY_BUFFER, m_vb);

	glGenBuffers(1, &m_ib);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ib);

	int POS_LOC = 0;

	size_t NumFloats = 0;

	glEnableVertexAttribArray(POS_LOC);
	glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)(NumFloats * sizeof(float)));
	NumFloats += 3;
}


void TerrainMesh::PopulateBuffers(const HeightMap* pHeightMap)
{
	std::vector<Vertex> Vertices;
	Vertices.resize(m_cols * m_rows);

	InitVertices(pHeightMap, Vertices);

	std::vector<unsigned int> Indices;
	int NumQuads = (m_cols - 1) * (m_rows - 1);
	Indices.resize(NumQuads * 6);
	InitIndices(Indices);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices[0]) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices[0]) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}


void TerrainMesh::Vertex::InitVertex(float worldScale, const HeightMap* pHeightMap, int x, int z)
{
	float y = pHeightMap->Get(x, z);

	Pos = glm::vec3((float)(x * worldScale), y, (float)(z * worldScale));
}


void TerrainMesh::InitVertices(const HeightMap* pHeightMap, std::vector<Vertex>& Vertices)
{
	int vertexIndex = 0;

	for (int z = 0; z < m_rows; z++) {
		for (int x = 0; x < m_cols; x++) {
			assert(vertexIndex < Vertices.size());
			Vertices[vertexIndex].InitVertex(m_worldScale, pHeightMap, x, z);
			vertexIndex++;
		}
	}

	assert(vertexIndex == Vertices.size());
}


void TerrainMesh::InitIndices(std::vector<unsigned int>& Indices)
{
	int Index = 0;

	for (int z = 0; z < m_rows - 1; z++) {
		for (int x = 0; x < m_cols - 1; x++) {
			unsigned int IndexBottomLeft = z * m_cols + x;
			unsigned int IndexTopLeft = (z + 1) * m_cols + x;
			unsigned int IndexTopRight = (z + 1) * m_cols + x + 1;
			unsigned int IndexBottomRight = z * m_cols + x + 1;

			// Add top left triangle
			assert(Index < Indices.size());
			Indices[Index++] = IndexBottomLeft;
			assert(Index < Indices.size());
			Indices[Index++] = IndexTopLeft;
			assert(Index < Indices.size());
			Indices[Index++] = IndexTopRight;

			// Add bottom right triangle
			assert(Index < Indices.size());
			Indices[Index++] = IndexBottomLeft;
			assert(Index < Indices.size());
			Indices[Index++] = IndexTopRight;
			assert(Index < Indices.size());
			Indices[Index++] = IndexBottomRight;
		}
	}

	assert(Index == Indices.size());
}


void TerrainMesh::Render()
{
	glBindVertexArray(m_vao);

	glDrawElements(GL_TRIANGLES, (m_cols - 1) * (m_rows - 1) * 6, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
}