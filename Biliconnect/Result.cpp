/*=========================================================================
	Date : 2021/12/21(火)	Result.h
		Author :
		Update :
=========================================================================*/
#include "Result.h"
#include "Button.h"
#include "Stage.h"
#include "SaveStage.h"
#include "SaveManager.h"
#include "SEManager.h"
#include "Volume.h"
using namespace math;



/*=============================================================================================
	コンストラクタ
=============================================================================================*/
Result::Result() : m_BGM(new BGM())
{
	for (int i = 0; i < MAX; i++)
	{
		m_Tex[i] = new Texture();
	}
	for (int i = 0; i < MA; i++)
	{
		m_BGEfTex[i] = new Texture();
	}
	this->Init();

	m_Data = SaveStage::Get(StageNum::Get());// Get
	m_Save = SaveManager::Get(StageNum::Get());// Get

	m_BGM->Load("result.wav");
	m_BGM->SetVolume(Volume::GetBGM() * MASTER_VOLUME);
	m_BGM->Play(-1);
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
Result::~Result()
{

}

/*=============================================================================================
	初期化処理
=============================================================================================*/
void Result::Init()
{
	int stagenum = StageNum::Get() % 10;

	//BG
	m_Tex[BG]->Create("resultBG.png", 1, 1);
	m_Size[BG] = math::Float2{ SCREEN_WIDTH,SCREEN_HEIGHT };
	m_Vel[BG] = math::Float2{ NULL,NULL };
	m_Pos[BG] = math::Float2{ SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f };
	m_Col[BG] = { 1.0f,1.0f,1.0f,1.0f };

	//エフェクト
	float reset = 60.0f;
	float HY = 0.0f;
	float HW = 0.0f;
	for (int i = 0; i < MA; i++)
	{
		if (i % 33 == 0)
			HW = 0.0f;
		if (i % 33 == 0)
			HY++;
		HW++;
		m_BGEfTex[i]->Create("result_bg.png", 1, 1);
		m_BGEfSize[i] = math::Float2{ reset,reset };
		m_BGEfPos[i] = math::Float2{ 0.0f + HW * reset - reset ,0.0f + HY * reset - reset };
		m_BGEfCol[i] = { 1.0f,1.0f,1.0f,0.2f };
		m_Step[i] = rand() % 30;
	}

	//バインダー
	m_Tex[BINDER]->Create("binder.png", 1, 1);
	m_Size[BINDER] = math::Float2{ 1000.0f,1050.0f };
	m_Vel[BINDER] = math::Float2{ NULL,200.0f };
	m_Pos[BINDER] = math::Float2{ 500.0f,SCREEN_HEIGHT + m_Size[BINDER].y };
	m_Col[BINDER] = { 1.0f,1.0f,1.0f,1.0f };

	//メニュー
	m_Tex[T_MENU]->Create("button02.png", 3, 1);
	m_Tex[T_MENU]->SetStartUVPosition(math::Float2(0.0f, 0.0f));
	m_Size[T_MENU] = math::Float2{ 670.0f * 0.8f,180.0f * 0.8f };
	m_Vel[T_MENU] = math::Float2{ NULL,NULL };
	m_Pos[T_MENU] = math::Float2{ 450.0f,SCREEN_HEIGHT - m_Size[T_MENU].y + 40.0f };
	m_Col[T_MENU] = { 1.0f,1.0f,1.0f,0.0f };

	//ネクスト
	m_Tex[T_NEXT]->Create("button.png", 3, 3);
	m_Tex[T_NEXT]->SetStartUVPosition(math::Float2(0.0f, 0.0f));
	m_Size[T_NEXT] = math::Float2{ 771.0f,185.0f };
	m_Vel[T_NEXT] = math::Float2{ NULL,NULL };
	m_Pos[T_NEXT] = math::Float2{ 1450.0f,SCREEN_HEIGHT - m_Size[T_NEXT].y - 150.0f };
	m_Col[T_NEXT] = { 1.0f,1.0f,1.0f,0.0f };

	//リトライ
	m_Tex[T_RETRY]->Create("button.png", 3, 3);
	m_Tex[T_RETRY]->SetStartUVPosition(math::Float2(0.0f, 0.0f));
	m_Size[T_RETRY] = math::Float2{ 771.0f,185.0f };
	m_Vel[T_RETRY] = math::Float2{ NULL,NULL };
	m_Pos[T_RETRY] = math::Float2{ 1450.0f,SCREEN_HEIGHT - m_Size[T_RETRY].y + 40.0f };
	m_Col[T_RETRY] = { 1.0f,1.0f,1.0f,0.0f };

	// 敵の数
	m_Tex[ENEMY_2]->Create("result_bar.png", 1, 1);
	m_Size[ENEMY_2] = math::Float2{ SIZE_X - 1.0f,SIZE_Y };
	m_Vel[ENEMY_2] = math::Float2{ NULL,NULL };
	m_Pos[ENEMY_2] = math::Float2{ 522.0f, 440.f };
	m_Col[ENEMY_2] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[ENEMY]->Create("result_bar.png", 1, 1);
	//m_Size[ENEMY] = math::Float2{ (SIZE_X * m_Data.kill) / m_Data.enemymax,SIZE_Y };
	//m_Size[ENEMY] = math::Float2{ (SIZE_X * 1.0f) / 1,SIZE_Y };
	m_Size[ENEMY] = math::Float2{ 0.0f,SIZE_Y };
	m_Vel[ENEMY] = math::Float2{ NULL,NULL };
	m_Pos[ENEMY] = math::Float2{ 262.0f, 430.f };
	m_Col[ENEMY] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[ZERO]->Create("o_font.png", 1, 1);
	m_Size[ZERO] = math::Float2{ 600.0f * 0.5f, 200.0f * 0.5f };
	m_Vel[ZERO] = math::Float2{ NULL,NULL };
	m_Pos[ZERO] = math::Float2{ 365.0f,440.0f };
	m_Col[ZERO] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[E_MAX]->Create("max_font.png", 1, 1);
	m_Size[E_MAX] = math::Float2{ 600.0f * 0.4f, 200.0f * 0.4f };
	m_Vel[E_MAX] = math::Float2{ NULL,NULL };
	m_Pos[E_MAX] = math::Float2{ 905.0f,438.0f };
	m_Col[E_MAX] = { 1.0f,1.0f,1.0f,0.0f };
	// ファイル
	if (stagenum == 0)
		m_Tex[FILE]->Create("File/book_file_icon.png", 1, 1);
	else if (stagenum == 1)
		m_Tex[FILE]->Create("File/cloud_file_icon.png", 1, 1);
	else if (stagenum == 2)
		m_Tex[FILE]->Create("File/document_file_icon.png", 1, 1);
	else if (stagenum == 3)
		m_Tex[FILE]->Create("File/download_file_icon.png", 1, 1);
	else if (stagenum == 4)
		m_Tex[FILE]->Create("File/game_file_icon.png", 1, 1);
	else if (stagenum == 5)
		m_Tex[FILE]->Create("File/movie_file_icon.png", 1, 1);
	else if (stagenum == 6)
		m_Tex[FILE]->Create("File/music_file_icon.png", 1, 1);
	else if (stagenum == 7)
		m_Tex[FILE]->Create("File/picture_file_icon.png", 1, 1);
	else if (stagenum == 8)
		m_Tex[FILE]->Create("File/screen_file_icon.png", 1, 1);
	else if (stagenum == 9)
		m_Tex[FILE]->Create("File/zip_file_icon.png", 1, 1);

	m_Size[FILE] = math::Float2{ 140, 140 };
	m_Vel[FILE] = math::Float2{ NULL,NULL };
	m_Pos[FILE] = math::Float2{ 680.0f, 605.f };
	m_Col[FILE] = { 0.3f,0.3f,0.3f,0.0f };

	// フォルダ
	m_Tex[FOLDER]->Create("File/file_icon.png", 1, 1);
	m_Size[FOLDER] = math::Float2{ 140, 140 };
	m_Vel[FOLDER] = math::Float2{ NULL,NULL };
	m_Pos[FOLDER] = math::Float2{ 680.0f, 610.f };
	m_Col[FOLDER] = { 0.3f,0.3f,0.3f,0.0f };

	// ライフ
	m_Tex[LIFE_1]->Create("life.png", 1, 1);
	m_Size[LIFE_1] = math::Float2{ 140 * 0.8f, 140 * 0.8f };
	m_Vel[LIFE_1] = math::Float2{ NULL,NULL };
	m_Pos[LIFE_1] = math::Float2{ 570.0f, 780.f };
	m_Col[LIFE_1] = { 0.3f,0.3f,0.3f,0.0f };

	m_Tex[LIFE_2]->Create("life.png", 1, 1);
	m_Size[LIFE_2] = math::Float2{ 140 * 0.8f, 140 * 0.8f };
	m_Vel[LIFE_2] = math::Float2{ NULL,NULL };
	m_Pos[LIFE_2] = math::Float2{ 570.0f + 140 * 0.8f, 780.f };
	m_Col[LIFE_2] = { 0.3f,0.3f,0.3f,0.0f };

	m_Tex[LIFE_3]->Create("life.png", 1, 1);
	m_Size[LIFE_3] = math::Float2{ 140 * 0.8f , 140 * 0.8f };
	m_Vel[LIFE_3] = math::Float2{ NULL,NULL };
	m_Pos[LIFE_3] = math::Float2{ 570.0f + (140 * 0.8f) * 2.0f, 780.0f };
	m_Col[LIFE_3] = { 0.3f,0.3f,0.3f,0.0f };

	//チェック
	m_Tex[CHECK_1]->Create("check.png", 1, 1);
	m_Size[CHECK_1] = math::Float2{ 100.0f,100.0f };
	m_Vel[CHECK_1] = math::Float2{ NULL,NULL };
	m_Pos[CHECK_1] = math::Float2{ 165.0f,SCREEN_HEIGHT - m_Size[T_RETRY].y - 420.0f };
	m_Col[CHECK_1] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[CHECK_2] = m_Tex[CHECK_1];
	m_Size[CHECK_2] = m_Size[CHECK_1];
	m_Vel[CHECK_2] = m_Vel[CHECK_1];
	m_Pos[CHECK_2] = math::Float2{ 165.0f,SCREEN_HEIGHT - m_Size[T_RETRY].y - 250.0f };
	m_Col[CHECK_2] = m_Col[CHECK_1];

	m_Tex[CHECK_3] = m_Tex[CHECK_1];
	m_Size[CHECK_3] = m_Size[CHECK_1];
	m_Vel[CHECK_3] = m_Vel[CHECK_1];
	m_Pos[CHECK_3] = math::Float2{ 165.0f,SCREEN_HEIGHT - m_Size[T_RETRY].y - 80.0f };
	m_Col[CHECK_3] = m_Col[CHECK_1];

	//モザイク
	m_Tex[MOSAIC_1]->Create("mosaic.png", 1, 1);
	m_Size[MOSAIC_1] = math::Float2{ 400.0f,50.0f };
	m_Vel[MOSAIC_1] = math::Float2{ NULL,NULL };
	m_Pos[MOSAIC_1] = math::Float2{ 420.0f,485.0f };
	m_Col[MOSAIC_1] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[MOSAIC_2] = m_Tex[MOSAIC_1];
	m_Size[MOSAIC_2] = math::Float2{ 295.0f,140.0f };
	m_Vel[MOSAIC_2] = math::Float2{ NULL,NULL };
	m_Pos[MOSAIC_2] = math::Float2{ 365.0f,610.0f };
	m_Col[MOSAIC_2] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[MOSAIC_3] = m_Tex[MOSAIC_1];
	m_Size[MOSAIC_3] = math::Float2{ 295.0f,140.0f };
	m_Vel[MOSAIC_3] = math::Float2{ NULL,NULL };
	m_Pos[MOSAIC_3] = math::Float2{ 365.0f,785.0f };
	m_Col[MOSAIC_3] = { 1.0f,1.0f,1.0f,0.0f };

	//文字
	m_Tex[CHAR_ENEMY]->Create("allenemy_font.png", 1, 1);
	m_Size[CHAR_ENEMY] = math::Float2{ 600.0f * 0.63f,200.0f * 0.63f };
	m_Vel[CHAR_ENEMY] = math::Float2{ NULL,NULL };
	m_Pos[CHAR_ENEMY] = math::Float2{ 415.0f,485.0f };
	m_Col[CHAR_ENEMY] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[CHAR_ALLITEM]->Create("allitem_font.png", 1, 1);
	m_Size[CHAR_ALLITEM] = math::Float2{ 600.0f * 0.5f,200.0f * 0.5f };
	m_Vel[CHAR_ALLITEM] = math::Float2{ NULL,NULL };
	m_Pos[CHAR_ALLITEM] = math::Float2{ 370.0f,658.0f };
	m_Col[CHAR_ALLITEM] = { 1.0f,1.0f,1.0f,0.0f };

	m_Tex[CHAR_MAXLIFE]->Create("maxlife_font.png", 1, 1);
	m_Size[CHAR_MAXLIFE] = math::Float2{ 600.0f * 0.5f,200.0f * 0.5f };
	m_Vel[CHAR_MAXLIFE] = math::Float2{ NULL,NULL };
	m_Pos[CHAR_MAXLIFE] = math::Float2{ 370.0f,830.0f };
	m_Col[CHAR_MAXLIFE] = { 1.0f,1.0f,1.0f,0.0f };

	m_Frame = 0;

	if (StageNum::Get() != 24)
		m_Select = NEXT;
	else
		m_Select = MENU;

	for (int i = 0; i < 3; i++)
	{
		m_SetCheck[i] = false;
	}

	m_ButtonFrame = 260;
	//m_ButtonFrame = 340;
	m_Quick = false;
	if (m_Data.kill == m_Data.enemymax)
		SetCheck(1, 0, 0);
	if (m_Data.coin == 3)
		SetCheck(0, 1, 0);
	if (m_Data.life == 3)
		SetCheck(0, 0, 1);

	if (m_Quick)
		m_ButtonFrame = 230;

	SEManager::Init();

	PushB = false;
	m_FrameSinceToPushB = 0;

	for (int i = 0; i < 3; i++)
	{
		m_QuickCheck[i] = false;
	}


}

/*=============================================================================================
	終了処理
=============================================================================================*/
void Result::Uninit()
{
	// セーブデータ更新
	if (m_Data.life > m_Save.life)
		m_Save.life = m_Data.life;

	if (m_Data.coin > m_Save.coin)
		m_Save.coin = m_Data.coin;

	if (m_Data.kill == m_Data.enemymax)
		m_Save.kill = 1;

	if(m_Select == NEXT)
		SaveManager::Set(StageNum::Get() - 1, m_Save);// Get
	else
		SaveManager::Set(StageNum::Get(), m_Save);// Get

	TextureManager::Unload();
	SoundManager::Unload();
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void Result::Update()
{
	m_Frame++;

	const int AppearFrame = 60;
	//バインダー
	if (m_Frame > AppearFrame)
	{
		//移動
		m_Pos[BINDER].y -= m_Vel[BINDER].y;
		if (m_Frame > 61)
			m_Vel[BINDER].y *= 0.85f;
	}
	if (m_Frame == AppearFrame)
		SEManager::Play(SOUND::PAGE);

	if (m_Frame == AppearFrame + 40)
		SEManager::Play(SOUND::PENKATU);

	if (m_Frame == AppearFrame + 290 && m_Data.life == 3
		&& m_Data.coin == 3 && m_Data.kill == m_Data.enemymax)
		SEManager::Play(SOUND::CLEAR2);
	/*else if (m_Frame == 10)
		SEManager::Play(SOUND::CLEAR);*/

	if (m_Frame == AppearFrame + 280 && (m_Frame == 0 || m_Data.life == 3
		|| m_Data.coin == 3 || m_Data.kill == m_Data.enemymax))
		SEManager::Play(SOUND::PEN);

	if (m_QuickCheck[0]&& m_QuickCheck[1])
	{

		//チェック1
		if (m_Frame > AppearFrame )
		{
			if (m_SetCheck[0])
			{
				//チェック1フェード
				if (m_Col[CHECK_1].w < 1.0f)
					m_Col[CHECK_1].w += 0.1f;
			}
		}

		//チェック2
		if (m_Frame > AppearFrame+20)
		{
			if (m_SetCheck[1])
			{
				//チェック2フェード
				if (m_Col[CHECK_2].w < 1.0f)
					m_Col[CHECK_2].w += 0.1f;
			}
		}

		//チェック3
		if (m_Frame > AppearFrame+40)
		{
			if (m_SetCheck[2])
			{
				//チェック3フェード
				if (m_Col[CHECK_3].w < 1.0f)
					m_Col[CHECK_3].w += 0.1f;
			}
		}
	}

	//敵の数
	if (m_Frame > AppearFrame + 130)
	{
		if (m_Col[ENEMY].w < 1.0f)
			m_Col[ENEMY].w += 0.1f;

		if (m_Col[ENEMY_2].w < 0.5f)
			m_Col[ENEMY_2].w += 0.1f;

		if (m_Col[ZERO].w < 1.0f)
			m_Col[ZERO].w += 0.1f;

		if (m_Col[E_MAX].w < 1.0f)
			m_Col[E_MAX].w += 0.1f;
	}
	if (m_Frame > AppearFrame + 180)
	{
	
		if (m_Size[ENEMY].x < (SIZE_X * m_Data.kill) / m_Data.enemymax)
			m_Size[ENEMY].x += 5.0f;

		//チェックの早出し判定
		if (m_Size[ENEMY].x >= (SIZE_X * m_Data.kill) / m_Data.enemymax)
			m_QuickCheck[0] = true;

	}

	//ファイル/フォルダ
	if (m_Frame > AppearFrame + 150)
	{
		if (m_Col[FOLDER].w < 1.0f)
			m_Col[FOLDER].w += 0.1f;
	}
	if (m_Frame > AppearFrame + 160)
	{
		if (m_Col[FILE].w < 1.0f)
			m_Col[FILE].w += 0.1f;
	}
	if (m_Frame > AppearFrame + 180 && (m_Data.coin == 3 || m_Data.coin == 2))
	{
		//ファイル
		if (m_Col[FILE].x < 1.0f)
		{
			m_Col[FILE].x += 0.1f;
			m_Col[FILE].y += 0.1f;
			m_Col[FILE].z += 0.1f;
		}
	}

	//フォルダ
	if (m_Frame > AppearFrame + 200 && (m_Data.coin == 3 || m_Data.coin == 1))
	{
		//フォルダー
		if (m_Col[FOLDER].x < 1.0f)
		{
			m_Col[FOLDER].x += 0.1f;
			m_Col[FOLDER].y += 0.1f;
			m_Col[FOLDER].z += 0.1f;
		}
	}

	//ライフ
	 if (m_Frame > AppearFrame+170)
	 {		 
		 if (m_Col[LIFE_1].w < 1.0f)
			m_Col[LIFE_1].w += 0.1f;

		 if (m_Col[LIFE_2].w < 1.0f)
			 m_Col[LIFE_2].w += 0.1f;

		 if (m_Col[LIFE_3].w < 1.0f)
			 m_Col[LIFE_3].w += 0.1f;
	 }

	if (m_Frame > AppearFrame + 210 && m_Data.life > 0)
	{
		if (m_Col[LIFE_1].x < 1.0f)
		{
			m_Col[LIFE_1].x += 0.1f;
			m_Col[LIFE_1].y += 0.1f;
			m_Col[LIFE_1].z += 0.1f;
		}

		if (m_Col[LIFE_1].x >= 1.0f && m_Data.life == 1)
		{
			m_QuickCheck[1] = true;
		}
	}
	if (m_Frame > AppearFrame + 240 && m_Data.life > 1)
	{


		if (m_Col[LIFE_2].x < 1.0f)
		{
			m_Col[LIFE_2].x += 0.1f;
			m_Col[LIFE_2].y += 0.1f;
			m_Col[LIFE_2].z += 0.1f;
		}

		if (m_Col[LIFE_2].x >= 1.0f && m_Data.life == 2)
		{
			m_QuickCheck[1] = true;
		}
	}
	if (m_Frame > AppearFrame + 270 && m_Data.life > 2)
	{
		if (m_Col[LIFE_3].x < 1.0f)
		{
			m_Col[LIFE_3].x += 0.1f;
			m_Col[LIFE_3].y += 0.1f;
			m_Col[LIFE_3].z += 0.1f;
		}

		if (m_Col[LIFE_3].x >= 1.0f && m_Data.life == 3)
		{
			m_QuickCheck[1] = true;
		}
	}

	//モザイク1
	if (m_Frame > AppearFrame +40)
	{
		//モザイク1フェード
			m_Col[MOSAIC_1].w = 1.0f;

		//モザイク1縮小
		if (m_Frame > AppearFrame + 50)
		{
			float spd = 15.0f;
			m_Size[MOSAIC_1].x -= spd;
			m_Pos[MOSAIC_1].x += spd * 0.5f;
		}
	}

	//モザイク2
	if (m_Frame > AppearFrame + 40)
	{
		//モザイク2フェード
		m_Col[MOSAIC_2].w = 1.0f;

		//モザイク2縮小
		if (m_Frame > AppearFrame + 70)
		{
			float spd = 15.0f;
			m_Size[MOSAIC_2].x -= spd;
			m_Pos[MOSAIC_2].x += spd * 0.5f;
		}
	}

	//モザイク3
	if (m_Frame > AppearFrame + 40)
	{
		//モザイク2フェード
		m_Col[MOSAIC_3].w = 1.0f;

		//モザイク2縮小
		if (m_Frame > AppearFrame + 90)
		{
			float spd = 15.0f;
			m_Size[MOSAIC_3].x -= spd;
			m_Pos[MOSAIC_3].x += spd * 0.5f;
		}
	}

	//文字の表示
	if (m_Frame > AppearFrame + 40)
	{
		if (m_Col[CHAR_ENEMY].w < 1.0f)
			m_Col[CHAR_ENEMY].w += 1.0f;
	
		if (m_Col[CHAR_ALLITEM].w < 1.0f)
		m_Col[CHAR_ALLITEM].w += 1.0f;
	
		if (m_Col[CHAR_MAXLIFE].w < 1.0f)
		m_Col[CHAR_MAXLIFE].w += 1.0f;
	}
	

	//ボタンの処理
	if (m_Frame > AppearFrame + m_ButtonFrame)
	{
		//メニューフェード
		if (m_Col[T_MENU].w < 1.0f)
			m_Col[T_MENU].w += 0.1f;
	}

	if (StageNum::Get() != 24)
	{
		if (m_Frame > AppearFrame + m_ButtonFrame)
		{
			//ネクストフェード
			if (m_Col[T_NEXT].w < 1.0f)
				m_Col[T_NEXT].w += 0.1f;
		}
	}

	if (m_Frame > AppearFrame + m_ButtonFrame)
	{
		//リトライフェード
		if (m_Col[T_RETRY].w < 1.0f)
			m_Col[T_RETRY].w += 0.1f;

	}

	if (!PushB && m_Frame > AppearFrame + m_ButtonFrame)
	{
		if (Fade::GetState())
		{
			//選択項目
			//上を押したら
			if (StageNum::Get() != 24)
			{
				if (Controller::GetButtonTriggerUp() || Controller::GetLStickTriggerUp())
				{
					if (m_Select == MENU)
					{
						SEManager::Play(SOUND::CURSOR);
						m_Select = RETRY;
					}

					if (m_Select == RETRY)
					{
						SEManager::Play(SOUND::CURSOR);
						m_Select = NEXT;
					}
				}

				//下を押したら
				if (Controller::GetButtonTriggerDown() || Controller::GetLStickTriggerDown())
				{
					
					if (m_Select == NEXT)
					{
						SEManager::Play(SOUND::CURSOR);
						m_Select = RETRY;
					}
				}
			}

			//右を押したら
			if (Controller::GetButtonTriggerRight() || Controller::GetLStickTriggerRight())
			{
				if (m_Select == MENU)
				{
					SEManager::Play(SOUND::CURSOR);
					m_Select = RETRY;
				}
			}

			//左を押したら
			if (Controller::GetButtonTriggerLeft() || Controller::GetLStickTriggerLeft())
			{
				if (m_Select == RETRY)
				{
					SEManager::Play(SOUND::CURSOR);
					m_Select = MENU;
				}

				if (m_Select == NEXT)
				{
					SEManager::Play(SOUND::CURSOR);
					m_Select = MENU;
				}
			}
		}
	}

	//ボタンが押されるとカウント開始
	if (PushB)
	{
		m_FrameSinceToPushB++;

		if (m_FrameSinceToPushB > 20)
		{
			PushB = false;

			if (m_Select == RETRY && Fade::GetState())
			{
				Fade::Transition(SCENE_TYPE::GAME, FADE_TYPE::STAIR, m_BGEfTex[0], Float3(1, 1, 0.3f));
			}
			if (m_Select == MENU && Fade::GetState())
			{

				Fade::Transition(SCENE_TYPE::STAGE_SELECT, FADE_TYPE::STAIR, m_BGEfTex[0], { 195.0f / 255.0f, 99.0f / 255.0f, 255.0f / 255.0f });
			}
			if (m_Select == NEXT && Fade::GetState())
			{
				if (StageNum::Get() == 25)
					StageNum::Set(0);
				else if (StageNum::Get() != 24)
					StageNum::Set(StageNum::Get() + 1);

				Fade::Transition(SCENE_TYPE::GAME, FADE_TYPE::CHAN, m_BGEfTex[0], Float3(1, 1, 0.3f));
			}
		}
	}
	else if (Controller::GetButtonTriggerB() && Fade::GetState() && !PushB && m_Frame > AppearFrame + m_ButtonFrame)
	{
		PushB = true;
		m_FrameSinceToPushB = 0;
		SEManager::Play(SOUND::DECISION);
	}
}

/*=============================================================================================
	描画処理
=============================================================================================*/
void Result::Draw()
{
	printf("%d", m_Save.coin);
	printf("%d", m_Data.coin);
	printf("%d", PushB);
	printf("%d", m_FrameSinceToPushB);

	//BG
	Sprite::DrawCenter(m_Pos[BG], m_Size[BG], m_Tex[BG], m_Col[BG]);
	//BGエフェクト
	for (int i = 0; i < MA; i++)
	{
		float CC = (float)(sin((m_Frame + m_Step[i] * 30) * 0.1f) * 0.1f);
	}

	for (int i = BINDER; i < MAX; i++)
	{
		float CC = (float)(sin(m_Frame * 0.1f) * 0.1f);


		if (i == ENEMY)
		{
			Sprite::DrawLeftTop(m_Pos[i], m_Size[i], m_Tex[i],
				Float4(m_Col[i].x, m_Col[i].y, m_Col[i].z, m_Col[i].w));
		}

		if (m_Select == MENU)
		{
			m_Tex[T_MENU]->SetStartUVPosition(math::Float2(0.0f, 0.0f));
			m_Tex[T_RETRY]->SetStartUVPosition(math::Float2(1.0f/3.0f, 1.0f/3.0f));
			m_Tex[T_NEXT]->SetStartUVPosition(math::Float2(1.0f/3.0f, 0.0f));

			if (PushB)
			{
				m_Tex[T_MENU]->SetStartUVPosition(math::Float2(0.66666666f, 0.0f));
			}

			if ((i == T_MENU) && i != ENEMY)
			{
				Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i],
					Float4(m_Col[i].x + CC, m_Col[i].y + CC, m_Col[i].z + CC, m_Col[i].w));
			}
			else if(i != ENEMY)
			{
				Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Col[i]);
			}

		}
		else
			if (m_Select == RETRY)
			{
				m_Tex[T_RETRY]->SetStartUVPosition(math::Float2(0.0f, 1.0f/3.0f));
				m_Tex[T_MENU]->SetStartUVPosition(math::Float2(1.0f/3.0f, 0.0f));
				m_Tex[T_NEXT]->SetStartUVPosition(math::Float2(1.0f/3.0f, 0.0f));

				if (PushB)
				{
					m_Tex[T_RETRY]->SetStartUVPosition(math::Float2(0.66666666f, 1.0f/3.0f));
				}

				if ((i == T_RETRY) && i != ENEMY)
				{
					Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i],
						Float4(m_Col[i].x + CC, m_Col[i].y + CC, m_Col[i].z + CC, m_Col[i].w));
				}
				else if (i != ENEMY)
				{
					Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Col[i]);
				}
			}
			else
				if (m_Select == NEXT)
				{

					m_Tex[T_NEXT]->SetStartUVPosition(math::Float2(0.0f, 0.0f));
					m_Tex[T_RETRY]->SetStartUVPosition(math::Float2(1.0f/3.0f, 1.0f/3.0f));
					m_Tex[T_MENU]->SetStartUVPosition(math::Float2(1.0f/3.0f, 0.0f));

					if (PushB)
					{
						m_Tex[T_NEXT]->SetStartUVPosition(math::Float2(0.66666666f, 0.0f));
					}

					if ((i == T_NEXT) && i != ENEMY)
					{
						Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i],
							Float4(m_Col[i].x + CC, m_Col[i].y + CC, m_Col[i].z + CC, m_Col[i].w));
					}
					else if (i != ENEMY)
					{
						Sprite::DrawCenter(m_Pos[i], m_Size[i], m_Tex[i], m_Col[i]);
					}
				}
	}



}

/*=============================================================================================
   チェックのセット
=============================================================================================*/
void Result::SetCheck(bool c1, bool c2, bool c3)
{
	if (c1)
		m_SetCheck[0] = true;
	if (c2)
		m_SetCheck[1] = true;
	if (c3)
		m_SetCheck[2] = true;
	
	if(!c1&& !c2&& !c3)
		m_Quick = true;
}

