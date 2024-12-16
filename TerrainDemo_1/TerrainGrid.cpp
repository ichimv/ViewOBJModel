#include "pch.h"

#include "HeightMap.h"
#include "TerrainMesh.h"
#include "TerrainGrid.h"

TerrainGrid::TerrainGrid(
   float fWorldScale, 
   std::shared_ptr <HeightMap> spHeightMap)
{
   m_columns = spHeightMap->GetWidth();
   m_rows = spHeightMap->GetHeight();
   m_fWorldScale = fWorldScale;

   m_spHeightMap = spHeightMap;

   m_spTerrainMesh = std::shared_ptr<TerrainMesh>(
      new TerrainMesh(
         m_columns,
         m_rows,
         m_fWorldScale,
         m_spHeightMap.get()));
}

TerrainGrid::~TerrainGrid()
{
}

void TerrainGrid::Render()
{
   m_spTerrainMesh->Render();
}