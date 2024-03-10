#pragma once
#include "GameCreateSystem.h"

class MoveChan;

class BG
{
public:
	BG(MoveChan& movechan);
	~BG();

	void Update(void);
	void Draw(void);
	void Draw2(void);
private:
	constexpr static float VEL_1 = 4.f;
	constexpr static float VEL_2 = 2.f;
	constexpr static int   BG_MAX = 2;

	math::Float2 m_Pos[BG_MAX];
	math::Float2 m_Pos2[BG_MAX];
	math::Float2 m_Pos3[BG_MAX];
	math::Float2 m_Size;

	Texture m_Tex;
	Texture m_Tex2;
	Texture m_Tex3;
	Texture m_Tex4;

	Texture m_Bug;
	Texture m_Goal;

	MoveChan& m_MoveChan;
};

