#include "SEManager.h"
#include "Volume.h"

SE	SEManager::m_Thunder;
SE	SEManager::m_Effect;
SE	SEManager::m_Fall;
SE	SEManager::m_Cursor;
SE	SEManager::m_Click;
SE	SEManager::m_Cancel;
SE	SEManager::m_Chin;
SE	SEManager::m_Clear;
SE	SEManager::m_Damage;
SE	SEManager::m_Decision;
SE	SEManager::m_Page;
SE	SEManager::m_Dash;
SE	SEManager::m_Elec;
SE	SEManager::m_Start;
SE	SEManager::m_Fail;
SE	SEManager::m_Item;
SE	SEManager::m_Pachi;
SE	SEManager::m_Bug;
SE	SEManager::m_Bug2;
SE	SEManager::m_Fade;
SE	SEManager::m_Warning;
SE	SEManager::m_Life;
SE	SEManager::m_Penkatu;
SE	SEManager::m_Clear2;
SE	SEManager::m_Pen;
SE	SEManager::m_GM;
SE	SEManager::m_Hyoi;
SE	SEManager::m_Down;
SE	SEManager::m_Hyon;


void SEManager::Init()
{
	m_Thunder.Load("thunder.wav");

	m_Effect.Load("effect.wav");

	m_Fall.Load("fall.wav");

	m_Cursor.Load("cursor.wav");

	m_Click.Load("click.wav");

	m_Cancel.Load("cancel.wav");

	m_Chin.Load("chin.wav");
	m_Chin.SetReverb("chin.rvb");

	m_Clear.Load("clear.wav");

	m_Damage.Load("damage.wav");

	m_Decision.Load("decision.wav");

	m_Page.Load("page.wav");

	m_Dash.Load("dash2.wav");

	m_Elec.Load("elec.wav");

	m_Start.Load("start.wav");

	m_Fail.Load("fail.wav");

	m_Item.Load("item.wav");

	m_Pachi.Load("pachi.wav");

	m_Bug.Load("bug.wav");

	m_Bug2.Load("bug2.wav");

	m_Fade.Load("fade.wav");

	m_Warning.Load("warning.wav");

	m_Life.Load("life.wav");

	m_Penkatu.Load("penkatu.wav");

	m_Clear2.Load("clear2.wav");

	m_Pen.Load("pen.wav");

	m_GM.Load("gameover.wav");

	m_Hyoi.Load("hyoi.wav");

	m_Down.Load("down.wav");

	m_Hyon.Load("hyon.wav");
}

void SEManager::Play(SOUND num)
{
	if (num == SOUND::THUNDER)
	{
		m_Thunder.Play(0);
		m_Thunder.SetVolume(Volume::GetSE() * 5);
	}
	if (num == SOUND::EFFECT)
	{
		m_Effect.Play(0);
		m_Effect.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::FALL)
	{
		m_Fall.Play(0);
		m_Fall.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::CURSOR)
	{
		m_Cursor.Play(0);
		m_Cursor.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::CLICK)
	{
		m_Click.Play(0);
		m_Click.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::CANCEL)
	{
		m_Cancel.Play(0);
		m_Cancel.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::CHIN)
	{
		m_Chin.Play(0);
		m_Chin.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::CLEAR)
	{
		m_Clear.Play(0);
		m_Clear.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::DAMAGE)
	{
		m_Damage.Play(0);
		m_Damage.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::DECISION)
	{
		m_Decision.Play(0);
		m_Decision.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::PAGE)
	{
		m_Page.Play(0);
		m_Page.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::DASH)
	{
		m_Dash.Play(0);
		m_Dash.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::ELEC)
	{
		m_Elec.Play(0);
		m_Elec.SetVolume(Volume::GetSE() * 4);
	}
	if (num == SOUND::START)
	{
		m_Start.Play(0);
		m_Start.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::FAIL)
	{
		m_Fail.Play(0);
		m_Fail.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::ITEM)
	{
		m_Item.Play(0);
		m_Item.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::PACHI)
	{
		m_Pachi.Play(0);
		m_Pachi.SetVolume(Volume::GetSE() * 8);
	}
	if (num == SOUND::BUG)
	{
		m_Bug.Play(0);
		m_Bug.SetVolume(Volume::GetSE() * 0);
	}
	if (num == SOUND::BUG2)
	{
		m_Bug2.Play(0);
		m_Bug2.SetVolume(Volume::GetSE() * 0);
	}
	if (num == SOUND::FADE)
	{
		m_Fade.Play(0);
		m_Fade.SetVolume(Volume::GetSE() * 8);
	}
	if (num == SOUND::WARNING)
	{
		m_Warning.Play(0);
		m_Warning.SetVolume(Volume::GetSE() * 12);
	}
	if (num == SOUND::LIFE)
	{
		m_Life.Play(0);
		m_Life.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::PENKATU)
	{
		m_Penkatu.Play(1);
		m_Penkatu.SetVolume(Volume::GetSE() * 6);
	}
	if (num == SOUND::CLEAR2)
	{
		m_Clear2.Play(0);
		m_Clear2.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::PEN)
	{
		m_Pen.Play(1);
		m_Pen.SetVolume(Volume::GetSE() * MASTER_VOLUME);
	}
	if (num == SOUND::GAMEOVER)
	{
		m_GM.Play(0);
		m_GM.SetVolume(Volume::GetSE() * MASTER_VOLUME  + 1);
	}
	if (num == SOUND::HYOI)
	{
		m_Hyoi.Play(0);
		m_Hyoi.SetVolume(Volume::GetSE() * 3);
	}
	if (num == SOUND::DOWN)
	{
		m_Down.Play(0);
		m_Down.SetVolume(Volume::GetSE() * 4);
	}
	if (num == SOUND::HYON)
	{
		m_Hyon.Play(0);
		m_Hyon.SetVolume(Volume::GetSE() * 3);
	}
}

