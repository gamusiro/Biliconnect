/*===========================================================================
	Date : 2022/03/05(�y)	MathCollision.h
		Author	: ���ނ��邧
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
		*		�o�E���f�B���O�{�b�N�X�̓����蔻��
		* @ param
		*		pos1	: ���S�|�W�V�������W(1)
		*		pos2	: ���S�|�W�V�������W(2)
		*		size1	: �{�b�N�X�T�C�Y(1)
		*		size2	: �{�b�N�X�T�C�Y(2)
		*		point	: ���������ꏊ���擾����
		* @ return 
		*		true	: �Փ˂��Ă���
		*		false	: �Փ˂��Ă��Ȃ�
		*/
		static bool Box(
			const Float2& pos1, const Float2& pos2,
			const Float2& size1, const Float2& size2
		);

		/*
		* @ brief
		*		�o�E���f�B���O�T�[�N���̓����蔻��
		* @ param
		*		pos1	: ���S�|�W�V�������W(1)
		*		pos2	: ���S�|�W�V�������W(2)
		*		radius1	: ���a(1)
		*		radius2	: ���a(2)
		* @ return
		*		true	: �Փ˂��Ă���
		*		false	: �Փ˂��Ă��Ȃ�
		*/
		static bool Circle(
			const Float2& pos1, const Float2& pos2,
			float radius1, float radius2
		);
	};
}

#endif // !MATHCOLLISION_H_
