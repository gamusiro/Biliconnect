/*===========================================================================
	Date : 2022/03/05(土)	MathCollision.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef MATHCOLLISION_H_
#define MATHCOLLISION_H_

#include "Float2.h"

namespace math
{
	class MathCollision
	{
	public:
		/*
		* @ brief
		*		バウンディングボックスの当たり判定
		* @ param
		*		pos1	: 中心ポジション座標(1)
		*		pos2	: 中心ポジション座標(2)
		*		size1	: ボックスサイズ(1)
		*		size2	: ボックスサイズ(2)
		*		point	: 当たった場所を取得する
		* @ return 
		*		true	: 衝突している
		*		false	: 衝突していない
		*/
		static bool Box(
			const Float2& pos1, const Float2& pos2,
			const Float2& size1, const Float2& size2
		);

		/*
		* @ brief
		*		バウンディングサークルの当たり判定
		* @ param
		*		pos1	: 中心ポジション座標(1)
		*		pos2	: 中心ポジション座標(2)
		*		radius1	: 半径(1)
		*		radius2	: 半径(2)
		* @ return
		*		true	: 衝突している
		*		false	: 衝突していない
		*/
		static bool Circle(
			const Float2& pos1, const Float2& pos2,
			float radius1, float radius2
		);
	};
}

#endif // !MATHCOLLISION_H_
