/*
*	Date : 2022/04/29(��)
*		Author : ���ނ��邧
*		Update : ----/--/--()
*/
#include "Monitor.h"

MonitorStruct Monitor::m_Monitors;

// �R�[���o�b�N�֐�
BOOL CALLBACK MonitorProc(HMONITOR hMon, HDC hdcMon, LPRECT lpMon, LPARAM dwDate)
{
	MonitorStruct* mon = (MonitorStruct*)dwDate;
	mon->rect.push_back(*lpMon);
	return true;
}

// ����������
void Monitor::Init()
{
	m_Monitors.count = GetSystemMetrics(SM_CMONITORS);	// ���j�^�[�����擾
	EnumDisplayMonitors(nullptr, nullptr, (MONITORENUMPROC)MonitorProc, (LPARAM)&m_Monitors);
}

// ���j�^�[��Ԃ�
RECT Monitor::GetMonitorRect()
{
	return m_Monitors.rect[0];
}

