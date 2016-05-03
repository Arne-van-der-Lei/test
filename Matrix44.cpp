#include "stdafx.h"
#include "Matrix44.h"


Matrix44::Matrix44()
{
	SetAsIdentity();
}


Matrix44::~Matrix44()
{
}

void Matrix44::SetCell(int row, int column, float value){
	m_Data[row * 4 + column] = value;
}
float Matrix44::GetCell(int row, int column){
	return m_Data[row * 4 + column];
}
void Matrix44::SetRow(int row, Float4& value){
	m_Data[row * 4] = value.GetX();
	m_Data[row * 4 + 1] = value.GetY();
	m_Data[row * 4 + 2] = value.GetZ();
	m_Data[row * 4 + 3] = value.GetW();
}
void Matrix44::SetRow(int row, float a1, float a2, float a3, float a4){
	m_Data[row * 4] = a1;
	m_Data[row * 4 + 1] = a2;
	m_Data[row * 4 + 2] = a3;
	m_Data[row * 4 + 3] = a4;
}
void Matrix44::SetColumn(int column, Float4& value){
	m_Data[column] = value.GetX();
	m_Data[4 + column] = value.GetY();
	m_Data[8 + column] = value.GetZ();
	m_Data[12 + column] = value.GetW();
}
void Matrix44::SetColumn(int column, float a1, float a2, float a3, float a4){
	m_Data[column] = a1;
	m_Data[4 + column] = a2;
	m_Data[8 + column] = a3;
	m_Data[12 + column] = a4;
}
void Matrix44::SetAsIdentity(){
	SetRow(0, 1, 0, 0, 0);
	SetRow(1, 0, 1, 0, 0);
	SetRow(2, 0, 0, 1, 0);
	SetRow(3, 0, 0, 0, 1);
}
void Matrix44::GetRow(int row, Float4& value){
	value.SetX(m_Data[row * 4]);
	value.SetY(m_Data[row * 4 + 1]);
	value.SetZ(m_Data[row * 4 + 2]);
	value.SetW(m_Data[row * 4 + 3]);
}
void Matrix44::GetColumn(int column, Float4& value){
	value.SetX(m_Data[column]);
	value.SetY(m_Data[4 + column]);
	value.SetZ(m_Data[8 + column]);
	value.SetW(m_Data[12 + column]);
}

void Matrix44::TransformPoint(Float3& tt, Float3& result){
	float xr = Float4::Dot(tt.x, tt.y, tt.z, 1, m_Data[0], m_Data[4], m_Data[8], m_Data[12]);
	float yr = Float4::Dot(tt.x, tt.y, tt.z, 1, m_Data[1], m_Data[5], m_Data[9], m_Data[13]);
	float zr = Float4::Dot(tt.x, tt.y, tt.z, 1, m_Data[2], m_Data[6], m_Data[10], m_Data[14]);
	float wr = Float4::Dot(tt.x, tt.y, tt.z, 1, m_Data[3], m_Data[7], m_Data[11], m_Data[15]);
	

	/*float xr = tt.x * m_Data[0] + tt.y * m_Data[4] + tt.z * m_Data[8] + m_Data[12];
	float yr = tt.x * m_Data[1] + tt.y * m_Data[5] + tt.z * m_Data[9] + m_Data[13];
	float zr = tt.x * m_Data[2] + tt.y * m_Data[6] + tt.z * m_Data[10] + m_Data[14];
	float wr = tt.x * m_Data[3] + tt.y * m_Data[7] + tt.z * m_Data[11] + m_Data[15];*/
	result.Set(xr / wr, yr / wr, zr / wr);
}

