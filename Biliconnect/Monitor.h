/*
*	Date : 2022/04/29(金)
*		Author : がむしるぉ
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
	*	モニターの情報を取得する
	*/
	static void Init();

	/*
	* @ brief \
	*	１番最初に取得したウィンドウサイズを返す
	*/
	static RECT GetMonitorRect();

private:
	static MonitorStruct m_Monitors;
};

