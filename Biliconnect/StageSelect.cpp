#include "StageSelect.h"
#include "Stage.h"
#include "SEManager.h"
#include "Volume.h"

using namespace math;

StageSelect::StageSelect()
{
	//if (m_Row == -1)
	//{
	//	m_Row = 0;
	//	m_Column = 0;
	//}
	//else
	//{
	//	m_Column = StageNum::Get() % 5;
	//	m_Row = StageNum::Get() / 5;
	//}

	trigger = false;
	timer = 0;
	m_BGM = new BGM;

	for (int i = 0; i < MAX; i++)
	{
		m_Tex[i] = new Texture;
	}

	for (int i = 0; i < STAGE_TEX_MAX; i++)
	{
		m_StageTex[i] = new Texture();
	}

	for (int i = 0; i < CLEAR_MAX; i++)
	{
		m_ClearTex[i] = new Texture();
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_EnemyTex[i] = new Texture();
	}

	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_ItemTex[i] = new Texture();
	}

	for (int i = 0; i < LIFE_MAX; i++)
	{
		m_LifeTex[i] = new Texture();
	}


}

StageSelect::~StageSelect()
{
	for (int i = 0; i < MAX; i++)
	{
		delete m_Tex[i];
	}
}

void StageSelect::Init()
{
	this->CreateStageTex();

	m_Tex[BG]->Create("StageSelect/haikei_1.png", 1, 1);
	m_Pos[BG] = { SCREEN_WIDTH * 0.5f,SCREEN_HEIGHT * 0.5f };
	m_Vel[BG] = { 0.0f, 0.0f };
	m_Size[BG] = { SCREEN_WIDTH,SCREEN_HEIGHT };
	m_Use[BG] = true;
	m_Color[BG] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[FRAME]->Create("Option/option_ground.png", 1, 1);
	m_Pos[FRAME] = { SCREEN_WIDTH - 200.0f,SCREEN_HEIGHT - 270.0f };
	m_Vel[FRAME] = { 0.0f, 0.0f };
	m_Size[FRAME] = { 320.0f,320.0f };
	m_Use[FRAME] = false;
	m_Color[FRAME] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[BACK]->Create("Button/back_title_2.png", 3, 1);
	m_Tex[BACK]->SetStartUVPosition(Float2((1.0f / 3.0f) * 0.0f, 1.0f));
	m_Pos[BACK] = { SCREEN_WIDTH - 200.0f,SCREEN_HEIGHT - 200.0f };
	m_Vel[BACK] = { 0.0f, 0.0f };
	m_Size[BACK] = { 200.0f,200.0f };
	m_Use[BACK] = true;
	m_Color[BACK] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[TUTORIAL_FRAME]->Create("Option/option_ground.png", 1, 1);
	m_Tex[TUTORIAL_FRAME]->SetStartUVPosition(Float2((1.0f / 3.0f) * 0.0f, 1.0f));
	m_Pos[TUTORIAL_FRAME] = { 250.0f,SCREEN_HEIGHT - 150.0f };
	m_Vel[TUTORIAL_FRAME] = { 0.0f, 0.0f };
	m_Size[TUTORIAL_FRAME] = { 600.0f * 0.9f,200.0f * 0.9f };
	m_Use[TUTORIAL_FRAME] = false;
	m_Color[TUTORIAL_FRAME] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[TUTORIAL]->Create("Button/tutorial_icon.png", 3, 1);
	m_Tex[TUTORIAL]->SetStartUVPosition(Float2((1.0f / 3.0f) * 0.0f, 1.0f));
	m_Pos[TUTORIAL] = { 240.0f,SCREEN_HEIGHT - 170.0f };
	m_Vel[TUTORIAL] = { 0.0f, 0.0f };
	m_Size[TUTORIAL] = { 600.0f * 0.7f,200.0f * 0.7f };
	m_Use[TUTORIAL] = true;
	m_Color[TUTORIAL] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[TRIANGLE_LEFT]->Create("StageSelect/l_logo.png", 1, 1);
	m_Pos[TRIANGLE_LEFT] = { SCREEN_WIDTH * 0.5f - 590.0f,150.0f };
	m_Vel[TRIANGLE_LEFT] = { 0.0f, 0.0f };
	m_Size[TRIANGLE_LEFT] = { 300.0f,300.0f };
	m_Use[TRIANGLE_LEFT] = true;
	m_Color[TRIANGLE_LEFT] = { 0.7f,0.7f, 0.7f, 1.0f };

	m_Tex[TRIANGLE_RIGHT]->Create("StageSelect/r_logo.png", 1, 1);
	m_Pos[TRIANGLE_RIGHT] = { SCREEN_WIDTH * 0.5f + 800.0f,150.0f };
	m_Vel[TRIANGLE_RIGHT] = { 0.0f, 0.0f };
	m_Size[TRIANGLE_RIGHT] = { 300.0f,300.0f };
	m_Use[TRIANGLE_RIGHT] = true;
	m_Color[TRIANGLE_RIGHT] = { 0.7f,0.7f, 0.7f, 1.0f };

	m_Tex[MOSAIC]->Create("StageSelect/mosaic.png", 1, 1);
	m_Pos[MOSAIC] = { SCREEN_WIDTH * 0.5f + 40.0f,155.0f };
	m_Vel[MOSAIC] = { 0.0f, 0.0f };
	m_Size[MOSAIC] = { 650.0f,90.0f };
	m_Use[MOSAIC] = false;
	m_Color[MOSAIC] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[T_AREA_1]->Create("StageSelect/Area/virus_1.png", 1, 1);
	m_Pos[T_AREA_1] = { SCREEN_WIDTH * 0.5f + 110.0f,150.0f };
	m_Vel[T_AREA_1] = { 0.0f, 0.0f };
	m_Size[T_AREA_1] = { 600.0f * 1.8f,200.0f * 1.8f };
	m_Use[T_AREA_1] = true;
	m_Color[T_AREA_1] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[T_AREA_2]->Create("StageSelect/Area/virus_2.png", 1, 1);
	m_Pos[T_AREA_2] = { SCREEN_WIDTH * 0.5f + 110.0f,150.0f };
	m_Vel[T_AREA_2] = { 0.0f, 0.0f };
	m_Size[T_AREA_2] = { 600.0f * 1.8f,200.0f * 1.8f };
	m_Use[T_AREA_2] = true;
	m_Color[T_AREA_2] = { 1.0f,1.0f, 1.0f, 0.0f };

	m_Tex[T_AREA_3]->Create("StageSelect/Area/virus_3.png", 1, 1);
	m_Pos[T_AREA_3] = { SCREEN_WIDTH * 0.5f + 110.0f,150.0f };
	m_Vel[T_AREA_3] = { 0.0f, 0.0f };
	m_Size[T_AREA_3] = { 600.0f * 1.8f,200.0f * 1.8f };
	m_Use[T_AREA_3] = true;
	m_Color[T_AREA_3] = { 1.0f,1.0f, 1.0f, 0.0f };

	m_Tex[T_AREA_4]->Create("StageSelect/Area/virus_4.png", 1, 1);
	m_Pos[T_AREA_4] = { SCREEN_WIDTH * 0.5f + 110.0f,150.0f };
	m_Vel[T_AREA_4] = { 0.0f, 0.0f };
	m_Size[T_AREA_4] = { 600.0f * 1.8f,200.0f * 1.8f };
	m_Use[T_AREA_4] = true;
	m_Color[T_AREA_4] = { 1.0f,1.0f, 1.0f, 0.0f };

	m_Tex[T_AREA_5]->Create("StageSelect/Area/virus_5.png", 1, 1);
	m_Pos[T_AREA_5] = { SCREEN_WIDTH * 0.5f + 110.0f,150.0f };
	m_Vel[T_AREA_5] = { 0.0f, 0.0f };
	m_Size[T_AREA_5] = { 600.0f * 1.8f,200.0f * 1.8f };
	m_Use[T_AREA_5] = true;
	m_Color[T_AREA_5] = { 1.0f,1.0f, 1.0f, 0.0f };

	m_Tex[CHECK]->Create("chan.png", 1, 1);
	m_Pos[CHECK] = { SCREEN_WIDTH * 0.5f ,SCREEN_HEIGHT * 0.5f };
	m_Vel[CHECK] = { 0.0f, 0.0f };
	m_Size[CHECK] = { 300.0f ,300.0f };
	m_Use[CHECK] = false;
	m_Color[CHECK] = { 1.0f,1.0f, 1.0f, 1.0f };

	m_Tex[T_STAGE_1] = m_StageTex[S_1_5];
	m_Pos[T_STAGE_1] = { SCREEN_WIDTH * 0.5f + 5.0f,SCREEN_HEIGHT * 0.5f };
	m_Vel[T_STAGE_1] = { 0.0f, 0.0f };
	m_Size[T_STAGE_1] = { 1000.0f * 1.1f,610.0f * 1.1f };
	m_Use[T_STAGE_1] = true;
	m_Color[T_STAGE_1] = { 1.0f,1.0f, 1.0f, 1.0f };
	m_StageAngle[T_STAGE_1] = 0.0f;

	m_Tex[T_STAGE_2] = m_StageTex[S_1_4];
	m_Pos[T_STAGE_2] = { SCREEN_WIDTH * 0.5f + 5.0f,SCREEN_HEIGHT * 0.5f };
	m_Vel[T_STAGE_2] = { 0.0f, 0.0f };
	m_Size[T_STAGE_2] = { 1000.0f * 1.1f,610.0f * 1.1f };
	m_Use[T_STAGE_2] = true;
	m_Color[T_STAGE_2] = { 1.0f,1.0f, 1.0f, 1.0f };
	m_StageAngle[T_STAGE_2] = 0.0f;

	m_Tex[T_STAGE_3] = m_StageTex[S_1_3];
	m_Pos[T_STAGE_3] = { SCREEN_WIDTH * 0.5f + 5.0f,SCREEN_HEIGHT * 0.5f };
	m_Vel[T_STAGE_3] = { 0.0f, 0.0f };
	m_Size[T_STAGE_3] = { 1000.0f * 1.1f,610.0f * 1.1f };
	m_Use[T_STAGE_3] = true;
	m_Color[T_STAGE_3] = { 1.0f,1.0f, 1.0f, 1.0f };
	m_StageAngle[T_STAGE_3] = 0.0f;

	m_Tex[T_STAGE_4] = m_StageTex[S_1_2];
	m_Pos[T_STAGE_4] = { SCREEN_WIDTH * 0.5f + 5.0f,SCREEN_HEIGHT * 0.5f };
	m_Vel[T_STAGE_4] = { 0.0f, 0.0f };
	m_Size[T_STAGE_4] = { 1000.0f * 1.1f,610.0f * 1.1f };
	m_Use[T_STAGE_4] = true;
	m_Color[T_STAGE_4] = { 1.0f,1.0f, 1.0f, 1.0f };
	m_StageAngle[T_STAGE_4] = 0.0f;

	m_Tex[T_STAGE_5] = m_StageTex[S_1_1];
	m_Pos[T_STAGE_5] = { SCREEN_WIDTH * 0.5f + 5.0f,SCREEN_HEIGHT * 0.5f };
	m_Vel[T_STAGE_5] = { 0.0f, 0.0f };
	m_Size[T_STAGE_5] = { 1000.0f * 1.1f,610.0f * 1.1f };
	m_Use[T_STAGE_5] = true;
	m_Color[T_STAGE_5] = { 1.0f,1.0f, 1.0f, 1.0f };
	m_StageAngle[T_STAGE_5] = 0.0f;

	for (int i = 0; i < CLEAR_MAX; i++)
	{
		m_ClearTex[i]->Create("StageSelect/CLEAR.png", 1, 1);
		m_ClearPos[i] = { SCREEN_WIDTH * 0.5f + 300.0f,SCREEN_HEIGHT * 0.5f + 320.0f };
		m_ClearVel[i] = { 0.0f, 0.0f };
		m_ClearSize[i] = { 800.0f * 0.5f,250.0f * 0.5f };
		m_ClearUse[i] = true;
		m_ClearColor[i] = { 1.0f,1.0f, 1.0f, 0.0f };//描画の有無はalpha値で決めてます。
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		m_EnemyTex[i]->Create("StageSelect/clearicon_vi.png", 2, 1);
		m_EnemyTex[i]->SetStartUVPosition(Float2(0.0f, 0.0f));
		m_EnemyPos[i] = { SCREEN_WIDTH * 0.5f - 210.0f,SCREEN_HEIGHT * 0.5f + 320.0f };
		m_EnemyVel[i] = { 0.0f, 0.0f };
		m_EnemySize[i] = { 110.0f,110.0f };
		m_EnemyUse[i] = true;
		m_EnemyColor[i] = { 1.0f,1.0f, 1.0f, 0.0f };//描画の有無はalpha値で決めてます。
	}

	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_ItemTex[i]->Create("StageSelect/clearicon_I.png", 2, 1);
		m_ItemTex[i]->SetStartUVPosition(Float2(0.0f, 0.0f));
		m_ItemPos[i] = { SCREEN_WIDTH * 0.5f + -90.0f,SCREEN_HEIGHT * 0.5f + 320.0f };
		m_ItemVel[i] = { 0.0f, 0.0f };
		m_ItemSize[i] = { 140.0f,140.0f };
		m_ItemUse[i] = true;
		m_ItemColor[i] = { 1.0f,1.0f, 1.0f, 0.0f };//描画の有無はalpha値で決めてます。
	}

	for (int i = 0; i < LIFE_MAX; i++)
	{
		m_LifeTex[i]->Create("StageSelect/clearicon_HP.png", 2, 1);
		m_LifeTex[i]->SetStartUVPosition(Float2(0.0f, 0.0f));
		m_LifePos[i] = { SCREEN_WIDTH * 0.5f + 30.0f,SCREEN_HEIGHT * 0.5f + 320.0f };
		m_LifeVel[i] = { 0.0f, 0.0f };
		m_LifeSize[i] = { 100.0f,100.0f };
		m_LifeUse[i] = true;
		m_LifeColor[i] = { 1.0f,1.0f, 1.0f, 0.0f };//描画の有無はalpha値で決めてます。
	}


	m_VerticaImputDirection = DOWN;

	int area = 0;
	int stage = 0;

	if (StageNum::Get() == 25)
	{
		area = 0;
		stage = 0;
	}
	else
	{
		area = StageNum::Get() / 5;
		stage = StageNum::Get() % 5;
	}

	//エリア系====================
	m_SelectArea = S_AREA_1 + area;
	m_MosaciFrame = 0;
	m_canBlinkRightTriangel = false;
	m_BlinkRightTriangleFrame = 0;
	m_canBlinkLeftTriangel = false;
	m_BlinkLeftTriangleFrame = 0;
	//エリア系====================
	//ステージ系==================

	m_SelectStage = S_STAGE_1 - stage;
	m_ShiftFtame = 1000;
	m_ChangeStageTexFrame = 0;
	//ステージ系==================
	//その他======================
	back = false;
	tutorial = false;

	FrameToback = 0;
	FrameTotorial = 0;

	m_isVerticalScrolling = false;
	m_isSideScrolling = false;
	m_SelectSection = SS_STAGE;
	m_Frame = 0;
	DisplayDataFrame = 0;


	switch (m_SelectArea)
	{
	case S_AREA_1:
		for (int i = 0; i < 5; i++)
		{
			m_Tex[S_STAGE_5 + i] = m_StageTex[S_1_1 + i];
		}
		break;
	case S_AREA_2:
		for (int i = 0; i < 5; i++)
		{
			m_Tex[S_STAGE_5 + i] = m_StageTex[S_2_1 + i];
		}
		break;
	case S_AREA_3:
		for (int i = 0; i < 5; i++)
		{
			m_Tex[S_STAGE_5 + i] = m_StageTex[S_3_1 + i];
		}
		break;
	case S_AREA_4:
		for (int i = 0; i < 5; i++)
		{
			m_Tex[S_STAGE_5 + i] = m_StageTex[S_4_1 + i];
		}
		break;
	case S_AREA_5:
		for (int i = 0; i < 5; i++)
		{
			m_Tex[S_STAGE_5 + i] = m_StageTex[S_5_1 + i];
		}
		break;
	}






	m_BGM->Load("menu.wav");
	m_BGM->SetVolume(Volume::GetBGM() * MASTER_VOLUME);
	m_BGM->Play();
	SEManager::Init();


}

