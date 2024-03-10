/*===========================================================================
	Date : 2022/02/08(��)	RasterizerState.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#ifndef RASTERIZERSTATE_H_
#define RASTERIZERSTATE_H_

#include "main.h"

class GraphicsManager;

/**********************************************************
	@brief �J�����O���[�h�̎w��
	None : �J�����O���[�h����		
	FRONT: �J�����O���[�h�t�����g	(���v���)
	BACK : �J�����O���[�h�o�b�N	(�����v���)
**********************************************************/
enum class CULL_MODE
{
	NONE, FRONT, BACK
};

class RasterizerState
{
public:
	RasterizerState(GraphicsManager* gm);
	~RasterizerState();

public:
	bool Create();					//��������
	void SetMode(CULL_MODE mode);	//���[�h�̎w��
	void Release();					//�I������

private:
	GraphicsManager*		m_GraphicsManager;
	ID3D11RasterizerState*	m_RS_Cull_Off;
	ID3D11RasterizerState*	m_RS_Cull_CW;
	ID3D11RasterizerState*	m_RS_Cull_CCW;
};

#endif // !RASTERIZERSTATE_H_
