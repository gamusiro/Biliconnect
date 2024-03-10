/*=========================================================================
	Date : 2021/03/05(“y)	PlayerLeft.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "PlayerLeft.h"
#include "Stage.h"
#include "MoveChan.h"
#include "MCState_OnLine.h"

using namespace math;

PlayerLeft::PlayerLeft()
{
	m_Tex.Create("R_01.png", 6, 1, 1.5f);

	m_Tex2.Create("RE.png", 6, 1, 1);

	m_Pos.x = 420;
	m_Pos.y = 500;

	m_Frame = 0;
	m_Col = { 1.0f,1.0f, 1.0f, 1.0f };
	trigger = false;
}

void PlayerLeft::Update()
{
	if ((Controller::GetLTTrigger() && !Dash::Get()) || MCState_OnLine::GetL())
		trigger = true;
	else if (!Dash::Get())
		trigger = false;

	int num = StageNum::Get() % 5;

	if (StageEnd::Get() && Stage::m_MoveNow.y < Stage::m_MoveMax - SCREEN_HEIGHT)
		AddPosY(0);
	else if (StageEnd::Get() && num == 4)
		AddPosY(0);
	else if (!StageStart::Get() && StageNum::Get() == 23)
		AddPosY(6);
	else if (!StageStart::Get())
		AddPosY(4);

	Float2 L = Controller::GetLeftStick();

	int lx = static_cast<int>(L.x * 100);
	int ly = static_cast<int>(L.y * 100);

	L = { lx * 0.011f,ly * 0.011f };

	if (Input::KeyboardPress(DIK_UP)) m_Pos -= BASE_SPEED;
	if (Input::KeyboardPress(DIK_DOWN)) m_Pos += BASE_SPEED;


	if (!MoveChan::GetDeath())
	{
		if (StageEnd::Get() && num == 4)
			m_Pos += L * BASE_SPEED;
		else if (!StageStart::Get() && !StageEnd::Get())
			m_Pos += L * BASE_SPEED;
	}

	if ((!StageEnd::Get() && Stage::m_MoveNow.y < Stage::m_MoveMax - SCREEN_HEIGHT) || num == 4)
	{
		if (m_Pos.x < 0 + m_Size.x * 0.5f)                    m_Pos.x = m_Size.x * 0.5f;
		if (m_Pos.x > (SCREEN_WIDTH - m_Size.x) * 0.5f - 50)        m_Pos.x = (SCREEN_WIDTH - m_Size.x) * 0.5f - 50;
		if (m_Pos.y < Stage::m_MoveNow.y + m_Size.y * 0.5f)                    m_Pos.y = Stage::m_MoveNow.y + m_Size.y * 0.5f;
		if (m_Pos.y > Stage::m_MoveNow.y + SCREEN_HEIGHT - m_Size.y * 0.5f)    m_Pos.y = Stage::m_MoveNow.y + SCREEN_HEIGHT - m_Size.y * 0.5f;
	}

	if (trigger && !StageStart::Get() && m_Tex.GetCurrentTexture() != 5)
		m_Tex.Update();
	else if (trigger && m_Tex.GetCurrentTexture() == 5)
	{
		m_Tex.SetCurrentTexture(5); m_Tex.Update();
	}
	else if (!StageStart::Get())
	{
		m_Tex.SetCurrentTexture(0); m_Tex.Update();
	}

	if (StageEnd::Get())
	{
		m_Tex.SetCurrentTexture(0); m_Tex.Update();
	}

	m_Tex2.Update();


	//ƒGƒtƒFƒNƒg‚ÌŠg‘åk¬
	if ((Controller::GetButtonPressLShoulder() || trigger) && !StageStart::Get() && !StageEnd::Get())
	{

		m_EffectSize.x += 20.0f;
		m_EffectSize.y += 20.0f;
		if (m_EffectSize.x > 200.0f)
		{
			m_EffectSize.x = 200.0f;
			m_EffectSize.y = 200.0f;
		}

	}
	else
	{
		m_EffectSize.x -= 20.0f;
		m_EffectSize.y -= 20.0f;
		if (m_EffectSize.x < 0.0f)
		{
			m_EffectSize.x = 0.0f;
			m_EffectSize.y = 0.0f;
		}

	}

	// ‚Ä‚ñ‚ß‚Â
	m_Frame++;
	float temp = 1.0f + sin(m_Frame * 0.2f) * 0.08f;
	m_Col = { temp,temp ,temp ,1.0f };
}

void PlayerLeft::Draw()
{
	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_Tex, m_Col);

	if (trigger && !StageStart::Get() && !StageEnd::Get())
		Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_EffectSize, &m_Tex2, math::Float4(1.0f, 1.0f, 1.0f, 0.8f));
}

