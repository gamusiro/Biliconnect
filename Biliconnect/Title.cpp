/*=========================================================================
	Date : 2021/12/21(��)	Title.cpp
		Author : ���ނ��邧
		Update :
=========================================================================*/
#include "Movie.h"
#include "Input.h"
#include "SE.h"

#include "Title.h"
#include "BGMOption.h"
#include "SEManager.h"
#include "Volume.h"
#include "Application.h"
using namespace math;

int g_degree;

/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
Title::Title() : m_BGM(new BGM())
{
	for (int i = 0; i < MAX; i++)
	{
		m_Tex[i] = new Texture();
	}

	m_BGM->Load("title.wav");
	m_BGM->SetVolume(Volume::GetBGM() * MASTER_VOLUME);
	m_BGM->Play(-1);

	first = true;
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
Title::~Title()
{
	for (int i = 0; i < MAX; i++)
	{
		delete m_Tex[i];
	}
}


/*=============================================================================================
	����������
=============================================================================================*/
void Title::Init()
{


	if (first)
	{
		m_Tex[BG]->Create("tbg.png", 1, 1);
		m_BGMOption = new BGMOption();
		m_BGMOption->Init();

	}
	m_Pos[BG] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Vel[BG] = Float2(NULL, NULL);
	m_Size[BG] = Float2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Color[BG] = Float4(1.0f, 1.0f, 1.0f, 1.0f);


	m_Tex[TITLE_LOGO]->Create("anime4.png", 15, 12);
	m_Pos[TITLE_LOGO] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f - 180.0f);
	m_Vel[TITLE_LOGO] = Float2(NULL, -10.0f);
	m_Size[TITLE_LOGO] = Float2(1540.0f, 636.0f);
	m_Color[TITLE_LOGO] = Float4(1.0f, 1.0f, 1.0f, 0.0f);


	m_Tex[CREDIT]->Create("staffcredits.png", 1, 1);
	m_Pos[CREDIT] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Vel[CREDIT] = Float2(NULL, -10.0f);
	m_Size[CREDIT] = Float2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Color[CREDIT] = Float4(1.0f, 1.0f, 1.0f, 0.0f);
	DisplayCredit = false;

	m_Tex[CREDIT_BUTTON]->Create("Button/creadits_start.png", 1, 1);
	m_Pos[CREDIT_BUTTON] = Float2(330.0f, SCREEN_HEIGHT - 120.0f);
	m_Vel[CREDIT_BUTTON] = Float2(NULL, -10.0f);
	m_Size[CREDIT_BUTTON] = Float2(600.0f*0.8f, 200.0f*0.8f);
	m_Color[CREDIT_BUTTON] = Float4(1.0f, 1.0f, 1.0f, 0.0f);

	m_Tex[EXIT]->Create("Button/exit_back.png", 1, 1);
	m_Pos[EXIT] = Float2(330.0f, SCREEN_HEIGHT - 220.0f);
	m_Vel[EXIT] = Float2(NULL, -10.0f);
	m_Size[EXIT] = Float2(600.0f*0.8f, 200.0f*0.8f);
	m_Color[EXIT] = Float4(1.0f, 1.0f, 1.0f, 0.0f);

	m_Tex[START]->Create("Button/start_icon.png", 3, 1);
	m_Pos[START] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 200.0f);
	m_Vel[START] = Float2(NULL, -10.0f);
	m_Size[START] = Float2(600.0f * 0.8f, 200.0f * 0.8f);
	m_Color[START] = Float4(1.0f, 1.0f, 1.0f, 0.0f);

	m_Tex[OPTION]->Create("Button/option_icon.png", 3, 1);
	m_Pos[OPTION] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 400.0f);
	m_Vel[OPTION] = Float2(NULL, -10.0f);
	m_Size[OPTION] = Float2(600.0f * 0.8f, 200.0f * 0.8f);
	m_Color[OPTION] = Float4(1.0f, 1.0f, 1.0f, 0.0f);

	m_Tex[PRESS_B]->Create("PressB.png", 1, 1);
	m_Pos[PRESS_B] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f + 250.0f);
	m_Vel[PRESS_B] = Float2(NULL, -10.0f);
	m_Size[PRESS_B] = Float2(800.0f * 1.2f, 100.0f * 1.2f);
	m_Color[PRESS_B] = Float4(1.0f, 1.0f, 1.0f, 0.0f);

	m_Tex[FADE]->Create("white.png", 1, 1);
	m_Pos[FADE] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Vel[FADE] = Float2(NULL, NULL);
	m_Size[FADE] = Float2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Color[FADE] = Float4(26.0f / 255.0f, 7.0f / 255.0f, 80.0f / 255.0f, 0.0f);

	m_Tex[FRAME]->Create("tf.png", 1, 1);
	m_Pos[FRAME] = Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Vel[FRAME] = Float2(NULL, NULL);
	m_Size[FRAME] = Float2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Color[FRAME] = Float4(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX; i++)
	{
		m_Use[i] = true;
	}

	//���[�h�Ǘ�
	m_ModeFrame = 0;
	m_Mode = MODE_1;

	m_Frame = 0;
	m_BlinkingFrame = 0;
	m_isBlinkingSpd = 0.04f;
	m_BlinkingMagnitude = 1.0f;
	m_Rarefaction = 1.0f;
	m_isBlinking = false;

	if (first)
	SEManager::Init();

	//�I������
	m_Select = S_START;

	canTransit = false;
	first = false;
}