void StageSelect::Uninit()
{
	m_BGM->Stop();

	if (m_Row == -1)
	{
		StageNum::Set(0);
	}

	//シーンごとに1度だけ呼ぶ
	TextureManager::Unload();
	SoundManager::Unload();




}

void StageSelect::Update()
{

	m_Frame++;

	//入力方向
	this->ImputDirection();

	//エリア関係=======================

	this->DisplayData();

	//エリアの選択項目
	this->SelectArea();

	//モザイクのリセット
	this->ResetMosaic();

	//表示するエリア
	this->DisplayArea();

	//モザイクのアニメーション設定
	this->MosaicAnimation();

	//三角の点滅
	this->BlinkTriangle();
	//エリア関係=======================

	//ステージ関係=====================
	//ステージの選択項目
	this->SelectStage();

	//選択項目を明るく、それ以外を暗くする
	this->BrightenStage();

	//ステージの色変え
	this->SetStageTex();

	//ステージの回転
	this->RotateStage();

	//ステージの引っ込みと出現
	this->ShiftStage();

	//選択項目上のクリアを明るく、それ以外を暗くする
	this->BrightenClear();

	//クリアの回転
	this->RotateClear();

	//クリアの引っ込みと出現
	this->ShiftClear();
	//ステージ関係=====================

	//その他===========================
	//戻る
	this->Back();


	//ステージ選択　チュートリアル　戻るの選択
	this->SelectSection();

	//スクロール管理
	this->ScrollingManager();

	//チュートリアル
	this->Tutorial();

	if (m_SelectSection == SS_STAGE)
	{
		if (Controller::GetButtonTriggerB() && !GetSideScrolling() && Fade::GetState())
		{
			SEManager::Play(SOUND::DECISION);

			StageNum::Set((m_SelectArea - S_AREA_1) * STAGE_Y + (S_STAGE_1 - m_SelectStage));

			Fade::Transition(SCENE_TYPE::GAME, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
		}
	}
}

void StageSelect::Draw()
{
	printf("%d", m_Row);
	printf("%d", m_Column);

	for (int i = 0; i < MAX; i++)
	{
		if (m_Use[i])
		{
			Sprite::DrawCenter(m_Pos[i] + m_ShiftPos[i], m_Size[i], m_Tex[i], m_Color[i]);

		}
	}

	//CLEARの描画
	for (int i = 0; i < CLEAR_MAX; i++)
	{
		if (m_ClearUse[i])
		{
			Sprite::DrawCenter(m_ClearPos[i], m_ClearSize[i], m_ClearTex[i], m_ClearColor[i]);
		}
	}

	//エネミー
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (m_EnemyUse[i])
		{
			Sprite::DrawCenter(m_EnemyPos[i], m_EnemySize[i], m_EnemyTex[i], m_EnemyColor[i]);
		}
	}

	//アイテム
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (m_ItemUse[i])
		{
			Sprite::DrawCenter(m_ItemPos[i], m_ItemSize[i], m_ItemTex[i], m_ItemColor[i]);
		}
	}

	//ライフ
	for (int i = 0; i < LIFE_MAX; i++)
	{
		if (m_LifeUse[i])
		{
			Sprite::DrawCenter(m_LifePos[i], m_LifeSize[i], m_LifeTex[i], m_LifeColor[i]);
		}
	}

}

