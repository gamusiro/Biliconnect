#include "Stage.h"
#include "Block.h"
#include "MoveChan.h"
#include "BulletBlock.h"

using namespace math;

BulletBlock::BulletBlock(BLOCKTYPE type, MoveChan& movechan, float vel, math::Float2 length, Float2 pos, Float2 size)
	: Block(type, pos, size), m_MoveChan(movechan), trigger(false), timer(0)
{
	// ������
	m_Type = type;

	if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Create("B_E.png", 3, 1, 15);
	m_Tex.SetCurrentTexture(0);
	m_Tex.Update();
	m_BulletTex.Create("gun.png", 3, 2, 1);
	m_Vel = vel;
	m_Color = { 1,1,1,1 };

	m_PosA = Float2(pos.x, pos.y);
	m_PosB = Float2(pos.x + length.x, pos.y + length.y);

	m_Bullet.Pos = Float2(0, 0);
	m_Bullet.Vel = Float2(0, 0);
	m_Bullet.Size = Float2(60, 60);
}

void BulletBlock::Update()
{
	if (!m_MoveChan.GetDeath() && !StageStart::Get())
	{
		if (m_Type == BLOCKTYPE::ENEMY)
		{
			//m_Tex.Update();
			m_BulletTex.Update();
		}
		m_Bullet.Pos += m_Bullet.Vel;

		if (m_Color.w != 0)
		{
			if (MathCollision::Box(
				Float2(m_Pos.x, m_Pos.y - SIZE_Y / 2),
				m_MoveChan.GetPos(),
				Float2(SIZE_X / 2, SIZE_Y / 2),
				Float2(m_MoveChan.GetSize(), m_MoveChan.GetSize()))
				&& !RE_B && !trigger && m_Pos.y < Stage::m_MoveNow.y + SCREEN_HEIGHT)
			{
				RE_B = true;
			}

			if (RE_B && !trigger)
			{
				timer++;
				m_Tex.Update();

				if (timer == 32)
					SetBullet();

				if (timer >= 46)
				{
					m_Tex.SetCurrentTexture(0);
					m_Tex.Update();
					timer = 0;
					RE_B = false;
					trigger = true;

				}
			}
			else if (trigger && !RE_B)
			{
				timer++;

				if (timer >= 100)
				{
					timer = 0;
					trigger = false;
				}
			}
		}

		//////////////////////// �ړ� ///////////////////////////////

		if (m_PosA.x > m_PosB.x)
		{
			m_Pos.x += m_Vel;
			// ���˕Ԃ�
			if (m_Pos.x > m_PosA.x || m_Pos.x < m_PosB.x)
				m_Vel *= -1;
		}
		else if (m_PosA.y > m_PosB.y)
		{
			m_Pos.y += m_Vel;
			// ���˕Ԃ�
			if (m_Pos.y > m_PosA.y || m_Pos.y < m_PosB.y)
				m_Vel *= -1;
		}
		else if (m_PosA.x == m_PosB.x)
		{
			m_Pos.y += m_Vel;
			// ���˕Ԃ�
			if (m_Pos.y < m_PosA.y || m_Pos.y > m_PosB.y)
				m_Vel *= -1;
		}
		else if (m_PosA.y == m_PosB.y)
		{
			m_Pos.x += m_Vel;
			// ���˕Ԃ�
			if (m_Pos.x < m_PosA.x || m_Pos.x > m_PosB.x)
				m_Vel *= -1;
		}
		else
		{
			m_Pos += m_Vel;
			// ���˕Ԃ�
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

		// �e�̓����蔻��
		Float2 pPos = m_MoveChan.GetPos();
		float pSize = m_MoveChan.GetSize() * 0.6f;

		float bT = m_Bullet.Pos.y - m_Bullet.Size.y * 0.5f;		// �u���b�N��
		float bB = m_Bullet.Pos.y + m_Bullet.Size.y * 0.5f;		// �u���b�N��
		float bL = m_Bullet.Pos.x - m_Bullet.Size.x * 0.5f;		// �u���b�N��
		float bR = m_Bullet.Pos.x + m_Bullet.Size.x * 0.5f;		// �u���b�N�E

		if (((pPos.y < bB && pPos.y > bT) && (std::fabsf(pPos.x - m_Bullet.Pos.x) < (pSize + m_Bullet.Size.x * 0.5f))) ||
			((pPos.x > bL && pPos.x < bR) && (std::fabsf(pPos.y - m_Bullet.Pos.y) < (pSize + m_Bullet.Size.y * 0.5f))))
		{
			// �_�b�V�����Ȃ�e������
			if (Dash::Get())
			{
				m_Bullet.Pos = { 0,0 };
				return;
			}
			else if (!Dash::Get())
			{
				m_MoveChan.MinusLife();
				//CollisionAction();
				return;
			}
		}
		else
		{
			Float2 bTL = m_Bullet.Pos - m_Bullet.Size * 0.5f;										// �u���b�N����
			Float2 bTR = { m_Bullet.Pos.x + m_Bullet.Size.x * 0.5f, m_Bullet.Pos.y - m_Bullet.Size.y * 0.5f };	// �u���b�N�E��
			Float2 bBL = { m_Bullet.Pos.x - m_Bullet.Size.x * 0.5f, m_Bullet.Pos.y + m_Bullet.Size.y * 0.5f };	// �u���b�N����
			Float2 bBR = m_Bullet.Pos + m_Bullet.Size * 0.5f;										// �u���b�N�E��

			float disTL = MathFloat::LengthSq(pPos - bTL);							// �����Ƃ̋���
			float disTR = MathFloat::LengthSq(pPos - bTR);							// �E��Ƃ̋���
			float disBL = MathFloat::LengthSq(pPos - bBL);							// �����Ƃ̋���
			float disBR = MathFloat::LengthSq(pPos - bBR);							// �E���Ƃ̋���

			if (disTL < pSize * pSize || disTR < pSize * pSize || disBL < pSize * pSize || disBR < pSize * pSize)
			{
				// �_�b�V�����Ȃ�e������
				if (Dash::Get())
				{
					m_Bullet.Pos = { 0,0 };
					return;
				}
				else if (!Dash::Get())
				{
					m_MoveChan.MinusLife();
					//CollisionAction();
					return;
				}
			}
		}
	}
}

void BulletBlock::Draw()
{
	Sprite::DrawCenter(m_Pos - Stage::m_MoveNow, m_Size, &m_Tex, m_Color);

	Sprite::DrawCenter(m_Bullet.Pos - Stage::m_MoveNow, m_Bullet.Size + 50, &m_BulletTex, m_Color);
}

void BulletBlock::CollisionAction()
{
	//m_Color = { 1,0,0,1 };
}

void BulletBlock::SetBullet()
{
	m_Bullet.Pos = m_Pos;

	Float2 pos = m_MoveChan.GetPos();

	if(m_Pos.x > pos.x)
		m_Bullet.Vel = Float2(-(m_Pos.x - pos.x) / 70, -VELOCITY);
	if (m_Pos.x < pos.x)
		m_Bullet.Vel = Float2((pos.x - m_Pos.x) / 70, -VELOCITY);
}
