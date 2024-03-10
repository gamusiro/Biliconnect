#include "StageTelop.h"
#include "Stage.h"
#include "Bug.h"
#include "SEManager.h"
#include "Game.h"

using namespace math;

StageTelop::StageTelop()
{
	StageTelop::Reset();
	Telop.Create("mojihai.png", 1, 1, 1);

	Num_1.Create("num.png", 10, 1, 1);
	Num_2.Create("num.png", 10, 1, 1);

	if(StageNum::Get() == 25)
		Slash.Create("tutorial2.png", 1, 1, 1);
	else 
		Slash.Create("sl.png", 1, 1, 1);

	Mojihai.Create("mojihai.png", 1, 1, 1);
	Warning.Create("warning.png", 1, 1, 1);
	Kome.Create("kome.png", 1, 1, 1);
	Waku.Create("suuji_waku.png", 1, 1, 1);

	int num_1 = (StageNum::Get() / 5) + 1;
	int num_2 = (StageNum::Get() % 5) + 1;

	Num_1.SetCurrentTexture(num_1); Num_1.Update();
	Num_2.SetCurrentTexture(num_2); Num_2.Update();

	m_Pos = {-SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	m_Size = { SCREEN_WIDTH, 700 };

	m_NumPos = { SCREEN_WIDTH + SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	m_NumSize = { 170, 170 };

	m_WarPos = { -SCREEN_WIDTH / 2, +SCREEN_HEIGHT + 175 };
	m_WarVel = { 0, 0 };
	m_WarSize = { SCREEN_WIDTH + 100, 700 };
	m_WarColor = { 1 , 0,0,0.2f };
	m_WarColor2 = { 1 , 1,1,0 };

	trigger = true;
	m_Frame = 0;
	m_Frame2 = 0;
	AddVel = 0;
}

StageTelop::~StageTelop()
{
}

void StageTelop::Update(void)
{	
	if(m_Pos.x < SCREEN_WIDTH / 2 - 100)
	m_Pos.x += 60;

	if (m_Pos.x >= SCREEN_WIDTH / 2 - 100 && m_Pos.x <= SCREEN_WIDTH / 2 + 100)
		m_Pos.x += 3;

	if (m_Pos.x > SCREEN_WIDTH / 2 + 100)
		m_Pos.x += 60;

	if (m_NumPos.x > SCREEN_WIDTH / 2 + 100)
		m_NumPos.x -= 60;

	if (m_NumPos.x <= SCREEN_WIDTH / 2 + 100 && m_NumPos.x >= SCREEN_WIDTH / 2 - 100)
		m_NumPos.x -= 3;

	if (m_NumPos.x < SCREEN_WIDTH / 2 - 100)
		m_NumPos.x -= 60;

	if (isWarning)
	{
		if (m_Frame == INTERVAL)
		{
			if (trigger)
				trigger = false;
			else
				trigger = true;

			m_Frame = 0;
		}
		else if (m_Frame <= INTERVAL)
		{
			if (trigger)
				m_WarColor.w += 0.013f;
			else
				m_WarColor.w -= 0.013f;
		}

		if (m_Frame2 > 70 && m_Frame2 < 90)
		{
			m_WarColor2.w += 0.050f;
		}
		if (m_Frame2 > 90)
		{
			AddVel += 1.1f;
		}

		if (m_Frame2 > 90 && m_WarVel.x < SCREEN_WIDTH - 40)
		{
			m_WarVel.x += 0.93969262078591f * ((float)67 - AddVel);
			m_WarVel.y += -0.34202014332566f * ((float)67 - AddVel);
		}
		else if (m_Frame2 > 90 && m_WarVel.x > SCREEN_WIDTH - 40 && m_WarVel.x < SCREEN_WIDTH + 40)
		{
			m_WarVel.x += 0.93969262078591f * 1.5f;
			m_WarVel.y += -0.34202014332566f * 1.5f;
			AddVel = 0;
		}
		else if (m_Frame2 > 90 && m_WarVel.x > SCREEN_WIDTH + 40)
		{
			m_WarVel.x += 0.93969262078591f * AddVel;
			m_WarVel.y += -0.34202014332566f * AddVel;
		}

		// ‚Ä‚ñ‚ß‚Â
		m_Frame2++;

		if (m_Frame2 == 285)
			Bug::Set();

		if (m_Frame2 > 280)
		{
			trigger = false;
			m_WarColor.w -= 0.013f;
			m_WarColor2 -= 0.06f;
		}
		else
			m_Frame++;
	}
	else
	{
		
	}
}

void StageTelop::Draw(void)
{
	Sprite::DrawCenter(m_Pos, m_Size, &Telop);

	if (StageNum::Get() != 25)
	{
		Sprite::DrawCenter(Float2(m_NumPos.x - 220, m_NumPos.y), m_NumSize, &Num_1);
		Sprite::DrawCenter(m_NumPos, Float2(m_NumSize.x + 25, m_NumSize.y + 25), &Slash, { 1,1,1,1 }, 45);
		Sprite::DrawCenter(Float2(m_NumPos.x + 220, m_NumPos.y), m_NumSize, &Num_2);
	}
	if (StageNum::Get() == 25)
	Sprite::DrawCenter(m_NumPos, Float2(m_NumSize.x * 4.5f, m_NumSize.y * 3), &Slash, { 1,1,1,1 });

	if (isWarning)
	{
		Sprite::DrawCenter(Float2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Float2(SCREEN_WIDTH, SCREEN_HEIGHT), nullptr, m_WarColor);

		if(m_Frame2 > 70)
		Sprite::DrawCenter(Float2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), Float2(SCREEN_WIDTH + 300, SCREEN_HEIGHT / 3 + 550), &Mojihai, m_WarColor2, 340);
		Sprite::DrawCenter(m_WarPos + m_WarVel, Float2(SCREEN_WIDTH, SCREEN_HEIGHT), &Warning, {1,1,1,1}, 340);

		Sprite::DrawCenter(Float2(1650, 1000), Float2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4), &Kome, m_WarColor2);
	}
}
void StageTelop::Draw2(void)
{
	Sprite::DrawCenter(Float2(1720, 80), Float2(620, 260), &Waku, { 1,1,1,1.0f });

	if (StageNum::Get() != 25)
	{
		Sprite::DrawCenter(Float2(1720 + 70, 80), m_NumSize / 2, &Num_2);
		Sprite::DrawCenter(Float2(1720 - 40, 80), Float2(m_NumSize.x / 2 + 25, m_NumSize.y / 2 + 25), &Slash, { 1,1,1,1 }, 45);
		Sprite::DrawCenter(Float2(1720 - 150, 80), m_NumSize / 2, &Num_1);
	}
	if (StageNum::Get() == 25)
		Sprite::DrawCenter(Float2(1720 - 30, 75), Float2(m_NumSize.x * 2.0f, m_NumSize.y * 1.5f), &Slash, { 1,1,1,1 });
}

void StageTelop::SetWarning()
{
	isWarning = true;
}
