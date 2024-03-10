/*=========================================================================
	Date : 2021/12/04(�y)	FrameController.cpp
		Author : ���ނ��邧
		Update :

		��FPS����N���X
=========================================================================*/
#include <time.h>
#pragma comment(lib, "winmm.lib")	//time.h�𗘗p���邽�ߕK�v�ȃ��C�u����

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
	����������
=============================================================================================*/
void FrameController::Init()
{
	//�t���[���J�E���g�̏�����
	timeBeginPeriod(1);
	m_LastTime		= m_FPSLastTime = timeGetTime();
	m_CurrentTime	= m_FrameCount	= 0;
}

/*=============================================================================================
	�I������
=============================================================================================*/
void FrameController::Uninit()
{
	//����\�����ɖ߂�
	timeEndPeriod(1);
}

/*=============================================================================================
	�X�V����
=============================================================================================*/
void FrameController::Update()
{
	//�������~���b�P�ʂŎ擾����
	m_CurrentTime = timeGetTime();
}

/*=============================================================================================
	���䏈��
=============================================================================================*/
void FrameController::Controller(Window* window, int frame)
{
	while (1)
	{
		//1�b���ƂɃ`�F�b�N����
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
			{//nullptr�ł����
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
