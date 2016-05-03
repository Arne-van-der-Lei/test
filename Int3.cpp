#include "stdafx.h"
#include "Int3.h"

Int3::Int3() :x(0), y(0), z(0)
{
}

Int3::Int3(int x, int y, int z) :x(x), y(y), z(z)
{
}


Int3::~Int3()
{
}

void Int3::ClampColor() {
	__m128i toClamp = _mm_set_epi32(x,y,z,0);
	__m128i maxClamp = _mm_set_epi32(255, 255, 255, 0);
	__m128i minClamp = _mm_set_epi32(0, 0, 0, 0);
	__m128i result = _mm_max_epi32(_mm_min_epi32(toClamp, maxClamp),minClamp);
	__declspec(align(16)) int clamped[4];
	_mm_store_si128((__m128i*)clamped, result);
	x = clamped[3];
	y = clamped[2];
	z = clamped[1];
}
