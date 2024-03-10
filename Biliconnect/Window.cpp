/*=========================================================================
	Date : 2021/11/28(日)	Window.cpp
		Author	: がむしるぉ
		Update	: 2022/02/05(土)
		Comment	:
		※ウィンドウ画面のクラス
=========================================================================*/
#include "Monitor.h"
#include "resource.h"

#include "Window.h"
#include "Title.h"

/*=============================================================================================
	コンストラクタ
=============================================================================================*/
Window::Window()
	:m_instance(),
	m_className(),
	m_windowTitle(),
	m_hwnd(),
	m_message()
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
Window::~Window()
{
}

/*=============================================================================================
	ウィンドウプロシージャ
=============================================================================================*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	/*case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		}
		break;*/

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

/*=============================================================================================
	初期化処理
=============================================================================================*/
int Window::Init(HINSTANCE hInstance, const LPCSTR& wnd_class_name)
{
	m_instance	= hInstance;
	m_className = wnd_class_name;

	//画面ウィンドウの生成
	WNDCLASSEX wcex;
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_CLASSDC;
	wcex.lpfnWndProc	= &WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(nullptr, IDC_ICON);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= m_className;
	wcex.hIconSm		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));;

	//ウィンドウの登録
	if (FAILED(RegisterClassEx(&wcex)))
	{
		return -1;
	}
	return 0;
}

/*=============================================================================================
	終了処理
=============================================================================================*/
void Window::Uninit()
{
	UnregisterClass(m_className, m_instance);
}

/*=============================================================================================
	画面の生成
=============================================================================================*/
void Window::Create(const LPCSTR& window_name)
{
	if (window_name != nullptr)
	{//ウィンドウの名前があれば
		m_windowTitle = window_name;
	}
	else
	{//ウィンドウの名前がなければ
		m_windowTitle = "Untitle Window";
	}
	
	m_hwnd = CreateWindow(
		m_className,
		m_windowTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		WINDOW_SIZE_WIDTH,
		WINDOW_SIZE_HEIGHT,
//		GetSystemMetrics(SM_CXSCREEN),
//		GetSystemMetrics(SM_CYSCREEN),
		nullptr,
		nullptr,
		m_instance,
		nullptr);
}

/*=============================================================================================
	画面の表示
=============================================================================================*/
void Window::Show(int nCmdShow)
{
#ifndef _DEBUG
	RECT rect = Monitor::GetMonitorRect();

	//力技のフルスクリーン
	SetMenu(m_hwnd, NULL);										//メニューを隠す
	SetWindowLong(m_hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);	//ウィンドウのスタイルを変更
	MoveWindow(m_hwnd,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		TRUE);
	SetFocus(m_hwnd);											//キー入力受付ウィンドウに設定する
#endif // _DEBUG

	//ウィンドウの表示開始
	ShowWindow(m_hwnd, nCmdShow);
	UpdateWindow(m_hwnd);
}

/*=============================================================================================
	メッセージのディスパッチ
=============================================================================================*/
bool Window::Dispatcher()
{
	if (PeekMessage(&m_message, nullptr, 0, 0, PM_REMOVE))
	{
		if (m_message.message == WM_QUIT)
		{
			return false;
		}
		else
		{
			TranslateMessage(&m_message);
			DispatchMessage(&m_message);
		}
	}
	return true;
}

void Window::Exit()
{
	PostMessage(m_hwnd, WM_DESTROY, 0, 0);
}
