#pragma once
#include "Float3.h"
class Ray
{
public:
	Ray() {}
	Ray(Float3 start, Float3 dir);
	virtual ~Ray();


	//! The start of the ray.
	Float3 Start;
	//! The direction of the ray.
	Float3 Dir;
};

