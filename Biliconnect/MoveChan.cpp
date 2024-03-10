/*=========================================================================
	Date : 2021/03/05(“y)	MoveChan.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "MoveChan.h"
#include "Line.h"
#include "Stage.h"
#include "Button.h"
#include "HitStop.h"

#include "MCState.h"
#include "MCState_Nomal.h"
#include "MCState_Damage.h"
#include "MCState_OnLine.h"
#include "MCState_Jump.h"
#include "SEManager.h"

using namespace math;

MoveChan::MoveChan(math::Float2 pos, Line& line)
	: m_Pos(pos), m_Color(1, 1, 1, 1), m_Life{ Float2(LIFE_POS_X ,LIFE_POS_Y) },
	m_Energy{ Float2(ENERGY_POS_X ,ENERGY_POS_Y) },
	m_MoveState(MOVESTATE::JUMP), m_DamageState(DAMAGESTATE::NOMAL),
	m_Effects(this->GetPos())
{
	MoveChan::Reset();
	m_Frame = 0;
	m_Tex.Create("piri.png", 5, 1);
	m_Damage.Create("hit_piri03.png", 5, 2);

	m_MoveStates[static_cast<int>(MOVESTATE::ONLINE)] = std::make_unique<MCState_OnLine>(*this, line);
	m_MoveStates[static_cast<int>(MOVESTATE::JUMP)] = std::make_unique<MCState_Jump>(*this, line);

	m_DamageStates[static_cast<int>(DAMAGESTATE::NOMAL)] = std::make_unique<MCState_Nomal>(*this);
	m_DamageStates[static_cast<int>(DAMAGESTATE::DAMAGE)] = std::make_unique<MCState_Damage>(*this, m_Color);

	m_MoveStates[static_cast<int>(m_MoveState)]->Update();
}

MoveChan::~MoveChan()
{
}

void MoveChan::Update()
{
	m_Life.Update();
	//m_Energy.Update();
	m_MoveStates[static_cast<int>(m_MoveState)]->Update();
	m_DamageStates[static_cast<int>(m_DamageState)]->Update();
	Animation();
	m_Effects.Update();

	if (m_Animation == ANIMATION::DAMAGE)
		m_Damage.Update();

	m_Frame++;

}

void MoveChan::Draw()
{
	
	

	m_Life.Draw();
	m_Effects.Draw();

	if (m_Animation == ANIMATION::DAMAGE)
		Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, Float2(110 + 15 + sinf(m_Frame * 0.2f) * 5.0f, 110 + 15 + cosf(m_Frame * 0.2f) * 5.0f), &m_Damage, m_Color);
	else
		Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, Float2(m_Size.x + 15 + sinf(m_Frame * 0.2f) * 5.0f, m_Size.y + 15 + cosf(m_Frame * 0.2f) * 5.0f), &m_Tex, m_Color);

	//m_Energy.Draw();
}

void MoveChan::SetAnimation(ANIMATION num)
{
	m_Animation = num;
	m_Tex.SetStartUVPosition(Float2(0.2f * (int)m_Animation, 0.0f));
}

void MoveChan::MinusLife()
{
	m_DamageStates[static_cast<int>(m_DamageState)]->Damage();
}

void MoveChan::AddLife()
{
	m_Life.Heal();
}

void MoveChan::MinusEnergy()
{
	if (m_Energy.Minus())
	{

	}
}

void MoveChan::AddEnergy()
{
	m_Energy.Plus();
}

void MoveChan::Damage()
{
	SEManager::Play(SOUND::DAMAGE);
	HitStop::Set(4);
	if (m_Life.Damage())
	{
		// Ž€–S
		SEManager::Play(SOUND::PACHI);
		SEManager::Stop(SOUND::ELEC);
		isDeath = true;
		StageEnd::Set();
		ChangeState(MOVESTATE::JUMP);
		Controller::StopVibration();
	}
}

void MoveChan::ChangeState(MOVESTATE state)
{
	m_MoveState = state;
	m_MoveStates[static_cast<int>(m_MoveState)]->Set();
}

void MoveChan::ChangeState(DAMAGESTATE state)
{
	m_DamageState = state;
	m_DamageStates[static_cast<int>(m_DamageState)]->Set();
}

void MoveChan::Animation()
{
	static int timer = 0;

	if (m_Animation == ANIMATION::NORMAL)
	{
		timer++;

		if (timer > 110)
		{
			m_Tex.SetStartUVPosition(Float2(0.2f, 0.0f));
		}
		if (timer > 120)
		{
			m_Tex.SetStartUVPosition(Float2(0.0f, 0.0f));
			timer = 0;
		}
	}
	else if (m_Animation == ANIMATION::SMILE)
	{
		timer++;

		if (timer > 0)
		{
			m_Tex.SetStartUVPosition(Float2(0.8f, 0.0f));
		}
		if (timer > 90)
		{
			m_Animation = ANIMATION::NORMAL;
			m_Tex.SetStartUVPosition(Float2(0.0f, 0.0f));
			timer = 0;
		}
	}
	else
		timer = 0;
}
