#include "MCState_Nomal.h"
#include "MoveChan.h"

MCState_Nomal::MCState_Nomal(MoveChan& movechan)
	: MCState(movechan)
{
}

void MCState_Nomal::Damage()
{
	m_MoveChan.Damage();
	ChangeState();
}

void MCState_Nomal::ChangeState()
{
	m_MoveChan.SetAnimation(ANIMATION::DAMAGE);
	m_MoveChan.ChangeState(MoveChan::DAMAGESTATE::DAMAGE);
}
