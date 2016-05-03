#pragma once
#include "Float3.h"
class Float4
{
	friend class Rasterizer;
public:
	Float4();
	Float4(float x, float y, float z, float w);
	virtual ~Float4();

	float GetX(){
		return x;
	}

	void SetX(float x){
		this->x = x;
	}

	float GetY(){
		return y;
	}

	void SetY(float y){
		this->y = y;
	}

	float GetZ(){
		return z;
	}

	void SetZ(float z){
		this->z = z;
	}
	
	float GetW(){
		return w;
	}

	void SetW(float w){
		this->w = w;
	}

	static float Dot(Float4& v1,Float4& v2);
	static float Dot(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2);
	static float Dot(Float3& v1, float w1, Float3& v2, float w2);
private:
	float x,y,z,w;
};

