/*=========================================================================
	Date : 2021/12/18(��)	Input.cpp
		Author : ���ނ��邧
		Update : 2021/12/18(��)

		���L�[�{�[�h�B�}�E�X�̓��͏���
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
	�f�o�C�X�̏���������
=============================================================================================*/
bool Input::Init(HINSTANCE hInstance, Window* wind)
{
	if (m_input == nullptr)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
			IID_IDirectInput8, (void**)&m_input, NULL);
	}

	//�L�[�{�[�h����������
	if (!KeyboardInit(wind->Get_HWND()))
		return false;

	//�}�E�X�̏���������
	if (!MouseInit(wind->Get_HWND()))
		return false;

	return true;
}

/*=============================================================================================
	�f�o�C�X�̏I������
=============================================================================================*/
void Input::Uninit()
{
	//�L�[�{�[�h�̏I������
	KeyboardUninit();
	//�}�E�X�̃L�[�{�[�h����
	MouseUninit();

	if (m_input != nullptr)
	{
		m_input->Release();
		m_input = nullptr;
	}
}

/*=============================================================================================
	�f�o�C�X�̍X�V����
=============================================================================================*/
void Input::Update()
{
	//�L�[�{�[�h�X�V����
	KeyboardUpdate();
	//�}�E�X�̍X�V����
	MouseUpdate();
}

/*=============================================================================================
	�L�[�{�[�h�̓��͏���(Press)
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
	�L�[�{�[�h�̓��͏���(Trigger)
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
	�L�[�{�[�h�̓��͏���(Release)
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
	�}�E�X�̓��͍��N���b�N����(Press)
=============================================================================================*/
bool Input::MouseLeftPress()
{
	return MousePress(m_NowMouseState.rgbButtons[0]);
}

/*=============================================================================================
	�}�E�X�̓��͍��N���b�N����(Trigger)
=============================================================================================*/
bool Input::MouseLeftTrigger()
{
	return MouseTrigger(m_NowMouseState.rgbButtons[0], m_OldMouseState.rgbButtons[0]);
}

/*=============================================================================================
	�}�E�X�̓��͍��N���b�N����(Release)
=============================================================================================*/
bool Input::MouseLeftRelease()
{
	return MouseRelease(m_NowMouseState.rgbButtons[0], m_OldMouseState.rgbButtons[0]);
}

/*=============================================================================================
	�}�E�X�̓��͉E�N���b�N����(Press)
=============================================================================================*/
bool Input::MouseRightPress()
{
	return MousePress(m_NowMouseState.rgbButtons[1]);
}

/*=============================================================================================
	�}�E�X�̓��͉E�N���b�N����(Trigger)
=============================================================================================*/
bool Input::MouseRightTrigger()
{
	return MouseTrigger(m_NowMouseState.rgbButtons[1], m_OldMouseState.rgbButtons[1]);
}

/*=============================================================================================
	�}�E�X�̓��͉E�N���b�N����(Release)
=============================================================================================*/
bool Input::MouseRightRelease()
{
	return MouseRelease(m_NowMouseState.rgbButtons[1], m_OldMouseState.rgbButtons[1]);
}

/*=============================================================================================
	�}�E�X�̓��͒��S�N���b�N����(Press)
=============================================================================================*/
bool Input::MouseCenterPress()
{
	return MousePress(m_NowMouseState.rgbButtons[2]);
}

/*=============================================================================================
	�}�E�X�̓��͒��S�N���b�N����(Trigger)
=============================================================================================*/
bool Input::MouseCenterTrigger()
{
	return MouseTrigger(m_NowMouseState.rgbButtons[2], m_OldMouseState.rgbButtons[2]);
}

/*=============================================================================================
	�}�E�X�̓��͒��S�N���b�N����(Release)
=============================================================================================*/
bool Input::MouseCenterRelease()
{
	return MouseRelease(m_NowMouseState.rgbButtons[2], m_OldMouseState.rgbButtons[2]);
}

