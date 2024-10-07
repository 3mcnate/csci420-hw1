#include <memory>
#include <algorithm>

using namespace std;

struct Vertex
{
  Vertex(float x, float y, float z, float color)
  {
    this->x = x;
    this->y = y;
    this->z = z;
    this->color = color;
  }

  float x;
  float y;
  float z;
  float color;
};

Vertex createVertex(float xBias, float zBias, float resolution, unsigned char pixel, int x, int y)
{
  float x1 = (-x + xBias) / (resolution - 1);
  float y1 = (float)pixel / 255.0f;
  float z1 = (-y + zBias) / (resolution - 1);
  float color = (pixel + 30.0) / 285.0;

  return Vertex(x1, y1, z1, color);
}

void addLineToVBO(std::unique_ptr<float[]>& vertexVBO, std::unique_ptr<float[]>& colorVBO, int &vIndex, int &cIndex, Vertex vertex1, Vertex vertex2)
{
  vertexVBO[vIndex++] = vertex1.x;
  vertexVBO[vIndex++] = vertex1.y;
  vertexVBO[vIndex++] = vertex1.z;

  vertexVBO[vIndex++] = vertex2.x;
  vertexVBO[vIndex++] = vertex2.y;
  vertexVBO[vIndex++] = vertex2.z;

  std::fill_n(colorVBO.get() + cIndex, 4, vertex1.color);
  cIndex += 4;
  std::fill_n(colorVBO.get() + cIndex, 4, vertex2.color);
  cIndex += 4;
}