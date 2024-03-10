#include "Stage.h"
#include "Block.h"
#include "MoveChan.h"
#include "RushBlock.h"

using namespace math;

RushBlock::RushBlock(BLOCKTYPE type, MoveChan& movechan, Float2 pos, Float2 size)
	: Block(type, pos, size), m_MoveChan(movechan), trigger(false)
{
	// èâä˙âª
	m_Type = type;

	if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Create("enemy_red.png", 5, 2, 10);
	m_Color = { 1,1,1,1 };

	m_Type = type;
}

void RushBlock::Update()
{
	if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Update();

	if (MathCollision::Box(
		Float2(m_Pos.x, m_Pos.y - SIZE_Y / 2),
		m_MoveChan.GetPos(),
		Float2(SIZE_X / 2, SIZE_Y / 2),
		Float2(m_MoveChan.GetSize(), m_MoveChan.GetSize()))
		&& !trigger
		&& m_Pos.y < Stage::m_MoveNow.y + SCREEN_HEIGHT)
	{
		trigger = true;
		Set();
	}

	if (trigger)
		m_Pos += m_Vel;
}

void RushBlock::Draw()
{
	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_Tex, m_Color);
}

void RushBlock::Set()
{
	Float2 pos = m_MoveChan.GetPos();

	if (m_Pos.x > pos.x)
		m_Vel = Float2(-(m_Pos.x - pos.x) / VELOCITY, -(m_Pos.y - pos.y) / VELOCITY);
		//m_Vel = (m_Pos - pos) / VELOCITY;

	if (m_Pos.x < pos.x)
		m_Vel = Float2((pos.x - m_Pos.x) / VELOCITY, -(m_Pos.y - pos.y) / VELOCITY);
}

void RushBlock::CollisionAction()
{
	//m_Color = { 1,0,0,1 };
}