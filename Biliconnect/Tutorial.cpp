#include "Tutorial.h"
#include "Stage.h"
#include "SEManager.h"

using namespace math;

Tutorial::Tutorial()
{
	m_Tuto[TUTO_1].Create("Tutorial/tutorial_01.png", 1, 1);
	m_Tuto[TUTO_2].Create("Tutorial/tutorial_02.png", 1, 1);
	m_Tuto[TUTO_3].Create("Tutorial/tutorial_03.png", 1, 1);
	m_Tuto[TUTO_4].Create("Tutorial/tutorial_04.png", 1, 1);
	m_Tuto[TUTO_5].Create("Tutorial/tutorial_05.png", 1, 1);
	m_Tuto[TUTO_6].Create("Tutorial/tutorial_06.png", 1, 1);
	m_Tuto[TUTO_7].Create("Tutorial/tutorial_07.png", 1, 1);
	m_Tuto[TUTO_8].Create("Tutorial/tutorial_08.png", 1, 1);
	m_Tuto[TUTO_9].Create("Tutorial/tutorial_09.png", 1, 1);
	m_Tuto[TUTO_10].Create("Tutorial/tutorial_10.png", 1, 1);
}

Tutorial::~Tutorial()
{
}

void Tutorial::Init(void)
{
	for (int i = 0; i < TUTO_MAX; i++)
	{
		m_Pos[i] = Float2(50, 57);
		m_Vel[i] = Float2(0, 0);
		m_Size[i] = Float2(SCREEN_WIDTH - 100, SCREEN_HEIGHT);
		m_Color[i] = Float4(1, 1, 1, 0);
	}

	m_timer = 0;
	num = 0;
}

void Tutorial::Uninit(void)
{
}