void StageSelect::CreateStageTex()
{
	m_StageTex[S_1_1]->Create("StageSelect/01/G5.png", 1, 1);
	m_StageTex[S_1_2]->Create("StageSelect/01/G4.png", 1, 1);
	m_StageTex[S_1_3]->Create("StageSelect/01/G3.png", 1, 1);
	m_StageTex[S_1_4]->Create("StageSelect/01/G2.png", 1, 1);
	m_StageTex[S_1_5]->Create("StageSelect/01/G1.png", 1, 1);

	m_StageTex[S_2_1]->Create("StageSelect/02/B5.png", 1, 1);
	m_StageTex[S_2_2]->Create("StageSelect/02/B4.png", 1, 1);
	m_StageTex[S_2_3]->Create("StageSelect/02/B3.png", 1, 1);
	m_StageTex[S_2_4]->Create("StageSelect/02/B2.png", 1, 1);
	m_StageTex[S_2_5]->Create("StageSelect/02/B1.png", 1, 1);

	m_StageTex[S_3_1]->Create("StageSelect/03/5.png", 1, 1);
	m_StageTex[S_3_2]->Create("StageSelect/03/4.png", 1, 1);
	m_StageTex[S_3_3]->Create("StageSelect/03/3.png", 1, 1);
	m_StageTex[S_3_4]->Create("StageSelect/03/2.png", 1, 1);
	m_StageTex[S_3_5]->Create("StageSelect/03/1.png", 1, 1);

	m_StageTex[S_4_1]->Create("StageSelect/04/O5.png", 1, 1);
	m_StageTex[S_4_2]->Create("StageSelect/04/O4.png", 1, 1);
	m_StageTex[S_4_3]->Create("StageSelect/04/O3.png", 1, 1);
	m_StageTex[S_4_4]->Create("StageSelect/04/O2.png", 1, 1);
	m_StageTex[S_4_5]->Create("StageSelect/04/O1.png", 1, 1);

	m_StageTex[S_5_1]->Create("StageSelect/05/R5.png", 1, 1);
	m_StageTex[S_5_2]->Create("StageSelect/05/R4.png", 1, 1);
	m_StageTex[S_5_3]->Create("StageSelect/05/R3.png", 1, 1);
	m_StageTex[S_5_4]->Create("StageSelect/05/R2.png", 1, 1);
	m_StageTex[S_5_5]->Create("StageSelect/05/R1.png", 1, 1);
}

