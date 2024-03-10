#include "MCState_Damage.h"
#include "MoveChan.h"

MCState_Damage::MCState_Damage(MoveChan& movechan, math::Float4& alfa)
	: MCState(movechan), m_Frame(0), m_Color(alfa)
{

}

void MCState_Damage::Update()
{
	if (!m_MoveChan.GetDeath())
	{
		++m_Frame;
		if (m_Frame == INVINCIBLE_TIME)
		{
			ChangeState();
			return;
		}
		if (m_Frame % FLASH_RATE == 0)
		{
			if (m_Color.w == ALFA_MAX) m_Color.w = ALFA_MIN;
			else					   m_Color.w = ALFA_MAX;
		}

		if (m_Frame > 60)
		{
			m_MoveChan.SetAnimation(ANIMATION::NORMAL);
		}
	}
}

void MCState_Damage::ChangeState()
{
	m_Color = { 1,1,1,1 };
	m_MoveChan.SetAnimation(ANIMATION::NORMAL);
	m_MoveChan.ChangeState(MoveChan::DAMAGESTATE::NOMAL);
}

void MCState_Damage::Set()
{
	m_Frame = 0;
	m_Color = { 1,1,1,1 };
}
