#include "stdafx.h"
#include "Mesh.h"


Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::AddVertex(float x, float y, float z){
	m_Vertices.push_back(Float3(x, y, z));
}

void Mesh::AddNormal(float x, float y, float z){
	m_Normals.push_back(Float3(x, y, z));
}

void Mesh::AddTexCoord(float u, float v){
	m_Texcoords.push_back(Float2(u, v));
}

void Mesh::AddTriangle(int i1, int i2, int i3){
	m_Indices.push_back(Int3(i1,i2,i3));
	
	Float3 p1 = GetVertex(i1);
	Float3 p2 = GetVertex(i2);
	Float3 p3 = GetVertex(i3);
	Triangle t(p1, p2, p3);
	m_Triangles.push_back(t);
}


Float3& Mesh::GetVertex(int index){
	return m_Vertices[index];
}

Float3& Mesh::GetNormal(int index){
	return m_Normals[index];
}

Float2& Mesh::GetTexCoord(int index){
	return m_Texcoords[index];
}

Int3& Mesh::GetTriangleIndices(int index){
	return m_Indices[index];
}

Triangle& Mesh::GetTriangle(int index) {
	return m_Triangles[index];
}

size_t Mesh::GetNrOfVertices(){
	return m_Vertices.size();
}

size_t Mesh::GetNrOfTriangles(){
	return m_Indices.size();
}

void Mesh::InterpolateNormal(Int3& indices, Float3& lambdas, Float3& result) {
	// Task 12: Get the correct normals (see task 11) and interpolate
	// with the help of the lambdas variable and store into result.
	Float3 norm1 = GetNormal(indices.x);
	Float3 norm2 = GetNormal(indices.y);
	Float3 norm3 = GetNormal(indices.z);
	result.x = Float3::Dot(norm1.x, norm2.x, norm3.x, lambdas.x, lambdas.y, lambdas.z);
	result.y = Float3::Dot(norm1.y, norm2.y, norm3.y, lambdas.x, lambdas.y, lambdas.z);
	result.z = Float3::Dot(norm1.z, norm2.z, norm3.z, lambdas.x, lambdas.y, lambdas.z);
}

void Mesh::InterpolateTexcoords(Int3& indices, Float3& lambdas, Float2& result) {
	Float2 uv1 = GetTexCoord(indices.x);
	Float2 uv2 = GetTexCoord(indices.y);
	Float2 uv3 = GetTexCoord(indices.z);
	// Task 11: interpolate with the help of the lambdas variable and store into result.
	result.x = Float3::Dot(uv1.x, uv2.x, uv3.x, lambdas.x, lambdas.y, lambdas.z);
	result.y = Float3::Dot(uv1.y, uv2.y, uv3.y, lambdas.x, lambdas.y, lambdas.z);
}

void Mesh::SetTransform(float tx, float ty, float tz) {
	m_World.SetAsTranslate(tx, ty, tz);
	m_World.WorldOrthonormalInverse(m_WorldI);
}
void Mesh::SetTransform(float tx, float ty, float tz, float rx, float ry, float rz) {

}