/*===============================================================
	Date : 2021/12/25(土)	Int2.h
		Author	: がむしるぉ
		Comment	: 意外と便利なんよね
===============================================================*/
#ifndef INT2_H_
#define INT2_H_

namespace math
{
	class Int2
	{
	public:
		//コンストラクタ
		Int2();
		Int2(int x, int y);
		Int2(const Int2& vec);

		//デストラクタ
		~Int2();

		//演算子(足し算)
		Int2 operator +		(const Int2& vec);
		Int2 operator +		(const int& v);
		Int2 operator +=	(const Int2& vec);
		Int2 operator +=	(const int& v);

		//演算子(引き算)
		Int2 operator -		(const Int2& vec);
		Int2 operator -		(const int& v);
		Int2 operator -=	(const Int2& vec);
		Int2 operator -=	(const int& v);

		//演算子(掛け算)
		Int2 operator *		(const Int2& vec);
		Int2 operator *		(const int& v);
		Int2 operator *=	(const Int2& vec);
		Int2 operator *=	(const int& v);

		//演算子(割り算)
		Int2 operator /		(const Int2& vec);
		Int2 operator /		(const int& v);
		Int2 operator /=	(const Int2& vec);
		Int2 operator /=	(const int& v);

	public:
		//メンバ変数
		int x;
		int y;
	};
}

#endif //!INT2_H_
