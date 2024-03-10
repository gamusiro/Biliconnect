#include "PauseState_Option.h"
#include "Pause.h"
#include "PauseState.h"
#include "SEManager.h"
#include "BGMOption.h"

using namespace math;

PauseState_Option::PauseState_Option(Pause& pause, Game* game)
	: PauseState(pause, game)
{
	m_BGMOption = new BGMOption();

	m_Tex.Create("Button/bgm_icon.png", 3, 1);
	m_Tex2.Create("Button/se_icon.png", 3, 1);
	m_Tex3.Create("Button/back_icon.png", 3, 1);
	m_Mouse.Create("Button/cursor_icon.png", 2, 1);

	m_Pos = 300;
}

void PauseState_Option::Update()
{
	//if ((Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown()) && m_Pos != 700 && !trigger)
	//{
	//	SEManager::Play(SOUND::CURSOR);
	//	m_Pos += 200;
	//}
	//if ((Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp()) && m_Pos != 300 && !trigger)
	//{
	//	SEManager::Play(SOUND::CURSOR);
	//	m_Pos -= 200;
	//}

	//if (m_Pos == 300)
	//{
	//	m_Tex.SetCurrentTexture(1);	m_Tex.Update();
	//	m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
	//	m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
	//}
	//else if (m_Pos == 500)
	//{
	//	m_Tex.SetCurrentTexture(0);	m_Tex.Update();
	//	m_Tex2.SetCurrentTexture(1); m_Tex2.Update();
	//	m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
	//}
	//else if (m_Pos == 700)
	//{
	//	m_Tex.SetCurrentTexture(0);	m_Tex.Update();
	//	m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
	//	m_Tex3.SetCurrentTexture(1); m_Tex3.Update();
	//}

	//if (trigger)
	//{
	//	timer++;

	//	if (m_Pos == 300)
	//	{
	//		m_Tex.SetStartUVPosition(Float2(0.6666f, 1.0f));
	//		if (timer > WAIT)
	//			m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	//	}
	//	else if (m_Pos == 500)
	//	{
	//		m_Tex2.SetStartUVPosition(Float2(0.6666f, 1.0f));
	//		if (timer > WAIT)
	//			m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	//	}
	//	else if (m_Pos == 700)
	//	{
	//		m_Tex3.SetStartUVPosition(Float2(0.6666f, 1.0f));
	//		if (timer > WAIT)
	//			m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	//	}
	//}

	//if (Controller::GetButtonTriggerB() && !trigger)
	//{
	//	m_Mouse.SetCurrentTexture(1);	m_Mouse.Update();

	//	if (m_Pos == 300)
	//		SEManager::Play(SOUND::CLICK);
	//	else if (m_Pos == 500)
	//		SEManager::Play(SOUND::CLICK);
	//	else if (m_Pos == 700)
	//		SEManager::Play(SOUND::CANCEL);

	//	trigger = true;
	//	timer = 0;
	//}
	//else if (Controller::GetButtonTriggerA())
	//{
	//	SEManager::Play(SOUND::CANCEL);
	//	m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	//}

	if (Controller::GetButtonTriggerA())
	{
		SEManager::Play(SOUND::CANCEL);
		m_BGMOption->OperateOption(false);
		m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	}
	if (Controller::GetButtonTriggerB() && m_BGMOption->GetSelect() == 2)
	{
		SEManager::Play(SOUND::CLICK);
		m_BGMOption->OperateOption(false);
		m_Pause.ChangeState(Pause::PAUSESTATE::SELECT);
	}

	m_BGMOption->Update();
}

void PauseState_Option::Draw()
{
	/*Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), Float2(1400, 1000), nullptr, Float4(1.0f, 1.0f, 1.0f, 0.7f));
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 300), Float2(400, 150), &m_Tex);
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 500), Float2(400, 150), &m_Tex2);
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, 700), Float2(400, 150), &m_Tex3);

	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f + 80, m_Pos + 30), Float2(100, 100), &m_Mouse);*/

	m_BGMOption->Draw();
}

void PauseState_Option::Set()
{
	m_BGMOption->Init();
	m_BGMOption->OperateOption(true);
	m_Pos = 300;
	timer = 0;
	trigger = false;

	m_Tex.SetCurrentTexture(1);	m_Tex.Update();
	m_Tex2.SetCurrentTexture(0); m_Tex2.Update();
	m_Tex3.SetCurrentTexture(0); m_Tex3.Update();
	m_Mouse.SetCurrentTexture(0);	m_Mouse.Update();
}
