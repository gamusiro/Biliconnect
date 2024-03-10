#include "Pause.h"
#include "PauseState.h"
#include "PauseState_Select.h"
#include "PauseState_Option.h"
#include "PauseState_Stage.h"
#include "PauseState_ReStart.h"

using namespace math;

Pause::Pause(Game* game) : m_State(PAUSESTATE::SELECT)
{
	m_States[static_cast<int>(PAUSESTATE::SELECT)] = std::make_unique<PauseState_Select>(*this, game);
	m_States[static_cast<int>(PAUSESTATE::OPTION)] = std::make_unique<PauseState_Option>(*this, game);
	m_States[static_cast<int>(PAUSESTATE::STAGE)] = std::make_unique<PauseState_Stage>(*this, game);
	m_States[static_cast<int>(PAUSESTATE::RESTART)] = std::make_unique<PauseState_ReStart>(*this, game);

	Waku.Create("Option/option_ground.png", 1, 1);
}

Pause::~Pause()
{
}

void Pause::Update()
{
	//if (Controller::GetButtonTriggerStart() && m_GameState != GAMESTATE::PAUSE)
	//	m_GameState = GAMESTATE::PAUSE;
	//else if (Controller::GetButtonTriggerStart() && m_GameState == GAMESTATE::PAUSE)
	//	m_GameState = GAMESTATE::PLAY;

	/*if (m_GameState == GAMESTATE::PLAY)
	{
		ChangeState(Pause::PAUSESTATE::SELECT);
	}
	else if (m_GameState == GAMESTATE::PAUSE)
	{
		m_States[static_cast<int>(m_State)]->Update();
	}*/

	m_States[static_cast<int>(m_State)]->Update();
}

void Pause::Draw()
{
	Sprite::DrawCenter(Float2(0, 0), Float2(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2), nullptr, Float4(0.2f, 0.2f, 0.2f, 0.4f));
	Sprite::DrawCenter(Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f), Float2(SCREEN_WIDTH, SCREEN_HEIGHT), &Waku);
	
	m_States[static_cast<int>(m_State)]->Draw();
}

void Pause::ChangeState(PAUSESTATE state)
{
	m_State = state;
	m_States[static_cast<int>(m_State)]->Set();
}

void Pause::ResetState()
{
	m_State = PAUSESTATE::SELECT;
	m_States[static_cast<int>(m_State)]->Set();
}
