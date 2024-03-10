/*===========================================================================
	Date : 2022/02/05(土)	main.cpp
		Author	: がむしるぉ
		Update	: 
		Comment	: OpenGLがトラウマになった日
===========================================================================*/
#include "Window.h"
#include "OutputConsole.h"
#include "Application.h"
#include "FrameController.h"
#include "Monitor.h"

#include "main.h"


/*=============================================================================================
	エントリーポイント
=============================================================================================*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// モニター(物理デバイス情報を取得)
	Monitor::Init();

	//コンソールウィンドウを表示する
	OutputConsole consoleWindow;
	consoleWindow.Init();

	FrameController::Init();

	//アプリケーションの初期化処理
	Application app(hInstance, nCmdShow);
	if (app.Init())
	{//アプリケーションの初期化処理に成功
		consoleWindow.Clear();

		while (!app.Close())
		{//ゲームループ
			consoleWindow.Update();
			FrameController::Update();
			
			app.Update();
			app.Draw();

			FrameController::Controller(nullptr, 60);
		}
	}

	FrameController::Uninit();

	//アプリケーションの終了処理
	app.Uninit();

	//ウィンドウの終了処理
	consoleWindow.Uninit();

	return 0;
}