void StageSelect::ImputDirection()
{
	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		if (Controller::GetButtonTriggerRShoulder())
			m_SideImputDirection = RIGHT;

		if (Controller::GetButtonTriggerLShoulder())
			m_SideImputDirection = LEFT;

		if (Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown())
			m_VerticaImputDirection = UP;

		if (Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp())
			m_VerticaImputDirection = DOWN;
	}

}

void StageSelect::SelectArea()
{
	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		if (Controller::GetButtonTriggerRShoulder())
		{
			SEManager::Play(SOUND::CURSOR);

			m_SelectArea++;

			if (m_SelectArea > S_AREA_5)
				m_SelectArea = S_AREA_1;

			m_Row += 1;

			if (m_Row > 4)
				m_Row = 0;
		}

		if (Controller::GetButtonTriggerLShoulder())
		{
			SEManager::Play(SOUND::CURSOR);
			m_SelectArea--;

			if (m_SelectArea < S_AREA_1)
				m_SelectArea = S_AREA_5;

			m_Row -= 1;

			if (m_Row < 0)
				m_Row = 4;
		}
	}

}

void StageSelect::DisplayArea()
{
	constexpr float alphaSpd = 0.05f;
	constexpr float alphaMax = 1.0f;
	constexpr float alphaMin = 0.0f;

	//表示するエリア
	for (int i = S_AREA_1; i < S_AREA_5 + 1; i++)
	{
		if (i == m_SelectArea)
		{
			m_Color[i].w += alphaSpd;

			if (m_Color[i].w > alphaMax)
				m_Color[i].w = alphaMax;
		}
		else
		{
			m_Color[i].w -= alphaSpd;

			if (m_Color[i].w < alphaMin)
				m_Color[i].w = alphaMin;
		}
	}
}

void StageSelect::ResetMosaic()
{
	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		//モザイクのリセット
		if (Controller::GetButtonTriggerLShoulder() || Controller::GetButtonTriggerRShoulder())
		{
			m_Pos[MOSAIC].x = SCREEN_WIDTH * 0.5f + 40.0f;
			m_Size[MOSAIC].x = 650.0f;
			m_MosaciFrame = 0;
		}

	}
}

void StageSelect::MosaicAnimation()
{
	//アニメーション
	float mosaicSpd = 0.0f;
	int StartDeleteMosaic = 20;

	m_MosaciFrame++;
	if (m_MosaciFrame > StartDeleteMosaic)
	{
		if (m_Size[MOSAIC].x > 0.0f)
		{
			//サイズの縮小
			m_Size[MOSAIC].x -= mosaicSpd;
			if (m_Size[MOSAIC].x < 0.0f)
				m_Size[MOSAIC].x = 0.0f;

			//位置の調整
			m_Pos[MOSAIC].x += mosaicSpd * 0.5f;
		}
	}
}

