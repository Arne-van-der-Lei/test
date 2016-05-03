#pragma once
#include "Mesh.h"
class SphereMesh: public Mesh
{
public:
	SphereMesh(int radialSamples, int axialSampes, float radius);
	virtual ~SphereMesh();
	
};

