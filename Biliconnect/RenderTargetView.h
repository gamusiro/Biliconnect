/*===========================================================================
	Date : 2022/02/08(��)	RenderTargetView.h
		Author	: ���ނ��邧
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
	bool Create(IDXGISwapChain* swapChain);		//��������
	void Clear(float r, float g, float b);		//�`��̃N���A����
	void Release();								//�������

private:
	GraphicsManager*		m_GraphicsManager;
	ID3D11RenderTargetView* m_d3dRTV;

private:
	friend GraphicsManager;
};

#endif // !RENDERTARGETVIEW_H_
