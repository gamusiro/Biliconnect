/*=============================================================================================================
	Controller.cpp (Xinputを利用)
				Author	:	白 人

				Create	:	2021/11/09
				Update	:	2021/12/18
=============================================================================================================*/
#include <Windows.h>

#include "Controller.h"
using namespace math;

#pragma comment(lib, "xinput.lib")

#define DEADZONE 8000

#define MAX_VIBRATION_VALUE (unsigned int)	65535
#define MIN_VIBRATION_VALUE (unsigned int)		0

//グローバル変数(XInput)
static XINPUT_STATE     state, old_state;
static XINPUT_VIBRATION	vibration;

/*===================================================================
   初期化処理
===================================================================*/
void Controller::Init()
{
    // XInputEnable(true);
}

/*===================================================================
    終了処理
===================================================================*/
void Controller::Uninit()
{
    // XInputEnable(false);
}

/*===================================================================
	更新処理
===================================================================*/
void Controller::Update()
{
	// XInput
	old_state = state;
	if (XInputGetState(0, &state) == ERROR_SUCCESS)
	{
		//接続されている
		int a = 0;
	}
	else
	{
		//接続されていない
		int b = 0;
	}
}

/*===================================================================
	バイブレーションの設定処理
===================================================================*/
void Controller::SetVibration(UINT val)
{
	val = MathCommons::Max(val, MIN_VIBRATION_VALUE);
	val = MathCommons::Min(val, MAX_VIBRATION_VALUE);

	vibration.wRightMotorSpeed = val;
	vibration.wLeftMotorSpeed = val;
	XInputSetState(0, &vibration);
}

/*===================================================================
	バイブレーションの設定処理
===================================================================*/
void Controller::SetVibrationRight(UINT val)
{
	val = MathCommons::Max(val, MIN_VIBRATION_VALUE);
	val = MathCommons::Min(val, MAX_VIBRATION_VALUE);

	vibration.wRightMotorSpeed = val;
	XInputSetState(0, &vibration);
}

/*===================================================================
	バイブレーションの設定処理
===================================================================*/
void Controller::SetVibrationLeft(UINT val)
{
	val = MathCommons::Max(val, MIN_VIBRATION_VALUE);
	val = MathCommons::Min(val, MAX_VIBRATION_VALUE);

	vibration.wLeftMotorSpeed = val;
	XInputSetState(0, &vibration);
}

/*===================================================================
	バイブレーションの停止処理
===================================================================*/
void Controller::StopVibration()
{
	vibration.wRightMotorSpeed = 0;
	vibration.wLeftMotorSpeed = 0;
	XInputSetState(0, &vibration);
}

/*===================================================================
	スティックの傾き取得
===================================================================*/
Float2 Controller::GetLeftStick() { return Controller::GetStick(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY); } //LStick
Float2 Controller::GetRightStick(){ return Controller::GetStick(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY); } //RStick

/*===================================================================
	LStickPress取得
===================================================================*/
bool Controller::GetLStickPressUp()		{ return Controller::StickPressUp   (state.Gamepad.sThumbLY); }
bool Controller::GetLStickPressDown()	{ return Controller::StickPressDown (state.Gamepad.sThumbLY); }
bool Controller::GetLStickPressRight()	{ return Controller::StickPressRight(state.Gamepad.sThumbLX); }
bool Controller::GetLStickPressLeft()	{ return Controller::StickPressLeft (state.Gamepad.sThumbLX); }

/*===================================================================
	RStickPress取得
===================================================================*/
bool Controller::GetRStickPressUp()		{ return Controller::StickPressUp   (state.Gamepad.sThumbRY); }
bool Controller::GetRStickPressDown()	{ return Controller::StickPressDown (state.Gamepad.sThumbRY); }
bool Controller::GetRStickPressRight()	{ return Controller::StickPressRight(state.Gamepad.sThumbRX); }
bool Controller::GetRStickPressLeft()	{ return Controller::StickPressLeft (state.Gamepad.sThumbRX); }

