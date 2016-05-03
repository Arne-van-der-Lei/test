#include "stdafx.h"
#include "Triangle.h"
#include "Float4.h"
#include "math.h"


Triangle::Triangle(Float3 p1, Float3 p2, Float3 p3) :m_Origin(p1), m_V1(p2 - p1), m_V2(p3 - p1)
{
	Float3::Cross(m_V1, m_V2, m_Normal);
	m_Normal.Normalize();

	m_U = m_V1.Normalized();
	Float3::Cross(m_Normal, m_U, m_V);
	m_V.Normalize();

	m_LocalU.Set(m_V1.GetLength(), 0);
	m_LocalV.Set(Float3::Dot(m_V2, m_U), Float3::Dot(m_V2, m_V));

	OU = -Float3::Dot(m_U, m_Origin);
	OV = -Float3::Dot(m_V, m_Origin);
}


Triangle::~Triangle()
{
}

float Triangle::Distance(Float3 p){
	Float3 diff = p - m_Origin;
	return Float3::Dot(m_Normal,diff);
}

bool Triangle::Intersect2(Float3& rayStart,Float3& rayDir, Float3& lambdas,float& t,Float3& I) {
	// first, find the intersection point
	// (rayStart + t*ray.Dir - m_Origin) Dot (m_Normal) = 0
	Float3 rayVec = rayStart - m_Origin;
	float num = -Float3::Dot(rayVec, m_Normal);
	float denum = Float3::Dot(rayDir, m_Normal);
	// Isolate t
	t = num / denum;
	 // magic number: 0.01
	if (t < 0.01f) {
		return false;
	}
	// Intersection is ray starting point + t times the ray direction.
	I = rayStart + t*rayDir;
	// calculate local x and y.
	float x = Float4::Dot(m_U, 1, I, OU);
	float y = Float4::Dot(m_V, 1, I, OV);
	// calculate local u and v.
	float v = y / m_LocalV.y;
	float u = (x - m_LocalV.x*v) / (m_LocalU.x);
	// set the lambdas.
	lambdas.Set(1 - u - v, u, v);
	// replace with check if the lambdas are correct.
	return v > 0 && u > 0 && u+v<1;
}

float Triangle::DotWithNorm(Float3& vec) {
	return Float3::Dot(m_Normal,vec);
}