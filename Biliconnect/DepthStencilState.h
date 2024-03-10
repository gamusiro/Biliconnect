/*===========================================================================
	Date : 2022/02/08(Œ)	DepthStencilState.h
		Author	: ‚ª‚Ş‚µ‚é‚§
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
	bool Create();				//¶¬ˆ—
	void SetEnable(bool use);	//İ’èˆ—
	void Release();				//I—¹ˆ—

private:
	GraphicsManager*			m_GraphicsManager;
	ID3D11DepthStencilState*	m_Enable;
	ID3D11DepthStencilState*	m_Disable;
};

#endif // !DEPTHSTENCILSTATE_H_
