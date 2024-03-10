/*=========================================================================
	Date : 2021/12/18(日)	Input.h
		Author : がむしるぉ
		Update : 2021/12/18(日)

		※キーボード。マウスの入力処理
=========================================================================*/
#ifndef INPUT_H_
#define INPUT_H_

#include "main.h"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define	NUM_KEY_MAX			(256)

#define USE_KEYBOARD
#define USE_MOUSE

class Window;

class Input
{
public:
	static bool Init(HINSTANCE hInstance, Window* wind);
	static void Uninit();
	static void Update();

public:
	static bool KeyboardPress(int key);
	static bool KeyboardTrigger(int key);
	static bool KeyboardRelease(int key);

public:
	static bool MouseLeftPress();
	static bool MouseLeftTrigger();
	static bool MouseLeftRelease();
	static bool MouseRightPress();
	static bool MouseRightTrigger();
	static bool MouseRightRelease();
	static bool MouseCenterPress();
	static bool MouseCenterTrigger();
	static bool MouseCenterRelease();

public:
	static math::Float3 GetMouseXYZ();

private:
	static bool MousePress(BYTE buttonType);
	static bool MouseTrigger(BYTE buttonType, BYTE oldButtonType);
	static bool MouseRelease(BYTE buttonType, BYTE oldButtonType);

private:
	static bool KeyboardInit(HWND hwnd);
	static void KeyboardUpdate();
	static void KeyboardUninit();
	static bool MouseInit(HWND hwnd);
	static void MouseUpdate();
	static void MouseUninit();

private:
	static LPDIRECTINPUT8		m_input;					// IDirectInput8インターフェースへのポインタ
	static LPDIRECTINPUTDEVICE8	m_inputKeyboard;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
	static LPDIRECTINPUTDEVICE8	m_inputMouse;
	static DIMOUSESTATE2		m_NowMouseState;
	static DIMOUSESTATE2		m_OldMouseState;
	static BYTE					m_NowKeyboardState[256];
	static BYTE					m_OldKeyboardState[256];
};

#endif // !INPUT_H_
