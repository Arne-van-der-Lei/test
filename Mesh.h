#pragma once
#include "Float2.h"
#include "Float3.h"
#include "Int3.h"
#include "Triangle.h"
#include "Texture.h"
#include "Matrix44.h"

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();


	void SetTexture(Texture* texture) {
		m_pTexture = texture;
	}

	Texture* GetTexture() {
		return m_pTexture;
	}

	void AddVertex(float x, float y, float z);
	void AddNormal(float x, float y, float z);
	void AddTexCoord(float u, float v);
	void AddTriangle(int i1, int i2, int i3);


	Float3& GetVertex(int index);
	Float3& GetNormal(int index);
	
	Int3& GetTriangleIndices(int index);
	Triangle& GetTriangle(int index);
	Float2& GetTexCoord(int index);

	size_t GetNrOfVertices();
	size_t GetNrOfTriangles();

	void InterpolateTexcoords(Int3& indices, Float3& lambdas, Float2& result);
	void InterpolateNormal(Int3& indices, Float3& lambdas, Float3& result);

	void SetTransform(float tx, float ty, float tz);
	void SetTransform(float tx, float ty, float tz, float rx, float ry, float rz);
	
	Matrix44& GetWorldInverse() {
		return m_WorldI;
	}

	Matrix44& GetWorld() {
		return m_World;
	}
private:
	
	std::vector<Float3> m_Vertices;
	std::vector<Float3> m_Normals;
	std::vector<Float2> m_Texcoords;
	std::vector<Int3> m_Indices;
	std::vector<Triangle> m_Triangles;

	Texture* m_pTexture;
	Matrix44 m_World, m_WorldI;
};

