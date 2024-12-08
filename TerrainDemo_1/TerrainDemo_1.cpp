#include "pch.h"
#include "TerrainDemo_1.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

extern DemoApp* g_App;

int main()
{
	g_App = new TerrainDemo_1(SCR_WIDTH, SCR_HEIGHT, "TerrainDemo_1");

	g_App->Run();

	delete g_App;

	return 0;
}
