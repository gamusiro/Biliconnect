/*===========================================================================
	Date : 2022/02/07(��)	SwapChain.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#ifndef SWAPCHAIN_H_
#define SWAPCHAIN_H_

#include "main.h"

class GraphicsManager;

class SwapChain
{
public:
	SwapChain(GraphicsManager* gm);
	~SwapChain();

public:
	bool Create(IDXGIFactory* fact);	//��������
	void Release();						//�������
	void Present();						//�o�b�t�@�̐؂�ւ�����
	void ScreenChanger(bool full);		//�\�����[�h�ؑ�

private:
	GraphicsManager*	m_GraphicsManager;
	IDXGISwapChain*		m_dxgiSC;

private:
	friend GraphicsManager;
};

#endif // !SWAPCHAIN_H_