void Matrix44::TransformVector(Float3& tt, Float3& result){
	float xr = Float3::Dot(tt.x, tt.y, tt.z, m_Data[0], m_Data[4], m_Data[8]);
	float yr = Float3::Dot(tt.x, tt.y, tt.z, m_Data[1], m_Data[5], m_Data[9]);
	float zr = Float3::Dot(tt.x, tt.y, tt.z, m_Data[2], m_Data[6], m_Data[10]);

	/*float xr = toTransform.x * m_Data[0] + toTransform.y * m_Data[4] + toTransform.z * m_Data[8];
	float yr = toTransform.x * m_Data[1] + toTransform.y * m_Data[5] + toTransform.z * m_Data[9];
	float zr = toTransform.x * m_Data[2] + toTransform.y * m_Data[6] + toTransform.z * m_Data[10];*/
	result.Set(xr, yr, zr);
}

void Matrix44::Multiply(Matrix44 & toMultiply, Matrix44& result){
	Float4 rowBuffer; 
	Float4 columnBuffer; 
	for (int irow = 0; irow < 4; irow++) {
		for (int icolumn = 0; icolumn < 4; icolumn++) {
			GetRow(irow, rowBuffer);
			toMultiply.GetColumn(icolumn, columnBuffer);
			result.SetCell(irow, icolumn, Float4::Dot(rowBuffer,columnBuffer));
		}
	}
}
void Matrix44::SetAsViewTransform(Float3 e, Float3 t){
	Float3 l(t.x- e.x, t.y - e.y, t.z - e.z);
	l.Normalize();

	Float3 r;
	Float3 unitZ(0, 0, 1);
	Float3::Cross(l, unitZ,r);
	r.Normalize();

	Float3 u;
	Float3::Cross(r, l,u);
	u.Normalize();

	SetColumn(0, r.x, r.y, r.z, -Float3::Dot(r,e));
	SetColumn(1, u.x, u.y, u.z, -Float3::Dot(u, e));
	SetColumn(2, l.x, l.y, l.z, -Float3::Dot(l, e));
	SetColumn(3, 0, 0, 0, 1);
}

void Matrix44::SetAsZRotation(float angle){
	SetAsIdentity();
	SetRow(0, cos(angle),sin(angle), 0, 0);
	SetRow(1, -sin(angle), cos(angle), 0, 0);
}

void Matrix44::ViewInverse(Matrix44 & dest)
{
	Float4 ax,ay,az,o;
	this->GetRow(0, ax); dest.SetColumn(0, ax);
	this->GetRow(1, ay); dest.SetColumn(1, ay);
	this->GetRow(2, az); dest.SetColumn(2, az);
	dest.SetColumn(3, 0, 0, 0, 1);

	GetRow(3,o);

	dest.SetCell(3, 0, -Float4::Dot(ax, o));
	dest.SetCell(3, 1, -Float4::Dot(ay, o));
	dest.SetCell(3, 2, -Float4::Dot(az, o));
	dest.SetCell(3, 3, 1);
}

void Matrix44::WorldOrthonormalInverse(Matrix44 & dest)
{
	Float4 ax, ay, az, o;
	this->GetRow(0, ax); dest.SetColumn(0, ax);
	this->GetRow(1, ay); dest.SetColumn(1, ay);
	this->GetRow(2, az); dest.SetColumn(2, az);
	dest.SetColumn(3, 0, 0, 0, 1);

	GetRow(3, o);

	dest.SetCell(3, 0, -Float4::Dot(ax, o));
	dest.SetCell(3, 1, -Float4::Dot(ay, o));
	dest.SetCell(3, 2, -Float4::Dot(az, o));
	dest.SetCell(3, 3, 1);
}

void Matrix44::SetAsTranslate(float x, float y, float z) {
	SetRow(3, x, y, z, 1);
}

void Matrix44::SetAsYRotation(float angle){
	SetAsIdentity();
	SetRow(0, cos(angle),0 , sin(angle), 0);
	SetRow(2, sin(angle),0, cos(angle), 0);
}

void Matrix44::SetAsXRotation(float angle){
	SetAsIdentity();
	SetRow(1,0, cos(angle), sin(angle), 0);
	SetRow(2, 0,-sin(angle), cos(angle), 0);
}