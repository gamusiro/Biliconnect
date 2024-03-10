/*=========================================================================
	Date : 2021/03/06(日)	Line.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "Line.h"
#include "Stage.h"

#include <cmath>

using namespace math;

Line::Line(math::Float2& startpos, math::Float2& endpos)
	: m_StartPos(startpos), m_EndPos(endpos)
{
	m_DistanceSE = m_EndPos - m_StartPos;

	m_Start = math::Float2((m_StartPos.x + 50), m_StartPos.y);
	m_End = math::Float2((m_EndPos.x - 50), m_EndPos.y);
	m_Tex.Create("result_bg.png",100,1);
}

void Line::Update()
{
	m_Start = math::Float2((m_StartPos.x + 50), m_StartPos.y);
	m_End = math::Float2((m_EndPos.x - 50), m_EndPos.y);

	m_DistanceSE = m_End - m_Start;												// 2点間XY距離更新

	m_Pos = MathFloat::Lerp(m_Start, m_End, 0.5f);								// 中心座標更新

	m_Frame++;
}

void Line::Draw()
{
	float rad = std::atan2f(m_DistanceSE.y, m_DistanceSE.x) / MY_O_PI * 180.0f;	// 角度計算
	m_Size.x = MathFloat::Length(m_DistanceSE);									// 長さ計算

	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, Float2(m_Size.x, m_Size.y), &m_Tex, m_Color, rad);

	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, Float2(m_Size.x, m_Size.y), &m_Tex, m_Color, rad);

	m_Color.x = sinf(m_Frame * 0.1f) * 0.4f + 1.5f;
	m_Color.y = sinf(m_Frame * 0.1f) * 0.4f + 1.5f;
	m_Color.z = sinf(m_Frame * 0.1f) * 0.4f + 0;


}
