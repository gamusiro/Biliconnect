#pragma once
#include "GameCreateSystem.h"

class StageTelop
{
public:
	StageTelop();
	~StageTelop();

	void Update(void);
	void Draw(void);
	void Draw2(void);

	static void SetWarning();
	static void Reset() { isWarning = false; }

private:
	Texture Telop;
	Texture Num_1;
	Texture Slash;
	Texture Num_2;
	Texture Mojihai;
	Texture Warning;
	Texture Kome;
	Texture Waku;

	math::Float2 m_Pos;
	math::Float2 m_Size;

	math::Float2 m_NumPos;
	math::Float2 m_NumSize;

	math::Float2 m_WarPos;
	math::Float2 m_WarVel;
	math::Float2 m_WarSize;
	math::Float4 m_WarColor;
	math::Float4 m_WarColor2;
	float AddVel;

	static bool isWarning;

	int m_Frame;
	int m_Frame2;
	bool trigger;

	constexpr static int INTERVAL = 30;
};
__declspec(selectany) bool StageTelop::isWarning(false);

