/*===============================================================
	Date : 2021/12/07(火)	Int2.cpp
		Author	: がむしるぉ
		Comment	: 意外とテクスチャ管理で有能
===============================================================*/
#include "Int2.h"
using namespace math;

//コンストラクタ
Int2::Int2() :x(0), y(0) {}
Int2::Int2(int x, int y) : x(x), y(y) {}
Int2::Int2(const Int2& vec) : x(vec.x), y(vec.y) {}

//デストラクタ
Int2::~Int2() {}

//演算子のオーバーロード(足し算)
Int2 Int2::operator +	(const Int2& vec)	{ return Int2(x + vec.x, y + vec.y); }
Int2 Int2::operator +	(const int&  f )	{ return Int2(x + f, y + f); }
Int2 Int2::operator +=	(const Int2& vec)	{ return *this = *this + vec; }
Int2 Int2::operator +=	(const int&  f )	{ return *this = *this + f; }

//演算子のオーバーロード(引き算)
Int2 Int2::operator -	(const Int2& vec)	{ return Int2(x - vec.x, y - vec.y); }
Int2 Int2::operator -	(const int& f)		{ return Int2(x - f, y - f); }
Int2 Int2::operator -=	(const Int2& vec)	{ return *this = *this - vec; }
Int2 Int2::operator -=	(const int& f)		{ return *this = *this - f; }

//演算子のオーバーロード(掛け算)
Int2 Int2::operator *	(const Int2& vec)	{ return Int2(x * vec.x, y * vec.y); }
Int2 Int2::operator *	(const int& f)		{ return Int2(x * f, y * f); }
Int2 Int2::operator *=	(const Int2& vec)	{ return *this = *this * vec; }
Int2 Int2::operator *=	(const int& f)		{ return *this = *this * f; }

//演算子のオーバーロード(割り算)
Int2 Int2::operator /	(const Int2& vec)	{ return Int2(x / vec.x, y / vec.y); }
Int2 Int2::operator /	(const int& f)		{ return Int2(x / f, y / f); }
Int2 Int2::operator /=	(const Int2& vec)	{ return *this = *this / vec; }
Int2 Int2::operator /=	(const int& f)		{ return *this = *this / f; }