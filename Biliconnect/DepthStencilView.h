/*===========================================================================
	Date : 2022/02/08(月)	DepthStencilView.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef DEPTHSTENCLIVIEW_H_
#define DEPTHSTENCLIVIEW_H_

#include "main.h"

class GraphicsManager;

class DepthStencilView
{
public:
	DepthStencilView(GraphicsManager* gm);
	~DepthStencilView();

public:
	bool Create(IDXGISwapChain* swapChain);	//生成処理
	void Clear();							//バッファのクリア処理
	void Release();							//解放処理

private:
	GraphicsManager*		m_GraphicsManager;
	ID3D11DepthStencilView* m_d3dDSV;

private:
	friend GraphicsManager;
};

#endif // !DEPTHSTENCLIVIEW_H_
