/*=========================================================================
	Date : 2021/03/05(�y)	Player.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "GameCreateSystem.h"

#include "Button.h"

class Player
{
public:
	struct Rail
	{
		math::Float2	m_Line;
		float			m_Speed;
	};

public:
	Player() {}
	virtual ~Player() {}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	// �ʒu�Q��
	math::Float2& GetPos() { return m_Pos; }
	void AddPosY(float vel) { m_Pos.y += vel; }

protected:
	math::Float2		m_Pos	= { 0, 85 };
	math::Float2		m_Size	= { 100, 100 };
	math::Float2        m_EffectSize = { 1, 10 };

	Texture				m_Tex;

	bool	trigger;						// �E�������̃g���K;
	float	m_Place		= 0;				// �}��ϐ�
	float	ADD_PLACE	= 0.1f;				// �}��ϐ��ϓ��l(�ړ����x (0 < x < 1))

protected:
	constexpr static float BASE_SPEED	= 14;		// ��{�X�s�[�h
};

#endif
