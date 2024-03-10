/*=========================================================================
	Date : 2021/04/05(火)	MCState_Jump.cpp
		Author :
		Update :
=========================================================================*/
#include "MCState_Jump.h"
#include "MoveChan.h"
#include "Line.h"
#include "Stage.h"
#include "SEManager.h"

using namespace math;

MCState_Jump::MCState_Jump(MoveChan& movechan, Line& line)
	: MCState(movechan), m_Line(line), m_Vel(Float2(0, 0)), trigger(true), timer(0)
{
}

void MCState_Jump::Update()
{
	if (m_MoveChan.GetDeath())
		timer++;

	// 空中処理
	if (timer > TRIGGER_TIMER || !m_MoveChan.GetDeath())
	{
		m_Vel.y += GRAVITY;
		m_MoveChan.SetPos(m_MoveChan.GetPos() + m_Vel);
	}

	if (!trigger)
		m_MoveChan.SetAnimation(ANIMATION::DAMAGE);

	if (timer == 57)
		SEManager::Play(SOUND::FALL);

	// ラインとの衝突確認
	if (trigger)
	{
		Float2 pPos = m_MoveChan.GetPos();				//MovePos
		float pSize = m_MoveChan.GetSize() * 0.5f;		//MoveSize

		Float2 StartPoint = m_Line.GetPointPosA();	// 線始点
		Float2 EndPoint = m_Line.GetPointPosB();	// 線終点

		Float2 vecAB = EndPoint - StartPoint;
		Float2 vecAC = pPos - StartPoint;

		Float2 NvecAB = MathFloat::Normalize(vecAB);

		float cross = std::fabsf(MathFloat::Cross(NvecAB, vecAC));

		if (cross <= pSize)
		{
			Float2 vecBC = pPos - EndPoint;

			float dot1 = MathFloat::Dot(vecAB, vecAC);
			float dot2 = MathFloat::Dot(vecAB, vecBC);

			if (dot1 * dot2 > 0)
			{
				float distanceAC = MathFloat::LengthSq(vecAC);
				float distanceBC = MathFloat::LengthSq(vecBC);

				if (distanceAC > pSize * pSize && distanceBC > pSize * pSize)
				{
					return;
				}
			}
			//あててんのよ
			ChangeState();
		}
	}


	if (m_MoveChan.GetPos().y > Stage::m_MoveNow.y + SCREEN_HEIGHT + 200)
	{
		trigger = false;
		if (Fade::GetState())
			Fade::Transition(SCENE_TYPE::GAMEOVER, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
	}
}

void MCState_Jump::ChangeState()
{
	SEManager::Play(SOUND::START);
	m_MoveChan.SetAnimation(ANIMATION::SMILE);
	m_MoveChan.ChangeState(MoveChan::MOVESTATE::ONLINE);
}

void MCState_Jump::Set()
{
	m_Vel = Float2(0, JUMP_Y);
	timer = 0;
	trigger = false;
}
