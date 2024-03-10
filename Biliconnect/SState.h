/*=========================================================================
	Date : 2022/04/22(‹à)	SState.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef SSTATE_H_
#define SSTATE_H_

#include "GameCreateSystem.h"
#include "Stage.h"

class SState
{
public:
	SState(Stage& stage) : m_Stage(stage) {}

	virtual void Update() {};

protected:
	virtual void ChangeState() {};

protected:
	Stage& m_Stage;
};

#endif
