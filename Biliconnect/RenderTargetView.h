/*===========================================================================
	Date : 2022/02/08(月)	RenderTargetView.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef RENDERTARGETVIEW_H_
#define RENDERTARGETVIEW_H_

#include "main.h"

class GraphicsManager;

class RenderTargetView
{
public:
	RenderTargetView(GraphicsManager* gm);
	~RenderTargetView();

public:
	bool Create(IDXGISwapChain* swapChain);		//生成処理
	void Clear(float r, float g, float b);		//描画のクリア処理
	void Release();								//解放処理

private:
	GraphicsManager*		m_GraphicsManager;
	ID3D11RenderTargetView* m_d3dRTV;

private:
	friend GraphicsManager;
};

#endif // !RENDERTARGETVIEW_H_
