/*===============================================================
	Date : 2021/12/07(��)	Float3.h
		Author	: ���ނ��邧
		Comment	: �o��n�ŏ��߂Ēʕ񂳂ꂽ��
===============================================================*/
#ifndef FLOAT3_H_
#define FLOAT3_H_

namespace math
{
	class Float3
	{
	public:
		//�R���X�g���N�^
		Float3();
		Float3(float x, float y, float z);
		Float3(const Float3& vec);

		//�f�X�g���N�^
		~Float3();

	public:
		//���Z�q�̃I�[�o�[���[�h(�����Z)
		Float3 operator +	(const Float3& vec);
		Float3 operator +	(const float& f);
		Float3 operator +=	(const Float3& vec);
		Float3 operator +=	(const float& f);

		//���Z�q�̃I�[�o�[���[�h(�����Z)
		Float3 operator -	(const Float3& vec);
		Float3 operator -	(const float& f);
		Float3 operator -=	(const Float3& vec);
		Float3 operator -=	(const float& f);

		//���Z�q�̃I�[�o�[���[�h(�|���Z)
		Float3 operator *	(const Float3& vec);
		Float3 operator *	(const float& f);
		Float3 operator *=	(const Float3& vec);
		Float3 operator *=	(const float& f);

		//���Z�q�̃I�[�o�[���[�h(����Z)
		Float3 operator /	(const Float3& vec);
		Float3 operator /	(const float& f);
		Float3 operator /=	(const Float3& vec);
		Float3 operator /=	(const float& f);

	public:
		float x;
		float y;
		float z;
	};
}

#endif // !FLOAT3_H_

