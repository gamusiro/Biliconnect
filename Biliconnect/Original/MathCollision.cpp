/*===========================================================================
	Date : 2022/03/05(�y)	MathCollision.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "MathCollision.h"

/*=============================================================================================
	�o�E���f�B���O�{�b�N�X
=============================================================================================*/
bool math::MathCollision::Box(const Float2& pos1, const Float2& pos2, const Float2& size1, const Float2& size2)
{
	Float2 halfSize[2] = { size1, size2 };

	for (int i = 0; i < 2; i++)
	{//�T�C�Y�𔼕��ɂ���
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
	�o�E���f�B���O�T�[�N��
=============================================================================================*/
bool math::MathCollision::Circle(const Float2& pos1, const Float2& pos2, float radius1, float radius2)
{
	float subX		= pos2.x - pos1.x;
	float subY		= pos2.y - pos1.y;
	float distance	= (subX * subX + subY * subY);
	float addRadius	= (radius1 + radius2) * (radius1 + radius2);

	if (distance < addRadius)
	{//�Փ˂��Ă���
		return true;
	}

	return false;
}
