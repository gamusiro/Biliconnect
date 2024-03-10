/*===============================================================
	Date : 2021/12/07(火)	Float4.h
		Author	: がむしるぉ
		Comment	: 出会い系で初めて通報された日
===============================================================*/
#ifndef FLOAT4_H_
#define FLOAT4_H_

namespace math
{
	class Float4
	{
	public:
		//コンストラクタ
		Float4();
		Float4(float x, float y, float z, float w);
		Float4(const Float4& vec);

		//デストラクタ
		~Float4();

	public:
		//演算子のオーバーロード(足し算)
		Float4 operator +	(const Float4& vec);
		Float4 operator +	(const float& f);
		Float4 operator +=	(const Float4& vec);
		Float4 operator +=	(const float& f);

		//演算子のオーバーロード(引き算)
		Float4 operator -	(const Float4& vec);
		Float4 operator -	(const float& f);
		Float4 operator -=	(const Float4& vec);
		Float4 operator -=	(const float& f);

		//演算子のオーバーロード(掛け算)
		Float4 operator *	(const Float4& vec);
		Float4 operator *	(const float& f);
		Float4 operator *=	(const Float4& vec);
		Float4 operator *=	(const float& f);

		//演算子のオーバーロード(割り算)
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