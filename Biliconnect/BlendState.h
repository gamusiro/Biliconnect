/*===========================================================================
	Date : 2022/02/08(��)	BlendState.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#ifndef BLENDSTATE_H_
#define BLENDSTATE_H_

#include "main.h"

class GraphicsManager;

/**********************************************************
	@brief �u�����h���[�h�̎w��
	None		: �u�����h�Ȃ�
	ALPHA		: �A���t�@�u�����h
	ADD			: ���Z�u�����h
	SUBTRACT	: ���Z�u�����h
**********************************************************/
enum class BLEND_MODE
{
	NONE, 
	ALPHA,
	ADD,
	SUBTRACT
};

class BlendState
{
public:
	BlendState(GraphicsManager* gm);
	~BlendState();

public:
	bool Create();					//��������
	void SetMode(BLEND_MODE mode);	//�ݒ菈��
	void Release();					//�������

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11BlendState*	m_BlendNone;
	ID3D11BlendState*	m_BlendAlpha;
	ID3D11BlendState*	m_BlendAdd;
	ID3D11BlendState*	m_BlendSub;
};

#endif // !BLENDSTATE_H_
