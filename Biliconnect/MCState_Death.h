/*=========================================================================
	Date : 2021/05/07(“y)	MCState_Desth.h
		Author : Mrrrrrrrrrr!!!!!!
		Update :
=========================================================================*/
#ifndef MCSTATE_DH_H_
#define MCSTATE_DH_H_

#include "MCState.h"

class MCState_Death : public MCState
{
public:
	MCState_Death(MoveChan& movechan, math::Float4& alfa);

	void Update() override;
	void ChangeState() override;

	void Set() override;
};

#endif
