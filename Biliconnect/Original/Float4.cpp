/*===============================================================
	Date : 2021/12/07(火)	Float4.cpp
		Author	: がむしるぉ
		Comment	: 出会い系で初めて通報された日
===============================================================*/
#include "Float4.h"
using namespace math;

//コンストラクタ
Float4::Float4() : x(0), y(0), z(0), w(0) {}
Float4::Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Float4::Float4(const Float4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

//デストラクタ
Float4::~Float4() {}

//演算子のオーバーロード(足し算)
Float4 Float4::operator +	(const Float4& vec) { return Float4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w); }
Float4 Float4::operator +	(const float& f)	{ return Float4(this->x + f, this->y + f, this->z + f, this->w + f); }
Float4 Float4::operator +=	(const Float4& vec) { return *this = *this + vec; }
Float4 Float4::operator +=	(const float& f)	{ return *this = *this + f; }

//演算子のオーバーロード(引き算)
Float4 Float4::operator -	(const Float4& vec) { return Float4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w); }
Float4 Float4::operator -	(const float& f)	{ return Float4(this->x - f, this->y - f, this->z - f, this->w - f); }
Float4 Float4::operator -=	(const Float4& vec) { return *this = *this - vec; }
Float4 Float4::operator -=	(const float& f)	{ return *this = *this - f; }

//演算子のオーバーロード(掛け算)
Float4 Float4::operator *	(const Float4& vec) { return Float4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w); }
Float4 Float4::operator *	(const float& f)	{ return Float4(this->x * f, this->y * f, this->z * f, this->w * f); }
Float4 Float4::operator *=	(const Float4& vec) { return *this = *this * vec; }
Float4 Float4::operator *=	(const float& f)	{ return *this = *this * f; }

//演算子のオーバーロード(割り算)
Float4 Float4::operator /	(const Float4& vec) { return Float4(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w); }
Float4 Float4::operator /	(const float& f)	{ return Float4(this->x / f, this->y / f, this->z / f, this->w / f); }
Float4 Float4::operator /=	(const Float4& vec) { return *this = *this / vec; }
Float4 Float4::operator /=	(const float& f)	{ return *this = *this / f; }
