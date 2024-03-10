/*=========================================================================
	Date : 2021/04/05(��)	MCState_OnLine.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "MCState_OnLine.h"
#include "Button.h"
#include "Line.h"
#include "MoveChan.h"
#include "Stage.h"
#include "SEManager.h"

using namespace math;

MCState_OnLine::MCState_OnLine(MoveChan& movechan, Line& line)
	: MCState(movechan), m_Left(false), m_Right(false),
	m_TargetPosA(line.GetPointPosA()), m_TargetPosB(line.GetPointPosB()), trigger(true)
{
	m_DistanceAB = m_TargetPosA - m_TargetPosB;							// 2�_��XY
	right = false;
	left = false;
}

void MCState_OnLine::Update()
{
	m_DistanceAB = m_TargetPosA - m_TargetPosB;							// 2�_��XY
	float vector = MathFloat::Length(m_DistanceAB);						// 2�_�ԋ���
	float ratio = (BASE_SPEED + m_AddSpeed + m_Addvel) / vector;		// ��������


	if ((Controller::GetButtonTriggerB() || Controller::GetButtonTriggerX()
		|| Controller::GetButtonTriggerA() || Controller::GetButtonTriggerY()
		|| Controller::GetButtonTriggerDown() || Controller::GetButtonTriggerUp()
		|| Controller::GetButtonTriggerRight() || Controller::GetButtonTriggerLeft()
		|| Controller::GetButtonTriggerLShoulder()
		|| Controller::GetButtonTriggerLThumb() || Controller::GetButtonTriggerRThumb()) && !StageStart::Get())
		m_MoveChan.SetAnimation(ANIMATION::SMILE);

	// �A�j���[�V��������
	if (Dash::Get()	&& m_MoveChan.GetAnimation() != ANIMATION::DAMAGE)
		m_MoveChan.SetAnimation(ANIMATION::POWER);
	else if (!Dash::Get() && m_MoveChan.GetAnimation() != ANIMATION::DAMAGE && m_MoveChan.GetAnimation() != ANIMATION::SMILE)
		m_MoveChan.SetAnimation(ANIMATION::NORMAL);

	if (Dash::Get())
	{
		m_Addvel += DASH_SPEED * 12;
		Controller::SetVibration(65535);
	}

	if (right)	m_Place += m_Addvel * ratio;
	else if (left)	m_Place -= m_Addvel * ratio;


	int num = StageNum::Get() % 5;

	if (StageEnd::Get() && num == 4)
		trigger = true;
	else if (StageEnd::Get())
		trigger = false;

	if (!m_MoveChan.GetDeath() && !StageStart::Get() && trigger)
	{
		// ���������΍�
		if (Dash::Get() && (Controller::GetLTTrigger() || Controller::GetRTTrigger() || Controller::GetButtonTriggerRShoulder()))
		{
		
		}
		// ������
		else if (Controller::GetLTTrigger()
			&& !Dash::Get() && m_Place != 0)
		{
			SEManager::Play(SOUND::DASH);
			SEManager::Play(SOUND::ELEC);
			Dash::Set(true);
			right = false;
			left = true;
		}
		// ������ ���]
		else if (Controller::GetButtonTriggerRShoulder()
			&& !Dash::Get() && m_Place == 0)
		{
			SEManager::Play(SOUND::DASH);
			SEManager::Play(SOUND::ELEC);
			Dash::Set(true);
			right = true;
			left = false;
		}
		// �E����
		else if (Controller::GetRTTrigger()
			&& !Dash::Get() && m_Place != 1)
		{
			SEManager::Play(SOUND::DASH);
			SEManager::Play(SOUND::ELEC);
			Dash::Set(true);
			right = true;
			left = false;
		}
		// �E���� ���]
		else if (Controller::GetButtonTriggerRShoulder()
			&& !Dash::Get() && m_Place == 1)
		{
			SEManager::Play(SOUND::DASH);
			SEManager::Play(SOUND::ELEC);
			Dash::Set(true);
			right = false;
			left = true;
		}
		// ���� ���]���S
		else if (Controller::GetButtonTriggerRShoulder()
			&& !Dash::Get() && m_Place != 1 && m_Place != 0)
		{
			SEManager::Play(SOUND::DASH);
			SEManager::Play(SOUND::ELEC);
			Dash::Set(true);
			right = true;
			left = false;
		}
		// ����
		else
		{
			m_Addvel *= 0.92f;
			Controller::StopVibration();
		}
	}

	if (Controller::GetButtonTriggerDown())
		m_MoveChan.AddEnergy();

	//m_Place += DIRECTION * ratio;						// �����l���ړ�

	if (m_Place > 1)									// �������]
	{
		m_Place = 1;
		if (!Controller::GetButtonPressRShoulder())
			m_Addvel = 0;

		Dash::Set(false);
	}
	if (m_Place < 0)
	{
		m_Place = 0;
		if (!Controller::GetButtonPressLShoulder())
			m_Addvel = 0;

		Dash::Set(false);
	}

	if ((m_Place == 1 || m_Place == 0) && !Dash::Get())									// �������]
	{
		SEManager::Stop(SOUND::ELEC);
		right = false;
		left = false;
	}

	m_MoveChan.SetPos((math::MathFloat::Lerp(m_TargetPosA, m_TargetPosB, m_Place)));
}

void MCState_OnLine::ChangeState()
{
	m_MoveChan.ChangeState(MoveChan::MOVESTATE::JUMP);
}

void MCState_OnLine::Set()
{
	m_DistanceAB = m_TargetPosA - m_TargetPosB;				// 2�_��XY
	Float2 distance = m_TargetPosA - m_MoveChan.GetPos();	// A��MC

	float sizeAB = MathFloat::Length(m_DistanceAB);			//�e�����Z�o
	float sizeAC = MathFloat::Length(distance);				//

	m_Place = sizeAC / sizeAB;								// �����Ŕz�u

	if (m_DistanceAB.x < 0)
	{
		if (m_Left) DIRECTION = 1;
		else		DIRECTION = -1;
	}
	else if (m_DistanceAB.x > 0)
	{
		if (m_Left) DIRECTION = -1;
		else		DIRECTION = 1;
	}
	else DIRECTION = 1;
}
