/*=========================================================================
	Date : 2021/11/28(��)	Window.cpp
		Author	: ���ނ��邧
		Update	: 2022/02/05(�y)
		Comment	:
		���E�B���h�E��ʂ̃N���X
=========================================================================*/
#include "Monitor.h"
#include "resource.h"

#include "Window.h"
#include "Title.h"

/*=============================================================================================
	�R���X�g���N�^
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
	�f�X�g���N�^
=============================================================================================*/
Window::~Window()
{
}

/*=============================================================================================
	�E�B���h�E�v���V�[�W��
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
	����������
=============================================================================================*/
int Window::Init(HINSTANCE hInstance, const LPCSTR& wnd_class_name)
{
	m_instance	= hInstance;
	m_className = wnd_class_name;

	//��ʃE�B���h�E�̐���
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

	//�E�B���h�E�̓o�^
	if (FAILED(RegisterClassEx(&wcex)))
	{
		return -1;
	}
	return 0;
}

/*=============================================================================================
	�I������
=============================================================================================*/
void Window::Uninit()
{
	UnregisterClass(m_className, m_instance);
}

/*=============================================================================================
	��ʂ̐���
=============================================================================================*/
void Window::Create(const LPCSTR& window_name)
{
	if (window_name != nullptr)
	{//�E�B���h�E�̖��O�������
		m_windowTitle = window_name;
	}
	else
	{//�E�B���h�E�̖��O���Ȃ����
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
	��ʂ̕\��
=============================================================================================*/
void Window::Show(int nCmdShow)
{
#ifndef _DEBUG
	RECT rect = Monitor::GetMonitorRect();

	//�͋Z�̃t���X�N���[��
	SetMenu(m_hwnd, NULL);										//���j���[���B��
	SetWindowLong(m_hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);	//�E�B���h�E�̃X�^�C����ύX
	MoveWindow(m_hwnd,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		TRUE);
	SetFocus(m_hwnd);											//�L�[���͎�t�E�B���h�E�ɐݒ肷��
#endif // _DEBUG

	//�E�B���h�E�̕\���J�n
	ShowWindow(m_hwnd, nCmdShow);
	UpdateWindow(m_hwnd);
}

/*=============================================================================================
	���b�Z�[�W�̃f�B�X�p�b�`
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