/*===================================================================
	LStickTrigger取得
===================================================================*/
bool Controller::GetLStickTriggerUp()	{ return Controller::StickTriggerUp   (state.Gamepad.sThumbLY, old_state.Gamepad.sThumbLY); }
bool Controller::GetLStickTriggerDown() { return Controller::StickTriggerDown (state.Gamepad.sThumbLY, old_state.Gamepad.sThumbLY); }
bool Controller::GetLStickTriggerRight(){ return Controller::StickTriggerRight(state.Gamepad.sThumbLX, old_state.Gamepad.sThumbLX); }
bool Controller::GetLStickTriggerLeft()	{ return Controller::StickTriggerLeft (state.Gamepad.sThumbLX, old_state.Gamepad.sThumbLX); }

/*===================================================================
	RStickTrigger取得
===================================================================*/
bool Controller::GetRStickTriggerUp()	{ return Controller::StickTriggerUp   (state.Gamepad.sThumbRY, old_state.Gamepad.sThumbRY); }
bool Controller::GetRStickTriggerDown() { return Controller::StickTriggerDown (state.Gamepad.sThumbRY, old_state.Gamepad.sThumbRY); }
bool Controller::GetRStickTriggerRight(){ return Controller::StickTriggerRight(state.Gamepad.sThumbRX, old_state.Gamepad.sThumbRX); }
bool Controller::GetRStickTriggerLeft()	{ return Controller::StickTriggerLeft (state.Gamepad.sThumbRX, old_state.Gamepad.sThumbRX); }

/*===================================================================
	LStickTrigger取得
===================================================================*/
bool Controller::GetLStickReleaseUp()	{ return Controller::StickReleaseUp   (state.Gamepad.sThumbLY, old_state.Gamepad.sThumbLY); }
bool Controller::GetLStickReleaseDown() { return Controller::StickReleaseDown (state.Gamepad.sThumbLY, old_state.Gamepad.sThumbLY); }
bool Controller::GetLStickReleaseRight(){ return Controller::StickReleaseRight(state.Gamepad.sThumbLX, old_state.Gamepad.sThumbLX); }
bool Controller::GetLStickReleaseLeft()	{ return Controller::StickReleaseLeft (state.Gamepad.sThumbLX, old_state.Gamepad.sThumbLX); }

/*===================================================================
	RStickTrigger取得
===================================================================*/
bool Controller::GetRStickReleaseUp()	{ return Controller::StickReleaseUp   (state.Gamepad.sThumbRY, old_state.Gamepad.sThumbRY); }
bool Controller::GetRStickReleaseDown() { return Controller::StickReleaseDown (state.Gamepad.sThumbRY, old_state.Gamepad.sThumbRY); }
bool Controller::GetRStickReleaseRight(){ return Controller::StickReleaseRight(state.Gamepad.sThumbRX, old_state.Gamepad.sThumbRX); }
bool Controller::GetRStickReleaseLeft()	{ return Controller::StickReleaseLeft (state.Gamepad.sThumbRX, old_state.Gamepad.sThumbRX); }



