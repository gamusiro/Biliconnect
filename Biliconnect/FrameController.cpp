/*=========================================================================
	Date : 2021/12/04(土)	FrameController.cpp
		Author : がむしるぉ
		Update :

		※FPS制御クラス
=========================================================================*/
#include <time.h>
#pragma comment(lib, "winmm.lib")	//time.hを利用するため必要なライブラリ

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG


#include "Window.h"

#include "FrameController.h"

DWORD FrameController::m_CurrentTime	= 0;
DWORD FrameController::m_LastTime		= 0;
DWORD FrameController::m_FPSLastTime	= 0;
DWORD FrameController::m_FrameCount		= 0;
UINT  FrameController::m_CountFPS		= 0;


/*=============================================================================================
	初期化処理
=============================================================================================*/
void FrameController::Init()
{
	//フレームカウントの初期化
	timeBeginPeriod(1);
	m_LastTime		= m_FPSLastTime = timeGetTime();
	m_CurrentTime	= m_FrameCount	= 0;
}

/*=============================================================================================
	終了処理
=============================================================================================*/
void FrameController::Uninit()
{
	//分解能を元に戻す
	timeEndPeriod(1);
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void FrameController::Update()
{
	//時刻をミリ秒単位で取得する
	m_CurrentTime = timeGetTime();
}

/*=============================================================================================
	制御処理
=============================================================================================*/
void FrameController::Controller(Window* window, int frame)
{
	while (1)
	{
		//1秒ごとにチェックする
		if ((m_CurrentTime - m_FPSLastTime) >= 1000)
		{
#ifdef _DEBUG
			m_CountFPS = (int)(m_FrameCount * 1000.0f / (m_CurrentTime - m_FPSLastTime));
#endif // _DEBUG


			m_FPSLastTime = m_CurrentTime;
			m_FrameCount = 0;
		}

		if ((signed)(m_CurrentTime - m_LastTime) >= (1000 / frame))
		{
			m_LastTime = m_CurrentTime;
			m_FrameCount++;

#ifdef _DEBUG
			if (window)
			{//nullptrであれば
				char	buffer[1024];
				wsprintf(buffer, window->Get_Title());
				wsprintf(&buffer[strlen(buffer)], "FPS : %d", m_CountFPS);
				SetWindowText(window->Get_HWND(), buffer);
			}
			std::cout << "FPS : " << m_CountFPS << std::endl;
#endif // _DEBUG

			break;
		}
		m_CurrentTime = timeGetTime();
	}
}
