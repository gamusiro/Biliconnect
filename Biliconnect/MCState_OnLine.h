/*=========================================================================
	Date : 2021/04/05(��)	MCState_OnLine.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef MCSTATE_O_H_
#define MCSTATE_O_H_

#include "MCState.h"
class MoveChan;
class Line;

class MCState_OnLine : public MCState
{
public:
	MCState_OnLine(MoveChan& movechan, Line& line);

	void Update() override;
	void ChangeState() override;
	void Set() override;

	static bool GetL() { return left; }
	static bool GetR() { return right; }

private:
	math::Float2&	m_TargetPosA;			// ���`�⊮�n�_
	math::Float2&	m_TargetPosB;			// ���`�⊮�I�_
	math::Float2	m_DistanceAB;			// 2�_��X/Y����

	float			m_Place = 0;			// �}��ϐ�
	int				DIRECTION = 1;			// �ړ�����
	float			m_AddSpeed = 0;			// �_�b�V��

	static bool right;
	static bool left;

	float m_Addvel = 0;

	bool m_Left;
	bool m_Right;

	bool trigger;// �����邩�ǂ����̃t���O

private:
	constexpr static float BASE_SPEED = 10.f;	// ����x
	constexpr static float DASH_SPEED = .075f;	// �_�b�V�����x
	constexpr static float BACK_SPEED = .5f;	// �߂鑬�x
	constexpr static float VIB_POW = 14000.0f;	// �U���̋���
};
__declspec(selectany) bool MCState_OnLine::right(false);
__declspec(selectany) bool MCState_OnLine::left(false);
#endif