void SEManager::Stop(SOUND num)
{
	if (num == SOUND::THUNDER)
	{
		m_Thunder.Stop();
	}
	if (num == SOUND::EFFECT)
	{
		m_Effect.Stop();
	}
	if (num == SOUND::FALL)
	{
		m_Fall.Stop();
	}
	if (num == SOUND::CURSOR)
	{
		m_Cursor.Stop();
	}
	if (num == SOUND::CLICK)
	{
		m_Click.Stop();
	}
	if (num == SOUND::CANCEL)
	{
		m_Cancel.Stop();
	}
	if (num == SOUND::CHIN)
	{
		m_Chin.Stop();
	}
	if (num == SOUND::CLEAR)
	{
		m_Clear.Stop();
	}
	if (num == SOUND::DAMAGE)
	{
		m_Damage.Stop();
	}
	if (num == SOUND::DECISION)
	{
		m_Decision.Stop();
	}
	if (num == SOUND::PAGE)
	{
		m_Page.Stop();
	}
	if (num == SOUND::DASH)
	{
		m_Dash.Stop();
	}
	if (num == SOUND::ELEC)
	{
		m_Elec.Stop();
	}
	if (num == SOUND::START)
	{
		m_Start.Stop();
	}
	if (num == SOUND::FAIL)
	{
		m_Fail.Stop();
	}
	if (num == SOUND::ITEM)
	{
		m_Item.Stop();
	}
	if (num == SOUND::PACHI)
	{
		m_Pachi.Stop();
	}
	if (num == SOUND::FADE)
	{
		m_Fade.Stop();
	}
	if (num == SOUND::WARNING)
	{
		m_Warning.Stop();
	}
	if (num == SOUND::LIFE)
	{
		m_Life.Stop();
	}
	if (num == SOUND::PENKATU)
	{
		m_Penkatu.Stop();
	}
	if (num == SOUND::PEN)
	{
		m_Pen.Stop();
	}
	if (num == SOUND::CLEAR2)
	{
		m_Clear2.Stop();
	}
	if (num == SOUND::GAMEOVER)
	{
		m_GM.Stop();
	}
	if (num == SOUND::HYOI)
	{
		m_Hyoi.Stop();
	}
	if (num == SOUND::DOWN)
	{
		m_Down.Stop();
	}
	if (num == SOUND::HYON)
	{
		m_Hyon.Stop();
	}
}

void SEManager::StopAll()
{
		m_Thunder.Stop();
		m_Effect.Stop();
		m_Fall.Stop();
		m_Cursor.Stop();
		m_Click.Stop();
		m_Cancel.Stop();
		m_Chin.Stop();
		m_Clear.Stop();
		m_Damage.Stop();
		m_Decision.Stop();
		m_Page.Stop();
		m_Dash.Stop();
		m_Elec.Stop();
		m_Start.Stop();
		m_Fail.Stop();
		m_Item.Stop();
		m_Pachi.Stop();
		m_Fade.Stop();
		m_Warning.Stop();
		m_Life.Stop();
		m_Penkatu.Stop();
		m_Pen.Stop();
		m_Clear2.Stop();
		m_GM.Stop();
		m_Hyoi.Stop();
		m_Down.Stop();
		m_Hyon.Stop();
}
