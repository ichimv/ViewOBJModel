#pragma once

#include <types.h>

class TerrainGrid
{
public:
   TerrainGrid(
      float fWorldScale, 
      std::shared_ptr <HeightMap> spHeightMap);

   virtual ~TerrainGrid();

   void Render();

private:

   unsigned int m_columns;
   unsigned int m_rows;

   float m_fWorldScale = 1.0f;

   class std::shared_ptr <HeightMap> m_spHeightMap;
   class std::shared_ptr <class TerrainMesh> m_spTerrainMesh;
};

