/*=========================================================================
	Date : 2021/12/21(火)	Result.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef RESULT_H_
#define RESULT_H_

#include "GameCreateSystem.h"
#include "SceneInterface.h"
#include "SaveStage.h"
#include "SaveManager.h"


class Result :public SceneInterface
{
public:
	Result();
	~Result();

public:
	void Init();	//初期化処理
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Draw();	//描画処理
	void SetCheck(bool c1, bool c2, bool c3);
private:

	//テクスチャ
	enum {
		BG,
		BINDER,
		T_MENU,
		T_NEXT,
		T_RETRY,
		CHAR_ENEMY,
		CHAR_ALLITEM,
		CHAR_MAXLIFE,
		CHECK_1,
		CHECK_2,
		CHECK_3,
		ENEMY_2,
		ENEMY,
		ZERO,
		E_MAX,
		FILE,
		FOLDER,
		LIFE_1,
		LIFE_2,
		LIFE_3,
		MOSAIC_1,
		MOSAIC_2,
		MOSAIC_3,
		MAX,
	};

	//選択項目
	typedef enum {
		MENU,
		NEXT, 
		RETRY,
	}SELECT;

	Texture* m_Tex[MAX];
	math::Float2  m_Size[MAX],m_Pos[MAX],m_Vel[MAX];
	math::Float4  m_Col[MAX];

	int m_Frame;
	SELECT m_Select;

	#define MA  1089
	Texture* m_BGEfTex[MA];
	BGM* m_BGM;
	math::Float2 m_BGEfSize[MA], m_BGEfPos[MA];
	math::Float4  m_BGEfCol[MA];
	int m_Step[MA];
	int m_Step2[MA];
	float m_red;

	bool m_SetCheck[3];
	bool PushB;
	int m_FrameSinceToPushB;

	SaveStage::NowData m_Data;	// 現在のステージのデータ変数
	SaveManager::SaveData m_Save; // セーブデータ

	constexpr static float SIZE_X = 520.f;
	constexpr static float SIZE_Y = 20.f;

	int m_ButtonFrame;
	bool m_Quick = 0;
	bool m_QuickCheck[3];

	constexpr static int MASTER_VOLUME = 6;	// マスターボリューム
};


#endif // !RESULT_H_