void Tutorial::Update(void)
{
	if (!StageStart::Get())
	{
		if (StageNum::Get() == 25 && num < 5)
		{
			m_timer++;
			if (m_timer == 10)
				SEManager::Play(SOUND::HYOI);
			else if (m_timer < 30)
			{
				m_Vel[num].y -= 2.0f;
				m_Color[num].w += 0.0335f;
			}
			else if (m_timer < 120)
			{
				if (m_timer == 119)
					SEManager::Play(SOUND::DOWN);
			}
			else if (m_timer < 132)
			{
				m_Vel[num].x -= 4.2f;
				m_Vel[num].y += 13.0f;
				m_Size[num].x -= SCREEN_WIDTH / 18;
				m_Size[num].y -= SCREEN_HEIGHT / 18;
			}
			else if (m_timer > 900)
			{
				if (m_Color[num].w < 0)
				{
					num += 1;
					m_timer = 0;
					m_Vel[num] += 0.0f;
				}
				if (m_timer == 901)
					SEManager::Play(SOUND::HYON);
				m_Color[num].w -= 0.0335f;
			}
		}
		if (StageNum::Get() == 0 && num < 1)
		{
			m_timer++;
			if (m_timer == 10)
				SEManager::Play(SOUND::HYOI);
			else if (m_timer < 30)
			{
				m_Vel[TUTO_6].y -= 2.0f;
				m_Color[TUTO_6].w += 0.0335f;
			}
			else if (m_timer < 120)
			{
				if (m_timer == 119)
					SEManager::Play(SOUND::DOWN);
			}
			else if (m_timer < 132)
			{
				m_Vel[TUTO_6].x -= 4.2f;
				m_Vel[TUTO_6].y += 13.0f;
				m_Size[TUTO_6].x -= SCREEN_WIDTH / 18;
				m_Size[TUTO_6].y -= SCREEN_HEIGHT / 18;
			}
			else if (m_timer > 640)
			{
				if (m_Color[TUTO_6].w < 0)
				{
					num += 1;
					m_timer = 0;
					m_Vel[TUTO_6] += 0.0f;
				}
				if (m_timer == 641)
					SEManager::Play(SOUND::HYON);
				m_Color[TUTO_6].w -= 0.0335f;
			}
		}
		if (StageNum::Get() == 2 && num < 1)
		{
			m_timer++;
			if (m_timer == 10)
				SEManager::Play(SOUND::HYOI);
			else if (m_timer < 30)
			{
				m_Vel[TUTO_7].y -= 2.0f;
				m_Color[TUTO_7].w += 0.0335f;
			}
			else if (m_timer < 120)
			{
				if (m_timer == 119)
					SEManager::Play(SOUND::DOWN);
			}
			else if (m_timer < 132)
			{
				m_Vel[TUTO_7].x -= 4.2f;
				m_Vel[TUTO_7].y += 13.0f;
				m_Size[TUTO_7].x -= SCREEN_WIDTH / 18;
				m_Size[TUTO_7].y -= SCREEN_HEIGHT / 18;
			}
			else if (m_timer > 640)
			{
				if (m_Color[TUTO_7].w < 0)
				{
					num += 1;
					m_timer = 0;
					m_Vel[TUTO_7] += 0.0f;
				}
				if (m_timer == 641)
					SEManager::Play(SOUND::HYON);
				m_Color[TUTO_7].w -= 0.0335f;
			}
		}
		if (StageNum::Get() == 7 && num < 1)
		{
			m_timer++;
			if (m_timer == 10)
				SEManager::Play(SOUND::HYOI);
			else if (m_timer < 30)
			{
				m_Vel[TUTO_8].y -= 2.0f;
				m_Color[TUTO_8].w += 0.0335f;
			}
			else if (m_timer < 120)
			{
				if (m_timer == 119)
					SEManager::Play(SOUND::DOWN);
			}
			else if (m_timer < 132)
			{
				m_Vel[TUTO_8].x -= 4.2f;
				m_Vel[TUTO_8].y += 13.0f;
				m_Size[TUTO_8].x -= SCREEN_WIDTH / 18;
				m_Size[TUTO_8].y -= SCREEN_HEIGHT / 18;
			}
			else if (m_timer > 640)
			{
				if (m_Color[TUTO_8].w < 0)
				{
					num += 1;
					m_timer = 0;
					m_Vel[TUTO_8] += 0.0f;
				}
				if (m_timer == 641)
					SEManager::Play(SOUND::HYON);
				m_Color[TUTO_8].w -= 0.0335f;
			}
		}
		if (StageNum::Get() == 10 && num < 1)
		{
			m_timer++;
			if (m_timer == 10)
				SEManager::Play(SOUND::HYOI);
			else if (m_timer < 30)
			{
				m_Vel[TUTO_9].y -= 2.0f;
				m_Color[TUTO_9].w += 0.0335f;
			}
			else if (m_timer < 120)
			{
				if (m_timer == 119)
					SEManager::Play(SOUND::DOWN);
			}
			else if (m_timer < 132)
			{
				m_Vel[TUTO_9].x -= 4.2f;
				m_Vel[TUTO_9].y += 13.0f;
				m_Size[TUTO_9].x -= SCREEN_WIDTH / 18;
				m_Size[TUTO_9].y -= SCREEN_HEIGHT / 18;
			}
			else if (m_timer > 640)
			{
				if (m_Color[TUTO_9].w < 0)
				{
					num += 1;
					m_timer = 0;
					m_Vel[TUTO_9] += 0.0f;
				}
				if (m_timer == 641)
					SEManager::Play(SOUND::HYON);
				m_Color[TUTO_9].w -= 0.0335f;
			}
		}
		if (StageNum::Get() == 16 && num < 1)
		{
			m_timer++;
			if (m_timer == 10)
				SEManager::Play(SOUND::HYOI);
			else if (m_timer < 30)
			{
				m_Vel[TUTO_10].y -= 2.0f;
				m_Color[TUTO_10].w += 0.0335f;
			}
			else if (m_timer < 120)
			{
				if (m_timer == 119)
					SEManager::Play(SOUND::DOWN);
			}
			else if (m_timer < 132)
			{
				m_Vel[TUTO_10].x -= 4.2f;
				m_Vel[TUTO_10].y += 13.0f;
				m_Size[TUTO_10].x -= SCREEN_WIDTH / 18;
				m_Size[TUTO_10].y -= SCREEN_HEIGHT / 18;
			}
			else if (m_timer > 640)
			{
				if (m_Color[TUTO_10].w < 0)
				{
					num += 1;
					m_timer = 0;
					m_Vel[TUTO_10] += 0.0f;
				}
				if (m_timer == 641)
					SEManager::Play(SOUND::HYON);
				m_Color[TUTO_10].w -= 0.0335f;
			}
		}
	}
}

void Tutorial::Draw(void)
{
	for (int i = 0; i < TUTO_MAX; i++)
		Sprite::DrawLeftTop(m_Pos[i] + m_Vel[i], m_Size[i], &m_Tuto[i], m_Color[i]);
}