/*=============================================================================================
	�}�E�X�̑��Βl���擾
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
	�}�E�X�̓��͏���(Press)
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
	�}�E�X�̓��͏���(Trigger)
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
	�}�E�X�̓��͏���(Release)
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
	�L�[�{�[�h�̏�����
=============================================================================================*/
bool Input::KeyboardInit(HWND hwnd)
{
	HRESULT ret = S_OK;

	//�f�o�C�X�̐���
	ret = m_input->CreateDevice(GUID_SysKeyboard, &m_inputKeyboard, NULL);
	if (FAILED(ret) || m_inputKeyboard == nullptr)
	{
		MessageBox(hwnd, "�L�[�{�[�h��������܂���ł���", "Not Found", MB_ICONWARNING);
		return false;
	}
	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	ret = m_inputKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret))
	{
		MessageBox(hwnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "Failed Set Up", MB_ICONWARNING);
		return false;
	}
	//�������[�h�̐ݒ�
	ret = m_inputKeyboard->SetCooperativeLevel(hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(ret))
	{
		MessageBox(hwnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "Failed Set Up", MB_ICONWARNING);
		return false;
	}

	//�L�[�{�[�h�̃A�N�Z�X�����擾����
	m_inputKeyboard->Acquire();

	return true;
}

/*=============================================================================================
	�L�[�{�[�h�̍X�V����
=============================================================================================*/
void Input::KeyboardUpdate()
{
	HRESULT ret = S_OK;

	//�O��f�[�^��ۑ�����
	::memcpy(m_OldKeyboardState, m_NowKeyboardState, 256);

	//�f�o�C�X����f�[�^���擾����
	ret = m_inputKeyboard->GetDeviceState(sizeof(m_NowKeyboardState), m_NowKeyboardState);
	if (!(SUCCEEDED(ret)))
	{
		//�A�N�Z�X�����擾����
		m_inputKeyboard->Acquire();
	}
}

/*=============================================================================================
	�L�[�{�[�h�̍X�V����
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
	�}�E�X�̏�����
=============================================================================================*/
bool Input::MouseInit(HWND hwnd)
{
	HRESULT ret = S_OK;

	//�f�o�C�X�̐���
	ret = m_input->CreateDevice(GUID_SysMouse, &m_inputMouse, NULL);
	if (FAILED(ret) || m_inputMouse == nullptr)
	{
		MessageBox(hwnd, "�}�E�X��������܂���ł���", "Not Found", MB_ICONWARNING);
		return false;
	}
	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	ret = m_inputMouse->SetDataFormat(&c_dfDIMouse2);
	if (FAILED(ret))
	{
		MessageBox(hwnd, "�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "Failed Set Up", MB_ICONWARNING);
		return false;
	}
	//�������[�h�̐ݒ�
	ret = m_inputMouse->SetCooperativeLevel(hwnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if (FAILED(ret))
	{
		MessageBox(hwnd, "�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", "Failed Set Up", MB_ICONWARNING);
		return false;
	}

	//�f�o�C�X�̐ݒ�
	DIPROPDWORD prop;

	prop.diph.dwSize		= sizeof(prop);
	prop.diph.dwHeaderSize	= sizeof(prop.diph);
	prop.diph.dwObj			= 0;
	prop.diph.dwHow			= DIPH_DEVICE;
	prop.dwData				= DIPROPAXISMODE_REL;	//�}�E�X�̈ړ��l ���Βl

	ret = m_inputMouse->SetProperty(DIPROP_AXISMODE, &prop.diph);
	if (FAILED(ret))
	{
		MessageBox(hwnd, "�}�E�X�̃v���p�e�B�ݒ�Ɏ��s���܂���", "Failed Set Up", MB_OK | MB_ICONWARNING);
		return false;
	}

	//�}�E�X�̃A�N�Z�X���擾
	m_inputMouse->Acquire();

	return true;
}

/*=============================================================================================
	�}�E�X�̍X�V����
=============================================================================================*/
void Input::MouseUpdate()
{
	HRESULT ret = S_OK;

	//�O��̒l��ۑ�����
	m_OldMouseState = m_NowMouseState;

	//�f�[�^�̎擾
	ret = m_inputMouse->GetDeviceState(sizeof(m_NowMouseState), &m_NowMouseState);
	if (FAILED(ret))
	{
		//�A�N�Z�X���𓾂�
		m_inputMouse->Acquire();
	}
}

/*=============================================================================================
	�}�E�X�̏I������
=============================================================================================*/
void Input::MouseUninit()
{
	if (m_inputMouse != nullptr)
	{
		m_inputMouse->Release();
		m_inputMouse = nullptr;
	}
}
