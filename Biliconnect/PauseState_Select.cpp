#include "PauseState_Select.h"
#include "Pause.h"
#include "PauseState.h"
#include "Game.h"
#include "SEManager.h"

using namespace math;

PauseState_Select::PauseState_Select(Pause& pause, Game* game)
	: PauseState(pause, game)
{
	m_Tex.Create("Button/menu_icon.png", 3, 1);
	m_Tex2.Create("Button/restart_icon.png", 3, 1);
	m_Tex3.Create("Button/option_icon.png", 3, 1);
	m_Tex4.Create("Button/back_icon.png", 3, 1);
	m_Mouse.Create("Button/cursor_icon.png", 2, 1);
	m_Pos = 300;

	m_DrawPos = 300.0f;
	m_InputDirection = DOWN;
}

void PauseState_Select::Update()
{
	if ((Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown()) && m_Pos != 900 && !trigger)
	{
		m_Pos += 200;
		SEManager::Play(SOUND::CURSOR);

		m_InputDirection = DOWN;
	}
	if ((Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp()) && m_Pos != 300 && !trigger)
	{
		m_Pos -= 200;
		SEManager::Play(SOUND::CURSOR);

		m_InputDirection = UP;
	}


	if (m_Pos == 300)
	{
		m_Tex.SetCurrentTexture(1);	m_Tex.Update();
		m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
		m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
		m_Tex4.SetCurrentTexture(0); m_Tex4.Update();
	}
	else if (m_Pos == 500)
	{
		m_Tex.SetCurrentTexture(0);	m_Tex.Update();
		m_Tex2.SetCurrentTexture(1); m_Tex2.Update();
		m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
		m_Tex4.SetCurrentTexture(0); m_Tex4.Update();
	}
	else if (m_Pos == 700)
	{
		m_Tex.SetCurrentTexture(0);	m_Tex.Update();
		m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
		m_Tex3.SetCurrentTexture(1); m_Tex3.Update();
		m_Tex4.SetCurrentTexture(0); m_Tex4.Update();
	}
	else if (m_Pos == 900)
	{
		m_Tex.SetCurrentTexture(0);	m_Tex.Update();
		m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
		m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
		m_Tex4.SetCurrentTexture(1); m_Tex4.Update();
	}

	//ƒ}ƒEƒX‚ÌˆÚ“®
	if (m_Pos == 300)
	{
		if (m_InputDirection == DOWN) 
		{
				m_DrawPos += 40.0f;
				if (m_DrawPos > 300.0f)
					m_DrawPos = 300.0f;
		}

		if (m_InputDirection == UP)
		{
				m_DrawPos -= 40.0f;
				if (m_DrawPos < 300.0f)
					m_DrawPos = 300.0f;
		}
	}

	if (m_Pos == 500)
	{
		if (m_InputDirection == DOWN)
		{
			m_DrawPos += 40.0f;
			if (m_DrawPos > 500.0f)
				m_DrawPos = 500.0f;
		}
		if (m_InputDirection == UP)
		{
			m_DrawPos -= 40.0f;
			if (m_DrawPos < 500.0f)
				m_DrawPos = 500.0f;
		}
	}

	if (m_Pos == 700)
	{
		if (m_InputDirection == DOWN)
		{
			m_DrawPos += 40.0f;
			if (m_DrawPos > 700.0f)
				m_DrawPos = 700.0f;
		}

		if (m_InputDirection == UP)
		{
			m_DrawPos -= 40.0f;
			if (m_DrawPos < 700.0f)
				m_DrawPos = 700.0f;
		}
	}

	if (m_Pos == 900)
	{
		if (m_InputDirection == DOWN)
		{
			m_DrawPos += 40.0f;
			if (m_DrawPos > 900.0f)
				m_DrawPos = 900.0f;
		}

		if (m_InputDirection == UP)
		{
			m_DrawPos -= 40.0f;
			if (m_DrawPos < 900.0f)
				m_DrawPos = 900.0f;
		}
	}


	if (trigger)
	{
		timer++;

		if (m_Pos == 300)
		{
			m_Tex.SetStartUVPosition(Float2(0.6666f, 1.0f));
			if (timer > WAIT)
				m_Pause.ChangeState(Pause::PAUSESTATE::STAGE);

		
		}
		else if (m_Pos == 500)
		{
			m_Tex2.SetStartUVPosition(Float2(0.6666f, 1.0f));
			if (timer > WAIT)
				m_Pause.ChangeState(Pause::PAUSESTATE::RESTART);
		}
		else if (m_Pos == 700)
		{
			m_Tex3.SetStartUVPosition(Float2(0.6666f, 1.0f));
			if (timer > WAIT)
				m_Pause.ChangeState(Pause::PAUSESTATE::OPTION);

		}
		else if (m_Pos == 900)
		{
			m_Tex4.SetStartUVPosition(Float2(0.6666f, 1.0f));
			if (timer > WAIT)
				m_Game->SetGameState((int)Game::GAMESTATE::PLAY);
		}
	}

	if (Controller::GetButtonTriggerB() && !trigger)
	{
		m_Mouse.SetCurrentTexture(1);	m_Mouse.Update();

		if (m_Pos == 300)
			SEManager::Play(SOUND::CLICK);
		else if (m_Pos == 500)
			SEManager::Play(SOUND::CLICK);
		else if (m_Pos == 700)
			SEManager::Play(SOUND::CLICK);
		else if (m_Pos == 900)
			SEManager::Play(SOUND::CLICK);

		trigger = true;
		timer = 0;
	}
	else if (Controller::GetButtonTriggerA())
	{
		SEManager::Play(SOUND::CANCEL);
		m_Game->SetGameState((int)Game::GAMESTATE::PLAY);
	}
}

void PauseState_Select::Draw()
{
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 300 - 60), Float2(400, 150), &m_Tex);
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 500 - 60), Float2(400, 150), &m_Tex2);
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 700 - 60), Float2(400, 150), &m_Tex3);
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 900 - 60), Float2(400, 150), &m_Tex4);
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f + 20, m_DrawPos - 30), Float2(100, 100), &m_Mouse);
}

void PauseState_Select::Set()
{
	m_Pos = 300;
	timer = 0;
	trigger = false;

	m_Tex.SetCurrentTexture(1);	m_Tex.Update();
	m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
	m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
	m_Tex4.SetCurrentTexture(0); m_Tex4.Update();
	m_Mouse.SetCurrentTexture(0);	m_Mouse.Update();
}
