#include "GoalEffect.h"
#include "Stage.h"
#include <random>

using namespace math;

GoalEffect::GoalEffect()
{
}

void GoalEffect::Init()
{
	m_Tex[USING_TEX].Create("bug5.png", 5, 2);
	m_Tex[TEX_1].Create("last_glitch003.png", 4, 4, 3);
	m_Tex[TEX_2].Create("fx_bug002.png", 4, 4, 3);
	m_Tex[TEX_3].Create("bug_block_003.png", 4, 4, 3);

	for (int i = 0; i < MAX; i++)
	{
		m_Use[i] = false;
	}
	m_Frame = 0;

	m_Rad = 0;
	m_Vol = 50;
	trigger = false;
}

void GoalEffect::Uninit()
{
}

void GoalEffect::Update()
{
	if (trigger)
	{
		float a = std::cosf(m_Rad);
		Stage::SetShake({ a * m_Vol,a * m_Vol });
		m_Rad += 10.f;
		if (m_Vol > 1.f)
		{
			m_Vol *= 0.95f; Controller::SetVibration(65535);
		}
		else
		{
			m_Vol = 0; m_Rad = 0; trigger = false;
		}
	}

	m_Frame++;

	for (int i = 0; i < MAX; i++)
	{
		if (m_Use[i])
		{
			m_Pos[i] += m_Vel[i];
		}
	}
}

void GoalEffect::Draw()
{
	m_Tex[USING_TEX].Update();
	for (int i = 0; i < MAX; i++)
	{
		if (m_Use[i])
		{
			if (i % 3 == 0)
			Sprite::DrawCenter(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_Tex[TEX_1], m_Col[i], (float)m_Rot[i]);
			if(i % 3 == 1)
			Sprite::DrawCenter(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_Tex[TEX_2], m_Col[i], (float)m_Rot[i]);
			if (i % 3 == 2)
			Sprite::DrawCenter(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_Tex[TEX_3], m_Col[i], (float)m_Rot[i]);
		}
	}
}

void GoalEffect::Set(math::Float2 pos)
{
	std::random_device randoms;
	std::mt19937 rando(randoms());

	trigger = true;
	int cnt = 0;

	for (int i = 0; i < MAX; i++)
	{
		if (!m_Use[i])
		{
			int temp = rando() % 360;
			int temp2 = rando() % 3;
			//ランダムなテクスチャ設定
			switch (temp2)
			{
			case 0:
				m_Tex[USING_TEX] = m_Tex[TEX_1];
			case 1:
				m_Tex[USING_TEX] = m_Tex[TEX_2];
			case 2:
				m_Tex[USING_TEX] = m_Tex[TEX_3];
			default:
				m_Tex[USING_TEX] = m_Tex[TEX_3];
			}

			m_Pos[i] = math:: Float2(pos.x, pos.y);
			m_Vel[i] = math::Float2(sinf((float)temp) * 70.0f, cosf((float)temp) * 70.0f);
			int tempSize = rando() % 3;
			if (tempSize == 0)
				m_Size[i] = math::Float2(RESET_SIZE, RESET_SIZE);
			if (tempSize == 1)
				m_Size[i] = math::Float2(RESET_SIZE * 2.0f, RESET_SIZE * 2.0f);
			if (tempSize == 2)
				m_Size[i] = math::Float2(RESET_SIZE * 4.0f, RESET_SIZE * 4.0f);
			m_Col[i] = math::Float4(1.0f, 1.0f, 1.0f, 1.0f);
			m_Rot[i] = temp;
			m_Use[i] = true;
			m_FrameSinceToSet[i] = 0;

			cnt++;
			if (cnt > 5)
			break;
		}
	}
}
