/*=========================================================================
	Date : 2021/04/05(��)	MCState_Jump.h
		Author :
		Update :
=========================================================================*/
#ifndef MCSTATE_J_H_
#define MCSTATE_J_H_

#include "MCState.h"
class MoveChan;
class Line;

class MCState_Jump : public MCState
{
public:
	MCState_Jump(MoveChan& movechan, Line& line);

	void Update();
	void ChangeState() override;
	void Set() override;

private:
	Line& m_Line;

private:
	math::Float2 m_Vel;
	bool trigger;
	int timer;

	constexpr static float JUMP_X = 6.f;	// �W�����v�ړ�����
	constexpr static float JUMP_Y = -15.f;	// �W�����v�ړ�����
	constexpr static float GRAVITY = .4f;	// �d��
	constexpr static int   TRIGGER_TIMER = 30;	// ���C���̍Ĕ���
};

#endif
