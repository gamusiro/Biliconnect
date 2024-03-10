#include "BG.h"
#include "Stage.h"
#include "MoveChan.h"

BG::BG(MoveChan& movechan): m_MoveChan(movechan)
{
	for (int i = 0; i < BG_MAX; i++)
	{
		m_Pos[i] = { SCREEN_WIDTH * 0.5f, (float)i * SCREEN_HEIGHT + (SCREEN_HEIGHT * 0.5f) };
		m_Pos2[i] = { SCREEN_WIDTH * 0.5f, (float)i * SCREEN_HEIGHT + (SCREEN_HEIGHT * 0.5f) };
		m_Pos3[i] = { SCREEN_WIDTH * 0.5f, (float)i * SCREEN_HEIGHT + (SCREEN_HEIGHT * 0.5f) };
	}

	m_Size = { SCREEN_WIDTH , SCREEN_HEIGHT };

	m_Tex.Create("all_2.png", 10, 5, 2);
	m_Goal.Create("goal.png", 1, 1);

	int num = StageNum::Get();
	if (num < 5 && num >= 0 )
	{
		m_Tex2.Create("Stage/1_bg.png", 1, 1);
		m_Tex3.Create("Stage/1_2.png", 1, 1);
		m_Tex4.Create("Stage/1_1.png", 1, 1);
	}
	else if (num < 10 && num >= 5)
	{
		m_Tex2.Create("Stage/2_bg.png", 1, 1);
		m_Tex3.Create("Stage/2_2.png", 1, 1);
		m_Tex4.Create("Stage/2_1.png", 1, 1);
	}
	else if (num < 15 && num >= 10)
	{
		m_Tex2.Create("Stage/3_bg.png", 1, 1);
		m_Tex3.Create("Stage/3_2.png", 1, 1);
		m_Tex4.Create("Stage/3_1.png", 1, 1);
	}
	else if (num < 20 && num >= 15)
	{
		m_Tex2.Create("Stage/4_bg.png", 1, 1);
		m_Tex3.Create("Stage/4_2.png", 1, 1);
		m_Tex4.Create("Stage/4_1.png", 1, 1);
	}
	else if (num < 25 && num >= 20)
	{
		m_Tex2.Create("Stage/5_bg.png", 1, 1);
		m_Tex3.Create("Stage/5_2.png", 1, 1);
		m_Tex4.Create("Stage/5_1.png", 1, 1);
	}
	else if (num == 25)
	{
		m_Tex2.Create("Stage/1_bg.png", 1, 1);
		m_Tex3.Create("Stage/1_2.png", 1, 1);
		m_Tex4.Create("Stage/1_1.png", 1, 1);
	}
}

BG::~BG()
{
}

void BG::Update(void)
{
	m_Tex.Update();

	if (!m_MoveChan.GetDeath() && !StageStart::Get())
	{
		if (Stage::m_MoveNow.y < Stage::m_MoveMax - SCREEN_HEIGHT)
		{
			for (int i = 0; i < BG_MAX; i++)
			{
				m_Pos[i].y -= VEL_2;

				if (StageNum::Get() == 23)
					m_Pos2[i].y -= 6;
				else
					m_Pos2[i].y -= VEL_1*0.7f;

				if (StageNum::Get() == 23)
					m_Pos3[i].y -= 7.2f;
				else
				m_Pos3[i].y -= VEL_1*0.9f;

				if (m_Pos[i].y < -(SCREEN_HEIGHT * 0.5f))
					m_Pos[i].y += SCREEN_HEIGHT * 2;

				if (m_Pos2[i].y < -(SCREEN_HEIGHT * 0.5f))
					m_Pos2[i].y += SCREEN_HEIGHT * 2;

				if (m_Pos3[i].y < -(SCREEN_HEIGHT * 0.5f))
					m_Pos3[i].y += SCREEN_HEIGHT * 2;
			}
		}
	}
}

void BG::Draw(void)
{
	for (int i = 0; i < BG_MAX; i++)
	{
		Sprite::DrawCenter(m_Pos[i], m_Size, &m_Tex2);
		Sprite::DrawCenter(m_Pos[i], m_Size, &m_Tex);
	}
	for (int i = 0; i < BG_MAX; i++)
	{
		Sprite::DrawCenter(m_Pos2[i], m_Size, &m_Tex4);
		//Sprite::DrawCenter(m_Pos2[i], m_Size, &m_Tex3);
		//Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_Tex5);
	}

	// 真ん中のライン
	Sprite::DrawCenter(math::Float2(5, SCREEN_HEIGHT * 0.5f), math::Float2(10, SCREEN_HEIGHT), nullptr, math::Float4(1, 0, 0.6f, 0.6f));
	Sprite::DrawCenter(math::Float2((SCREEN_WIDTH - 100) * 0.5f - 50, SCREEN_HEIGHT * 0.5f), math::Float2(10, SCREEN_HEIGHT), nullptr, math::Float4(1,0,0.6f,0.6f));
	Sprite::DrawCenter(math::Float2((SCREEN_WIDTH + 100) * 0.5f + 50, SCREEN_HEIGHT * 0.5f), math::Float2(10, SCREEN_HEIGHT), nullptr, math::Float4(0, 0.7f, 1, 0.6f));
	Sprite::DrawCenter(math::Float2(SCREEN_WIDTH - 5, SCREEN_HEIGHT * 0.5f), math::Float2(10, SCREEN_HEIGHT), nullptr, math::Float4(0, 0.7f, 1, 0.6f));
}

void BG::Draw2(void)
{
	math::Float2 tempSize = m_Size;
	tempSize *= 1.02f;

	for (int i = 0; i < BG_MAX; i++)
	{
		Sprite::DrawCenter(m_Pos3[i], tempSize, &m_Tex3,math::Float4(1.0f, 1.0f, 1.0f,0.8f));
	}

	int num = StageNum::Get() % 5;

	if (num != 4)
	{
		// ゴールライン
		//Sprite::DrawCenter(math::Float2(SCREEN_WIDTH * 0.5f, (Stage::m_MoveMax - SCREEN_HEIGHT * 0.5f) - Stage::m_MoveNow.y), math::Float2(SCREEN_WIDTH, 10), nullptr, math::Float4(1, 1, 1, 0.8f));

		Sprite::DrawCenter(math::Float2(SCREEN_WIDTH * 0.5f, (Stage::m_MoveMax) - Stage::m_MoveNow.y - SCREEN_HEIGHT / 2), math::Float2(SCREEN_WIDTH, SCREEN_HEIGHT), &m_Goal, math::Float4(1, 1, 1, 1.0f));
	}
}