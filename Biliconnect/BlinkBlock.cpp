#include "Stage.h"
#include "MoveChan.h"
#include "Block.h"
#include "BlinkBlock.h"

using namespace math;

BlinkBlock::BlinkBlock(BLOCKTYPE type, float interval, math::Float2 pos, int num, int color)
	: Block(type, pos, Float2(120,120), num, color), timer(0), m_Rad(0), m_Interval(interval)
{
	// èâä˙âª
	m_Type = type;

	isBlink = true;

	/*if (m_Type == BLOCKTYPE::BLOCK)
	m_Tex.Create("enemy_green.png", 5, 2, 10);
	m_Tex.SetCurrentTexture(1);	m_Tex.Update();*/
	m_Color = { 1,1,1,1 };

	if (m_Type == BLOCKTYPE::BLOCK)
	{
		int random = rand() % 3;

		if (random == 0)
			EffectTex.Create("fx_bug001.png", 4, 4, 3);
		if (random == 1)
			EffectTex.Create("fx_bug002.png", 4, 4, 3);
		if (random == 2)
			EffectTex.Create("fx_bug003.png", 4, 4, 3);

		m_Rot = 0;
	}

	if (interval < 0)
	{
		timer = (int)(INTERVAL * m_Interval);
		m_Interval *= -1;
	}
}

void BlinkBlock::Update()
{
#if 0
	m_Rad += ADDRAD;

	if (m_Rad > LIMIT)
	{
		m_Rad = 0;
	}

	m_Color.w = 1 - 1 * std::sinf(m_Rad * MY_O_PI);
#elif 1
	EffectTex.Update();
	timer++;
	if (timer >= INTERVAL * m_Interval)
	{
		if(m_Color.w <= 0.3f)
			m_Color.w = 1.0f;
		else if (m_Color.w >= 0.99f)
			m_Color.w = 0.3f;

		timer = 0;
	}
#else
	m_Color = { 0,1,1,1 };
#endif
}

void BlinkBlock::CollisionAction()
{
	/*if (m_Color.w >= 0.99f)
	m_Color = { 0,0,0,1 };*/
}
