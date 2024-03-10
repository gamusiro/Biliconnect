#include "Stage.h"
#include "MoveChan.h"
#include "Block.h"
#include "DangerBlock.h"

using namespace math;

DangerBlock::DangerBlock(BLOCKTYPE type, math::Float2 pos, math::Float2 size, float vel)
	: Block(type, pos, size), m_Vel(vel)
{
	// ‰Šú‰»
	m_Type = type;

	if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Create("white.png", 1, 1);
	m_Color = { 1,0.5f,0,1 };
}

void DangerBlock::Update()
{
	if (m_Size.x >= 1000)
		m_Pos.y += m_Vel;
}

void DangerBlock::CollisionAction()
{
	// ˆêŒ‚€‚ğ‹LÚ

	if (Fade::GetState())
	{
		Fade::Transition(SCENE_TYPE::GAMEOVER, FADE_TYPE::MASK);
	}
	
	//m_Color = { 0,0,0,1 };
}