void StageSelect::BlinkTriangle()
{
	float blinkingSpd = 0.15f;

	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		//点滅開始
		if (Controller::GetButtonTriggerRShoulder())
		{
			m_canBlinkRightTriangel = true;
			m_BlinkRightTriangleFrame = 0;
		}
	}


	//点滅フラグがtrueならば
	if (m_canBlinkRightTriangel)
	{
		//点滅フレーム
		m_BlinkRightTriangleFrame++;

		if (m_BlinkRightTriangleFrame * blinkingSpd > 3.14159265f)
			m_BlinkRightTriangleFrame = 3.14159265f / blinkingSpd;


		//180度以内なら点滅
		if (m_SideImputDirection == RIGHT)
		{
			m_Color[TRIANGLE_RIGHT].x = sin(m_BlinkRightTriangleFrame * blinkingSpd) * 0.8f + 0.7f;
			m_Color[TRIANGLE_RIGHT].y = sin(m_BlinkRightTriangleFrame * blinkingSpd) * 0.8f + 0.7f;
			m_Color[TRIANGLE_RIGHT].z = sin(m_BlinkRightTriangleFrame * blinkingSpd) * 0.8f + 0.7f;
		}
	}

	//180度までまわったらfalse
	if (m_BlinkRightTriangleFrame * blinkingSpd >= 3.14159265)
		m_canBlinkRightTriangel = false;


	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		//点滅開始
		if (Controller::GetButtonTriggerLShoulder())
		{
			m_canBlinkLeftTriangel = true;
			m_BlinkLeftTriangleFrame = 0;
		}
	}


	//点滅フラグがtrueならば
	if (m_canBlinkLeftTriangel)
	{
		//点滅フレーム
		m_BlinkLeftTriangleFrame++;

		if (m_BlinkLeftTriangleFrame * blinkingSpd > 3.14159265f)
			m_BlinkLeftTriangleFrame = 3.14159265f / blinkingSpd;


		//180度以内なら点滅
		if (m_SideImputDirection == LEFT)
		{
			m_Color[TRIANGLE_LEFT].x = sin(m_BlinkLeftTriangleFrame * blinkingSpd) * 0.8f + 0.7f;
			m_Color[TRIANGLE_LEFT].y = sin(m_BlinkLeftTriangleFrame * blinkingSpd) * 0.8f + 0.7f;
			m_Color[TRIANGLE_LEFT].z = sin(m_BlinkLeftTriangleFrame * blinkingSpd) * 0.8f + 0.7f;
		}
	}

	//180度までまわったらfalse
	if ((float)(m_BlinkLeftTriangleFrame)*blinkingSpd >= 3.14159265f)
		m_canBlinkLeftTriangel = false;
}

void StageSelect::SelectStage()
{
	//ステージ項目を選択中ならば
	if (m_SelectSection == SS_STAGE)
	{
		if (!GetSideScrolling())//スクロール中でなければ
		{
			//選択項目
			if (Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown())
			{

				m_Column -= 1;
				if (m_Column < 0)
					m_Column = 0;
				if (m_SelectStage < S_STAGE_1)
				{
					m_SelectStage++;
					SEManager::Play(SOUND::CURSOR);
				}
			}

			if (Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp())
			{
				m_Column += 1;

				if (m_Column > 4)
					m_Column = 4;

				if (m_SelectStage > S_STAGE_5)
				{
					m_SelectStage--;
					SEManager::Play(SOUND::CURSOR);
				}
			}
		}
	}
}

void StageSelect::BrightenStage()
{
	constexpr float colSpd = 0.1f;
	constexpr float colMax = 1.2f;
	constexpr float colMin = 0.9f;


	//選択項目を明るく、それ以外を暗くする
	for (int i = S_STAGE_5; i < S_STAGE_1 + 1; i++)
	{
		if (i == m_SelectStage && m_SelectSection == SS_STAGE)
		{
			m_Color[i].x += colSpd;
			m_Color[i].y += colSpd;
			m_Color[i].z += colSpd;

			if (m_Color[i].x > colMax)
			{
				m_Color[i].x = colMax;
				m_Color[i].y = colMax;
				m_Color[i].z = colMax;
			}
		}
		else
		{
			m_Color[i].x -= colSpd;
			m_Color[i].y -= colSpd;
			m_Color[i].z -= colSpd;

			if (m_Color[i].x < colMin)
			{
				m_Color[i].x = colMin;
				m_Color[i].y = colMin;
				m_Color[i].z = colMin;
			}
		}
	}

}

