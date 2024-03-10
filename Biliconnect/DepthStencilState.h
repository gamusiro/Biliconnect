/*===========================================================================
	Date : 2022/02/08(月)	DepthStencilState.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef DEPTHSTENCILSTATE_H_
#define DEPTHSTENCILSTATE_H_

#include "main.h"

class GraphicsManager;

class DepthStencilState
{
public:
	DepthStencilState(GraphicsManager* gm);
	~DepthStencilState();

public:
	bool Create();				//生成処理
	void SetEnable(bool use);	//設定処理
	void Release();				//終了処理

private:
	GraphicsManager*			m_GraphicsManager;
	ID3D11DepthStencilState*	m_Enable;
	ID3D11DepthStencilState*	m_Disable;
};

#endif // !DEPTHSTENCILSTATE_H_
