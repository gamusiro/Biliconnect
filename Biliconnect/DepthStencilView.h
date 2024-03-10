/*===========================================================================
	Date : 2022/02/08(��)	DepthStencilView.h
		Author	: ���ނ��邧
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
	bool Create(IDXGISwapChain* swapChain);	//��������
	void Clear();							//�o�b�t�@�̃N���A����
	void Release();							//�������

private:
	GraphicsManager*		m_GraphicsManager;
	ID3D11DepthStencilView* m_d3dDSV;

private:
	friend GraphicsManager;
};

#endif // !DEPTHSTENCLIVIEW_H_
