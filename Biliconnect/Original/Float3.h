/*===============================================================
	Date : 2021/12/07(火)	Float3.h
		Author	: がむしるぉ
		Comment	: 出会い系で初めて通報された日
===============================================================*/
#ifndef FLOAT3_H_
#define FLOAT3_H_

namespace math
{
	class Float3
	{
	public:
		//コンストラクタ
		Float3();
		Float3(float x, float y, float z);
		Float3(const Float3& vec);

		//デストラクタ
		~Float3();

	public:
		//演算子のオーバーロード(足し算)
		Float3 operator +	(const Float3& vec);
		Float3 operator +	(const float& f);
		Float3 operator +=	(const Float3& vec);
		Float3 operator +=	(const float& f);

		//演算子のオーバーロード(引き算)
		Float3 operator -	(const Float3& vec);
		Float3 operator -	(const float& f);
		Float3 operator -=	(const Float3& vec);
		Float3 operator -=	(const float& f);

		//演算子のオーバーロード(掛け算)
		Float3 operator *	(const Float3& vec);
		Float3 operator *	(const float& f);
		Float3 operator *=	(const Float3& vec);
		Float3 operator *=	(const float& f);

		//演算子のオーバーロード(割り算)
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

