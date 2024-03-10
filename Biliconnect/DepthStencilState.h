/*===========================================================================
	Date : 2022/02/08(��)	DepthStencilState.h
		Author	: ���ނ��邧
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
	bool Create();				//��������
	void SetEnable(bool use);	//�ݒ菈��
	void Release();				//�I������

private:
	GraphicsManager*			m_GraphicsManager;
	ID3D11DepthStencilState*	m_Enable;
	ID3D11DepthStencilState*	m_Disable;
};

#endif // !DEPTHSTENCILSTATE_H_
