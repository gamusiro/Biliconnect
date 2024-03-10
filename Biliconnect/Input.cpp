/*=========================================================================
	Date : 2021/12/18(日)	Input.cpp
		Author : がむしるぉ
		Update : 2021/12/18(日)

		※キーボード。マウスの入力処理
=========================================================================*/
#include "Window.h"

#include "input.h"
using namespace math;

LPDIRECTINPUT8			Input::m_input			= nullptr;
LPDIRECTINPUTDEVICE8	Input::m_inputKeyboard	= nullptr;
LPDIRECTINPUTDEVICE8	Input::m_inputMouse		= nullptr;
DIMOUSESTATE2			Input::m_NowMouseState	= {};
DIMOUSESTATE2			Input::m_OldMouseState	= {};
BYTE					Input::m_NowKeyboardState[256];
BYTE					Input::m_OldKeyboardState[256];

/*=============================================================================================
	デバイスの初期化処理
=============================================================================================*/
bool Input::Init(HINSTANCE hInstance, Window* wind)
{
	if (m_input == nullptr)
	{
		// DirectInputオブジェクトの作成
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_input, NULL);
	}

	//キーボード初期化処理
	if (!KeyboardInit(wind->Get_HWND()))
		return false;

	//マウスの初期化処理
	if (!MouseInit(wind->Get_HWND()))
		return false;

	return true;
}

/*=============================================================================================
	デバイスの終了処理
=============================================================================================*/
void Input::Uninit()
{
	//キーボードの終了処理
	KeyboardUninit();
	//マウスのキーボード処理
	MouseUninit();

	if (m_input != nullptr)
	{
		m_input->Release();
		m_input = nullptr;
	}
}

/*=============================================================================================
	デバイスの更新処理
=============================================================================================*/
void Input::Update()
{
	//キーボード更新処理
	KeyboardUpdate();
	//マウスの更新処理
	MouseUpdate();
}

/*=============================================================================================
	キーボードの入力処理(Press)
=============================================================================================*/
bool Input::KeyboardPress(int key)
{
	if (m_NowKeyboardState[key] & 0x80)
	{
		return true;
	}
	return false;
}

/*=============================================================================================
	キーボードの入力処理(Trigger)
=============================================================================================*/
bool Input::KeyboardTrigger(int key)
{
	if (m_NowKeyboardState[key] & 0x80)
	{
		if (!(m_OldKeyboardState[key] & 0x80))
		{
			return true;
		}
	}
	return false;
}

/*=============================================================================================
	キーボードの入力処理(Release)
=============================================================================================*/
bool Input::KeyboardRelease(int key)
{
	if (m_OldKeyboardState[key] & 0x80)
	{
		if (!(m_NowKeyboardState[key] & 0x80))
		{
			return true;
		}
	}
	return false;
}

/*=============================================================================================
	マウスの入力左クリック処理(Press)
=============================================================================================*/
bool Input::MouseLeftPress()
{
	return MousePress(m_NowMouseState.rgbButtons[0]);
}

/*=============================================================================================
	マウスの入力左クリック処理(Trigger)
=============================================================================================*/
bool Input::MouseLeftTrigger()
{
	return MouseTrigger(m_NowMouseState.rgbButtons[0], m_OldMouseState.rgbButtons[0]);
}

/*=============================================================================================
	マウスの入力左クリック処理(Release)
=============================================================================================*/
bool Input::MouseLeftRelease()
{
	return MouseRelease(m_NowMouseState.rgbButtons[0], m_OldMouseState.rgbButtons[0]);
}

/*=============================================================================================
	マウスの入力右クリック処理(Press)
=============================================================================================*/
bool Input::MouseRightPress()
{
	return MousePress(m_NowMouseState.rgbButtons[1]);
}

/*=============================================================================================
	マウスの入力右クリック処理(Trigger)
=============================================================================================*/
bool Input::MouseRightTrigger()
{
	return MouseTrigger(m_NowMouseState.rgbButtons[1], m_OldMouseState.rgbButtons[1]);
}

/*=============================================================================================
	マウスの入力右クリック処理(Release)
=============================================================================================*/
bool Input::MouseRightRelease()
{
	return MouseRelease(m_NowMouseState.rgbButtons[1], m_OldMouseState.rgbButtons[1]);
}

/*=============================================================================================
	マウスの入力中心クリック処理(Press)
=============================================================================================*/
bool Input::MouseCenterPress()
{
	return MousePress(m_NowMouseState.rgbButtons[2]);
}

/*=============================================================================================
	マウスの入力中心クリック処理(Trigger)
=============================================================================================*/
bool Input::MouseCenterTrigger()
{
	return MouseTrigger(m_NowMouseState.rgbButtons[2], m_OldMouseState.rgbButtons[2]);
}

/*=============================================================================================
	マウスの入力中心クリック処理(Release)
=============================================================================================*/
bool Input::MouseCenterRelease()
{
	return MouseRelease(m_NowMouseState.rgbButtons[2], m_OldMouseState.rgbButtons[2]);
}

/*=============================================================================================
	マウスの相対値を取得
=============================================================================================*/
Float3 Input::GetMouseXYZ()
{
	Float3 ret;
	ret.x = (float)m_NowMouseState.lX;
	ret.y = (float)m_NowMouseState.lY;
	ret.z = (float)m_NowMouseState.lZ;
	return ret;
}

