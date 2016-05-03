#pragma once
#include "Float2.h"
#include "Float3.h"
#include "Int3.h"
#include "Ray.h"

class Triangle
{
	
public:
	Triangle(Float3 m_V1, Float3 m_V2, Float3 m_V3);
	virtual ~Triangle();

	float Distance(Float3 other);

	bool Intersect2(Float3& rayStart,Float3& rayDir, Float3& lambdas, float& t, Float3& I);
	float DotWithNorm(Float3& vec);

private:
	Float3 m_Origin;
	Float3 m_V1;
	Float3 m_V2;

	Float3 m_Normal;
	Float3 m_U;
	Float3 m_V;
	float OU, OV;

	Float2 m_LocalU;
	Float2 m_LocalV;
};