void StageSelect::RotateStage()
{
	constexpr float spd = 0.02f;

	constexpr float first = 9.0f / 6.0f;
	constexpr float second = 8.0f / 6.0f;
	constexpr float third = 7.0f / 6.0f;
	constexpr float fourth = 5.10f / 6.0f;
	constexpr float fifth = 4.0f / 6.0f;


	//上にズレる
	if (m_VerticaImputDirection == UP)
	{
		switch (m_SelectStage)
		{
		case S_STAGE_1:
			m_StageAngle[S_STAGE_1] += spd;
			if (m_StageAngle[S_STAGE_1] > third)
				m_StageAngle[S_STAGE_1] = third;

			m_StageAngle[S_STAGE_2] += spd;
			if (m_StageAngle[S_STAGE_2] > second)
				m_StageAngle[S_STAGE_2] = second;

			m_StageAngle[S_STAGE_3] += spd;
			if (m_StageAngle[S_STAGE_3] > first)
				m_StageAngle[S_STAGE_3] = first;

			m_StageAngle[S_STAGE_4] += spd;
			if (m_StageAngle[S_STAGE_4] > first)
				m_StageAngle[S_STAGE_4] = first;

			m_StageAngle[S_STAGE_5] += spd;
			if (m_StageAngle[S_STAGE_5] > first)
				m_StageAngle[S_STAGE_5] = first;

			break;

		case S_STAGE_2:
			m_StageAngle[S_STAGE_1] += spd;
			if (m_StageAngle[S_STAGE_1] > fourth)
				m_StageAngle[S_STAGE_1] = fourth;

			m_StageAngle[S_STAGE_2] += spd;
			if (m_StageAngle[S_STAGE_2] > third)
				m_StageAngle[S_STAGE_2] = third;

			m_StageAngle[S_STAGE_3] += spd;
			if (m_StageAngle[S_STAGE_3] > second)
				m_StageAngle[S_STAGE_3] = second;

			m_StageAngle[S_STAGE_4] += spd;
			if (m_StageAngle[S_STAGE_4] > first)
				m_StageAngle[S_STAGE_4] = first;

			m_StageAngle[S_STAGE_5] += spd;
			if (m_StageAngle[S_STAGE_5] > first)
				m_StageAngle[S_STAGE_5] = first;
			break;

		case S_STAGE_3:
			m_StageAngle[S_STAGE_1] += spd;
			if (m_StageAngle[S_STAGE_1] > fifth)
				m_StageAngle[S_STAGE_1] = fifth;

			m_StageAngle[S_STAGE_2] += spd;
			if (m_StageAngle[S_STAGE_2] > fourth)
				m_StageAngle[S_STAGE_2] = fourth;

			m_StageAngle[S_STAGE_3] += spd;
			if (m_StageAngle[S_STAGE_3] > third)
				m_StageAngle[S_STAGE_3] = third;

			m_StageAngle[S_STAGE_4] += spd;
			if (m_StageAngle[S_STAGE_4] > second)
				m_StageAngle[S_STAGE_4] = second;

			m_StageAngle[S_STAGE_5] += spd;
			if (m_StageAngle[S_STAGE_5] > first)
				m_StageAngle[S_STAGE_5] = first;
			break;

		case S_STAGE_4:
			m_StageAngle[S_STAGE_1] += spd;
			if (m_StageAngle[S_STAGE_1] > fifth)
				m_StageAngle[S_STAGE_1] = fifth;

			m_StageAngle[S_STAGE_2] += spd;
			if (m_StageAngle[S_STAGE_2] > fifth)
				m_StageAngle[S_STAGE_2] = fifth;

			m_StageAngle[S_STAGE_3] += spd;
			if (m_StageAngle[S_STAGE_3] > fourth)
				m_StageAngle[S_STAGE_3] = fourth;

			m_StageAngle[S_STAGE_4] += spd;
			if (m_StageAngle[S_STAGE_4] > third)
				m_StageAngle[S_STAGE_4] = third;

			m_StageAngle[S_STAGE_5] += spd;
			if (m_StageAngle[S_STAGE_5] > second)
				m_StageAngle[S_STAGE_5] = second;
			break;

		case S_STAGE_5:
			m_StageAngle[S_STAGE_1] += spd;
			if (m_StageAngle[S_STAGE_1] > fifth)
				m_StageAngle[S_STAGE_1] = fifth;

			m_StageAngle[S_STAGE_2] += spd;
			if (m_StageAngle[S_STAGE_2] > fifth)
				m_StageAngle[S_STAGE_2] = fifth;

			m_StageAngle[S_STAGE_3] += spd;
			if (m_StageAngle[S_STAGE_3] > fifth)
				m_StageAngle[S_STAGE_3] = fifth;

			m_StageAngle[S_STAGE_4] += spd;
			if (m_StageAngle[S_STAGE_4] > fourth)
				m_StageAngle[S_STAGE_4] = fourth;

			m_StageAngle[S_STAGE_5] += spd;
			if (m_StageAngle[S_STAGE_5] > third)
				m_StageAngle[S_STAGE_5] = third;
			break;
		}
	}


	//下にズレる
	if (m_VerticaImputDirection == DOWN)
	{
		switch (m_SelectStage)
		{
		case S_STAGE_5:
			m_StageAngle[S_STAGE_1] -= spd;
			if (m_StageAngle[S_STAGE_1] < fifth)
				m_StageAngle[S_STAGE_1] = fifth;

			m_StageAngle[S_STAGE_2] -= spd;
			if (m_StageAngle[S_STAGE_2] < fifth)
				m_StageAngle[S_STAGE_2] = fifth;

			m_StageAngle[S_STAGE_3] -= spd;
			if (m_StageAngle[S_STAGE_3] < fifth)
				m_StageAngle[S_STAGE_3] = fifth;

			m_StageAngle[S_STAGE_4] -= spd;
			if (m_StageAngle[S_STAGE_4] < fourth)
				m_StageAngle[S_STAGE_4] = fourth;

			m_StageAngle[S_STAGE_5] -= spd;
			if (m_StageAngle[S_STAGE_5] < third)
				m_StageAngle[S_STAGE_5] = third;
			break;

		case S_STAGE_4:
			m_StageAngle[S_STAGE_1] -= spd;
			if (m_StageAngle[S_STAGE_1] < fifth)
				m_StageAngle[S_STAGE_1] = fifth;


			m_StageAngle[S_STAGE_2] -= spd;
			if (m_StageAngle[S_STAGE_2] < fifth)
				m_StageAngle[S_STAGE_2] = fifth;

			m_StageAngle[S_STAGE_3] -= spd;
			if (m_StageAngle[S_STAGE_3] < fourth)
				m_StageAngle[S_STAGE_3] = fourth;

			m_StageAngle[S_STAGE_4] -= spd;
			if (m_StageAngle[S_STAGE_4] < third)
				m_StageAngle[S_STAGE_4] = third;

			m_StageAngle[S_STAGE_5] -= spd;
			if (m_StageAngle[S_STAGE_5] < second)
				m_StageAngle[S_STAGE_5] = second;
			break;

		case S_STAGE_3:
			m_StageAngle[S_STAGE_1] -= spd;
			if (m_StageAngle[S_STAGE_1] < fifth)
				m_StageAngle[S_STAGE_1] = fifth;

			m_StageAngle[S_STAGE_2] -= spd;
			if (m_StageAngle[S_STAGE_2] < fourth)
				m_StageAngle[S_STAGE_2] = fourth;

			m_StageAngle[S_STAGE_3] -= spd;
			if (m_StageAngle[S_STAGE_3] < third)
				m_StageAngle[S_STAGE_3] = third;

			m_StageAngle[S_STAGE_4] -= spd;
			if (m_StageAngle[S_STAGE_4] < second)
				m_StageAngle[S_STAGE_4] = second;

			m_StageAngle[S_STAGE_5] -= spd;
			if (m_StageAngle[S_STAGE_5] < first)
				m_StageAngle[S_STAGE_5] = first;
			break;

		case S_STAGE_2:
			m_StageAngle[S_STAGE_1] -= spd;
			if (m_StageAngle[S_STAGE_1] < fourth)
				m_StageAngle[S_STAGE_1] = fourth;

			m_StageAngle[S_STAGE_2] -= spd;
			if (m_StageAngle[S_STAGE_2] < third)
				m_StageAngle[S_STAGE_2] = third;

			m_StageAngle[S_STAGE_3] -= spd;
			if (m_StageAngle[S_STAGE_3] < second)
				m_StageAngle[S_STAGE_3] = second;

			m_StageAngle[S_STAGE_4] -= spd;
			if (m_StageAngle[S_STAGE_4] < first)
				m_StageAngle[S_STAGE_4] = first;

			m_StageAngle[S_STAGE_5] -= spd;
			if (m_StageAngle[S_STAGE_5] < first)
				m_StageAngle[S_STAGE_5] = first;
			break;

		case S_STAGE_1:
			m_StageAngle[S_STAGE_1] -= spd;
			if (m_StageAngle[S_STAGE_1] < third)
				m_StageAngle[S_STAGE_1] = third;

			m_StageAngle[S_STAGE_2] -= spd;
			if (m_StageAngle[S_STAGE_2] < second)
				m_StageAngle[S_STAGE_2] = second;

			m_StageAngle[S_STAGE_3] -= spd;
			if (m_StageAngle[S_STAGE_3] < first)
				m_StageAngle[S_STAGE_3] = first;

			m_StageAngle[S_STAGE_4] -= spd;
			if (m_StageAngle[S_STAGE_4] < first)
				m_StageAngle[S_STAGE_4] = first;

			m_StageAngle[S_STAGE_5] -= spd;
			if (m_StageAngle[S_STAGE_5] < first)
				m_StageAngle[S_STAGE_5] = first;
			break;
		}

	}

	//ポジションを更新する
	for (int i = S_STAGE_5; i < S_STAGE_1 + 1; i++)
	{
		m_Pos[i] = {
	cos(m_StageAngle[i] * PI) * 1000.0f + SCREEN_WIDTH ,
	sin(m_StageAngle[i] * PI) * 700.0f + SCREEN_HEIGHT - 100.0f };
	}
}

