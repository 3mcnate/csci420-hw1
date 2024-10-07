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

void addVertexToVBO(std::unique_ptr<float[]>& vertexVBO, std::unique_ptr<float[]>& colorVBO, int &vIndex, int &cIndex, Vertex vertex)
{
  vertexVBO[vIndex++] = vertex.x;
  vertexVBO[vIndex++] = vertex.y;
  vertexVBO[vIndex++] = vertex.z;

  std::fill_n(colorVBO.get() + cIndex, 4, vertex.color);
  cIndex += 4;
}

void addLineToVBO(std::unique_ptr<float[]>& vertexVBO, std::unique_ptr<float[]>& colorVBO, int &vIndex, int &cIndex, Vertex vertex1, Vertex vertex2)
{
  addVertexToVBO(vertexVBO, colorVBO, vIndex, cIndex, vertex1);
  addVertexToVBO(vertexVBO, colorVBO, vIndex, cIndex, vertex2);
}

void addTriangleToVBO(std::unique_ptr<float[]>& vertexVBO, std::unique_ptr<float[]>& colorVBO, int &vIndex, int &cIndex, Vertex vertex1, Vertex vertex2, Vertex vertex3)
{
  addVertexToVBO(vertexVBO, colorVBO, vIndex, cIndex, vertex1);
  addVertexToVBO(vertexVBO, colorVBO, vIndex, cIndex, vertex2);
  addVertexToVBO(vertexVBO, colorVBO, vIndex, cIndex, vertex3);
}