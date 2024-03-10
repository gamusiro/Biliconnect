/*===========================================================================
	Date : 2022/03/05(土)	MathCollision.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "MathCollision.h"

/*=============================================================================================
	バウンディングボックス
=============================================================================================*/
bool math::MathCollision::Box(const Float2& pos1, const Float2& pos2, const Float2& size1, const Float2& size2)
{
	Float2 halfSize[2] = { size1, size2 };

	for (int i = 0; i < 2; i++)
	{//サイズを半分にする
		halfSize[i] *= 0.5f;
	}

	if (pos1.x + size1.x > pos2.x - size2.x &&
		pos1.x - size1.x < pos2.x + size2.x &&
		pos1.y + size1.y > pos2.y - size2.y &&
		pos1.y - size1.y < pos2.y + size2.y)
	{
		return true;
	}

    return false;
}

/*=============================================================================================
	バウンディングサークル
=============================================================================================*/
bool math::MathCollision::Circle(const Float2& pos1, const Float2& pos2, float radius1, float radius2)
{
	float subX		= pos2.x - pos1.x;
	float subY		= pos2.y - pos1.y;
	float distance	= (subX * subX + subY * subY);
	float addRadius	= (radius1 + radius2) * (radius1 + radius2);

	if (distance < addRadius)
	{//衝突している
		return true;
	}

	return false;
}
