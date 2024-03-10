/*=========================================================================
	Date : 2022/03/14?(��)	Button.h	���͊Ǘ�/�L�[�R���t�B�O
		Author : A.I.
		Update :
=========================================================================*/
#ifndef BUTTON_H_
#define BUTTON_H_

#include "GameCreateSystem.h"

class Button
{
//////////////// �R���g���[���[ ////////////////
public:
	static int	DashC;

////////////////   �L�[�{�[�h   ////////////////
public:
	static int LMoveLeftK;				// �ԍ��ړ�
	static int LMoveRightK;				// �ԉE�ړ�

	static int RMoveLeftK;				// ���ړ�
	static int RMoveRightK;				// �E�ړ�

	static int Z;				// ���ړ�
	static int X;				// �E�ړ�

		//////// �L�[�R���t�B�O�p////////
#if 0
public:
	static void SetMoveButtonPushC(int button)	{ m_Push_C = button; }

public:
	static void SetMoveButtonPushK(int button)	{ m_Push_K = button; }
#endif
};

//////////////// �R���g���[���[ ////////////////
__declspec(selectany) int Button::DashC(XINPUT_GAMEPAD_LEFT_SHOULDER);

////////////////   �L�[�{�[�h   ////////////////
__declspec(selectany) int Button::LMoveLeftK(DIK_Q);
__declspec(selectany) int Button::LMoveRightK(DIK_E);

__declspec(selectany) int Button::RMoveLeftK(DIK_A);
__declspec(selectany) int Button::RMoveRightK(DIK_D);

__declspec(selectany) int Button::Z(DIK_Z);
__declspec(selectany) int Button::X(DIK_X);
#endif