/*===================================================================
	特定ボタン(Press)の取得
===================================================================*/
bool Controller::GetButtonPressA()			{ return ButtonPress(XINPUT_GAMEPAD_A);}
bool Controller::GetButtonPressB()			{ return ButtonPress(XINPUT_GAMEPAD_B); }
bool Controller::GetButtonPressX()			{ return ButtonPress(XINPUT_GAMEPAD_X); }
bool Controller::GetButtonPressY()			{ return ButtonPress(XINPUT_GAMEPAD_Y); }
bool Controller::GetButtonPressLeft()		{ return ButtonPress(XINPUT_GAMEPAD_DPAD_LEFT); }
bool Controller::GetButtonPressRight()		{ return ButtonPress(XINPUT_GAMEPAD_DPAD_RIGHT); }
bool Controller::GetButtonPressUp()			{ return ButtonPress(XINPUT_GAMEPAD_DPAD_UP); }
bool Controller::GetButtonPressDown()		{ return ButtonPress(XINPUT_GAMEPAD_DPAD_DOWN); }
bool Controller::GetButtonPressStart()		{ return ButtonPress(XINPUT_GAMEPAD_START); }
bool Controller::GetButtonPressBack()		{ return ButtonPress(XINPUT_GAMEPAD_BACK); }
bool Controller::GetButtonPressLThumb()		{ return ButtonPress(XINPUT_GAMEPAD_LEFT_THUMB); }
bool Controller::GetButtonPressRThumb()		{ return ButtonPress(XINPUT_GAMEPAD_RIGHT_THUMB); }
bool Controller::GetButtonPressLShoulder()	{ return ButtonPress(XINPUT_GAMEPAD_LEFT_SHOULDER); }
bool Controller::GetButtonPressRShoulder()	{ return ButtonPress(XINPUT_GAMEPAD_RIGHT_SHOULDER); }

/*===================================================================
	特定ボタン(Trigger)の取得
===================================================================*/
bool Controller::GetButtonTriggerA()			{ return ButtonTrigger(XINPUT_GAMEPAD_A);}
bool Controller::GetButtonTriggerB()			{ return ButtonTrigger(XINPUT_GAMEPAD_B); }
bool Controller::GetButtonTriggerX()			{ return ButtonTrigger(XINPUT_GAMEPAD_X); }
bool Controller::GetButtonTriggerY()			{ return ButtonTrigger(XINPUT_GAMEPAD_Y); }
bool Controller::GetButtonTriggerLeft()			{ return ButtonTrigger(XINPUT_GAMEPAD_DPAD_LEFT); }
bool Controller::GetButtonTriggerRight()		{ return ButtonTrigger(XINPUT_GAMEPAD_DPAD_RIGHT); }
bool Controller::GetButtonTriggerUp()			{ return ButtonTrigger(XINPUT_GAMEPAD_DPAD_UP); }
bool Controller::GetButtonTriggerDown()			{ return ButtonTrigger(XINPUT_GAMEPAD_DPAD_DOWN); }
bool Controller::GetButtonTriggerStart()		{ return ButtonTrigger(XINPUT_GAMEPAD_START); }
bool Controller::GetButtonTriggerBack()			{ return ButtonTrigger(XINPUT_GAMEPAD_BACK); }
bool Controller::GetButtonTriggerLThumb()		{ return ButtonTrigger(XINPUT_GAMEPAD_LEFT_THUMB); }
bool Controller::GetButtonTriggerRThumb()		{ return ButtonTrigger(XINPUT_GAMEPAD_RIGHT_THUMB); }
bool Controller::GetButtonTriggerLShoulder()	{ return ButtonTrigger(XINPUT_GAMEPAD_LEFT_SHOULDER); }
bool Controller::GetButtonTriggerRShoulder()	{ return ButtonTrigger(XINPUT_GAMEPAD_RIGHT_SHOULDER); }

