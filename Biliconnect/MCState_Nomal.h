/*=========================================================================
	Date : 2021/04/04(ŒŽ)	MCState_Nomal.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef MCSTATE_N_H_
#define MCSTATE_N_H_

#include "MCState.h"

class MCState_Nomal : public MCState
{
public:
	MCState_Nomal(MoveChan& movechan);

	void Damage() override;
	void ChangeState() override;
};

#endif
