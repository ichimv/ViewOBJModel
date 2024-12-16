#pragma once

#include "DemoApp.h"

class TerrainDemo_1 : public DemoApp
{
public:
	TerrainDemo_1(int windowWidth, int windowHeight, const char* windowTitle, const char* shaderFilePath) :
		DemoApp(windowWidth, windowHeight, windowTitle, shaderFilePath)
	{
	}

	void InitFromFile(float fWorldScale, const char* pFilename);

	void RenderScene();

private:
	std::shared_ptr <class TerrainGrid> m_spTerrainGrid;
};