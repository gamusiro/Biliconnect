/*===========================================================================
	Date : 2022/02/05(�y)	main.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#ifndef MAIN_H_
#define MAIN_H_

#pragma warning(push)
#pragma warning(disable: 4005)

#include <iostream>

//DirectX11�̃C���N���[�h
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>

//�����N�̃p�X��ʂ�
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

//�I���W�i���N���X�̃C���N���[�h
#include "Original/MathManager.h"

#pragma warning(pop)

#define SCREEN_WIDTH	1920
#define SCREEN_HEIGHT	1080

#endif // !MAIN_H_
