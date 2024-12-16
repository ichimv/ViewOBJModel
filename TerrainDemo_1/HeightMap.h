#pragma once

#include <memory.h>
#include <corecrt_malloc.h>
#include <Utils.h>

class HeightMap
{
public:
   HeightMap(const char* pFilename)
   {
      InitFromFile(pFilename);
   }

   HeightMap(int cols, int rows)
   {
      Init(cols, rows);
   }


   void Init(int cols, int rows)
   {
      m_cols = cols;
      m_rows = rows;

      if (m_p) {
         free(m_p);
      }

      m_p = (float*)malloc(cols * rows * sizeof(float));
   }


   void Init(int cols, int rows, float initVal)
   {
      Init(cols, rows);

      for (int i = 0; i < cols * rows; i++) {
         m_p[i] = initVal;
      }
   }

   void InitFromFile(const char* pFilename)
   {
      int fileSize = 0;
      float* pData = (float*)ReadBinaryFile(pFilename, fileSize);

      if (fileSize % sizeof(float) != 0) {
         ERROR_MESSAGE("%s:%d - '%s' does not contain an whole number of floats (size %d)\n", __FILE__, __LINE__, pFilename, fileSize);
         exit(0);
      }

      int terrainSize = (int)sqrtf((float)fileSize / (float)sizeof(float));

      printf("Terrain size %d\n", terrainSize);

      if ((terrainSize * terrainSize) != (fileSize / sizeof(float))) {
         MESSAGE("%s:%d - '%s' does not contain a square height map - size %d\n", __FILE__, __LINE__, pFilename, fileSize);
         exit(0);
      }

      Init(terrainSize, terrainSize, pData);
   }

   void Init(int cols, int rows, float* pData)
   {
      m_cols = cols;
      m_rows = rows;

      if (m_p) {
         free(m_p);
      }

      m_p = pData;

      Normalize(-10, 500);

      float min, max;
      GetMinMax(min, max);
   }

   ~HeightMap()
   {
      Destroy();
   }


   void Destroy()
   {
      if (m_p) {
         free(m_p);
         m_p = NULL;
      }
   }

   float* GetAddr(int col, int row) const
   {
      size_t Index = CalcIndex(col, row);

      return &m_p[Index];
   }


   float* GetBaseAddr() const
   {
      return m_p;
   }


   int GetSize() const
   {
      return m_rows * m_cols;
   }


   int GetSizeInBytes() const
   {
      return GetSize() * sizeof(float);
   }


   const float& Get(int col, int row) const
   {
      return *GetAddr(col, row);
   }


   const float& Get(int Index) const
   {
#ifndef NDEBUG
      if (Index >= m_rows * m_cols) {
         ERROR_MESSAGE("%s:%d - index %d is out of bounds (max size %d)\n", __FILE__, __LINE__, Index, m_rows * m_cols);
         exit(0);
      }
#endif

      return m_p[Index];
   }


   float& At(int col, int row)
   {
      size_t Index = CalcIndex(col, row);

      return m_p[Index];
   }

   void Set(int col, int row, const float& Val)
   {
      *GetAddr(col, row) = Val;
   }


   void Set(int Index, const float& Val)
   {
#ifndef NDEBUG
      if (Index >= m_rows * m_cols) {
         ERROR_MESSAGE("%s:%d - index %d is out of bounds (max size %d)\n", __FILE__, __LINE__, Index, m_rows * m_cols);
         exit(0);
      }
#endif

      m_p[Index] = Val;
   }


   void GetMinMax(float& min, float& max)
   {
      max = min = m_p[0];

      for (int i = 1; i < m_rows * m_cols; i++) {
         if (m_p[i] < min) {
            min = m_p[i];
         }

         if (m_p[i] > max) {
            max = m_p[i];
         }
      }
   }


   void Normalize(float minRange, float maxRange)
   {
      float min, max;

      GetMinMax(min, max);

      if (max <= min) {
         return;
      }

      float minMaxDelta = max - min;
      float minMaxRange = maxRange - minRange;

      for (int i = 0; i < m_rows * m_cols; i++) {
         m_p[i] = ((m_p[i] - min) / minMaxDelta) * minMaxRange + minRange;
      }
   }


   void Print()
   {
      for (int y = 0; y < m_rows; y++) {
         printf("%d: ", y);
         for (int x = 0; x < m_cols; x++) {
            float f = (float)m_p[y * m_cols + x];
            printf("%.6f ", f);
         }
         printf("\n");
      }
   }

   int GetWidth() const { return m_cols; }
   int GetHeight() const { return m_rows; }

private:
   size_t CalcIndex(int col, int row) const
   {
#ifndef NDEBUG
      if (col < 0) {
         printf("%s:%d - negative col %d\n", __FILE__, __LINE__, col);
      }

      if (col >= m_cols) {
         printf("%s:%d - column overflow (%d vs %d)\n", __FILE__, __LINE__, col, m_cols);
         exit(0);
      }

      if (row < 0) {
         printf("%s:%d - negative row %d\n", __FILE__, __LINE__, row);
      }

      if (row >= m_rows) {
         printf("%s:%d - row overflow (%d vs %d)\n", __FILE__, __LINE__, row, m_rows);
         exit(0);
      }
#endif
      size_t Index = row * m_cols + col;

      return Index;
   }

   float* m_p = NULL;
   int m_cols = 0;
   int m_rows = 0;
};