/*=============================================================================================
	�I������
=============================================================================================*/
void Title::Uninit()
{
	first = true;

	delete m_BGM;

	//�V�[�����Ƃ�1�x�����Ă�
	TextureManager::Unload();
	SoundManager::Unload();
}

/*=============================================================================================
	�X�V����
=============================================================================================*/
void Title::Update()
{
	g_degree++;
	m_Tex[TITLE_LOGO]->Update();

	//�����[�h�P//���S�ƃv���X�̏㏸&�t�F�[�h
	if (m_Mode == MODE_1)
	{
		m_ModeFrame++;

		if (m_ModeFrame > 30 && m_ModeFrame < 60 * 1)
		{
			m_Pos[TITLE_LOGO].y += m_Vel[TITLE_LOGO].y;
			m_Vel[TITLE_LOGO].y *= 0.5f;
			m_Color[TITLE_LOGO].w += 0.05f;
			if (m_Color[TITLE_LOGO].w > 1.0f)
				m_Color[TITLE_LOGO].w = 1.0f;
		}

		if (m_ModeFrame > 60 && m_ModeFrame < 60 * +30)
		{

			m_Color[PRESS_B].w += 0.05f;
			if (m_Color[PRESS_B].w > 1.0f)
				m_Color[PRESS_B].w = 1.0f;
		}

		if (m_ModeFrame > 60 * 1 + 30)
		{
			m_Mode = MODE_2;
			m_ModeFrame = 0;
		}

	
	}

	//�����[�h2 �@�v���XB�_�Ł��v���XB���͉\
	if (m_Mode == MODE_2)
	{
		//�{�^��������������
		if (Controller::GetButtonTriggerB() && Fade::GetState() && !m_isBlinking)
		{
			SEManager::Play(SOUND::DECISION);
			m_isBlinking = true;
		}

		//�{�^������������̓_��
		if (m_isBlinking)
		{
			m_isBlinkingSpd = 0.5f;
			m_BlinkingMagnitude = 0.5f;
			m_ModeFrame++;//���Z�J�n
		}

		//�v���X�{�^���̓_�ł������ă��[�h3�ɂȂ�܂�
		if (m_ModeFrame > 50 && sinf(m_BlinkingFrame * m_isBlinkingSpd) * m_BlinkingMagnitude < 0.0f)
		{
			m_isBlinkingSpd = 0.0f;
			m_Rarefaction = 0.0f;
			m_Mode = MODE_3;
			m_ModeFrame = 0;
		}

		m_BlinkingFrame++;
		m_Color[PRESS_B].w = (sinf(m_BlinkingFrame * m_isBlinkingSpd) * m_BlinkingMagnitude + 1.2f) * m_Rarefaction;;
	}

	if (m_Mode == MODE_3)
	{
		if (!DisplayCredit)
		{
			if (Controller::GetButtonTriggerA() && !canTransit)
			{
				this->Init();
				SEManager::Play(SOUND::CANCEL);
			}
		}

		//�{�^���̃t�F�[�h�C��
		m_Color[START].w += 0.05f;
		if (m_Color[START].w > 1.0f)
			m_Color[START].w = 1.0f;

		m_Color[OPTION].w += 0.05f;
		if (m_Color[OPTION].w > 1.0f)
			m_Color[OPTION].w = 1.0f;

		m_Color[CREDIT_BUTTON].w += 0.05f;
		if (m_Color[CREDIT_BUTTON].w > 1.0f)
			m_Color[CREDIT_BUTTON].w = 1.0f;

		m_Color[EXIT].w += 0.05f;
		if (m_Color[EXIT].w > 1.0f)
			m_Color[EXIT].w = 1.0f;

		if (!DisplayCredit)
		{
			//�{�^�����������ꂽ��
			if (m_Color[OPTION].w >= 1.0f)
			{
				//���ڂ̑I��
				if (((Controller::GetLStickTriggerUp() && !canTransit) || (Controller::GetButtonTriggerUp()) && !canTransit))
				{
					if (m_Select == S_OPTION)
						SEManager::Play(SOUND::CURSOR);
					m_Select = S_START;
				}
				if (((Controller::GetLStickTriggerDown() && !canTransit) || (Controller::GetButtonTriggerDown()) && !canTransit))
				{
					if (m_Select == S_START)
						SEManager::Play(SOUND::CURSOR);
					m_Select = S_OPTION;
				}


				//����
				if (Controller::GetButtonTriggerB() && !canTransit)
				{
					canTransit = true;

					if (m_Select == S_OPTION)
						SEManager::Play(SOUND::CLICK);
					else if (m_Select == S_START)
						SEManager::Play(SOUND::DECISION);
				}



			}

			//�A�j���[�V����
			m_Tex[START]->Update();
			m_Tex[OPTION]->Update();


			//�X�^�[�g�������ꂽ�Ƃ��̏���
			if (m_Select == S_START)
			{
				m_Tex[START]->SetCurrentTexture(1);
				m_Tex[OPTION]->SetCurrentTexture(0);

				if (canTransit)
				{
					m_Tex[START]->SetCurrentTexture(2);
					m_ModeFrame++;


					//�V�[���J�ڂ��s��
					if (m_ModeFrame > 50 && Fade::GetState())
					{
						m_Color[FADE].w += 0.02f;
					}

					if (m_ModeFrame > 60 * 2 && Fade::GetState())
					{
						m_Size[FRAME] += Float2(5.0f, 5.0f);
					}

					if (m_ModeFrame > 60 * 2 + 30 && Fade::GetState())
					{
						Texture tex;
						tex.Create("result_bg.png", 1, 1);
						tex.SetImageID(0);
						/*if (Input::KeyboardPress(DIK_RSHIFT))
							Fade::Transition(SCENE_TYPE::GAME, FADE_TYPE::ALPHA);*/
							/*else*/
						Fade::Transition(SCENE_TYPE::STAGE_SELECT, FADE_TYPE::ALPHA, m_Tex[FADE], Float3(1.0f, 1.0f, 1.0f));
					}
				}
			}

			//�I�v�V�����������ꂽ�Ƃ��̏���
			if (m_Select == S_OPTION)
			{
				m_Tex[OPTION]->SetCurrentTexture(1);
				m_Tex[START]->SetCurrentTexture(0);

				if (canTransit)
				{
					m_Tex[OPTION]->SetCurrentTexture(2);
					m_ModeFrame++;

					if (m_ModeFrame > 30)
					{
						m_BGMOption->Back(false);
						m_BGMOption->OperateOption(true);
						m_Mode = MODE_4;
					}
				}
			}
		}

		if (Controller::GetButtonTriggerBack())
		{
			Application::GetWindow()->Exit();
		}

		if (Controller::GetButtonTriggerStart() && !DisplayCredit && !canTransit)
		{
			DisplayCredit = true;
			SEManager::Play(SOUND::CLICK);
		}
		else if ((Controller::GetButtonTriggerA()||Controller::GetButtonTriggerStart()) && DisplayCredit && !canTransit)
		{
			DisplayCredit = false;
			SEManager::Play(SOUND::DECISION);
		}
		if (DisplayCredit)
		{
			m_Color[CREDIT].w += 0.2f;
			if (m_Color[CREDIT].w > 1.0f)
				m_Color[CREDIT].w = 1.0f;

			m_Color[CREDIT_BUTTON].w -= 0.2f;
			if (m_Color[CREDIT_BUTTON].w < 0.0f)
				m_Color[CREDIT_BUTTON].w = 0.0f;
		}

		if (!DisplayCredit)
		{

			m_Color[CREDIT_BUTTON].w += 0.2f;
			if (m_Color[CREDIT_BUTTON].w > 1.0f)
				m_Color[CREDIT_BUTTON].w = 1.0f;

			m_Color[CREDIT].w -= 0.2f;
			if (m_Color[CREDIT].w < 0.0f)
				m_Color[CREDIT].w = 0.0f;

		}

	}
	else
	{
		m_Color[CREDIT_BUTTON].w -= 0.2f;
		if (m_Color[CREDIT_BUTTON].w < 0.0f)
			m_Color[CREDIT_BUTTON].w = 0.0f;

		m_Color[CREDIT].w -= 0.2f;
		if (m_Color[CREDIT].w < 0.0f)
			m_Color[CREDIT].w = 0.0f;
	}

	if (m_Mode == MODE_4)
	{
		m_BGM->SetVolume(Volume::GetBGM() * MASTER_VOLUME);

		if (Controller::GetButtonTriggerB() && m_BGMOption->GetSelect() == 2)
		{
			m_BGMOption->Back(true);
			SEManager::Play(SOUND::CLICK);

		}

		else if (Controller::GetButtonTriggerA())
		{
			SEManager::Play(SOUND::CANCEL);
			canTransit = false;
			m_ModeFrame = 0;
			m_Tex[OPTION]->SetCurrentTexture(1); m_Tex[OPTION]->Update();
			m_Mode = MODE_3;
			m_BGMOption->OperateOption(false);
		}

		m_BGMOption->Update();

		if (m_BGMOption->GetFrameSinceInputBack() > 20)
		{
			canTransit = false;
			m_ModeFrame = 0;
			m_Tex[OPTION]->SetCurrentTexture(1); m_Tex[OPTION]->Update();
			m_Mode = MODE_3;
			m_BGMOption->OperateOption(false);
		}
	}
}

/*=============================================================================================
	�`�揈��
=============================================================================================*/
void Title::Draw()
{
	for (int i = 0; i < MAX; i++)
	{

		if (DisplayCredit)
		{
			if (i == CREDIT || i == BG || i == FRAME)//�N���W�b�g
				Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
		}
		else
		{
			if (!m_BGMOption->GetOperateOption())//�I�v�V������\����
				Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
			else if (m_BGMOption->GetOperateOption())//�I�v�V�����\����
			{
				if (i == BG || i == FRAME)//BG�Ƙg�����\��
					Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
			}

		}

	}
	if (m_Mode == MODE_4)
		m_BGMOption->Draw();
}

/*=============================================================================================
	�Q�[���X�^�[�g
=============================================================================================*/
void Title::GameStart()
{
	static bool m_GameStart = false;

	if (m_GameStart)
	{

	}
}
