#ifndef TIMER_H_
#define TIMER_H_
#include "GameCreateSystem.h"

class Timer
{
public:

	Timer();
	void Update();
	void Draw();

private:
	Texture	m_Tex;

	math::Float2		m_Size;						// 幅と高さ
	math::Float2		m_Pos;						// 座標
	int					m_Second;					// 秒
	int					m_Minute;					// 分
	int					m_Timer;

private:
	constexpr static float DISTANCE_X = -70;
};

#endif // !TIMER_H_






