/*===========================================================================
	Date : 2022/02/07(日)	SwapChain.h
		Author	: がむしるぉ
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
	bool Create(IDXGIFactory* fact);	//生成処理
	void Release();						//解放処理
	void Present();						//バッファの切り替え処理
	void ScreenChanger(bool full);		//表示モード切替

private:
	GraphicsManager*	m_GraphicsManager;
	IDXGISwapChain*		m_dxgiSC;

private:
	friend GraphicsManager;
};

#endif // !SWAPCHAIN_H_
