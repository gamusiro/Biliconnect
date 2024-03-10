/*=========================================================================
	Date : 2022/01/31(月)	Matrix4x4.cpp
		Author : がむしるぉ
		Update :
=========================================================================*/
#include "Matrix4x4.h"
using namespace math;


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
Matrix4x4::Matrix4x4(bool zero)
	:m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f),
	 m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
	 m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
	 m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
{
	if (zero)
		m11 = m22 = m33 = m44 = 0.0f;
}
Matrix4x4::Matrix4x4(
	float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
	:m11(_11), m12(_12), m13(_13), m14(_14),
	 m21(_21), m22(_22), m23(_23), m24(_24),
	 m31(_31), m32(_32), m33(_33), m34(_34),
	 m41(_41), m42(_42), m43(_43), m44(_44)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
Matrix4x4::~Matrix4x4()
{
}

/*=============================================================================================
	演算子のオーバーロード(足し算)
=============================================================================================*/
Matrix4x4 Matrix4x4::operator+(const Matrix4x4& vec)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] + vec.mat[y][x];
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator+(const float& v)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] + v;
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator+=(const Matrix4x4& vec)
{
	return *this = *this + vec;
}
Matrix4x4 Matrix4x4::operator+=(const float& v)
{
	return *this = *this + v;
}

/*=============================================================================================
	演算子のオーバーロード(引き算)
=============================================================================================*/
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& vec)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] - vec.mat[y][x];
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator-(const float& v)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] - v;
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator-=(const Matrix4x4& vec)
{
	return *this = *this - vec;
}
Matrix4x4 Matrix4x4::operator-=(const float& v)
{
	return *this = *this - v;
}

/*=============================================================================================
	演算子のオーバーロード(掛け算)
=============================================================================================*/
Matrix4x4 Matrix4x4::operator*(const Matrix4x4& vec)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] * vec.mat[y][x];
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator*(const float& v)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] * v;
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator*=(const Matrix4x4& vec)
{
	return *this = *this * vec;
}
Matrix4x4 Matrix4x4::operator*=(const float& v)
{
	return *this = *this * v;
}

/*=============================================================================================
	演算子のオーバーロード(割り算)
=============================================================================================*/
Matrix4x4 Matrix4x4::operator/(const Matrix4x4& vec)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] / vec.mat[y][x];
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator/(const float& v)
{
	Matrix4x4 ret;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			ret.mat[y][x] = this->mat[y][x] / v;
		}
	}
	return ret;
}
Matrix4x4 Matrix4x4::operator/=(const Matrix4x4& vec)
{
	return *this = *this / vec;
}
Matrix4x4 Matrix4x4::operator/=(const float& v)
{
	return *this = *this / v;
}
