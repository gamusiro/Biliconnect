#pragma once
#include "GameCreateSystem.h"

enum class SOUND
{
	THUNDER,
	EFFECT,
	FALL,
	CURSOR,
	CLICK,
	CANCEL,
	CHIN,
	CLEAR,
	CLEAR2,
	DAMAGE,
	DECISION,
	PAGE,
	DASH,
	ELEC,
	START,
	FAIL,
	ITEM,
	PACHI,
	BUG,
	BUG2,
	FADE,
	WARNING,
	LIFE,
	PENKATU,
	PEN,
	GAMEOVER,
	HYOI,
	DOWN,
	HYON
};

class SEManager
{
public:
	static void Init();

	static void Play(SOUND num);
	static void Stop(SOUND num);
	static void StopAll();
private:
	static SE m_Thunder;
	static SE m_Effect;
	static SE m_Fall;
	static SE m_Cursor;
	static SE m_Click;
	static SE m_Cancel;
	static SE m_Chin;
	static SE m_Clear;
	static SE m_Damage;
	static SE m_Decision;
	static SE m_Page;
	static SE m_Dash;
	static SE m_Elec;
	static SE m_Start;
	static SE m_Fail;
	static SE m_Item;
	static SE m_Pachi;
	static SE m_Bug;
	static SE m_Bug2;
	static SE m_Warning;
	static SE m_Fade;
	static SE m_Life;
	static SE m_Penkatu;
	static SE m_Pen;
	static SE m_Clear2;
	static SE m_GM;
	static SE m_Hyoi;
	static SE m_Down;
	static SE m_Hyon;

	constexpr static int MASTER_VOLUME = 6;	// マスターボリューム
};

