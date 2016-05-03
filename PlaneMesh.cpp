#include "stdafx.h"
#include "PlaneMesh.h"


PlaneMesh::PlaneMesh(float size)
{
	float h = size / 2;
	AddVertex(-h, -h,0);
	AddTexCoord(0, 0);
	AddNormal(0, 0, 1);

	AddVertex(h, -h, 0);
	AddTexCoord(0, 1);
	AddNormal(0, 0, 1);

	AddVertex(h, h, 0);
	AddTexCoord(1, 1);
	AddNormal(0, 0, 1);

	AddVertex(-h, h, 0);
	AddTexCoord(1, 0);
	AddNormal(0, 0,1);

	AddTriangle(3,1,0);
	AddTriangle(2,1,3);
}


PlaneMesh::~PlaneMesh()
{
}
