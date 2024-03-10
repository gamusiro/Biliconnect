#include "Stage.h"
#include "MoveChan.h"
#include "Block.h"
#include "MoveDossun.h"

using namespace math;

MoveDossun::MoveDossun(BLOCKTYPE type, Float2& movechanpos, float movechansize, math::Float2 length, math::Float2 pos, math::Float2 size)
	: Block(type, pos, size), m_MoveChanPos(movechanpos), m_MoveChanSize(movechansize)
{
	// 初期化
	m_Type = type;
	isDoss = true;

	if (m_Type == BLOCKTYPE::BLOCK)
	m_Tex.Create("dossun.png", 2, 1);
	m_Tex.SetCurrentTexture(0);	m_Tex.Update();
	m_Color = { 1,1,1,1 };

	m_PosA = Float2(pos.x, pos.y);
	m_PosB = Float2(pos.x + length.x, pos.y + length.y);
	m_Vel = 0;
	trigger = false;

	if (m_PosB.x > m_PosA.x)
		m_Rot = 270;
	if (m_PosA.x > m_PosB.x)
		m_Rot = 90;
	if (m_PosB.y > m_PosA.y)
		m_Rot = 0;
	if (m_PosA.y > m_PosB.y)
		m_Rot = 180;
}

void MoveDossun::Update()
{
	/*if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Update();*/

	m_Vel += 0.5f;
	if (!trigger)
		m_Vel = 0;


	//// 右ドッスン
	//if (m_PosB.x > m_PosA.x)
	//{
	//	if (math::MathCollision::Box(
	//		Float2(m_Pos.x + (m_PosB.x - m_PosA.x) / 2, m_PosA.y),
	//		m_MoveChanPos,
	//		Float2((m_PosB.x - m_Pos.x) / 2, m_Size.y / 2),
	//		Float2(m_MoveChanSize, m_MoveChanSize)))
	//		trigger = true;

	//	if (trigger)
	//		m_Pos.x += m_Vel;
	//	if (m_Pos.x > m_PosB.x)
	//		trigger = false;

	//	if (m_Pos.x > m_PosA.x && !trigger)
	//		m_Pos.x -= BACKSPD;
	//}

	// 右ドッスン
	if (m_PosB.x > m_PosA.x)
	{
		if (math::MathCollision::Box(
			Float2(m_Pos.x + (m_PosB.x - m_PosA.x) / 2, m_PosA.y),
			m_MoveChanPos,
			Float2((m_PosB.x - m_Pos.x) / 2, m_Size.y / 2),
			Float2(m_MoveChanSize, m_MoveChanSize))
			&& m_Pos.x == m_PosA.x)
			trigger = true;

		if (trigger)
		{
			m_Pos.x += m_Vel;
			m_Tex.SetCurrentTexture(1);	m_Tex.Update();
		}
		if(m_Pos.x > m_PosB.x)
			trigger = false;

		if (m_Pos.x > m_PosA.x && !trigger)
			m_Pos.x -= BACKSPD;
		if (m_Pos.x < m_PosA.x)
		{
			m_Pos.x = m_PosA.x;
			m_Tex.SetCurrentTexture(0);	m_Tex.Update();
		}
	}
	// 左ドッスン
	if (m_PosA.x > m_PosB.x)
	{
		if (math::MathCollision::Box(
			Float2(m_Pos.x - (m_PosA.x - m_PosB.x) / 2, m_PosA.y),
			m_MoveChanPos,
			Float2(((m_PosA.x - m_PosB.x) - (m_PosA.x - m_Pos.x)) / 2, m_Size.y / 2),
			Float2(m_MoveChanSize, m_MoveChanSize))
			&& m_Pos.x == m_PosA.x)
			trigger = true;

		if (trigger)
		{
			m_Pos.x -= m_Vel;
			m_Tex.SetCurrentTexture(1);	m_Tex.Update();
		}
		if (m_Pos.x < m_PosB.x)
			trigger = false;

		if (m_Pos.x < m_PosA.x && !trigger)
			m_Pos.x += BACKSPD;
		if (m_Pos.x > m_PosA.x)
		{
			m_Tex.SetCurrentTexture(0);	m_Tex.Update();
			m_Pos.x = m_PosA.x;
		}
	}
	// 下ドッスン
	if (m_PosB.y > m_PosA.y)
	{
		if (math::MathCollision::Box(
			Float2(m_Pos.x, m_Pos.y + (m_PosB.y - m_PosA.y) / 2),
			m_MoveChanPos,
			Float2(m_Size.x / 2, (m_PosB.y - m_Pos.y) / 2),
			Float2(m_MoveChanSize, m_MoveChanSize))
			&& m_Pos.y == m_PosA.y)
			trigger = true;

		if (trigger)
		{
			m_Pos.y += m_Vel;
			m_Tex.SetCurrentTexture(1);	m_Tex.Update();
		}
		if (m_Pos.y > m_PosB.y)
			trigger = false;

		if (m_Pos.y > m_PosA.y && !trigger)
			m_Pos.y -= BACKSPD;
		if (m_Pos.y < m_PosA.y)
		{
			m_Tex.SetCurrentTexture(0);	m_Tex.Update();
			m_Pos.y = m_PosA.y;
		}
	}
	// 上ドッスン
	if (m_PosA.y > m_PosB.y)
	{
		if (math::MathCollision::Box(
			Float2(m_PosA.x, m_Pos.y - (m_PosA.y - m_PosB.y) / 2),
			m_MoveChanPos,
			Float2(m_Size.x / 2, ((m_PosA.y - m_PosB.y) - (m_PosA.y - m_Pos.y)) / 2),
			Float2(m_MoveChanSize, m_MoveChanSize))
			&& m_Pos.y == m_PosA.y)
			trigger = true;

		if (trigger)
		{
			m_Pos.y -= m_Vel;
			m_Tex.SetCurrentTexture(1);	m_Tex.Update();
		}
		if (m_Pos.y < m_PosB.y)
			trigger = false;

		if (m_Pos.y < m_PosA.y && !trigger)
			m_Pos.y += BACKSPD;
		if (m_Pos.y > m_PosA.y)
		{
			m_Tex.SetCurrentTexture(0);	m_Tex.Update();
			m_Pos.y = m_PosA.y;
		}
	}
}

void MoveDossun::CollisionAction()
{
	//m_Color = { 0,0,0,1 };
}