/*=============================================================================================
	マウスの入力処理(Press)
=============================================================================================*/
bool Input::MousePress(BYTE buttonType)
{
	if (buttonType & 0x80)
	{
		return true;
	}
	return false;
}

/*=============================================================================================
	マウスの入力処理(Trigger)
=============================================================================================*/
bool Input::MouseTrigger(BYTE buttonType, BYTE oldButtonType)
{
	if (buttonType & 0x80)
	{
		if (!(oldButtonType & 0x80))
		{
			return true;
		}
	}
	return false;
}

/*=============================================================================================
	マウスの入力処理(Release)
=============================================================================================*/
bool Input::MouseRelease(BYTE buttonType, BYTE oldButtonType)
{
	if (oldButtonType & 0x80)
	{
		if (!(buttonType & 0x80))
		{
			return true;
		}
	}
	return false;
}

/*=============================================================================================
	キーボードの初期化
=============================================================================================*/
bool Input::KeyboardInit(HWND hwnd)
{
	HRESULT ret = S_OK;

	//デバイスの生成
	ret = m_input->CreateDevice(GUID_SysKeyboard, &m_inputKeyboard, NULL);
	if (FAILED(ret) || m_inputKeyboard == nullptr)
	{
		MessageBox(hwnd, "キーボードが見つかりませんでした", "Not Found", MB_ICONWARNING);
		return false;
	}
	//データフォーマットの設定
	ret = m_inputKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret))
	{
		MessageBox(hwnd, "キーボードのデータフォーマットを設定できませんでした。", "Failed Set Up", MB_ICONWARNING);
		return false;
	}
	//協調モードの設定
	ret = m_inputKeyboard->SetCooperativeLevel(hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(ret))
	{
		MessageBox(hwnd, "キーボードの協調モードを設定できませんでした。", "Failed Set Up", MB_ICONWARNING);
		return false;
	}

	//キーボードのアクセス権を取得する
	m_inputKeyboard->Acquire();

	return true;
}

/*=============================================================================================
	キーボードの更新処理
=============================================================================================*/
void Input::KeyboardUpdate()
{
	HRESULT ret = S_OK;

	//前回データを保存する
	::memcpy(m_OldKeyboardState, m_NowKeyboardState, 256);

	//デバイスからデータを取得する
	ret = m_inputKeyboard->GetDeviceState(sizeof(m_NowKeyboardState), m_NowKeyboardState);
	if (!(SUCCEEDED(ret)))
	{
		//アクセス権を取得する
		m_inputKeyboard->Acquire();
	}
}

/*=============================================================================================
	キーボードの更新処理
=============================================================================================*/
void Input::KeyboardUninit()
{
	if (m_inputKeyboard != nullptr)
	{
		m_inputKeyboard->Release();
		m_inputKeyboard = nullptr;
	}
}

/*=============================================================================================
	マウスの初期化
=============================================================================================*/
bool Input::MouseInit(HWND hwnd)
{
	HRESULT ret = S_OK;

	//デバイスの生成
	ret = m_input->CreateDevice(GUID_SysMouse, &m_inputMouse, NULL);
	if (FAILED(ret) || m_inputMouse == nullptr)
	{
		MessageBox(hwnd, "マウスが見つかりませんでした", "Not Found", MB_ICONWARNING);
		return false;
	}
	//データフォーマットの設定
	ret = m_inputMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(ret))
	{
		MessageBox(hwnd, "マウスのデータフォーマットを設定できませんでした。", "Failed Set Up", MB_ICONWARNING);
		return false;
	}
	//協調モードの設定
	ret = m_inputMouse->SetCooperativeLevel(hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(ret))
	{
		MessageBox(hwnd, "マウスの協調モードを設定できませんでした。", "Failed Set Up", MB_ICONWARNING);
		return false;
	}

	//デバイスの設定
	DIPROPDWORD prop;

	prop.diph.dwSize		= sizeof(prop);
	prop.diph.dwHeaderSize	= sizeof(prop.diph);
	prop.diph.dwObj			= 0;
	prop.diph.dwHow			= DIPH_DEVICE;
	prop.dwData				= DIPROPAXISMODE_REL;	//マウスの移動値 相対値

	ret = m_inputMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(ret))
	{
		MessageBox(hwnd, "マウスのプロパティ設定に失敗しました", "Failed Set Up", MB_OK | MB_ICONWARNING);
		return false;
	}

	//マウスのアクセス権取得
	m_inputMouse->Acquire();

	return true;
}

/*=============================================================================================
	マウスの更新処理
=============================================================================================*/
void Input::MouseUpdate()
{
	HRESULT ret = S_OK;

	//前回の値を保存する
	m_OldMouseState = m_NowMouseState;

	//データの取得
	ret = m_inputMouse->GetDeviceState(sizeof(m_NowMouseState), &m_NowMouseState);
	if (FAILED(ret))
	{
		//アクセス権を得る
		m_inputMouse->Acquire();
	}
}

/*=============================================================================================
	マウスの終了処理
=============================================================================================*/
void Input::MouseUninit()
{
	if (m_inputMouse != nullptr)
	{
		m_inputMouse->Release();
		m_inputMouse = nullptr;
	}
}
