/*===============================================================
	Date : 2021/12/07(火)	Float2.h
		Author	: がむしるぉ
		Comment	: 出会い系で初めて通報された日
===============================================================*/
#ifndef FLOAT2_H_
#define FLOAT2_H_

namespace math
{
	class Float2
	{
	public:
		//コンストラクタ
		Float2();
		Float2(float x, float y);
		Float2(const Float2& vec);

		//デストラクタ
		~Float2();

		//演算子(足し算)
		Float2 operator	+	(const Float2& vec);
		Float2 operator +	(const float& v);
		Float2 operator +=	(const Float2& vec);
		Float2 operator +=	(const float& v);

		//演算子(引き算)
		Float2 operator -	(const Float2& vec);
		Float2 operator -	(const float& v);
		Float2 operator -=	(const Float2& vec);
		Float2 operator -=	(const float& v);

		//演算子(掛け算)
		Float2 operator *	(const Float2& vec);
		Float2 operator *	(const float& v);
		Float2 operator *=	(const Float2& vec);
		Float2 operator *=	(const float& v);

		//演算子(割り算)
		Float2 operator /	(const Float2& vec);
		Float2 operator /	(const float& v);
		Float2 operator /=	(const Float2& vec);
		Float2 operator /=	(const float& v);

	public:
		//メンバ変数
		float x;
		float y;
	};
}


#endif // !FLOAT2_H_

