#pragma once
#include "Float4.h"
#include "Float3.h"
class Matrix44
{
public:
	Matrix44();
	virtual ~Matrix44();

	void SetCell(int row, int column, float value);
	float GetCell(int row, int column);
	void SetRow(int row, Float4& value);
	void SetRow(int row, float a1, float a2, float a3, float a4);
	void SetColumn(int column,Float4& value);
	void SetColumn(int column, float a1, float a2, float a3, float a4);
	void SetAsIdentity();
	void GetRow(int row, Float4& value);
	void GetColumn(int column, Float4& value);

	void TransformVector(Float3& toTransform, Float3& result);
	void TransformPoint(Float3& toTransform, Float3& result);

	void Multiply(Matrix44 & toMultiply, Matrix44& result);
	void SetAsTranslate(float x, float y, float z);
	void SetAsViewTransform(Float3 e, Float3 t);
	void SetAsXRotation(float angle);
	void SetAsYRotation(float angle);
	void SetAsZRotation(float angle);

	void ViewInverse(Matrix44& dest);
	void WorldOrthonormalInverse(Matrix44& dest);
private:

	float m_Data[16];
};

