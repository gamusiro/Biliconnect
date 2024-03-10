/*
*	Date : 2022/04/29(金)
*		Author : がむしるぉ
*		Update : ----/--/--()
*/
#include "Monitor.h"

MonitorStruct Monitor::m_Monitors;

// コールバック関数
BOOL CALLBACK MonitorProc(HMONITOR hMon, HDC hdcMon, LPRECT lpMon, LPARAM dwDate)
{
	MonitorStruct* mon = (MonitorStruct*)dwDate;
	mon->rect.push_back(*lpMon);
	return true;
}

// 初期化処理
void Monitor::Init()
{
	m_Monitors.count = GetSystemMetrics(SM_CMONITORS);	// モニター数を取得
	EnumDisplayMonitors(nullptr, nullptr, (MONITORENUMPROC)MonitorProc, (LPARAM)&m_Monitors);
}

// モニターを返す
RECT Monitor::GetMonitorRect()
{
	return m_Monitors.rect[0];
}

