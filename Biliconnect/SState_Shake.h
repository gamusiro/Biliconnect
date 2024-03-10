/*=========================================================================
	Date : 2022/04/22(‹à)	SState_Shake.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef SSTATE_S_H_
#define SSTATE_S_H_

#include "SState.h"

class SState_Shake : public SState
{
public:
	SState_Shake(Stage& stage)
		: SState(stage), m_Rad(0), m_Vol(50.f) {}

	void Update()		override;

private:
	void ChangeState()	override;

private:
	float m_Rad;
	float m_Vol;
};

#endif
