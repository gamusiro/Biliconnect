/*===========================================================================
	Date : 2022/03/04(金)	MathCommons.h
		Author	: がむしるぉ
		Update	:
		Comment	: 
===========================================================================*/
#ifndef MATHCOMMONS_H_
#define MATHCOMMONS_H_


namespace math
{
	/*
	* @ brief
	*		円周率
	*/
	constexpr static float MY_O_PI = 3.141592653589f;
	
	class MathCommons
	{
	public:
		/*
		* @ brief
		*		2つの値を比較する
		* @ param
		*		c1 : 比較値(1)
		*		c2 : 比較値(2)
		* @ return
		*		大きいほうの値を返す
		*/
		template<class T>
		inline static T Max(T c1, T c2)
		{
			if (c1 > c2)
				return c1;
			return c2;
		}

		/*
		* @ brief
		*		2つの値を比較する
		* @ param
		*		c1 : 比較値(1)
		*		c2 : 比較値(2)
		* @ return
		*		小さいほうの値を返す
		*/
		template<class T>
		inline static T Min(T c1, T c2)
		{
			if (c1 < c2)
				return c1;
			return c2;
		}

		/*
		* @ brief
		*		角度 -> ラジアン
		* @ param
		*		degree : 角度
		* @ return
		*		ラジアン値
		*/
		static float Radian(float degree);

		/*
		* @ brief
		*		ラジアン -> 角度
		* @ param
		*		radian : ラジアン値
		* @ return
		*		角度
		*/
		static float Degree(float radian);
	};
}

#endif // !MATHCOMMONS_H_
