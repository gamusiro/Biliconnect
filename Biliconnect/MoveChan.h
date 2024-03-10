/*=========================================================================
	Date : 2021/03/05(“y)	MoveChan.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef MOVECHAN_H_
#define MOVECHAN_H_

#include <memory>
#include "GameCreateSystem.h"
#include "Line.h"
#include "LifeManager.h"
#include "EnergyManager.h"
#include "EffectManager.h"

class MCState;

enum class ANIMATION
{
	NORMAL,
	BLINK,
	DAMAGE,
	POWER,
	SMILE,
};

class MoveChan
{
public:
	enum class MOVESTATE
	{
		ONLINE,
		JUMP,
		MAX
	};

	enum class DAMAGESTATE
	{
		NOMAL = 0,
		DAMAGE,
		MAX
	};

public:
	MoveChan() = delete;
	MoveChan(math::Float2 pos, Line& line);
	~MoveChan();

	void Update();
	void Draw();

	void SetPos(math::Float2 pos) { m_Pos = pos; }
	void AddPosY(float y) { m_Pos.y += y; }

	math::Float2& GetPos() { return m_Pos; }
	float GetSize() { return m_Size.x; }

	void SetAnimation(ANIMATION num);
	ANIMATION GetAnimation() { return m_Animation; }
	void MinusLife();
	void AddLife();
	int GetLife() { return m_Life.Get(); }
	static bool GetDeath() { return isDeath; }
	void MinusEnergy();
	void AddEnergy();
	int GetEnergy() { return m_Energy.Get(); }

	void Damage();
	void ChangeState(MOVESTATE state);
	void ChangeState(DAMAGESTATE state);

	static void Reset() { isDeath = false; }

private:
	void Animation();

	math::Float2	m_Pos;
	math::Float2	m_Size = { 85,85 };
	static bool			isDeath;
	int             m_Frame;

	Texture			m_Tex;
	Texture			m_Damage;
	math::Float4	m_Color;
	ANIMATION		m_Animation;

	LifeManager		m_Life;
	EnergyManager	m_Energy;

	MOVESTATE					m_MoveState;
	std::unique_ptr<MCState>	m_MoveStates[static_cast<int>(MOVESTATE::MAX)];

	DAMAGESTATE					m_DamageState;
	std::unique_ptr<MCState>	m_DamageStates[static_cast<int>(DAMAGESTATE::MAX)];

	EffectManager	m_Effects;

private:
	constexpr static float LIFE_POS_X = 1550.0f;
	constexpr static float LIFE_POS_Y = 75.0f;

	constexpr static float ENERGY_POS_X = 270.0f;
	constexpr static float ENERGY_POS_Y = 55.0f;
};

class Dash
{
public:
	static void Set(bool dash) { isDash = dash; }
	static bool	Get() { return isDash; }

private:
	static bool isDash;
};
__declspec(selectany) bool Dash::isDash(false);
__declspec(selectany) bool MoveChan::isDeath(false);

#endif
