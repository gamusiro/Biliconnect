/*===============================================================
	Date : 2021/12/07(��)	Float2.h
		Author	: ���ނ��邧
		Comment	: �o��n�ŏ��߂Ēʕ񂳂ꂽ��
===============================================================*/
#ifndef FLOAT2_H_
#define FLOAT2_H_

namespace math
{
	class Float2
	{
	public:
		//�R���X�g���N�^
		Float2();
		Float2(float x, float y);
		Float2(const Float2& vec);

		//�f�X�g���N�^
		~Float2();

		//���Z�q(�����Z)
		Float2 operator	+	(const Float2& vec);
		Float2 operator +	(const float& v);
		Float2 operator +=	(const Float2& vec);
		Float2 operator +=	(const float& v);

		//���Z�q(�����Z)
		Float2 operator -	(const Float2& vec);
		Float2 operator -	(const float& v);
		Float2 operator -=	(const Float2& vec);
		Float2 operator -=	(const float& v);

		//���Z�q(�|���Z)
		Float2 operator *	(const Float2& vec);
		Float2 operator *	(const float& v);
		Float2 operator *=	(const Float2& vec);
		Float2 operator *=	(const float& v);

		//���Z�q(����Z)
		Float2 operator /	(const Float2& vec);
		Float2 operator /	(const float& v);
		Float2 operator /=	(const Float2& vec);
		Float2 operator /=	(const float& v);

	public:
		//�����o�ϐ�
		float x;
		float y;
	};
}


#endif // !FLOAT2_H_

