/*===============================================================
	Date : 2021/12/07(火)	Float2.cpp
		Author	: がむしるぉ
		Comment	: 出会い系で初めて通報された日
===============================================================*/
#include "Float2.h"
using namespace math;

//コンストラクタ
Float2::Float2() :x(0), y(0) {}
Float2::Float2(float x, float y) : x(x), y(y) {}
Float2::Float2(const Float2& vec) : x(vec.x), y(vec.y) {}

//デストラクタ
Float2::~Float2() {}

//演算子のオーバーロード(足し算)
Float2 Float2::operator +	(const Float2& vec) { return Float2(x + vec.x, y + vec.y); }
Float2 Float2::operator +	(const float &  f ) { return Float2(x + f, y + f); }
Float2 Float2::operator +=	(const Float2& vec) { return *this = *this + vec; }
Float2 Float2::operator +=	(const float &  f ) { return *this = *this + f; }

//演算子のオーバーロード(引き算)
Float2 Float2::operator -	(const Float2& vec) { return Float2(x - vec.x, y - vec.y); }
Float2 Float2::operator -	(const float& f)	{ return Float2(x - f, y - f); }
Float2 Float2::operator -=	(const Float2& vec) { return *this = *this - vec; }
Float2 Float2::operator -=	(const float& f)	{ return *this = *this - f; }

//演算子のオーバーロード(掛け算)
Float2 Float2::operator *	(const Float2& vec) { return Float2(x * vec.x, y * vec.y); }
Float2 Float2::operator *	(const float& f)	{ return Float2(x * f, y * f); }
Float2 Float2::operator *=	(const Float2& vec) { return *this = *this * vec; }
Float2 Float2::operator *=	(const float& f)	{ return *this = *this * f; }

//演算子のオーバーロード(割り算)
Float2 Float2::operator /	(const Float2& vec) { return Float2(x / vec.x, y / vec.y); }
Float2 Float2::operator /	(const float& f)	{ return Float2(x / f, y / f); }
Float2 Float2::operator /=	(const Float2& vec) { return *this = *this / vec; }
Float2 Float2::operator /=	(const float& f)	{ return *this = *this / f; }
