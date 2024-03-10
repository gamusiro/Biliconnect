/*===========================================================================
	Date : 2022/02/05(�y)	main.cpp
		Author	: ���ނ��邧
		Update	: 
		Comment	: OpenGL���g���E�}�ɂȂ�����
===========================================================================*/
#include "Window.h"
#include "OutputConsole.h"
#include "Application.h"
#include "FrameController.h"
#include "Monitor.h"

#include "main.h"


/*=============================================================================================
	�G���g���[�|�C���g
=============================================================================================*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ���j�^�[(�����f�o�C�X�����擾)
	Monitor::Init();

	//�R���\�[���E�B���h�E��\������
	OutputConsole consoleWindow;
	consoleWindow.Init();

	FrameController::Init();

	//�A�v���P�[�V�����̏���������
	Application app(hInstance, nCmdShow);
	if (app.Init())
	{//�A�v���P�[�V�����̏����������ɐ���
		consoleWindow.Clear();

		while (!app.Close())
		{//�Q�[�����[�v
			consoleWindow.Update();
			FrameController::Update();
			
			app.Update();
			app.Draw();

			FrameController::Controller(nullptr, 60);
		}
	}

	FrameController::Uninit();

	//�A�v���P�[�V�����̏I������
	app.Uninit();

	//�E�B���h�E�̏I������
	consoleWindow.Uninit();

	return 0;
}