/*===================================================================
	特定ボタン(Release)の取得
===================================================================*/
bool Controller::GetButtonReleaseA()		{ return ButtonRelease(XINPUT_GAMEPAD_A); }
bool Controller::GetButtonReleaseB()		{ return ButtonRelease(XINPUT_GAMEPAD_B); }
bool Controller::GetButtonReleaseX()		{ return ButtonRelease(XINPUT_GAMEPAD_X); }
bool Controller::GetButtonReleaseY()		{ return ButtonRelease(XINPUT_GAMEPAD_Y); }
bool Controller::GetButtonReleaseLeft()		{ return ButtonRelease(XINPUT_GAMEPAD_DPAD_LEFT); }
bool Controller::GetButtonReleaseRight()	{ return ButtonRelease(XINPUT_GAMEPAD_DPAD_RIGHT); }
bool Controller::GetButtonReleaseUp()		{ return ButtonRelease(XINPUT_GAMEPAD_DPAD_UP); }
bool Controller::GetButtonReleaseDown()		{ return ButtonRelease(XINPUT_GAMEPAD_DPAD_DOWN); }
bool Controller::GetButtonReleaseStart()	{ return ButtonRelease(XINPUT_GAMEPAD_START); }
bool Controller::GetButtonReleaseBack()		{ return ButtonRelease(XINPUT_GAMEPAD_BACK); }
bool Controller::GetButtonReleaseLThumb()	{ return ButtonRelease(XINPUT_GAMEPAD_LEFT_THUMB); }
bool Controller::GetButtonReleaseRThumb()	{ return ButtonRelease(XINPUT_GAMEPAD_RIGHT_THUMB); }
bool Controller::GetButtonReleaseLShoulder(){ return ButtonRelease(XINPUT_GAMEPAD_LEFT_SHOULDER); }
bool Controller::GetButtonReleaseRShoulder(){ return ButtonRelease(XINPUT_GAMEPAD_RIGHT_SHOULDER); }

/*===================================================================
	背面トリガーボタンの取得
===================================================================*/
float Controller::GetLTValue()	{ return state.Gamepad.bLeftTrigger / 255.f; }
float Controller::GetRTValue()	{ return state.Gamepad.bRightTrigger / 255.f; }
bool Controller::GetLTPress()	{ return TriggerPress(state.Gamepad.bLeftTrigger); }
bool Controller::GetRTPress()	{ return TriggerPress(state.Gamepad.bRightTrigger); }
bool Controller::GetLTTrigger()	{ return TriggerTrigger(state.Gamepad.bLeftTrigger, old_state.Gamepad.bLeftTrigger);}
bool Controller::GetRTTrigger()	{ return TriggerTrigger(state.Gamepad.bRightTrigger, old_state.Gamepad.bRightTrigger);}
bool Controller::GetLTRelease()	{ return TriggerRelease(state.Gamepad.bLeftTrigger, old_state.Gamepad.bLeftTrigger);}
bool Controller::GetRTRelease()	{ return TriggerRelease(state.Gamepad.bRightTrigger, old_state.Gamepad.bRightTrigger);}

/*===================================================================
	スティックの傾き取得
===================================================================*/
Float2 Controller::GetStick(const SHORT& stick_x, const SHORT& stick_y)
{
	Float2 result;

	// XInput
	result.x = (float)stick_x;
	result.y = (float)stick_y;

	if (result.x < DEADZONE && result.x > -DEADZONE)	result.x = 0.0f;
	if (result.y < DEADZONE && result.y > -DEADZONE)	result.y = 0.0f;

	result /= 0x7FFF;	//正規化する
	result.y *= -1;		//上下が反転するので
	return result;
}

