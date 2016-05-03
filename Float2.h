#pragma once
class Float2
{
public:
	Float2();
	Float2(float x, float y);
	virtual ~Float2();

	void Set(Float2& other) {
		x = other.x;
		y = other.y;
	}

	void Set(float x, float y){
		this->x = x;
		this->y = y;
	}

	void Saturate();
	float x, y;
};

