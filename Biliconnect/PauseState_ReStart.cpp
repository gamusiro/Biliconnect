#include "PauseState_ReStart.h"
#include "Pause.h"
#include "PauseState.h"
#include "SEManager.h"

using namespace math;

PauseState_ReStart::PauseState_ReStart(Pause& pause, Game* game)
	: PauseState(pause, game)
{
	m_Tex.Create("Button/yes_icon.png", 3, 1);
	m_Tex2.Create("Button/no_icon.png", 3, 1);
	m_Return.Create("Button/restart_game.png", 1, 1);
	m_Mouse.Create("Button/cursor_icon.png", 2, 1);
	m_Pos = 1320;

	m_DrawPos = 1320.0f;
	m_InputDirection = RIGHT;
}

void PauseState_ReStart::Update()
{

	
	//ƒ}ƒEƒX‚ÌˆÚ“®
		if (m_Pos == 600)
		{
			if (m_InputDirection == RIGHT)
			{
				m_DrawPos += 140.0f;
				if (m_DrawPos > 600.0f)
					m_DrawPos = 600.0f;
			}

			if (m_InputDirection == LEFT)
			{
				m_DrawPos -= 140.0f;
				if (m_DrawPos < 600.0f)
					m_DrawPos = 600.0f;
			}
		}

		if (m_Pos == 1320)
		{
			if (m_InputDirection == RIGHT)
			{
				m_DrawPos += 140.0f;
				if (m_DrawPos > 1320.0f)
					m_DrawPos = 1320.0f;
			}

			if (m_InputDirection == LEFT)
			{
				m_DrawPos -= 140.0f;
				if (m_DrawPos < 1320.0f)
					m_DrawPos = 1320.0f;
			}
		}



	if ((Controller::GetLStickTriggerRight() || Controller::GetButtonTriggerRight()) && m_Pos != 1320 && !trigger)
	{
		m_Pos += 720;
		SEManager::Play(SOUND::CURSOR);
		m_InputDirection = RIGHT;
	}
	if ((Controller::GetLStickTriggerLeft() || Controller::GetButtonTriggerLeft()) && m_Pos != 600 && !trigger)
	{
		m_Pos -= 720;
		SEManager::Play(SOUND::CURSOR);
		m_InputDirection = LEFT;
	}

	if (m_Pos == 600)
	{
		m_Tex.SetCurrentTexture(1);	m_Tex.Update();
		m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
	}
	else if (m_Pos == 1320)
	{
		m_Tex.SetCurrentTexture(0);	m_Tex.Update();
		m_Tex2.SetCurrentTexture(1); m_Tex2.Update();
	}

	if (trigger)
	{
		timer++;

		if (m_Pos == 600)
		{
			m_Tex.SetStartUVPosition(Float2(0.6666f, 1.0f));
			if (timer > WAIT && Fade::GetState())
			{
				Texture tex;
				tex.Create("chan2.png", 1, 1);
				tex.SetImageID(0);

				Fade::Transition(SCENE_TYPE::RESTART, FADE_TYPE::CHAN, &tex, {1,1,0.3f});
			}
		}
		else if (m_Pos == 1320)
		{
			m_Tex2.SetStartUVPosition(Float2(0.6666f, 1.0f));
			if (timer > WAIT)
				m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
		}
	}

	if (Controller::GetButtonTriggerB() && !trigger)
	{
		m_Mouse.SetCurrentTexture(1);	m_Mouse.Update();

		if (m_Pos == 600)
			SEManager::Play(SOUND::CLICK);
		else if (m_Pos == 1320)

			SEManager::Play(SOUND::CANCEL);
		trigger = true;
		timer = 0;
	}
	else if (Controller::GetButtonTriggerA())
	{
		SEManager::Play(SOUND::CANCEL);
		m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	}
}

void PauseState_ReStart::Draw()
{
	Sprite::DrawCenter(Float2(600, SCREEN_HEIGHT * 0.6f), Float2(400, 150), &m_Tex);
	Sprite::DrawCenter(Float2(1320, SCREEN_HEIGHT * 0.6f), Float2(400, 150), &m_Tex2);

	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f), Float2(900, 350), &m_Return);
	Sprite::DrawCenter(Float2(m_DrawPos + 80, SCREEN_HEIGHT * 0.6f + 30), Float2(100, 100), &m_Mouse);
}

void PauseState_ReStart::Set()
{
	m_Pos = 1320;
	timer = 0;
	trigger = false;

	m_Mouse.SetCurrentTexture(0);	m_Mouse.Update();
	m_Tex.SetCurrentTexture(0);	m_Tex.Update();
	m_Tex2.SetCurrentTexture(1); m_Tex2.Update();
}
