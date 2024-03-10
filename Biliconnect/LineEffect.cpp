/*=========================================================================
	Date : 2021/03/22(火)	MoveChanEffect.h
		Author :
		Update :
=========================================================================*/
#include "MoveChan.h"
#include "LineEffect.h"
#include "Line.h"
#include "Stage.h"
#include "Button.h"

using namespace math;

/*=========================================================================
 ライン
=========================================================================*/
LineEffect::LineEffect(math::Float2& movechan, Line* lineptr) : m_MoveChanPos(movechan), m_LinePtr(lineptr)
{
	for (int i = 0; i < LINE_EFFECT_MAX; i++)
	{
			m_YellowTex[i].Create("Effect/tail_yellow.png", 3, 3, 4);
			m_BlueTex[i].Create("Effect/tail_blue.png", 3, 3, 4);
			m_UsingTex[i] = m_YellowTex[i];
	}

	this->Init();
}

LineEffect::~LineEffect()
{

}

void  LineEffect::Init()
{
	for (int i = 0; i < LINE_EFFECT_MAX; i++)
	{
		m_Used[i] = false;
	}
}

void LineEffect::Update()
{
	//■しっぽのセット
	m_Frame++;
	if (m_Frame % m_frameToSetMoveChanEffect == 1)
		this->Set();

	for (int i = 0; i < LINE_EFFECT_MAX; i++)
	{
		if (m_Used[i])
		{
			//■セット後の処理
			//アニメ-ションの更新処理
			m_UsingTex[i].Update();

			//削除処理
			if (m_Size[i].x < 0.0f)
				m_Used[i] = false;
		}
	}
}

void LineEffect::Draw()
{
	for (int i = 0; i < LINE_EFFECT_MAX; i++)
	{
		if (m_Used[i])
		{
			Sprite::DrawCenterK(m_Pos[i] - Stage::m_MoveNow, m_Size[i], &m_UsingTex[i], m_Color, m_Rot[i]);
		}
	}
}

void LineEffect::Set()
{
	for (int i = 0; i < LINE_EFFECT_MAX; i++)
	{
		if (!m_Used[i])
		{
//			if (m_CurSpeed == MOVECHAN_EFFECT_NORMAL)
//				m_UsingTex[i] = m_YellowTex[i];
//			else
				m_UsingTex[i] = m_BlueTex[i];

			m_Pos[i] = Float2(m_MoveChanPos.x + (rand() % 100) + 200, m_MoveChanPos.y + (rand() % 100) - 50);
			m_Size[i] = m_DefinedSize;
			m_Rot[i] = ((float)(rand() % 40)) * 0.1f;
			m_Used[i] = true;
			m_UsingTex[i].SetCurrentTexture(0);
		}
	}
}


