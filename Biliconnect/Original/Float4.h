/*===============================================================
	Date : 2021/12/07(��)	Float4.h
		Author	: ���ނ��邧
		Comment	: �o��n�ŏ��߂Ēʕ񂳂ꂽ��
===============================================================*/
#ifndef FLOAT4_H_
#define FLOAT4_H_

namespace math
{
	class Float4
	{
	public:
		//�R���X�g���N�^
		Float4();
		Float4(float x, float y, float z, float w);
		Float4(const Float4& vec);

		//�f�X�g���N�^
		~Float4();

	public:
		//���Z�q�̃I�[�o�[���[�h(�����Z)
		Float4 operator +	(const Float4& vec);
		Float4 operator +	(const float& f);
		Float4 operator +=	(const Float4& vec);
		Float4 operator +=	(const float& f);

		//���Z�q�̃I�[�o�[���[�h(�����Z)
		Float4 operator -	(const Float4& vec);
		Float4 operator -	(const float& f);
		Float4 operator -=	(const Float4& vec);
		Float4 operator -=	(const float& f);

		//���Z�q�̃I�[�o�[���[�h(�|���Z)
		Float4 operator *	(const Float4& vec);
		Float4 operator *	(const float& f);
		Float4 operator *=	(const Float4& vec);
		Float4 operator *=	(const float& f);

		//���Z�q�̃I�[�o�[���[�h(����Z)
		Float4 operator /	(const Float4& vec);
		Float4 operator /	(const float& f);
		Float4 operator /=	(const Float4& vec);
		Float4 operator /=	(const float& f);

	public:
		float x;
		float y;
		float z;
		float w;
	};
}

#endif // !FLOAT4_H_