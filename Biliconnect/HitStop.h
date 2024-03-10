#pragma once

class HitStop
{
public:
	HitStop();
	void Update();
	static void Set(int timer) { m_Timer = timer; }
	static int	Get() { return m_Timer; }

private:
	static int m_Timer;
};
__declspec(selectany) int HitStop::m_Timer(0);
