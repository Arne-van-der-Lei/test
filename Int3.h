#pragma once
class Int3
{
public:
	Int3();
	Int3(int x, int y, int z);
	virtual ~Int3();

	void Set(Int3& other) {
		x = other.x;
		y = other.y;
		z = other.z;
	}

	void ClampColor();

	int GetX(){
		return x;
	}

	int GetY(){
		return y;
	}

	int GetZ(){
		return z;
	}

	inline Int3 operator+(const Int3& otherRef) const
	{
		return Int3(x + otherRef.x, y + otherRef.y, z + otherRef.z);
	}

	inline Int3& operator+=(const Int3& rhs) // compound assignment (does not need to be a member,
	{                           // but often is, to modify the private members)
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this; // return the result by reference
	}

	inline Int3& operator/=(int div)
	{
		x /= div;
		y /= div;
		z /= div;
		return *this;
	}

	int x,y,z;
};

