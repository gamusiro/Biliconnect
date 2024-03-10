#include "Stage.h"
#include "Block.h"
#include "MoveBlock.h"

using namespace math;

MoveBlock::MoveBlock(BLOCKTYPE type, float vel, math::Float2 length, math::Float2 pos, math::Float2 size)
	: Block(type, pos, size)
{
	// ‰Šú‰»
	m_Type = type;

	if(m_Type == BLOCKTYPE::ENEMY)
		m_Tex.Create("enemy_blue.png", 5, 2, 10);
	else if (m_Type == BLOCKTYPE::BLOCK)
	{
		m_Tex.Create("MoveEnemy.png", 2, 1, 10); 
		m_Tex.SetCurrentTexture(0);
		m_Tex.Update();
	}
		

	m_Vel = vel;
	m_Color = { 1,1,1,1 };

	m_PosA = Float2(pos.x, pos.y);
	m_PosB = Float2(pos.x + length.x, pos.y + length.y);
}

void MoveBlock::Update()
{
//.if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Update();

	//////////////////////// ˆÚ“® ///////////////////////////////

	if (m_PosA.x > m_PosB.x)
	{
		m_Pos.x += m_Vel;
		// ’µ‚Ë•Ô‚é
		if (m_Pos.x > m_PosA.x || m_Pos.x < m_PosB.x)
			m_Vel *= -1;
	}
	else if (m_PosA.y > m_PosB.y)
	{
		m_Pos.y += m_Vel;
		// ’µ‚Ë•Ô‚é
		if (m_Pos.y > m_PosA.y || m_Pos.y < m_PosB.y)
			m_Vel *= -1;
	}
	else if (m_PosA.x == m_PosB.x)
	{
		m_Pos.y += m_Vel;
		// ’µ‚Ë•Ô‚é
		if (m_Pos.y < m_PosA.y || m_Pos.y > m_PosB.y)
		m_Vel *= -1;
	}
	else if (m_PosA.y == m_PosB.y)
	{
		m_Pos.x += m_Vel;
		// ’µ‚Ë•Ô‚é
		if (m_Pos.x < m_PosA.x || m_Pos.x > m_PosB.x)
			m_Vel *= -1;
	}
	else
	{
		m_Pos += m_Vel;
		// ’µ‚Ë•Ô‚é
		if (m_Pos.x > m_PosB.x)
			m_Vel *= -1;
		else if (m_Pos.x < m_PosA.x)
			m_Vel *= -1;
		if (m_Pos.y > m_PosB.y)
			m_Vel *= -1;
		else if (m_Pos.y < m_PosA.y)
			m_Vel *= -1;
	}

	////////////////////////////////////////////////////////
}

void MoveBlock::CollisionAction()
{
	/*if (Controller::GetButtonPressLShoulder() || Input::KeyboardPress(DIK_LEFT))
		m_Color = { 0,0,0,0 };
	else
		m_Color = { 0,0,0,1 };*/

	//m_Color = { 0,0,0,1 };
}
