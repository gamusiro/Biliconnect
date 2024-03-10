/*===============================================================
	Date : 2021/12/07(��)	Float4.cpp
		Author	: ���ނ��邧
		Comment	: �o��n�ŏ��߂Ēʕ񂳂ꂽ��
===============================================================*/
#include "Float4.h"
using namespace math;

//�R���X�g���N�^
Float4::Float4() : x(0), y(0), z(0), w(0) {}
Float4::Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Float4::Float4(const Float4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}

//�f�X�g���N�^
Float4::~Float4() {}

//���Z�q�̃I�[�o�[���[�h(�����Z)
Float4 Float4::operator +	(const Float4& vec) { return Float4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w); }
Float4 Float4::operator +	(const float& f)	{ return Float4(this->x + f, this->y + f, this->z + f, this->w + f); }
Float4 Float4::operator +=	(const Float4& vec) { return *this = *this + vec; }
Float4 Float4::operator +=	(const float& f)	{ return *this = *this + f; }

//���Z�q�̃I�[�o�[���[�h(�����Z)
Float4 Float4::operator -	(const Float4& vec) { return Float4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w); }
Float4 Float4::operator -	(const float& f)	{ return Float4(this->x - f, this->y - f, this->z - f, this->w - f); }
Float4 Float4::operator -=	(const Float4& vec) { return *this = *this - vec; }
Float4 Float4::operator -=	(const float& f)	{ return *this = *this - f; }

//���Z�q�̃I�[�o�[���[�h(�|���Z)
Float4 Float4::operator *	(const Float4& vec) { return Float4(this->x * vec.x, this->y * vec.y, this->z * vec.z, this->w * vec.w); }
Float4 Float4::operator *	(const float& f)	{ return Float4(this->x * f, this->y * f, this->z * f, this->w * f); }
Float4 Float4::operator *=	(const Float4& vec) { return *this = *this * vec; }
Float4 Float4::operator *=	(const float& f)	{ return *this = *this * f; }

//���Z�q�̃I�[�o�[���[�h(����Z)
Float4 Float4::operator /	(const Float4& vec) { return Float4(this->x / vec.x, this->y / vec.y, this->z / vec.z, this->w / vec.w); }
Float4 Float4::operator /	(const float& f)	{ return Float4(this->x / f, this->y / f, this->z / f, this->w / f); }
Float4 Float4::operator /=	(const Float4& vec) { return *this = *this / vec; }
Float4 Float4::operator /=	(const float& f)	{ return *this = *this / f; }
