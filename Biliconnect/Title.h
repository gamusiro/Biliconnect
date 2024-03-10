/*=========================================================================
	Date : 2021/12/21(火)	Title.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef TITLE_H_
#define TITLE_H_

//これをインクルードする
#include "GameCreateSystem.h"
#include "SceneInterface.h"

class BGMOption;

class Title : public SceneInterface
{
public:
	Title();
	~Title();

public:
	void Init();	//初期化処理
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Draw();	//描画処理
	void GameStart();

private:
	BGMOption* m_BGMOption;
	BGM* m_BGM;

	//テクスチャ
	enum {
		BG,
		TITLE_LOGO,
		CREDIT,
		EXIT,
		CREDIT_BUTTON,
		PRESS_B,
		START,
		OPTION,
		FADE,
		FRAME,
		MAX,
	};

	//モード
	typedef enum {
		MODE_1,
		MODE_2,
		MODE_3,
		MODE_4,
	}MODE;

	//選択項目
	typedef enum {
		S_START,
		S_OPTION,
	}SELECT;



	
	Texture*  	 m_Tex[MAX];
	math::Float2 m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
	math::Float4 m_Color[MAX];
	bool         m_Use[MAX];
	int          m_Frame;
	
	//モード管理
	int m_ModeFrame;
	MODE m_Mode;


	//Pressボタンの点滅
	int m_BlinkingFrame;
	float m_isBlinkingSpd, m_BlinkingMagnitude, m_Rarefaction;
	bool m_isBlinking;

	//選択項目
	SELECT m_Select;

	//クレジット表示
	bool DisplayCredit;

	bool canTransit;

	constexpr static int MASTER_VOLUME = 6;	// マスターボリューム
	bool first;
};

#endif // !TITLE_H_


