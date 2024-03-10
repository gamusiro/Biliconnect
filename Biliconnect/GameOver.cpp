/*=========================================================================
	Date : 2022/4/29(金)	GameOver.cpp
		Author : Mr.
		Update :
=========================================================================*/
#include "Movie.h"
#include "Input.h"

#include "GameOver.h"
#include "SEManager.h"
using namespace math;

/*=============================================================================================
	コンストラクタ
=============================================================================================*/
GameOver::GameOver()
	:m_Texture(new Texture())
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
GameOver::~GameOver()
{
	delete m_Texture;
}

/*=============================================================================================
	初期化処理
=============================================================================================*/
void GameOver::Init()
{
	m_Texture->Create("scenely01.jpg", 1, 1);

	//■BGとムーブちゃん
	m_Tex[BG].Create("result_bg.png", 1, 1);
	m_Pos[BG] = math::Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Vel[BG] = math::Float2(NULL, NULL);
	m_Size[BG] = math::Float2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Col[BG] = math::Float4(0.4f, 0.4f, 0.4f, 1.0f);

	m_Tex[ANIMATION].Create("all_2.png", 10, 5, 2);
	m_Pos[ANIMATION] = math::Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
	m_Vel[ANIMATION] = math::Float2(NULL, NULL);
	m_Size[ANIMATION] = math::Float2(SCREEN_WIDTH, SCREEN_HEIGHT);
	m_Col[ANIMATION] = math::Float4(0.5f, 0.5f, 0.5f, 1.0f);

	m_Tex[MC].Create("hit_piri03.png", 5, 2, 2);
	m_Tex[MC].SetStartUVPosition(math::Float2(2.0f / 5.0f, 1.0f));
	m_Pos[MC] = math::Float2(SCREEN_WIDTH * 0.5f + 400.0f, -750.0f - 22.0f * 200.0f);
	m_Vel[MC] = math::Float2(NULL, 10.0f);
	m_Size[MC] = math::Float2(200.0f, 200.0f);
	m_Col[MC] = math::Float4(1.2f, 1.2f, 1.2f, 1.0f);
	m_Bound[MC] = -20.0f;
	m_Gravity[MC] = 1.0f;
	m_MCJump = false;


	m_Tex[BG2].Create("Stage/stage3_1.png", 1, 1);
	m_Pos[BG2] = math::Float2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT);
	m_Vel[BG2] = math::Float2(NULL, NULL);
	m_Size[BG2] = math::Float2(SCREEN_WIDTH, SCREEN_HEIGHT * 0.5f);
	m_Col[BG2] = math::Float4(1.0f, 1.0f, 1.0f, 1.0f);
	m_Tex[BG2].SetStartUVPosition(Float2(1.0f, 0.5f));

	m_Tex[BG3].Create("Stage/stage3_1.png", 1, 1);
	m_Pos[BG3] = math::Float2(SCREEN_WIDTH * 0.5f, 0.0f);
	m_Vel[BG3] = math::Float2(NULL, NULL);
	m_Size[BG3] = math::Float2(SCREEN_WIDTH, SCREEN_HEIGHT * 0.5f);
	m_Col[BG3] = math::Float4(1.0, 1.0, 1.0, 1.0f);
	m_Tex[BG3].SetStartUVPosition(Float2(1.0f, 0.5f));

	//■RETRY　MENU
	//テクスチャ表示設定
	m_Tex[RETRY].Create("button.png", 3, 3);
	m_Vel[RETRY] = math::Float2(NULL, NULL);
	m_Size[RETRY] = math::Float2(760.0f * 0.8f, 145.0f);
	m_Col[RETRY] = math::Float4(1.0f, 1.0f, 1.0f, 1.0f);

	m_Tex[MENU].Create("button.png", 3, 3);
	m_Vel[MENU] = math::Float2(NULL, NULL);
	m_Size[MENU] = math::Float2(435.0f * 1.4f, 105.0f * 1.4f);
	m_Col[MENU] = math::Float4(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX; i++)
	{
		m_BlinkingFrame[i] = 0;
		m_GameOverPos[i] = NONE;


		//■GAMEOVERの設定
		if (i >= G && i <= R2)
		{
			//点滅
			m_BlinkingFrame[i] = i * 10;
			//バウンドする高さ
			m_Bound[i] = -20.0f;
			m_Gravity[i] = 1.0f;


			if (i <= E_1)
				m_GameOverPos[i] = UP;

			if (i >= O)
				m_GameOverPos[i] = DOWN;

			//GAMEとOVERのポジション
			if (m_GameOverPos[i] == UP)
			{
				StartPositionY[i] = -750.0f - i * 200;
			}

			if (m_GameOverPos[i] == DOWN)
				StartPositionY[i] = -500.0f - i * 200;

			//テクスチャ表示設定
			m_Tex[i].Create("gameover_tex.png", 4, 5);
			m_Tex[i].SetStartUVPosition(Float2((1.0f / 4.0f) * ((i - G) % 4), (1.0f / 5.0f) * ((i - G) / 4)));
			m_Vel[i] = math::Float2(NULL, 10.0f);
			m_Size[i] = math::Float2(250.0f, 250.0f);
			m_Col[i] = math::Float4(1.0f, 1.0f, 1.0f, 1.0f);
		}


	}

	//■各ポジション
	m_Pos[G] = math::Float2(300.0f, StartPositionY[G]);
	m_Pos[A] = math::Float2(550.0f, StartPositionY[A]);

	for (int i = M1; i <= M5; i++) {
		m_Pos[i] = math::Float2(800.0f, StartPositionY[i]);
	}

	m_Pos[E_1] = math::Float2(1050.0f, StartPositionY[E_1]);
	m_Pos[O] = math::Float2(300.0f, StartPositionY[O]);

	for (int i = V1; i <= V5; i++) {
		m_Pos[i] = math::Float2(550.0f, StartPositionY[i]);
	}

	m_Pos[E_2] = math::Float2(800.0f, StartPositionY[E_2]);
	m_Pos[R1] = math::Float2(1050.0f, StartPositionY[R1]);
	m_Pos[R2] = math::Float2(1050.0f, StartPositionY[R2]);

	m_Pos[RETRY] = math::Float2(1480.0f, 520.0f);
	m_Pos[MENU] = math::Float2(1500.0f, 680.0f);

	SEManager::Init();
	SEManager::Play(SOUND::GAMEOVER);

	PushB = false;
	m_FrameSinceToPushB = 0;

	//項目
	m_Select = S_RETRY;
}

