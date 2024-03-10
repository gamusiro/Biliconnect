/*=========================================================================
	Date : 2022/03/14?(月)	Button.h	入力管理/キーコンフィグ
		Author : A.I.
		Update :
=========================================================================*/
#ifndef BUTTON_H_
#define BUTTON_H_

#include "GameCreateSystem.h"

class Button
{
//////////////// コントローラー ////////////////
public:
	static int	DashC;

////////////////   キーボード   ////////////////
public:
	static int LMoveLeftK;				// 赤左移動
	static int LMoveRightK;				// 赤右移動

	static int RMoveLeftK;				// 青左移動
	static int RMoveRightK;				// 青右移動

	static int Z;				// 青左移動
	static int X;				// 青右移動

		//////// キーコンフィグ用////////
#if 0
public:
	static void SetMoveButtonPushC(int button)	{ m_Push_C = button; }

public:
	static void SetMoveButtonPushK(int button)	{ m_Push_K = button; }
#endif
};

//////////////// コントローラー ////////////////
__declspec(selectany) int Button::DashC(XINPUT_GAMEPAD_LEFT_SHOULDER);

////////////////   キーボード   ////////////////
__declspec(selectany) int Button::LMoveLeftK(DIK_Q);
__declspec(selectany) int Button::LMoveRightK(DIK_E);

__declspec(selectany) int Button::RMoveLeftK(DIK_A);
__declspec(selectany) int Button::RMoveRightK(DIK_D);

__declspec(selectany) int Button::Z(DIK_Z);
__declspec(selectany) int Button::X(DIK_X);
#endif
