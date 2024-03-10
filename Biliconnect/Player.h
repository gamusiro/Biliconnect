/*=========================================================================
	Date : 2021/03/05(土)	Player.h
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

	// 位置参照
	math::Float2& GetPos() { return m_Pos; }
	void AddPosY(float vel) { m_Pos.y += vel; }

protected:
	math::Float2		m_Pos	= { 0, 85 };
	math::Float2		m_Size	= { 100, 100 };
	math::Float2        m_EffectSize = { 1, 10 };

	Texture				m_Tex;

	bool	trigger;						// 右か左かのトリガ;
	float	m_Place		= 0;				// 媒介変数
	float	ADD_PLACE	= 0.1f;				// 媒介変数変動値(移動速度 (0 < x < 1))

protected:
	constexpr static float BASE_SPEED	= 14;		// 基本スピード
};

#endif
