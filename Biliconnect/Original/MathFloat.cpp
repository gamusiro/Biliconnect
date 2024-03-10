/*=========================================================================
	Date : 2022/01/31(��)	MathFloat.cpp
		Author : ���ނ��邧
		Update :
=========================================================================*/
#include <math.h>

#include "MathFloat.h"
using namespace math;

/*=============================================================================================
	���όv�Z2D
=============================================================================================*/
float MathFloat::Dot(const Float2& vec1, const Float2& vec2) 
{ 
	return (vec1.x * vec2.x + vec1.y * vec2.y); 
}
float MathFloat::Dot(const Float3& vec1, const Float3& vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}
float MathFloat::Dot(const Float4& vec1, const Float4& vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
}

/*=============================================================================================
	�O�όv�Z
=============================================================================================*/
float math::MathFloat::Cross(const Float2& vec1, const Float2& vec2)
{
	return vec1.x * vec2.y - vec1.y * vec2.x;
}
Float3 MathFloat::Cross(const Float3& vec1, const Float3& vec2)
{
	Float3 ret;
	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return ret;
}

/*=============================================================================================
	�x�N�g���̒���(�������̌v�Z�L)
=============================================================================================*/
float MathFloat::Length(const Float2& v)
{
	return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f));
}
float MathFloat::Length(const Float3& v)
{
	return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
}
float MathFloat::Length(const Float4& v)
{
	return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f) + powf(v.w, 2.0f));
}

/*=============================================================================================
	�x�N�g���̒���(�������̌v�Z��)
=============================================================================================*/
float MathFloat::LengthSq(const Float2& v)
{
	return powf(v.x, 2.0f) + powf(v.y, 2.0f);
}
float MathFloat::LengthSq(const Float3& v)
{
	return powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f);
}
float MathFloat::LengthSq(const Float4& v)
{
	return powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f) + powf(v.w, 2.0f);
}

/*=============================================================================================
	���`���
=============================================================================================*/
Float2 MathFloat::Lerp(const Float2& start, const Float2& end, float mediated)
{
	Float2 ret = start;
	Float2 sub = end;
	sub -= start;
	return ret + (sub * mediated);
}
Float3 MathFloat::Lerp(const Float3& start, const Float3& end, float mediated)
{
	Float3 ret = start;
	Float3 sub = end;
	sub -= start;
	return ret + (sub * mediated);
}
Float4 MathFloat::Lerp(const Float4& start, const Float4& end, float mediated)
{
	Float4 ret = start;
	Float4 sub = end;
	sub -= start;
	return ret + (sub * mediated);
}

/*=============================================================================================
	�ő�l��Ԃ�
=============================================================================================*/
Float2 MathFloat::Maxmize(const Float2& vec1, const Float2& vec2)
{
	Float2 ret = vec1;
	if (vec1.x < vec2.x) ret.x = vec2.x;
	if (vec1.y < vec2.y) ret.y = vec2.y;
	return ret;
}
Float3 MathFloat::Maxmize(const Float3& vec1, const Float3& vec2)
{
	Float3 ret = vec1;
	if (vec1.x < vec2.x) ret.x = vec2.x;
	if (vec1.y < vec2.y) ret.y = vec2.y;
	if (vec1.z < vec2.z) ret.z = vec2.z;
	return ret;
}
Float4 MathFloat::Maxmize(const Float4& vec1, const Float4& vec2)
{
	Float4 ret = vec1;
	if (vec1.x < vec2.x) ret.x = vec2.x;
	if (vec1.y < vec2.y) ret.y = vec2.y;
	if (vec1.z < vec2.z) ret.z = vec2.z;
	if (vec1.w < vec2.w) ret.w = vec2.w;
	return ret;
}

/*=============================================================================================
	�ŏ��l��Ԃ�
=============================================================================================*/
Float2 MathFloat::Minimize(const Float2& vec1, const Float2& vec2)
{
	Float2 ret = vec1;
	if (vec1.x > vec2.x) ret.x = vec2.x;
	if (vec1.y > vec2.y) ret.y = vec2.y;
	return ret;
}
Float3 MathFloat::Minimize(const Float3& vec1, const Float3& vec2)
{
	Float3 ret = vec1;
	if (vec1.x > vec2.x) ret.x = vec2.x;
	if (vec1.y > vec2.y) ret.y = vec2.y;
	if (vec1.z > vec2.z) ret.z = vec2.z;
	return ret;
}
Float4 MathFloat::Minimize(const Float4& vec1, const Float4& vec2)
{
	Float4 ret = vec1;
	if (vec1.x > vec2.x) ret.x = vec2.x;
	if (vec1.y > vec2.y) ret.y = vec2.y;
	if (vec1.z > vec2.z) ret.z = vec2.z;
	if (vec1.w > vec2.w) ret.w = vec2.w;
	return ret;
}

/*=============================================================================================
	���K���l��Ԃ�
=============================================================================================*/
Float2 MathFloat::Normalize(const Float2& v)
{
	Float2 ret = v;
	float length = MathFloat::Length(v);
	float unit = 0;

	//��W���[����V�X�e��
	if (length > 0.0f)
		unit = 1.0f / length;

	return ret * unit;
}
Float3 MathFloat::Normalize(const Float3& v)
{
	Float3 ret = v;
	float length = MathFloat::Length(v);
	float unit = 0;

	//��W���[����V�X�e��
	if (length > 0.0f)
		unit = 1.0f / length;

	return ret * unit;
}
Float4 MathFloat::Normalize(const Float4& v)
{
	Float4 ret = v;
	float length = MathFloat::Length(v);
	float unit = 0;

	//��W���[����V�X�e��
	if (length > 1.0f)
		unit = 1.0f / length;
	else
		unit = length;

	return ret * unit;
}
