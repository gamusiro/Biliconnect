/*===============================================================
	Date : 2021/12/25(�y)	Int2.h
		Author	: ���ނ��邧
		Comment	: �ӊO�ƕ֗��Ȃ���
===============================================================*/
#ifndef INT2_H_
#define INT2_H_

namespace math
{
	class Int2
	{
	public:
		//�R���X�g���N�^
		Int2();
		Int2(int x, int y);
		Int2(const Int2& vec);

		//�f�X�g���N�^
		~Int2();

		//���Z�q(�����Z)
		Int2 operator +		(const Int2& vec);
		Int2 operator +		(const int& v);
		Int2 operator +=	(const Int2& vec);
		Int2 operator +=	(const int& v);

		//���Z�q(�����Z)
		Int2 operator -		(const Int2& vec);
		Int2 operator -		(const int& v);
		Int2 operator -=	(const Int2& vec);
		Int2 operator -=	(const int& v);

		//���Z�q(�|���Z)
		Int2 operator *		(const Int2& vec);
		Int2 operator *		(const int& v);
		Int2 operator *=	(const Int2& vec);
		Int2 operator *=	(const int& v);

		//���Z�q(����Z)
		Int2 operator /		(const Int2& vec);
		Int2 operator /		(const int& v);
		Int2 operator /=	(const Int2& vec);
		Int2 operator /=	(const int& v);

	public:
		//�����o�ϐ�
		int x;
		int y;
	};
}

#endif //!INT2_H_
