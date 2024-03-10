/*=========================================================================
	Date : 2021/04/04(月)	Life.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef LIFE_H_
#define LIFE_H_

#include "GameCreateSystem.h"

class Life
{
private:
	constexpr static float SIZE = 140;

	constexpr static float COLOR_MAX = 1;
	constexpr static float COLOR_MIN = 0;
	constexpr static float COLOR_RATE = 0.025f;

private:
	math::Float2 m_Pos;
	math::Float2 m_Size;
	math::Float4 m_Color;

	bool m_Active;	// 活性フラグ
	constexpr static int FLASH_RATE = 4;
	int m_Frame;

	constexpr static float ALFA_MAX = 1;
	constexpr static float ALFA_MIN = 0.1f;

	Texture m_Tex;
	Texture m_Texout;

public:
	Life() = delete;
	// 描画座標指定-何個目
	Life(math::Float2 pos, int num = 0);

	void Update();
	void Draw();

	// 活性化切り替え
	void ActivateChange();

	bool GetActive() { return m_Active; }
};

#endif
