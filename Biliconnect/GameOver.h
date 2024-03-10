/*=========================================================================
	Date : 2022/4/29(金)	GameOver.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef GAMEOVER_H_
#define GAMEOVER_H_

//これをインクルードする
#include "GameCreateSystem.h"
#include "SceneInterface.h"

class GameOver : public SceneInterface
{
public:
	GameOver();
	~GameOver();

public:
	void Init();	//初期化処理
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Draw();	//描画処理

private:
	enum{
		BG,
		ANIMATION,
		BG2,
		MC,
		G,
		A,
		M1,
		M2,
		M3,
		M4,
		M5,
		E_1,
		O,
		V1,
		V2,
		V3,
		V4,
		V5,
		E_2,
		R1,
		R2,
		RETRY,
		MENU,
		BG3,
		//RETRY,
		//MENU,
		MAX,

	};

	typedef enum {
		S_RETRY,
		S_MENU,
	}SELECT;

	typedef enum {
		NONE,
		UP,
		DOWN,
	}GAME_OVER_POS;

	Texture *m_Texture,m_Tex[MAX];
	math::Float2 m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
	math::Float4 m_Col[MAX];
	float StartPositionX[MAX],StartPositionY[MAX],m_Gravity[MAX], m_Bound[MAX];
	GAME_OVER_POS m_GameOverPos[MAX];
	int m_Frame = 0;
	int m_BlinkingFrame[MAX];

	bool PushB;
	int m_FrameSinceToPushB;
	bool m_MCJump;
	
	SELECT m_Select;


};

#endif // !GAMEOVER_H_


