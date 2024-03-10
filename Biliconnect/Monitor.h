/*
*	Date : 2022/04/29(��)
*		Author : ���ނ��邧
*		Update : ----/--/--()
*/
#pragma once
#include <Windows.h>
#include <vector>

struct MonitorStruct
{
	int					count;
	std::vector<RECT>	rect;
};

class Monitor
{
public:
	/*
	* @ brief \
	*	���j�^�[�̏����擾����
	*/
	static void Init();

	/*
	* @ brief \
	*	�P�ԍŏ��Ɏ擾�����E�B���h�E�T�C�Y��Ԃ�
	*/
	static RECT GetMonitorRect();

private:
	static MonitorStruct m_Monitors;
};

