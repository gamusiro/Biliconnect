/*=========================================================================
	Date : 2021/04/04(ŒŽ)	MCState_Damage.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef MCSTATE_C_H_
#define MCSTATE_C_H_

#include "MCState.h"

class MCState_Damage : public MCState
{
public:
	MCState_Damage(MoveChan& movechan, math::Float4& alfa);

	void Update() override;
	void ChangeState() override;

	void Set() override;

private:
	constexpr static int INVINCIBLE_TIME = 90;
	constexpr static int FLASH_RATE = 5;
	int m_Frame;

	constexpr static float ALFA_MAX = 1;
	constexpr static float ALFA_MIN = 0.1f;
	math::Float4& m_Color;
};

#endif
