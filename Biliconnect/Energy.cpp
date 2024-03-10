/*=========================================================================
	Date : 2021/05/03(‰Î)	Energy.cpp
		Author : Mr.
		Update :
=========================================================================*/
#include "Energy.h"

using namespace math;

Energy::Energy(math::Float2 pos, int num)
	: m_Pos(Float2(pos.x - num * SIZE, pos.y)), m_Color(Float4(1, 1, 1, 1)), m_Active(true)
{
	m_Tex.Create("Life.png", 1, 1);
	m_Texout.Create("Lifeout.png", 1, 1);
}

void Energy::Update()
{
	if (m_Active && m_Color.x <= COLOR_MAX)
	{
		m_Color.x += COLOR_RATE * 4;
		m_Color.y = m_Color.x;
		m_Color.z = m_Color.x;
		m_Color.w = m_Color.x;
	}
	else if (!m_Active && m_Color.x >= COLOR_MIN)
	{
		m_Color.x -= COLOR_RATE;
		m_Color.y = m_Color.x;
		m_Color.z = m_Color.x;
		m_Color.w = m_Color.x;
	}
}

void Energy::Draw()
{
	Sprite::DrawCenter(m_Pos, Float2(SIZE + 4, SIZE + 4), &m_Texout);
	Sprite::DrawCenter(m_Pos, Float2(SIZE, SIZE), &m_Tex, m_Color);
}

void Energy::ActivateChange()
{
	m_Active = !m_Active;
}
