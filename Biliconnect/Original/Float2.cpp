/*===============================================================
	Date : 2021/12/07(��)	Float2.cpp
		Author	: ���ނ��邧
		Comment	: �o��n�ŏ��߂Ēʕ񂳂ꂽ��
===============================================================*/
#include "Float2.h"
using namespace math;

//�R���X�g���N�^
Float2::Float2() :x(0), y(0) {}
Float2::Float2(float x, float y) : x(x), y(y) {}
Float2::Float2(const Float2& vec) : x(vec.x), y(vec.y) {}

//�f�X�g���N�^
Float2::~Float2() {}

//���Z�q�̃I�[�o�[���[�h(�����Z)
Float2 Float2::operator +	(const Float2& vec) { return Float2(x + vec.x, y + vec.y); }
Float2 Float2::operator +	(const float &  f ) { return Float2(x + f, y + f); }
Float2 Float2::operator +=	(const Float2& vec) { return *this = *this + vec; }
Float2 Float2::operator +=	(const float &  f ) { return *this = *this + f; }

//���Z�q�̃I�[�o�[���[�h(�����Z)
Float2 Float2::operator -	(const Float2& vec) { return Float2(x - vec.x, y - vec.y); }
Float2 Float2::operator -	(const float& f)	{ return Float2(x - f, y - f); }
Float2 Float2::operator -=	(const Float2& vec) { return *this = *this - vec; }
Float2 Float2::operator -=	(const float& f)	{ return *this = *this - f; }

//���Z�q�̃I�[�o�[���[�h(�|���Z)
Float2 Float2::operator *	(const Float2& vec) { return Float2(x * vec.x, y * vec.y); }
Float2 Float2::operator *	(const float& f)	{ return Float2(x * f, y * f); }
Float2 Float2::operator *=	(const Float2& vec) { return *this = *this * vec; }
Float2 Float2::operator *=	(const float& f)	{ return *this = *this * f; }

//���Z�q�̃I�[�o�[���[�h(����Z)
Float2 Float2::operator /	(const Float2& vec) { return Float2(x / vec.x, y / vec.y); }
Float2 Float2::operator /	(const float& f)	{ return Float2(x / f, y / f); }
Float2 Float2::operator /=	(const Float2& vec) { return *this = *this / vec; }
Float2 Float2::operator /=	(const float& f)	{ return *this = *this / f; }
