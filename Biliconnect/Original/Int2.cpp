/*===============================================================
	Date : 2021/12/07(��)	Int2.cpp
		Author	: ���ނ��邧
		Comment	: �ӊO�ƃe�N�X�`���Ǘ��ŗL�\
===============================================================*/
#include "Int2.h"
using namespace math;

//�R���X�g���N�^
Int2::Int2() :x(0), y(0) {}
Int2::Int2(int x, int y) : x(x), y(y) {}
Int2::Int2(const Int2& vec) : x(vec.x), y(vec.y) {}

//�f�X�g���N�^
Int2::~Int2() {}

//���Z�q�̃I�[�o�[���[�h(�����Z)
Int2 Int2::operator +	(const Int2& vec)	{ return Int2(x + vec.x, y + vec.y); }
Int2 Int2::operator +	(const int&  f )	{ return Int2(x + f, y + f); }
Int2 Int2::operator +=	(const Int2& vec)	{ return *this = *this + vec; }
Int2 Int2::operator +=	(const int&  f )	{ return *this = *this + f; }

//���Z�q�̃I�[�o�[���[�h(�����Z)
Int2 Int2::operator -	(const Int2& vec)	{ return Int2(x - vec.x, y - vec.y); }
Int2 Int2::operator -	(const int& f)		{ return Int2(x - f, y - f); }
Int2 Int2::operator -=	(const Int2& vec)	{ return *this = *this - vec; }
Int2 Int2::operator -=	(const int& f)		{ return *this = *this - f; }

//���Z�q�̃I�[�o�[���[�h(�|���Z)
Int2 Int2::operator *	(const Int2& vec)	{ return Int2(x * vec.x, y * vec.y); }
Int2 Int2::operator *	(const int& f)		{ return Int2(x * f, y * f); }
Int2 Int2::operator *=	(const Int2& vec)	{ return *this = *this * vec; }
Int2 Int2::operator *=	(const int& f)		{ return *this = *this * f; }

//���Z�q�̃I�[�o�[���[�h(����Z)
Int2 Int2::operator /	(const Int2& vec)	{ return Int2(x / vec.x, y / vec.y); }
Int2 Int2::operator /	(const int& f)		{ return Int2(x / f, y / f); }
Int2 Int2::operator /=	(const Int2& vec)	{ return *this = *this / vec; }
Int2 Int2::operator /=	(const int& f)		{ return *this = *this / f; }