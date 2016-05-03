#pragma once

class Float3
{
	friend class Matrix44;
	friend class Rasterizer;
	friend class Triangle;
public:
	Float3();
	Float3(float x, float y, float z);
	virtual ~Float3();

	static float Dot(const Float3& op1, const Float3& op2);
	static float Dot(float x1, float y1, float z1, float x2, float y2, float z2);
	static void Cross(Float3& op1, Float3& op2, Float3& result);
	static void Cross(Float3& p1, Float3& p2, Float3& p3, Float3& result);
	static void Reflect(Float3& toReflect, Float3& normal, Float3& result);

	void Set(float x, float y, float z);
	void Set(Float3& toSet);
	float GetLength() const;
	void Normalize();
	Float3 Normalized() const;
	void Normalized(Float3& result) const;

	inline Float3 operator-(const Float3& otherRef) const
	{
		return Float3(x - otherRef.x, y - otherRef.y, z-otherRef.z);
	}

	inline Float3 operator+(const Float3& otherRef) const
	{
		return Float3(x + otherRef.x, y + otherRef.y, z + otherRef.z);
	}

	inline Float3 operator*( float scalar) const {
		return Float3(x * scalar, y * scalar, z * scalar);
	}

	float x, y, z;
};

Float3 operator*(float scalar, const Float3& other);
