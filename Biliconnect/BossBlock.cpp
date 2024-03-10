/*=========================================================================
	Date : 2021/05/26(木)	BossBlock.cpp
		Author : み
		Update :
=========================================================================*/
#include "BossBlock.h"
#include "MoveChan.h"
#include "Stage.h"
#include "EnemyNum.h"
#include "SEManager.h"
#include "HitStop.h"
#include "Bug.h"

#include <cmath>

using namespace math;

BossBlock::BossBlock(MoveChan& movechan)
	: m_Movechan(movechan)
{
	m_Tex.Create("boss.png", 2, 1, 10);
	m_Tex.SetCurrentTexture(0);
	m_Tex.Update();

	if(StageNum::Get() % 5 == 4)
	EnemyNum::Add();
	m_Rot = 0;

	m_Pos.x = SCREEN_WIDTH / 2;
	m_Pos.y = Stage::m_MoveMax - SCREEN_HEIGHT / 2;

	m_Size = { 320 * 1.5f, 320 };
	m_ColSize = { 100 * 1.5f, 100 };

	m_Color = { 1,1,1,1 };

	trigger = false;
	timer = 0;
}

void BossBlock::Update()
{
	if (trigger)
	{
		timer++;

		if (timer > 130)
		{
			m_Movechan.SetAnimation(ANIMATION::SMILE);
		}
	}

	if (Stage::m_MoveNow.y > Stage::m_MoveMax - SCREEN_HEIGHT && m_Color.w == 1)
	{
		if (m_Pos.x > m_Movechan.GetPos().x)
			m_Pos.x += 6;
		if (m_Pos.x < m_Movechan.GetPos().x)
			m_Pos.x -= 6;
		if (m_Pos.y < m_Movechan.GetPos().y)
			m_Pos.y -= 6;
		if (m_Pos.y > m_Movechan.GetPos().y)
			m_Pos.y += 6;

		if (m_Pos.x < 0 + m_Size.x * 0.5f + 100)										m_Pos.x = m_Size.x * 0.5f + 100;
		if (m_Pos.x > (SCREEN_WIDTH - m_Size.x * 0.5f) - 100)        m_Pos.x = (SCREEN_WIDTH - m_Size.x * 0.5f - 100);
		if (m_Pos.y < Stage::m_MoveNow.y + m_Size.y * 0.5f)                    m_Pos.y = Stage::m_MoveNow.y + m_Size.y * 0.5f;
		if (m_Pos.y > Stage::m_MoveNow.y + SCREEN_HEIGHT - m_Size.y * 0.5f)    m_Pos.y = Stage::m_MoveNow.y + SCREEN_HEIGHT - m_Size.y * 0.5f;
	}

	m_Tex.Update();
}

void BossBlock::Draw()
{
	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_Tex, m_Color, m_Rot);
}

void BossBlock::CheckCollision(MoveChan& movechan, Bug& bug)
{
	if (m_Color.w == 1 && !movechan.GetDeath())
	{
		// 体当たりとは当たり判定を分ける
		if (Dash::Get())
		{
			Float2 pPos = movechan.GetPos();
			float pSize = movechan.GetSize() * 1.5f;

			float bT = m_Pos.y - m_ColSize.y * 1.5f;		// ブロック上
			float bB = m_Pos.y + m_ColSize.y * 1.5f;		// ブロック下
			float bL = m_Pos.x - m_ColSize.x * 1.5f;		// ブロック左
			float bR = m_Pos.x + m_ColSize.x * 1.5f;		// ブロック右

			if (((pPos.y < bB && pPos.y > bT) && (std::fabsf(pPos.x - m_Pos.x) < (pSize + m_ColSize.x * 0.5f))) ||
				((pPos.x > bL && pPos.x < bR) && (std::fabsf(pPos.y - m_Pos.y) < (pSize + m_ColSize.y * 0.5f))))
			{
				SEManager::Play(SOUND::THUNDER);
				SEManager::Play(SOUND::EFFECT);
				EnemyNum::Kill();
				HitStop::Set(10);
				m_Color = { 0,0,0,0 };

				bug.Explode();
				trigger = true;
			}
			else
			{
				Float2 bTL = m_Pos - m_ColSize * 0.5f;										// ブロック左上
				Float2 bTR = { m_Pos.x + m_ColSize.x * 0.5f, m_Pos.y - m_ColSize.y * 0.5f };	// ブロック右上
				Float2 bBL = { m_Pos.x - m_ColSize.x * 0.5f, m_Pos.y + m_ColSize.y * 0.5f };	// ブロック左下
				Float2 bBR = m_Pos + m_ColSize * 0.5f;										// ブロック右下

				float disTL = MathFloat::LengthSq(pPos - bTL);							// 左下との距離
				float disTR = MathFloat::LengthSq(pPos - bTR);							// 右上との距離
				float disBL = MathFloat::LengthSq(pPos - bBL);							// 左下との距離
				float disBR = MathFloat::LengthSq(pPos - bBR);							// 右下との距離

				if (disTL < pSize * pSize || disTR < pSize * pSize || disBL < pSize * pSize || disBR < pSize * pSize)
				{
					SEManager::Play(SOUND::THUNDER);
					SEManager::Play(SOUND::EFFECT);
					EnemyNum::Kill();
					HitStop::Set(10);
					m_Color = { 0,0,0,0 };

					bug.Explode();
					trigger = true;
				}
			}
		}
		else
		{
			if (MathCollision::Circle(movechan.GetPos(), m_Pos, movechan.GetSize() / 2, m_ColSize.x / 2))
			{
				movechan.MinusLife();
				CollisionAction();
				return;
			}
		}
	}
}

void BossBlock::CollisionAction()
{
	//m_Color = { 0,0,0,1 };
}
