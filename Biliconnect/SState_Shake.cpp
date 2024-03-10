#include "SState_Shake.h"
#include "SState_Nomal.h"
#include "HitStop.h"

void SState_Shake::Update()
{
	if (HitStop::Get() == 4)
	{
		m_Rad = 0;
		m_Vol = 0;
	}

	float a = std::cosf(m_Rad);
	Stage::SetShake({ a * m_Vol,a * m_Vol });
	m_Rad += 10.f;
	if (m_Vol > 1.f) m_Vol *= 0.9f;
	else ChangeState();
}

void SState_Shake::ChangeState()
{
	m_Stage.ChangeState(new SState_Nomal(m_Stage));
}
