#include "pch.h"
#include "TerrainDemo_1.h"
#include "HeightMap.h"
#include "TerrainGrid.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern DemoApp* g_App;

void TerrainDemo_1::InitFromFile(float fWorldScale, const char* pFilename)
{
	std::shared_ptr<HeightMap> spHeightMap = std::shared_ptr<HeightMap>(
		new HeightMap(pFilename));

	m_spTerrainGrid = std::shared_ptr<TerrainGrid>(
		new TerrainGrid(fWorldScale, spHeightMap));
}

void TerrainDemo_1::RenderScene()
{
	DemoApp::RenderScene();

	m_spTerrainGrid->Render();
}

int main()
{
	const char* shaderFilePath = "..\\Shaders\\terrain";
	g_App = new TerrainDemo_1(SCR_WIDTH, SCR_HEIGHT, "TerrainDemo_1", shaderFilePath);

	float fWorldScale = 10.f;
	const char* pFilename = "..\\Data\\heightmap.raw";
	((TerrainDemo_1*)g_App)->InitFromFile(fWorldScale, pFilename);

	g_App->Run();

	delete g_App;

	return 0;
}