void StageSelect::RotateClear()
{

}

void StageSelect::ShiftStage()
{
	const int ShiftFinishFrame = 20;

	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		if (Controller::GetButtonTriggerLShoulder() || Controller::GetButtonTriggerRShoulder())
		{
			m_ShiftFtame = 0;
			DisplayDataFrame = -20;
		}
	}


	m_ShiftFtame++;

	for (int i = S_STAGE_5; i < S_STAGE_1 + 1; i++)
	{
		if (m_ShiftFtame < 20)//右に行って
			m_ShiftPos[i].x += 100.0f;
		else if (m_ShiftFtame > ShiftFinishFrame)//戻る
		{
			m_ShiftPos[i].x -= 100.0f;
			if (m_ShiftPos[i].x < 0.0f)
			{
				m_ShiftPos[i].x = 0.0f;
				this->SetSideScrolling(false);
			}
		}
	}
}

void StageSelect::BrightenClear()
{
	constexpr float colSpd = 0.1f;
	constexpr float colMax = 1.0f;
	constexpr float colMin = 0.7f;

	//選択項目を明るく、それ以外を暗くする
	for (int i = S_STAGE_5; i < S_STAGE_1 + 1; i++)
	{
		if (i == m_SelectStage)
		{
			if (m_SelectSection == SS_STAGE)
			{
				m_Color[i].x += colSpd;
				m_Color[i].y += colSpd;
				m_Color[i].z += colSpd;
			}
			if (m_Color[i].x > colMax)
			{
				m_Color[i].x = colMax;
				m_Color[i].y = colMax;
				m_Color[i].z = colMax;
			}
		}
		else
		{
			m_Color[i].x -= colSpd;
			m_Color[i].y -= colSpd;
			m_Color[i].z -= colSpd;

			if (m_Color[i].x < colMin)
			{
				m_Color[i].x = colMin;
				m_Color[i].y = colMin;
				m_Color[i].z = colMin;
			}
		}
	}
}

void StageSelect::ShiftClear()
{

}

void StageSelect::SetStageTex()
{
	//ステージ項目を選択中ならば

	if (!GetSideScrolling())//スクロール中でなければ
	{
		if (Controller::GetButtonTriggerLShoulder() || Controller::GetButtonTriggerRShoulder())
		{
			m_ChangeStageTexFrame = 0;
			m_canChangeStageTex = true;
		}
	}


	m_ChangeStageTexFrame++;
	if (m_ChangeStageTexFrame > 10 && m_canChangeStageTex)
	{
		m_canChangeStageTex = false;

		switch (m_SelectArea)
		{
		case S_AREA_1:
			for (int i = 0; i < 5; i++)
			{
				m_Tex[S_STAGE_5 + i] = m_StageTex[S_1_1 + i];
			}
			break;
		case S_AREA_2:
			for (int i = 0; i < 5; i++)
			{
				m_Tex[S_STAGE_5 + i] = m_StageTex[S_2_1 + i];
			}
			break;
		case S_AREA_3:
			for (int i = 0; i < 5; i++)
			{
				m_Tex[S_STAGE_5 + i] = m_StageTex[S_3_1 + i];
			}
			break;
		case S_AREA_4:
			for (int i = 0; i < 5; i++)
			{
				m_Tex[S_STAGE_5 + i] = m_StageTex[S_4_1 + i];
			}
			break;
		case S_AREA_5:
			for (int i = 0; i < 5; i++)
			{
				m_Tex[S_STAGE_5 + i] = m_StageTex[S_5_1 + i];
			}
			break;
		}
	}
}

void StageSelect::Back()
{
	if (!back)
	{
		if (!GetSideScrolling())//スクロール中でなければ
		{
			if (Controller::GetButtonTriggerA())
			{
				SEManager::Play(SOUND::CANCEL);
				back = true;
			}

			if (Controller::GetButtonTriggerB() && m_SelectSection == SS_BACK)
			{
				SEManager::Play(SOUND::CANCEL);
				back = true;
			}
		}
	}

	if (back)
	{
		FrameToback++;
		m_Tex[BACK]->SetStartUVPosition(Float2((1.0f / 3.0f) * 2.0f, 0.0f));

	}
	else if (!back)
	{
		//光らせる
		if (m_SelectSection == SS_BACK)
		{
			m_Tex[BACK]->SetStartUVPosition(Float2((1.0f / 3.0f) * 1.0f, 0.0f));

			m_Color[BACK].x = sin(m_Frame * 0.2f) * 0.1f + 1.0f;
			m_Color[BACK].y = sin(m_Frame * 0.2f) * 0.1f + 1.0f;
			m_Color[BACK].z = sin(m_Frame * 0.2f) * 0.1f + 1.0f;
		}
		else
		{
			m_Tex[BACK]->SetStartUVPosition(Float2((1.0f / 3.0f) * 0.0f, 0.0f));
			m_Color[BACK].x = 1.0f;
			m_Color[BACK].y = 1.0f;
			m_Color[BACK].z = 1.0f;
		}
	}

	if (FrameToback > 20 && Fade::GetState())
		Fade::Transition(SCENE_TYPE::TITLE, FADE_TYPE::ALPHA, nullptr, Float3(26.0f / 255.0f, 7.0f / 255.0f, 80.0f / 255.0f));
}

void StageSelect::ScrollingManager()
{
	//入力したらスクロール判定
	if (!GetSideScrolling())
	{
		if (Controller::GetButtonTriggerLShoulder() || Controller::GetButtonTriggerRShoulder())
			this->SetSideScrolling(true);
	}
}


