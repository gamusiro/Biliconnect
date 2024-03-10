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

	math::Float2		m_Size;						// ���ƍ���
	math::Float2		m_Pos;						// ���W
	int					m_Second;					// �b
	int					m_Minute;					// ��
	int					m_Timer;

private:
	constexpr static float DISTANCE_X = -70;
};

#endif // !TIMER_H_






