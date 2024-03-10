/*===============================================================
	Date : 2021/12/07(火)	Float3.cpp
		Author	: がむしるぉ
		Comment	: 出会い系で初めて通報された日
===============================================================*/
#include "Float3.h"
using namespace math;

//コンストラクタ
Float3::Float3() : x(0.0f), y(0.0f), z(0.0f) {}
Float3::Float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
Float3::Float3(const Float3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

//デストラクタ
Float3::~Float3() {}

//演算子のオーバーロード(足し算)
Float3 Float3::operator	+	(const Float3& vec) { return Float3(this->x + vec.x, this->y + vec.y, this->z + vec.z); }
Float3 Float3::operator	+	(const float &  f ) { return Float3(this->x + f, this->y + f, this->z + f); }
Float3 Float3::operator	+=	(const Float3& vec) { return *this = *this + vec; }
Float3 Float3::operator	+=	(const float &  f ) { return *this = *this +  f ; }

//演算子のオーバーロード(引き算)
Float3 Float3::operator	-	(const Float3& vec) { return Float3(this->x - vec.x, this->y - vec.y, this->z - vec.z); }
Float3 Float3::operator	-	(const float &  f ) { return Float3(this->x - f, this->y - f, this->z - f); }
Float3 Float3::operator	-=	(const Float3& vec) { return *this = *this - vec; }
Float3 Float3::operator	-=	(const float &  f ) { return *this = *this -  f ; }

//演算子のオーバーロード(掛け算)
Float3 Float3::operator	*	(const Float3& vec) { return Float3(this->x * vec.x, this->y * vec.y, this->z * vec.z); }
Float3 Float3::operator	*	(const float &  f ) { return Float3(this->x * f, this->y * f, this->z * f); }
Float3 Float3::operator	*=	(const Float3& vec) { return *this = *this * vec; }
Float3 Float3::operator	*=	(const float &  f ) { return *this = *this *  f ; }

//演算子のオーバーロード(割り算)
Float3 Float3::operator	/	(const Float3& vec) { return Float3(this->x / vec.x, this->y / vec.y, this->z / vec.z); }
Float3 Float3::operator	/	(const float &  f ) { return Float3(this->x / f, this->y / f, this->z / f); }
Float3 Float3::operator	/=	(const Float3& vec) { return *this = *this / vec; }
Float3 Float3::operator	/=	(const float &  f ) { return *this = *this /  f ; }
