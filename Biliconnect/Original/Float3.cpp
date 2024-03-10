/*===============================================================
	Date : 2021/12/07(��)	Float3.cpp
		Author	: ���ނ��邧
		Comment	: �o��n�ŏ��߂Ēʕ񂳂ꂽ��
===============================================================*/
#include "Float3.h"
using namespace math;

//�R���X�g���N�^
Float3::Float3() : x(0.0f), y(0.0f), z(0.0f) {}
Float3::Float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
Float3::Float3(const Float3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

//�f�X�g���N�^
Float3::~Float3() {}

//���Z�q�̃I�[�o�[���[�h(�����Z)
Float3 Float3::operator	+	(const Float3& vec) { return Float3(this->x + vec.x, this->y + vec.y, this->z + vec.z); }
Float3 Float3::operator	+	(const float &  f ) { return Float3(this->x + f, this->y + f, this->z + f); }
Float3 Float3::operator	+=	(const Float3& vec) { return *this = *this + vec; }
Float3 Float3::operator	+=	(const float &  f ) { return *this = *this +  f ; }

//���Z�q�̃I�[�o�[���[�h(�����Z)
Float3 Float3::operator	-	(const Float3& vec) { return Float3(this->x - vec.x, this->y - vec.y, this->z - vec.z); }
Float3 Float3::operator	-	(const float &  f ) { return Float3(this->x - f, this->y - f, this->z - f); }
Float3 Float3::operator	-=	(const Float3& vec) { return *this = *this - vec; }
Float3 Float3::operator	-=	(const float &  f ) { return *this = *this -  f ; }

//���Z�q�̃I�[�o�[���[�h(�|���Z)
Float3 Float3::operator	*	(const Float3& vec) { return Float3(this->x * vec.x, this->y * vec.y, this->z * vec.z); }
Float3 Float3::operator	*	(const float &  f ) { return Float3(this->x * f, this->y * f, this->z * f); }
Float3 Float3::operator	*=	(const Float3& vec) { return *this = *this * vec; }
Float3 Float3::operator	*=	(const float &  f ) { return *this = *this *  f ; }

//���Z�q�̃I�[�o�[���[�h(����Z)
Float3 Float3::operator	/	(const Float3& vec) { return Float3(this->x / vec.x, this->y / vec.y, this->z / vec.z); }
Float3 Float3::operator	/	(const float &  f ) { return Float3(this->x / f, this->y / f, this->z / f); }
Float3 Float3::operator	/=	(const Float3& vec) { return *this = *this / vec; }
Float3 Float3::operator	/=	(const float &  f ) { return *this = *this /  f ; }
