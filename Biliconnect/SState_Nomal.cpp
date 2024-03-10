#include "SState_Nomal.h"
#include "SState_Shake.h"
#include "HitStop.h"

void SState_Nomal::Update()
{
	if (HitStop::Get() > 0)
		ChangeState();
}

void SState_Nomal::ChangeState()
{
	m_Stage.ChangeState(new SState_Shake(m_Stage));
}
