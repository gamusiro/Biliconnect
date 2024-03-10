/*=========================================================================
	Date : 2021/04/05(火)	MCState_Jump.h
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

	constexpr static float JUMP_X = 6.f;	// ジャンプ移動距離
	constexpr static float JUMP_Y = -15.f;	// ジャンプ移動距離
	constexpr static float GRAVITY = .4f;	// 重力
	constexpr static int   TRIGGER_TIMER = 30;	// ラインの再判定
};

#endif
