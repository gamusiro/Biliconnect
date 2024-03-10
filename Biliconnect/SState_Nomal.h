/*=========================================================================
	Date : 2022/04/22(‹à)	SState_Nomal.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef SSTATE_N_H_
#define SSTATE_N_H_

#include "SState.h"

class SState_Nomal : public SState
{
public:
	SState_Nomal(Stage& stage) : SState(stage) {}

	void Update()		override;

private:
	void ChangeState()	override;
};

#endif