/*=============================================================================================
	終了処理
=============================================================================================*/
void GameOver::Uninit()
{
	//シーンごとに1度だけ呼ぶ
	TextureManager::Unload();
	SoundManager::Unload();
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void GameOver::Update()
{
	//フレーム
	m_Frame++;

	//アニメーション更新
	m_Tex[ANIMATION].Update();
	m_Tex[MC].Update();

	for (int i = 0; i < MAX; i++)
	{
		if (i >= MC && i <= R2)
		{
			m_Pos[i] += m_Vel[i];
			m_Vel[i].y += m_Gravity[i];


			//加速
			if (m_Vel[i].y < 30.0f)
				m_Vel[i].y++;
			if (m_Vel[i].y > 30.0f)
				m_Vel[i].y = 30.0f;



			if (m_GameOverPos[i] == UP || i == MC)
			{
				if (m_Pos[i].y > 400.0f)
				{
					m_Pos[i].y = 400.0f;
					m_Vel[i].y = m_Bound[i];
					m_Bound[i] *= 0.8f;

					if (m_Bound[i] > 0.0f)
						m_Bound[i] = 0.0f;
				}
			}

			if (m_GameOverPos[i] == DOWN)
			{
				if (m_Pos[i].y > 650.0f)
				{
					m_Pos[i].y = 650.0f;
					m_Vel[i].y = m_Bound[i];
					m_Bound[i] *= 0.8f;

					if (m_Bound[i] > 0.0f)
						m_Bound[i] = 0.0f;
				}
			}
		}



	}


	if (m_Select == S_MENU)
	{
		m_Tex[MENU].SetStartUVPosition(math::Float2(0.0f, 0.66666666f));
		m_Tex[RETRY].SetStartUVPosition(math::Float2(0.33333333f, 0.33333333f));
	}

	if (m_Select == S_RETRY)
	{
		m_Tex[RETRY].SetStartUVPosition(math::Float2(0.0f, 0.33333333f));
		m_Tex[MENU].SetStartUVPosition(math::Float2(0.33333333f, 0.66666666f));
	}

	if (m_FrameSinceToPushB < 1)
	{
		//入力
		//下を押したら
		if (Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown())
		{

			if (m_Select == S_RETRY)
			{
				SEManager::Play(SOUND::CURSOR);
				m_Select = S_MENU;
			}
		}

		//上を押したら
		if (Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp())
		{
			if (m_Select == S_MENU)
			{
				m_Select = S_RETRY;
				SEManager::Play(SOUND::CURSOR);
			}
		}

		//B(決定)を押したら
		if (Controller::GetButtonTriggerB() && !PushB)
		{
			SEManager::Play(SOUND::DECISION);
			PushB = true;
		}
	}

	if (PushB)
	{
		m_FrameSinceToPushB++;
		if (m_Select == S_RETRY)
			m_Tex[RETRY].SetStartUVPosition(math::Float2(0.6666666f, 0.3333333f));

		if (m_Select == S_MENU)
			m_Tex[MENU].SetStartUVPosition(math::Float2(0.66666666f, 0.6666666f));


	}

		if (m_FrameSinceToPushB > 60)
		{
			if (Fade::GetState()) 
			{
				if (m_Select == S_RETRY)
				{
					PushB = true;
					Fade::Transition(SCENE_TYPE::GAME, FADE_TYPE::STAIR, nullptr, Float3(1.0f, 1.0f, 0.3f));
				}

				if (m_Select == S_MENU)
				{
					PushB = true;
					Fade::Transition(SCENE_TYPE::STAGE_SELECT, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
				}

			}
		}

	

}


/*=============================================================================================
	描画処理
=============================================================================================*/
void GameOver::Draw()
{
	for (int i = 0; i < MAX; i++)
	{
		m_BlinkingFrame[i]++;
		if (m_Select == S_RETRY)
		{
			if (i != RETRY && !(i >= G && i <= R2))
				Sprite::DrawCenter(m_Pos[i], m_Size[i], &m_Tex[i], m_Col[i]);
			if (i == RETRY)
				Sprite::DrawCenter(m_Pos[i], m_Size[i], &m_Tex[i],
					Float4(
						m_Col[i].x + sin(m_Frame * 0.08f) * 0.2f + 0.1f,
						m_Col[i].y + sin(m_Frame * 0.08f) * 0.2f + 0.1f,
						m_Col[i].z + sin(m_Frame * 0.08f) * 0.2f + 0.1f,
						m_Col[i].w)
				);

			if (i >= G && i <= R2)
			{
				Sprite::DrawCenter(m_Pos[i], m_Size[i], &m_Tex[i],
					Float4(
						m_Col[i].x + sin(m_BlinkingFrame[i] * 0.08f) * 0.2f + 0.3f,
						m_Col[i].y + sin(m_BlinkingFrame[i] * 0.08f) * 0.2f + 0.3f,
						m_Col[i].z + sin(m_BlinkingFrame[i] * 0.08f) * 0.2f + 0.3f,
						m_Col[i].w)
				);
			}

		}

		if (m_Select == S_MENU)
		{
			if (i != MENU && !(i >= G && i <= R2))
				Sprite::DrawCenter(m_Pos[i], m_Size[i], &m_Tex[i], m_Col[i]);
			if (i == MENU)
				Sprite::DrawCenter(m_Pos[i], m_Size[i], &m_Tex[i],
					Float4(
						m_Col[i].x + sin(m_Frame * 0.08f) * 0.2f + 0.1f,
						m_Col[i].y + sin(m_Frame * 0.08f) * 0.2f + 0.1f,
						m_Col[i].z + sin(m_Frame * 0.08f) * 0.2f + 0.1f,
						m_Col[i].w)
				);

			if (i >= G && i <= R2)
			{
				Sprite::DrawCenter(m_Pos[i], m_Size[i], &m_Tex[i],
					Float4(
						m_Col[i].x + sin(m_BlinkingFrame[i] * 0.08f) * 0.2f + 0.3f,
						m_Col[i].y + sin(m_BlinkingFrame[i] * 0.08f) * 0.2f + 0.3f,
						m_Col[i].z + sin(m_BlinkingFrame[i] * 0.08f) * 0.2f + 0.3f,
						m_Col[i].w)
				);
			}
		}
	}
}