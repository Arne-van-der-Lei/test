#include "stdafx.h"
#include "Float4.h"



Float4::Float4()
{
}

Float4::Float4(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {
}


Float4::~Float4()
{
}

float Float4::Dot(Float4& op1, Float4& op2) {
	// Task 8: replace with SSE
	return Float4::Dot(op1.x, op1.y, op1.z, op1.w, op2.x, op2.y, op2.z, op2.w);
	//return op2.x * op2.x + op1.y * op2.y + op1.z * op2.z + op1.w * op2.w;
}

float Float4::Dot(float x1, float y1, float z1, float w1, float x2, float y2, float z2, float w2) {
	// Task 8: replace with SSE
	__m128 v1 = _mm_setr_ps(x1, y1, z1, w1);
	__m128 v2 = _mm_setr_ps(x2,y2,z2,w2);
	__m128 dpResult = _mm_dp_ps(v1, v2, 0xf1);
	return _mm_cvtss_f32(dpResult);
	//return x1*x2 + y1*y2 + z1*z2 + w1*w2;
}

float Float4::Dot(Float3& op1, float w1, Float3& op2, float w2) {
	// Task 8: replace with SSE
	return Float4::Dot(op1.x, op1.y, op1.z, w1, op2.x, op2.y, op2.z, w2);
	//return op1.x * op2.x + op1.y * op2.y + op1.z * op2.z + w1 * w2;
}
