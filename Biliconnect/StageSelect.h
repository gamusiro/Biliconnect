#pragma once

#include <memory>
#include "GameCreateSystem.h"
#include "SceneInterface.h"
#include "SaveStage.h"
#include "SaveManager.h"

class StageSelect : public SceneInterface
{
public:
	StageSelect();
	~StageSelect();

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	void CreateStageTex();
	void ImputDirection();

	void SelectArea();
	void DisplayArea();
	void ResetMosaic();
	void MosaicAnimation();
	void BlinkTriangle();

	void SelectStage();
	void BrightenStage();
	void RotateStage();
	void ShiftStage();
	void SetStageTex();

	void BrightenClear();
	void RotateClear();
	void ShiftClear();

	void Back();
	void ScrollingManager();
	void SetSideScrolling(bool tf);
	bool GetSideScrolling();
	void SetCleared(int area, int stage);
	void SelectSection();
	void Tutorial();

	void DisplayData();



private:
	constexpr static int STAGE_X = 5;	// yoko
	constexpr static int STAGE_Y = 5;	// tate
	constexpr static int MASTER_VOLUME = 6;	// マスターボリューム
	constexpr static float PI = 3.14159265359f;
	constexpr static int STAGE_TEX_MAX = 25;
	enum {
		BG,
		FRAME,
		BACK,
		TUTORIAL_FRAME,
		TUTORIAL,
		T_STAGE_5,//ここ数字逆
		T_STAGE_4,
		T_STAGE_3,
		T_STAGE_2,
		T_STAGE_1,

		CHECK,
		T_AREA_1,
		T_AREA_2,
		T_AREA_3,
		T_AREA_4,
		T_AREA_5,
		MOSAIC,
		TRIANGLE_LEFT,
		TRIANGLE_RIGHT,
		MAX,
	};


	enum {
		S_AREA_1 = T_AREA_1,
		S_AREA_2,
		S_AREA_3,
		S_AREA_4,
		S_AREA_5,
	};

	enum {
		S_STAGE_5 = T_STAGE_5,
		S_STAGE_4,
		S_STAGE_3,
		S_STAGE_2,
		S_STAGE_1,
	};

	enum {
		S_1_1,
		S_1_2,
		S_1_3,
		S_1_4,
		S_1_5,

		S_2_1,
		S_2_2,
		S_2_3,
		S_2_4,
		S_2_5,

		S_3_1,
		S_3_2,
		S_3_3,
		S_3_4,
		S_3_5,

		S_4_1,
		S_4_2,
		S_4_3,
		S_4_4,
		S_4_5,

		S_5_1,
		S_5_2,
		S_5_3,
		S_5_4,
		S_5_5,
	};


	typedef enum {
		SS_STAGE,
		SS_BACK,
		SS_TUTORIAL,
	}SELECT_SECTION;

	typedef enum {
		UP,
		DOWN,
	}VERTICAL_INPUT_DIRECTION;

	typedef enum {
		RIGHT,
		LEFT,
	}SIDE_INPUT_DIRECTION;

	enum {
		AREA_RIGHT_MAX,
		AREA_LEFT_MAX,
		STAGE_RIGHT_MAX,
		STAGE_LEFT_MAX,
	};

	BGM* m_BGM;

	Texture* m_Tex[MAX];
	math::Float2 m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
	math::Float4 m_Color[MAX];
	bool m_Use[MAX];
	VERTICAL_INPUT_DIRECTION m_VerticaImputDirection;
	SIDE_INPUT_DIRECTION m_SideImputDirection;

	int    m_SelectStage;

	//エリア
	int     m_SelectArea;
	int     m_MosaciFrame;
	bool    m_canBlinkRightTriangel, m_canBlinkLeftTriangel;
	int     m_BlinkRightTriangleFrame, m_BlinkLeftTriangleFrame;

	//ステージ
	math::Float2  m_ShiftPos[MAX];
	float   m_StageAngle[MAX];
	float   m_ShiftFtame;
	Texture* m_StageTex[STAGE_TEX_MAX];
	int     m_ChangeStageTexFrame;
	bool    m_canChangeStageTex;

	//その他
	bool back;
	bool tutorial;
	int FrameToback;
	int FrameTotorial;
	bool m_isVerticalScrolling;
	bool m_isSideScrolling;
	int m_ClearedStage[STAGE_TEX_MAX];

	int m_Frame;

	int m_Row;
	int m_Column;

	bool trigger;
	int  timer;

	SaveStage::NowData m_Data;	// 現在のステージのデータ変数
	SaveManager::SaveData m_Save; // セーブデータ

	SELECT_SECTION m_SelectSection;

	int realSelectArea = 0;;
	int realSelectStage = 0;;

	int DisplayDataFrame = 0;//データを表示するまでの時間

#define CLEAR_MAX 25
	Texture* m_ClearTex[CLEAR_MAX];
	math::Float2 m_ClearPos[CLEAR_MAX], m_ClearVel[CLEAR_MAX], m_ClearSize[CLEAR_MAX];
	math::Float4 m_ClearColor[CLEAR_MAX];
	bool m_ClearUse[CLEAR_MAX];

#define ENEMY_MAX 25
	Texture* m_EnemyTex[ENEMY_MAX];
	math::Float2 m_EnemyPos[ENEMY_MAX], m_EnemyVel[ENEMY_MAX], m_EnemySize[ENEMY_MAX];
	math::Float4 m_EnemyColor[ENEMY_MAX];
	bool m_EnemyUse[ENEMY_MAX];

#define ITEM_MAX 25
	Texture* m_ItemTex[ITEM_MAX];
	math::Float2 m_ItemPos[ITEM_MAX], m_ItemVel[ITEM_MAX], m_ItemSize[ITEM_MAX];
	math::Float4 m_ItemColor[ITEM_MAX];
	bool m_ItemUse[ITEM_MAX];

#define LIFE_MAX 25
	Texture* m_LifeTex[LIFE_MAX];
	math::Float2 m_LifePos[LIFE_MAX], m_LifeVel[LIFE_MAX], m_LifeSize[LIFE_MAX];
	math::Float4 m_LifeColor[LIFE_MAX];
	bool m_LifeUse[LIFE_MAX];


};

