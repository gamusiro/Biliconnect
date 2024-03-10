/*===========================================================================
	Date : 2022/03/04(��)	MathCommons.h
		Author	: ���ނ��邧
		Update	:
		Comment	: 
===========================================================================*/
#ifndef MATHCOMMONS_H_
#define MATHCOMMONS_H_


namespace math
{
	/*
	* @ brief
	*		�~����
	*/
	constexpr static float MY_O_PI = 3.141592653589f;
	
	class MathCommons
	{
	public:
		/*
		* @ brief
		*		2�̒l���r����
		* @ param
		*		c1 : ��r�l(1)
		*		c2 : ��r�l(2)
		* @ return
		*		�傫���ق��̒l��Ԃ�
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
		*		2�̒l���r����
		* @ param
		*		c1 : ��r�l(1)
		*		c2 : ��r�l(2)
		* @ return
		*		�������ق��̒l��Ԃ�
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
		*		�p�x -> ���W�A��
		* @ param
		*		degree : �p�x
		* @ return
		*		���W�A���l
		*/
		static float Radian(float degree);

		/*
		* @ brief
		*		���W�A�� -> �p�x
		* @ param
		*		radian : ���W�A���l
		* @ return
		*		�p�x
		*/
		static float Degree(float radian);
	};
}

#endif // !MATHCOMMONS_H_
