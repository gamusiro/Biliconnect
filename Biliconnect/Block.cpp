/*=========================================================================
	Date : 2021/03/06(日)	Block.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "Block.h"
#include "MoveChan.h"
#include "Player.h"
#include "Stage.h"
#include "HitStop.h"
#include "Score.h"
#include "DefeatEffect.h"
#include "EnemyNum.h"
#include "SEManager.h"

#include <cmath>

using namespace math;

Block::Block(BLOCKTYPE type, math::Float2 pos, math::Float2 size, int num, int color)
	: GameObject(pos, size, { 0.75f, 0.75f, 0.75f, 1 }), m_Type(type), m_Num(num), m_color(color)
{
	isBlink = false;
	isDoss = false;
	isCoin = false;

	if (m_Type == BLOCKTYPE::ENEMY)
	{
		m_Tex.Create("enemy_blue.png", 5, 2, 10);
		EnemyNum::Add();
		m_Rot = 0;
	}
	if (m_Type == BLOCKTYPE::ITEM)
	{
		m_Tex.Create("life.png", 1, 1);
		m_Rot = 0;
	}
	else if (m_Type == BLOCKTYPE::BLOCK)
	{
		if (color == 0)
			m_Tex.Create("bug.png", 3, 3);
		if (color == 1)
			m_Tex.Create("bug2.png", 3, 3);
		if (color == 2)
			m_Tex.Create("bug3.png", 3, 3);
		if (color == 3)
			m_Tex.Create("bug4.png", 3, 3);
		if (color == 4)
			m_Tex.Create("bug5.png", 3, 3);
		if (color == 5)
			m_Tex.Create("bug6.png", 3, 3);
		if (color == 6)
			m_Tex.Create("bug7.png", 3, 3);
		if (color == 7)
			m_Tex.Create("bug8.png", 3, 3);
		if (color == 8)
			m_Tex.Create("bug9.png", 3, 3);
		if (color == 9)
			m_Tex.Create("bug10.png", 3, 3);

		int random = rand() % 3;

		if (random == 0)
			EffectTex.Create("fx_bug001.png", 4, 4, 3);
		if (random == 1)
			EffectTex.Create("fx_bug002.png", 4, 4, 3);
		if (random == 2)
			EffectTex.Create("fx_bug003.png", 4, 4, 3);

		m_Rot = 0;
	}


	if (num > 0)
	{
		m_Tex.SetCurrentTexture(num - 1);
		m_Tex.Update();
	}
	else
	{
		m_Tex.SetCurrentTexture(4);
		m_Tex.Update();
	}

	m_Color = { 1,1,1,1 };

}

void Block::Update()
{
	if (m_Type == BLOCKTYPE::ENEMY)
		m_Tex.Update();
	else if (m_Type == BLOCKTYPE::BLOCK && (m_Num == 1 || m_Num == 3 || m_Num == 7 || m_Num == 9) && !isBlink)
		EffectTex.Update();
	
}

void Block::Draw()
{
	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_Tex, m_Color, m_Rot);

	if (m_Type == BLOCKTYPE::BLOCK && (m_Num == 1 || m_Num == 3 || m_Num == 7 || m_Num == 9) && !isBlink)
		Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &EffectTex, m_Color);
}

void Block::CheckCollision(MoveChan& movechan, DefeatEffect& df, DefeatEffect2& df2, DefeatEffect3& df3, CharacterEffect& ch)
{
	if (m_Color.w == 1 && !movechan.GetDeath())
	{
		// 体当たりとは当たり判定を分ける
		if (Dash::Get() && m_Type == BLOCKTYPE::ENEMY)
		{
			Float2 pPos = movechan.GetPos();
			float pSize = movechan.GetSize() * 1.5f;

			float bT = m_Pos.y - m_Size.y * 1.5f;		// ブロック上
			float bB = m_Pos.y + m_Size.y * 1.5f;		// ブロック下
			float bL = m_Pos.x - m_Size.x * 1.5f;		// ブロック左
			float bR = m_Pos.x + m_Size.x * 1.5f;		// ブロック右

			if (((pPos.y < bB && pPos.y > bT) && (std::fabsf(pPos.x - m_Pos.x) < (pSize + m_Size.x * 0.5f))) ||
				((pPos.x > bL && pPos.x < bR) && (std::fabsf(pPos.y - m_Pos.y) < (pSize + m_Size.y * 0.5f))))
			{
				SEManager::Play(SOUND::THUNDER);
				SEManager::Play(SOUND::EFFECT);
				EnemyNum::Kill();
				HitStop::Set(4);

				if(m_Size.x >= 200)
				df.Set(m_Pos);
				df2.Set(m_Pos);
				df3.Set();
				//ch.Set(m_Pos);
				Score::Add(50);
				m_Color = { 0,0,0,0 };
			}
			else
			{
				Float2 bTL = m_Pos - m_Size * 0.5f;										// ブロック左上
				Float2 bTR = { m_Pos.x + m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f };	// ブロック右上
				Float2 bBL = { m_Pos.x - m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f };	// ブロック左下
				Float2 bBR = m_Pos + m_Size * 0.5f;										// ブロック右下

				float disTL = MathFloat::LengthSq(pPos - bTL);							// 左下との距離
				float disTR = MathFloat::LengthSq(pPos - bTR);							// 右上との距離
				float disBL = MathFloat::LengthSq(pPos - bBL);							// 左下との距離
				float disBR = MathFloat::LengthSq(pPos - bBR);							// 右下との距離

				if (disTL < pSize * pSize || disTR < pSize * pSize || disBL < pSize * pSize || disBR < pSize * pSize)
				{
					SEManager::Play(SOUND::THUNDER);
					SEManager::Play(SOUND::EFFECT);
					EnemyNum::Kill();
					HitStop::Set(4);
					if (m_Size.x >= 200)
					df.Set(m_Pos);
					df2.Set(m_Pos);
					df3.Set();
					//ch.Set(m_Pos);
					Score::Add(50);
					m_Color = { 0,0,0,0 };
				}
			}
		}
		else
		{
			//Float2 pPos = movechan.GetPos();
			//float pSize = movechan.GetSize() * 0.5f;

			//float bT = m_Pos.y - m_Size.y * 0.5f;		// ブロック上
			//float bB = m_Pos.y + m_Size.y * 0.5f;		// ブロック下
			//float bL = m_Pos.x - m_Size.x * 0.5f;		// ブロック左
			//float bR = m_Pos.x + m_Size.x * 0.5f;		// ブロック右

			//if (((pPos.y < bB && pPos.y > bT) && (std::fabsf(pPos.x - m_Pos.x) < (pSize + m_Size.x * 0.5f))) ||
			//	((pPos.x > bL && pPos.x < bR) && (std::fabsf(pPos.y - m_Pos.y) < (pSize + m_Size.y * 0.5f))))
			//{
			//	if (m_Type == BLOCKTYPE::ITEM)
			//		movechan.AddEnergy();
			//	else if (m_Type != BLOCKTYPE::ITEM)
			//	{
			//		movechan.MinusLife();
			//	}
			//	CollisionAction();
			//	return;
			//}
			//else
			//{
			//	Float2 bTL = m_Pos - m_Size * 0.5f;										// ブロック左上
			//	Float2 bTR = { m_Pos.x + m_Size.x * 0.5f, m_Pos.y - m_Size.y * 0.5f };	// ブロック右上
			//	Float2 bBL = { m_Pos.x - m_Size.x * 0.5f, m_Pos.y + m_Size.y * 0.5f };	// ブロック左下
			//	Float2 bBR = m_Pos + m_Size * 0.5f;										// ブロック右下

			//	float disTL = MathFloat::LengthSq(pPos - bTL);							// 左下との距離
			//	float disTR = MathFloat::LengthSq(pPos - bTR);							// 右上との距離
			//	float disBL = MathFloat::LengthSq(pPos - bBL);							// 左下との距離
			//	float disBR = MathFloat::LengthSq(pPos - bBR);							// 右下との距離

			//	if (disTL < pSize * pSize || disTR < pSize * pSize || disBL < pSize * pSize || disBR < pSize * pSize)
			//	{
			//		if (m_Type == BLOCKTYPE::ITEM)
			//			movechan.AddEnergy();
			//		else if (m_Type != BLOCKTYPE::ITEM)
			//		{
			//			movechan.MinusLife();
			//		}
			//		CollisionAction();
			//		return;
			//	}
			//}
			if (MathCollision::Circle(movechan.GetPos(), m_Pos, movechan.GetSize() / 2, m_Size.x / 2) && !isDoss)
			{
				if (m_Type == BLOCKTYPE::ITEM && isCoin)
					movechan.AddLife();
				else if (m_Type != BLOCKTYPE::ITEM)
				{
					movechan.MinusLife();
				}
				CollisionAction();
				return;
			}
			if (MathCollision::Box(movechan.GetPos(), m_Pos, Float2(movechan.GetSize() / 2, movechan.GetSize() / 2), Float2(m_Size.x * 0.8f / 2, m_Size.y / 2)) && isDoss)
			{
				if (m_Type == BLOCKTYPE::ITEM && isCoin)
					movechan.AddLife();
				else if (m_Type != BLOCKTYPE::ITEM)
				{
					movechan.MinusLife();
				}
				CollisionAction();
				return;
			}
		}
	}
}

void Block::CollisionAction()
{
	//m_Color = { 0,0,0,1 };
}
