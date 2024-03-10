#pragma once
#include "GameCreateSystem.h"
#include "GoalEffect.h"
class MoveChan;
class GoalEffect;

typedef struct
{
	math::Float2 pos, size, vel, addVel;
	float rot;
	int frame;
	bool use, alreadyUsed;
	UINT tex;
	math::Float4 color;

}CRYSTAL_EFFECT;

class Bug
{
public:
	Bug(MoveChan& movechan);
	~Bug();

	void Update(void);
	void Draw(void);
	void Draw2(void);

	void Delete();
	void Explode();
	bool Get() { return trigger; }

	static void Set() { Wintri = true; }
	static void Reset() { Wintri = false; }

private:
	constexpr static float VEL = 4.f;
	constexpr static int   BUG_MAX = 10;
	constexpr static int   WINDOW_MAX = 4;
	constexpr static int   INTERVAL = 15;
	constexpr static float   ALPHA = 1.0f;

	math::Float2 m_Pos[BUG_MAX];
	math::Float2 m_Pos2[BUG_MAX];
	math::Float2 m_WinPos[WINDOW_MAX];
	math::Float2 m_WinSize;
	int deleteTimer[WINDOW_MAX];
	bool Win_Use[WINDOW_MAX];
	math::Float4 m_WinColor[WINDOW_MAX];

	int timer[BUG_MAX];
	math::Float2 m_Size;
	math::Float4 m_Color[BUG_MAX];
	CRYSTAL_EFFECT g_GoalEffect[20][100];

	int timer2;// エフェクトが消え去るまでの時間
	bool	trigger;
	int count;
	int bugtimer;
	int count2;
	int bugtimer2;

	Texture m_Bug[BUG_MAX];
	Texture m_Window[WINDOW_MAX];

	MoveChan& m_MoveChan;
	GoalEffect  m_GoalEffect;

	bool m_GoalEffectON = false;

	static bool Wintri;
};
__declspec(selectany) bool Bug::Wintri(false);

