#include "stdafx.h"
#include "Float2.h"


Float2::Float2()
{
}

Float2::Float2(float x, float y) :x(x), y(y)
{
}


Float2::~Float2()
{
}

void Float2::Saturate() {
	// Task 1: Follow the teacher
	__m128 toSaturate = _mm_setr_ps(x, y, 0, 0);
	__m128 max = _mm_setr_ps(1, 1, 0, 0);
	__m128 min = _mm_setzero_ps();

	__m128 maxSaturated = _mm_min_ps(max, toSaturate);
	__m128 minSaturated = _mm_max_ps(maxSaturated, min);

	__declspec(align(16)) float result[4];
	_mm_store_ps(result, minSaturated);
	x = result[0];
	y = result[1];
}
