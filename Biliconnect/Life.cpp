/*=========================================================================
	Date : 2021/04/04(ŒŽ)	Life.h
		Author : A.I.
		Update :
=========================================================================*/
#include "Life.h"

using namespace math;

Life::Life(math::Float2 pos, int num)
	: m_Pos(Float2(pos.x + num * SIZE, pos.y)), m_Size(Float2(SIZE, SIZE)), m_Color(Float4(1, 1, 1, 1)), m_Active(true)
{
	m_Tex.Create("Life.png", 1, 1);
	m_Texout.Create("Lifeout.png", 1, 1);
}

void Life::Update()
{
	/*if (m_Active && m_Color.x <= COLOR_MAX)
	{
		m_Color.x += COLOR_RATE;
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
	}*/
	if (m_Active && m_Frame != 0)
	{
		m_Frame = 0;
		m_Size = Float2(SIZE * 1.3, SIZE * 1.3);
		m_Color.w = 0;
	}

	if (m_Active && m_Color.w < COLOR_MAX)
	{
		m_Size -= 1;
		m_Color.w += 0.025f;
	}
	else if (!m_Active)
	{
		m_Size += 0.4f;
		++m_Frame;
		if (m_Frame % FLASH_RATE == 0)
		{
			if (m_Color.w == ALFA_MAX) m_Color.w = ALFA_MIN;
			else					   m_Color.w = ALFA_MAX;
		}
		if (m_Frame > 60)
		{
			m_Size = Float2(SIZE * 1.3, SIZE * 1.3);
			m_Color.w = 0;
		}
	}
}

void Life::Draw()
{
	Sprite::DrawCenter(m_Pos, Float2(SIZE + 4, SIZE + 4), &m_Texout);
	Sprite::DrawCenter(m_Pos, Float2(m_Size.x, m_Size.y), &m_Tex, m_Color);
}

void Life::ActivateChange()
{
	m_Active = !m_Active;
}
