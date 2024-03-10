/*=========================================================================
	Date : 2021/12/21(��)	Game.cpp
		Author : ���ނ��邧
		Update :
=========================================================================*/
#include "Game.h"
using namespace math;

#include "Stage.h"
#include "Pause.h"
#include "SEManager.h"
#include "Volume.h"

float degree;

/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
Game::Game()
	:m_Texture(new Texture()),
	m_BGM(new BGM())
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
Game::~Game()
{
	delete m_BGM;
	delete m_Texture;
}

/*=============================================================================================
	����������
=============================================================================================*/
void Game::Init()
{
	//m_Texture->Create("scenely02.jpg", 1, 1);

	int num = StageNum::Get() % 5;
	if (StageNum::Get() == 24)
		m_BGM->Load("area5.wav");
	else if (num == 4)
		m_BGM->Load("In_The_Battle.wav");
	else
		m_BGM->Load("stage.wav");
	m_BGM->SetVolume(Volume::GetBGM() * MASTER_VOLUME);
	m_BGM->Play(-1);
	SEManager::Init();

	m_Stage = std::make_unique<Stage>();
	m_Stage->Init();

	m_Pause = std::make_unique<Pause>(this);

	degree = 0.0f;

	m_GameState = 0;
}

/*=============================================================================================
	�I������
=============================================================================================*/
void Game::Uninit()
{
	m_Stage->Uninit();

	m_BGM->Stop();
	Controller::StopVibration();

	TextureManager::Unload();
	SoundManager::Unload();
}

/*=============================================================================================
	�X�V����
=============================================================================================*/
void Game::Update()
{
	if (m_GameState == (int)GAMESTATE::PLAY)
	{
		m_BGM->SetVolume(Volume::GetBGM() * MASTER_VOLUME);

	/*	if (Input::KeyboardTrigger(DIK_P))
			m_BGM->Pause();
		else if (Input::KeyboardTrigger(DIK_Q))
			m_BGM->Play();*/

		m_Stage->Update();

		if (Controller::GetButtonTriggerStart() && Fade::GetState() && (StageStart::GetTimer() < 280 || StageStart::GetTimer() > 600))
		{
			m_Pause->ResetState();
			SetGameState((int)GAMESTATE::PAUSE);
		}
	}
	else if (m_GameState == (int)GAMESTATE::PAUSE && Fade::GetState())
	{
		m_BGM->SetVolume(Volume::GetBGM() * 1);
		m_Pause->Update();

		if (Controller::GetButtonTriggerStart())
			SetGameState((int)GAMESTATE::PLAY);
	}

	//if ((Input::KeyboardTrigger(DIK_RETURN) || Controller::GetButtonTriggerY()) && Fade::GetState())
	//{
	//	Fade::Transition(SCENE_TYPE::RESULT, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
	//}
}

/*=============================================================================================
	�`�揈��
=============================================================================================*/
void Game::Draw()
{
	m_Stage->Draw();

	if (m_GameState == (int)GAMESTATE::PAUSE)
	{
		m_Pause->Draw();
	}
}