void StageSelect::SetSideScrolling(bool tf)
{
	m_isSideScrolling = tf;
}

bool StageSelect::GetSideScrolling()
{
	return m_isSideScrolling;
}

//クリア済みの表示
void StageSelect::SetCleared(int area, int stage)
{
	for (int i = 0; i < STAGE_TEX_MAX; i++)
	{
		m_ClearedStage[i] = false;
	}
}

void StageSelect::SelectSection()
{
	if (m_SelectSection == SS_STAGE)
	{

		if (Controller::GetButtonTriggerRight())
		{
			SEManager::Play(SOUND::CURSOR);
			m_SelectSection = SS_BACK;
		}
		if (Controller::GetButtonTriggerLeft())
		{
			SEManager::Play(SOUND::CURSOR);
			m_SelectSection = SS_TUTORIAL;
		}
	}
	else
		if (m_SelectSection == SS_TUTORIAL)
		{
			if (Controller::GetButtonTriggerRight())
			{
				SEManager::Play(SOUND::CURSOR);
				m_SelectSection = SS_STAGE;
			}
		}
		else
			if (m_SelectSection == SS_BACK)
			{
				if (Controller::GetButtonTriggerLeft())
				{
					SEManager::Play(SOUND::CURSOR);
					m_SelectSection = SS_STAGE;
				}
			}
}

void StageSelect::Tutorial()
{
	if (!back)
	{
		//光らせる
		if (m_SelectSection == SS_TUTORIAL)
		{
			m_Tex[TUTORIAL]->SetStartUVPosition(Float2((1.0f / 3.0f) * 1.0f, 0.0f));

			m_Color[TUTORIAL].x = sin(m_Frame * 0.2f) * 0.1f + 1.0f;
			m_Color[TUTORIAL].y = sin(m_Frame * 0.2f) * 0.1f + 1.0f;
			m_Color[TUTORIAL].z = sin(m_Frame * 0.2f) * 0.1f + 1.0f;
		}
		else
		{
			m_Tex[TUTORIAL]->SetStartUVPosition(Float2((1.0f / 3.0f) * 0.0f, 0.0f));

			m_Color[TUTORIAL].x = 1.0f;
			m_Color[TUTORIAL].y = 1.0f;
			m_Color[TUTORIAL].z = 1.0f;
		}

	}
	else
	{
		m_Tex[TUTORIAL]->SetStartUVPosition(Float2((1.0f / 3.0f) * 0.0f, 0.0f));
	}
	//移動
	if (!GetSideScrolling())//スクロール中でなければ
	{
		if (Controller::GetButtonTriggerB() && m_SelectSection == SS_TUTORIAL && Fade::GetState())
		{
			SEManager::Play(SOUND::DECISION);
			tutorial = true;
		}
	}

	if (tutorial)
	{
		FrameTotorial++;
		m_Tex[TUTORIAL]->SetStartUVPosition(Float2((1.0f / 3.0f) * 2.0f, 0.0f));
	}

	if (FrameTotorial > 20 && Fade::GetState())
	{
		/*if (Controller::GetButtonTriggerB() && !GetSideScrolling() && Fade::GetState() && m_SelectSection == SS_TUTORIAL)
		{*/
		/*SEManager::Play(SOUND::DECISION);*/
		StageNum::Set(25);
		Fade::Transition(SCENE_TYPE::GAME, FADE_TYPE::STAIR, nullptr, Float3(1, 1, 0.3f));
	}
}

void StageSelect::DisplayData()
{
	int x = m_SelectArea - T_AREA_1;//調整

	int y = S_STAGE_1 - m_SelectStage;//調整

	int w = 5;//エリア数

	int selectDataIndex = x * w + y;


	DisplayDataFrame++;
	float spd = 0.1f;
	for (int i = 0; i < CLEAR_MAX; i++)
	{

		m_Save = SaveManager::Get(i);// Get


		if (i == selectDataIndex)
		{
			if (DisplayDataFrame > 20)
			{
				//倒したエネミーの数がMAXならば
				m_EnemyColor[i].w += spd;
				if (m_EnemyColor[i].w > 1.0f)
					m_EnemyColor[i].w = 1.0f;

				if (m_Save.kill > 0)
				{
					m_EnemyTex[i]->SetStartUVPosition(Float2((1.0f / 2.0f) * 1.0f, 0.0f));
				}
			}

			if (DisplayDataFrame > 23)
			{
				//アイテムをすべて獲得しているならば

				m_ItemColor[i].w += spd;
				if (m_ItemColor[i].w > 1.0f)
					m_ItemColor[i].w = 1.0f;

				if (m_Save.coin == 3)
				{
					m_ItemTex[i]->SetStartUVPosition(Float2((1.0f / 2.0f) * 1.0f, 0.0f));
					m_ItemSize[i] = Float2(100.0f, 100.0f);
				}
			}

			if (DisplayDataFrame > 26)
			{
				//ライフが３ならば
				m_LifeColor[i].w += spd;
				if (m_LifeColor[i].w > 1.0f)
					m_LifeColor[i].w = 1.0f;
				if (m_Save.life == 3)
				{
					m_LifeTex[i]->SetStartUVPosition(Float2((1.0f / 2.0f) * 1.0f, 0.0f));
				}

			}
			if (DisplayDataFrame > 29)
			{
				//ゲームをクリアしているならば
				if (m_Save.life > 0)
				{
					m_ClearColor[i].w += spd;
					if (m_ClearColor[i].w > 1.0f)
						m_ClearColor[i].w = 1.0f;
				}
			}
		}
		else
		{
			m_ClearColor[i].w = 0.0f;

			m_EnemyColor[i].w = 0.0f;

			m_ItemColor[i].w = 0.0f;

			m_LifeColor[i].w = 0.0f;

		}
	}



	//ステージ項目を選択中ならば
	if (m_SelectSection == SS_STAGE)
	{
		if (!GetSideScrolling())//スクロール中でなければ
		{
			//選択項目
			if (Controller::GetLStickTriggerDown() || Controller::GetButtonTriggerDown())
			{
				if (m_SelectStage < S_STAGE_1)
				{
					DisplayDataFrame = 0;
				}
			}

			if (Controller::GetLStickTriggerUp() || Controller::GetButtonTriggerUp())
			{
				if (m_SelectStage > S_STAGE_5)
				{
					DisplayDataFrame = 0;
				}
			}
		}
	}
}






















