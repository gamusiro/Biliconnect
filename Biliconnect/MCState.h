/*=========================================================================
	Date : 2021/04/04(ŒŽ)	MCState.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef MCSTATE_H_
#define MCSTATE_H_

#include "GameCreateSystem.h"
class MoveChan;

class MCState
{
public:
	MCState(MoveChan& movechan) : m_MoveChan(movechan) {}

	virtual void Update(){}
	virtual void Damage(){}
	virtual void Set() {}

	virtual void ChangeState() = 0;

protected:
	MoveChan& m_MoveChan;
};

#endif
