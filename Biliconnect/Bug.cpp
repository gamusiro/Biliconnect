#include "Bug.h"
#include "Stage.h"
#include "MoveChan.h"
#include "SEManager.h"
#include "GoalEffect.h"
#include "BossBlock.h"
#include <random>

Bug::Bug(MoveChan& movechan) : m_MoveChan(movechan), trigger(false)
{
	m_GoalEffect.Init();
	Bug::Reset();

	std::random_device randoms;
	std::mt19937 rando(randoms());

	for (int i = 0; i < BUG_MAX; i++)
	{
		m_Pos[i] = { static_cast<float>(rando() % SCREEN_WIDTH), static_cast<float>(rando() % SCREEN_HEIGHT) };
		m_Pos2[i] = { static_cast<float>(rando() % SCREEN_WIDTH), m_Pos[i].y + SCREEN_HEIGHT };

		int random = rand() % 3;

		timer[i] = -50 * random;

		m_Color[i] = { 1.0f,1.0f,1.0f,0.7f };

		if (random == 0)
			m_Bug[i].Create("last_glitch001.png", 4, 4, 3);
		if (random == 1)
			m_Bug[i].Create("last_glitch002.png", 4, 4, 3);
		if (random == 2)
			m_Bug[i].Create("last_glitch003.png", 4, 4, 3);
	}

	timer2 = 0;

	count = 0;
	bugtimer = rando() % 220 + 200;

	count2 = 0;
	bugtimer2 = rando() % 220 + 100;

	m_Size = { 120 , 120 };

	Texture window;
	window.Create("error_anim.png", 9, 2, 2);

	for (int i = 0; i < WINDOW_MAX; i++)
	{
		m_Window[i].Create(nullptr, 9, 2, 2);
		m_Window[i].SetImageID(window.GetTextureID());
		m_WinColor[i] = m_Color[i] = { 1.f,1.f,1.f,ALPHA };
	}

	deleteTimer[0] = 0;
	deleteTimer[1] = 3;
	deleteTimer[2] = 8;
	deleteTimer[3] = 12;

	m_WinSize = { 500 , 500 };
}

Bug::~Bug()
{
}

void Bug::Update(void)
{
	std::random_device randoms;
	std::mt19937 rando(randoms());
	
	count++;
	count2++;

	if (count > bugtimer)
	{
		SEManager::Play(SOUND::BUG);
		count = 0;
		bugtimer = rando() % 60 + 140;
	}
	if (count2 > bugtimer2)
	{
		SEManager::Play(SOUND::BUG2);
		count2 = 0;
		bugtimer2 = rando() % 70 + 140;
	}


	if (!trigger)
	{
		if (!m_MoveChan.GetDeath() && !StageStart::Get())
		{
			if (Stage::m_MoveNow.y < Stage::m_MoveMax - SCREEN_HEIGHT)
			{
				for (int i = 0; i < BUG_MAX; i++)
				{
					m_Pos[i].y -= VEL;
					m_Pos2[i].y -= VEL;

					if (m_Pos[i].y < -(SCREEN_HEIGHT * 0.5f))
						m_Pos[i].y += SCREEN_HEIGHT * 2;
					if (m_Pos2[i].y < -(SCREEN_HEIGHT * 0.5f))
						m_Pos2[i].y += SCREEN_HEIGHT * 2;
				}
			}
		}

		for (int i = 0; i < BUG_MAX; i++)
		{
			m_Bug[i].Update();

			timer[i]++;
			if (timer[i] > 50 && m_Color[i].w == 0.7f)
			{
				timer[i] = 0;
				m_Color[i].w = 0;
			}
			if (timer[i] > 50 && m_Color[i].w == 0)
			{
				timer[i] = 0;
				m_Color[i].w = 0.7f;
			}
		}
	}
	else if (trigger)
	{
		timer2++;

		if (timer2 > 130)
		{
			for (int i = 0; i < BUG_MAX; i++)
			{
				m_Size.x += 0.07f;
				m_Color[i].w -= 0.01f;
				m_WinColor[i].w -= 0.01f;
			}
		}
		if (timer2 == 130)
			Delete();
	}

	m_GoalEffect.Update();

	if (m_GoalEffectON)
		m_GoalEffect.Set(BossBlock::Get());


	// ウィンドウエフェクト！

	for (int i = 0; i < WINDOW_MAX; i++)
	{
		m_Window[i].Update();

		deleteTimer[i]++;

		if (deleteTimer[i] > INTERVAL && m_WinColor[i].w == ALPHA)
		{
			deleteTimer[i] = 0;
			m_WinColor[i].w = 0;
		}
		if (deleteTimer[i] > INTERVAL && m_WinColor[i].w == 0)
		{
			m_WinPos[i].x = rando() % SCREEN_WIDTH;
			m_WinPos[i].y = rando() % SCREEN_HEIGHT;

			deleteTimer[i] = 0;
			m_WinColor[i].w = ALPHA;
		}
	}

	
}

void Bug::Draw(void)
{
	for (int i = 0; i < BUG_MAX; i++)
	{
		if (Wintri)
		Sprite::DrawCenter(m_Pos[i], m_Size, &m_Bug[i], m_Color[i]);
	}
	for (int i = 0; i < BUG_MAX; i++)
	{
		if (Wintri)
		Sprite::DrawCenter(m_Pos2[i], m_Size, &m_Bug[i], m_Color[i]);
	}

	m_GoalEffect.Draw();
}

void Bug::Draw2(void)
{
	for (int i = 0; i < WINDOW_MAX; i++)
	{
		if (Wintri)
			Sprite::DrawCenter(m_WinPos[i], m_WinSize, &m_Window[i], m_WinColor[i]);
	}
}

void Bug::Delete()
{
	for (int i = 0; i < BUG_MAX; i++)
	{
		m_Color[i].w = 1;
	}
}

void Bug::Explode()
{
	trigger = true;
	m_GoalEffectON = true;
}
