#ifndef SCORE_H_
#define SCORE_H_

#include "GameCreateSystem.h"

struct ScoreEffect
{
	bool	use;
	math::Float2	pos;
	math::Float2	vel;
	math::Float2	addvel;
	math::Float2	size;
	math::Float4	color;
	float	rot;
};

class Score
{
public:

	Score();
	void Update();
	void Draw();

	static void Add(int num) { m_NowScore += num; trigger = true; timer = 0; }
	static int Get() { return m_NowScore; }

private:
	Texture	Numerator;
	Texture	Denominator;
	Texture	Slash;
	Texture	Waku;
	Texture	WakuL;
	Texture	File;
	Texture	Folder;

	math::Float2		m_Size;						// ���ƍ���
	math::Float2		m_Pos;						// ���W
	static int			m_Score;					// �X�R�A
	math::Float4		m_ColorF;					// �t���[���悤
	math::Float4		m_ColorC[2];					// �R�C���悤
	static int			m_NowScore;
	int                 m_digit;					// ����
	static int			trigger;
	static int			timer;

	void SetEffect();

	int m_Frame = 0;
	float Blinking = 0.0f;

private:
	constexpr static float DISTANCE_X = -70;
	constexpr static float PLUS_Y = -130;
	constexpr static float PLUS_X = 20;
	constexpr static int   SCORE_EFFECT_MAX = 25;

	ScoreEffect			m_SE[SCORE_EFFECT_MAX];
	Texture m_EffectTex[SCORE_EFFECT_MAX];
};
#endif // !SCORE_H_

