/*=========================================================================
	Date : 2021/12/21(火)	Title.cpp
		Author : がむしるぉ
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
	コンストラクタ
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
	デストラクタ
=============================================================================================*/
Title::~Title()
{
	for (int i = 0; i < MAX; i++)
	{
		delete m_Tex[i];
	}
}


/*=============================================================================================
	初期化処理
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

	//モード管理
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

	//選択項目
	m_Select = S_START;

	canTransit = false;
	first = false;
}


/*=============================================================================================
	終了処理
=============================================================================================*/
void Title::Uninit()
{
	first = true;

	delete m_BGM;

	//シーンごとに1度だけ呼ぶ
	TextureManager::Unload();
	SoundManager::Unload();
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void Title::Update()
{
	g_degree++;
	m_Tex[TITLE_LOGO]->Update();

	//■モード１//ロゴとプレスの上昇&フェード
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

	//■モード2 　プレスB点滅＆プレスB入力可能
	if (m_Mode == MODE_2)
	{
		//ボタンを押した判定
		if (Controller::GetButtonTriggerB() && Fade::GetState() && !m_isBlinking)
		{
			SEManager::Play(SOUND::DECISION);
			m_isBlinking = true;
		}

		//ボタンを押した後の点滅
		if (m_isBlinking)
		{
			m_isBlinkingSpd = 0.5f;
			m_BlinkingMagnitude = 0.5f;
			m_ModeFrame++;//加算開始
		}

		//プレスボタンの点滅が消えてモード3になるまで
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

		//ボタンのフェードイン
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
			//ボタンが両方現れたら
			if (m_Color[OPTION].w >= 1.0f)
			{
				//項目の選択
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


				//決定
				if (Controller::GetButtonTriggerB() && !canTransit)
				{
					canTransit = true;

					if (m_Select == S_OPTION)
						SEManager::Play(SOUND::CLICK);
					else if (m_Select == S_START)
						SEManager::Play(SOUND::DECISION);
				}



			}

			//アニメーション
			m_Tex[START]->Update();
			m_Tex[OPTION]->Update();


			//スタートが押されたときの処理
			if (m_Select == S_START)
			{
				m_Tex[START]->SetCurrentTexture(1);
				m_Tex[OPTION]->SetCurrentTexture(0);

				if (canTransit)
				{
					m_Tex[START]->SetCurrentTexture(2);
					m_ModeFrame++;


					//シーン遷移を行う
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

			//オプションが押されたときの処理
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
	描画処理
=============================================================================================*/
void Title::Draw()
{
	for (int i = 0; i < MAX; i++)
	{

		if (DisplayCredit)
		{
			if (i == CREDIT || i == BG || i == FRAME)//クレジット
				Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
		}
		else
		{
			if (!m_BGMOption->GetOperateOption())//オプション非表示時
				Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
			else if (m_BGMOption->GetOperateOption())//オプション表示時
			{
				if (i == BG || i == FRAME)//BGと枠だけ表示
					Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Color[i]);
			}

		}

	}
	if (m_Mode == MODE_4)
		m_BGMOption->Draw();
}

/*=============================================================================================
	ゲームスタート
=============================================================================================*/
void Title::GameStart()
{
	static bool m_GameStart = false;

	if (m_GameStart)
	{

	}
}