/*===================================================================
	StickTrigger(上)取得
===================================================================*/
bool Controller::StickTriggerUp(const SHORT& stick_y, const SHORT& old_stick_y)
{
	bool result = false;

	if (stick_y > DEADZONE)
	{
		int old_y = (int)old_stick_y / DEADZONE;
		if (old_y == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickTrigger(下)取得
===================================================================*/
bool Controller::StickTriggerDown(const SHORT& stick_y, const SHORT& old_stick_y)
{
	bool result = false;

	if (stick_y < -DEADZONE)
	{
		// XInput
		int old_y = (int)old_stick_y / DEADZONE;
		if (old_y == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickTrigger(右)取得
===================================================================*/
bool Controller::StickTriggerRight(const SHORT& stick_x, const SHORT& old_stick_x)
{
	bool result = false;

	if (stick_x > DEADZONE)
	{
		// XInput
		int old_x = (int)old_stick_x / DEADZONE;
		if (old_x == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickTrigger(左)取得
===================================================================*/
bool Controller::StickTriggerLeft(const SHORT& stick_x, const SHORT& old_stick_x)
{
	bool result = false;

	if (stick_x < -DEADZONE)
	{
		// XInput
		int old_x = (int)old_stick_x / DEADZONE;
		if (old_x == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickPress(上)取得
===================================================================*/
bool Controller::StickPressUp(const SHORT& stick_y)
{
	bool result = false;

	if (stick_y > DEADZONE)
	{
		result = true;
	}
	return result;
}

/*===================================================================
	StickPress(下)取得
===================================================================*/
bool Controller::StickPressDown(const SHORT& stick_y)
{
	bool result = false;

	if (stick_y < -DEADZONE)
	{
		result = true;
	}
	return result;
}

/*===================================================================
	StickPress(右)取得
===================================================================*/
bool Controller::StickPressRight(const SHORT& stick_x)
{
	bool result = false;

	if (stick_x > DEADZONE)
	{
		result = true;
	}
	return result;
}

/*===================================================================
	StickPress(左)取得
===================================================================*/
bool Controller::StickPressLeft(const SHORT& stick_x)
{
	bool result = false;

	if (stick_x < -DEADZONE)
	{
		result = true;
	}
	return result;
}

/*===================================================================
	StickRelease(上)取得
===================================================================*/
bool Controller::StickReleaseUp(const SHORT& stick_y, const SHORT& old_stick_y)
{
	bool result = false;

	if (old_stick_y > DEADZONE)
	{
		// XInput
		int now_y = (int)stick_y / DEADZONE;
		if (now_y == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickRelease(下)取得
===================================================================*/
bool Controller::StickReleaseDown(const SHORT& stick_y, const SHORT& old_stick_y)
{
	bool result = false;

	if (old_stick_y < -DEADZONE)
	{
		// XInput
		int now_y = (int)stick_y / DEADZONE;
		if (now_y == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickRelease(右)取得
===================================================================*/
bool Controller::StickReleaseRight(const SHORT& stick_x, const SHORT& old_stick_x)
{
	bool result = false;

	if (old_stick_x > DEADZONE)
	{
		// XInput
		int now_x = (int)stick_x / DEADZONE;
		if (now_x == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	StickRelease(左)取得
===================================================================*/
bool Controller::StickReleaseLeft(const SHORT& stick_x, const SHORT& old_stick_x)
{
	bool result = false;

	if (old_stick_x < -DEADZONE)
	{
		// XInput
		int now_x = (int)stick_x / DEADZONE;
		if (now_x == 0)
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	背面トリガーボタン(Press)の取得
===================================================================*/
bool Controller::TriggerPress(const SHORT& trigger)
{
	if (trigger > 128)
	{
		return true;
	}
	return false;
}

/*===================================================================
	背面トリガーボタン(Trigger)の取得
===================================================================*/
bool Controller::TriggerTrigger(const SHORT& trigger, const SHORT& old_trigger)
{
	if (trigger > 128)
	{
		if (old_trigger < 128)
		{
			return true;
		}
	}
	return false;
}

/*===================================================================
	背面トリガーボタン(Release)の取得
===================================================================*/
bool Controller::TriggerRelease(const SHORT& trigger, const SHORT& old_trigger)
{
	if (trigger < 128)
	{
		if (old_trigger > 128)
		{
			return true;
		}
	}
	return false;
}

/*===================================================================
	Press取得
===================================================================*/
bool Controller::ButtonPress(UINT button)
{
	bool result = false;

	if (state.Gamepad.wButtons & button)
	{
		result = true;
	}
	return result;
}

/*===================================================================
	Trigger取得
===================================================================*/
bool Controller::ButtonTrigger(UINT button)
{
	bool result = false;

	if (state.Gamepad.wButtons & button)
	{
		if (!(old_state.Gamepad.wButtons & button))
		{
			result = true;
		}
	}
	return result;
}

/*===================================================================
	Release取得
===================================================================*/
bool Controller::ButtonRelease(UINT button)
{
	bool result = false;

	if (!(state.Gamepad.wButtons & button))
	{
		if (old_state.Gamepad.wButtons & button)
		{
			result = true;
		}
	}
	return result;
}