#include "stdafx.h"
#include "Float3.h"

#include "mmintrin.h"

Float3::Float3():x(0),y(0),z(0)
{
}

Float3::Float3(float xv, float yv, float zv) :x(xv), y(yv), z(zv)
{
}


Float3::~Float3()
{
}

float Float3::Dot(const Float3& op1, const Float3& op2){
	// Task 2: Implement with SSE instructions.
	__m128 v1 = _mm_setr_ps(op1.x, op1.y, op1.z, 0);
	__m128 v2 = _mm_setr_ps(op2.x, op2.y, op2.z, 0);
	return _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0x71));
	// return op1.x * op2.x + op1.y * op2.y + op1.z * op2.z;
}

float Float3::Dot(float x1, float y1, float z1, float x2, float y2, float z2)
{
	// Task 3: Implement with SSE instructions.
	return x1*x2 + y1*y2 + z1*z2;
}

void Float3::Reflect(Float3& toReflect, Float3& normal, Float3& result) {
	// Task 4: Implement in regular C++
	// Assumes that the normal has a length of 1.
	float h = Float3::Dot(toReflect, normal);
	result = toReflect - 2 * h * normal;
}

void Float3::Cross(Float3& op1, Float3& op2, Float3& result){
	// Task 7: Change to SSE equivalent
	__m128 c1 = _mm_setr_ps(op1.y, op1.z, op1.x, 0);
	__m128 c2 = _mm_setr_ps(op2.z, op2.x, op2.y, 0);
	__m128 left = _mm_mul_ps(c1, c2);
	c1 = _mm_setr_ps(op1.z, op1.x, op1.y, 0);
	c2 = _mm_setr_ps(op2.y, op2.z, op2.x, 0);
	__m128 right = _mm_mul_ps(c1, c2);
	__m128 normal = _mm_sub_ps(left, right);
	__declspec(align(16)) float tempResult[4];
	_mm_store_ps(tempResult, normal);
	float xr2 = tempResult[0];
	float yr2 = tempResult[1];
	float zr2 = tempResult[2];
	/*float xr = op1.y * op2.z - op1.z * op2.y;
	float yr = op1.z * op2.x - op1.x * op2.z;
	float zr = op1.x * op2.y - op1.y * op2.x;*/
	result.Set(xr2, yr2, zr2);
}

void Float3::Cross(Float3& p1, Float3& p2, Float3& p3, Float3& result){
	// Task 7: Change to SSE equivalent
	Float3::Cross(p2 - p1, p3 - p1,result);
	/*float x1 = p2.x - p1.x;
	float y1 = p2.y - p1.y;
	float z1 = p2.z - p1.z;

	float x2 = p3.x - p1.x;
	float y2 = p3.y - p1.y;
	float z2 = p3.z - p1.z;

	float xr = y1 * z2 - z1 * y2;
	float yr = z1 * x2 - x1 * z2;
	float zr = x1 * y2 - y1 * x2;
	result.Set(xr, yr, zr);*/
}

float Float3::GetLength()const{
	__m128 v = _mm_setr_ps(x,y,z, 0);
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v, v, 0x71)));
	//return sqrt(x*x + y*y + z*z);
}

void Float3::Normalize(){
	// Task 5: Follow the teacher.
	__m128 v = _mm_setr_ps(x, y, z, 0);
	__m128 inverse_norm = _mm_rsqrt_ps(_mm_dp_ps(v, v, 0x77));
	// bitmask : 01110111
	__m128 r = _mm_mul_ps(v, inverse_norm);
	__declspec(align(16)) float result[4];
	_mm_store_ps(result, r);
	x = result[0];
	y = result[1];
	z = result[2];
}

Float3 Float3::Normalized()const{
	// Task 6a: Use SSE
	float length = GetLength();
	return Float3(x / length, y / length, z / length);
}

void Float3::Normalized(Float3& result) const{
	// Task 6b: Use SSE
	float length = GetLength();
	result.Set(x / length, y / length, z / length);
}

void Float3::Set(float x, float y, float z){
	this->x = x;
	this->y = y;
	this->z = z;
}

void Float3::Set(Float3& toSet){
	x = toSet.x;
	y = toSet.y;
	z = toSet.z;
}

Float3 operator*(float scalar, const Float3& other){
	return other*scalar;
}

