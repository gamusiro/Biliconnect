#include "Timer.h"

using namespace math;

Timer::Timer() : m_Size(Float2(70, 70)), m_Second(0), m_Minute(0), m_Timer(0)
{
	m_Tex.Create("num.png", 10, 1);
}

void Timer::Update()
{
	m_Timer++;

	if (m_Timer > 59)
	{
		m_Second += 1;
		m_Timer = 0;
	}
	if (m_Second > 59)
	{
		m_Minute += 1;
		m_Second = 0;
	}
}

void Timer::Draw()
{
	//////////////////////////	秒	///////////////////////////////
	int second = m_Second;

	for (int i = 0; i < 2; i++)
	{
		float x = (float)(second % 10);

		float px = 1800 + DISTANCE_X * i;
		float py = 200;
		float pw = m_Size.x;
		float ph = m_Size.y;

		float tw = 1.0f / 10;		// テクスチャの幅
		float tx = x * tw;			// テクスチャの左上X座標
		float ty = 0.0f;			// テクスチャの左上Y座標

		m_Tex.SetStartUVPosition(Float2(tx, ty));

		Sprite::DrawLeftTop(Float2(px, py), Float2(pw, ph), &m_Tex);

		// 次の桁へ
		second /= 10;
	}

	//////////////////////////	分	///////////////////////////////
	int minute = m_Minute;
	float x = (float)(minute % 10);

	float px = 1600;
	float py = 200;
	float pw = m_Size.x;
	float ph = m_Size.y;

	float tw = 1.0f / 10;		// テクスチャの幅
	float tx = x * tw;			// テクスチャの左上X座標
	float ty = 0.0f;			// テクスチャの左上Y座標

	m_Tex.SetStartUVPosition(Float2(tx, ty));

	Sprite::DrawLeftTop(Float2(px, py), Float2(pw, ph), &m_Tex);
}
