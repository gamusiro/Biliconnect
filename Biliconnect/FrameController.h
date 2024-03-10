/*=========================================================================
	Date : 2021/12/04(ìy)	FrameController.h
		Author : Ç™ÇﬁÇµÇÈÇß
		Update :

		Å¶FPSêßå‰ÉNÉâÉX
=========================================================================*/
#ifndef FRAMECONTROLLER_H_
#define FRAMECONTROLLER_H_

#include <Windows.h>

class Window;

class FrameController
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Controller(Window* window, int frame);

private:
	static DWORD m_CurrentTime;
	static DWORD m_LastTime;
	static DWORD m_FPSLastTime;
	static DWORD m_FrameCount;
	static UINT	 m_CountFPS;
};

#endif // !FRAMECONTROLLER_H_

