/*===========================================================================
	Date : 2022/02/08(��)	RasterizerState.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "RasterizerState.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
RasterizerState::RasterizerState(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_RS_Cull_Off(nullptr),
	m_RS_Cull_CW(nullptr),
	m_RS_Cull_CCW(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
RasterizerState::~RasterizerState()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool RasterizerState::Create()
{
	D3D11_RASTERIZER_DESC rd = {};
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));

	//�J�����O���[�h�̐ݒ�(CULL_NONE)
	rd.FillMode				= D3D11_FILL_MODE::D3D11_FILL_SOLID;	//�h��Ԃ����[�h
	rd.CullMode				= D3D11_CULL_MODE::D3D11_CULL_NONE;		//�J�����O���[�h�̎w��
	rd.DepthClipEnable		= true;									//�N���b�s���O������L����
	rd.MultisampleEnable	= false;								//�T���v���𗘗p���Ȃ�
	m_GraphicsManager->GetDevice()->CreateRasterizerState(&rd, &m_RS_Cull_Off);

	//�J�����O���[�h�̐ݒ�(CULL_FRONT)
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;	//�J�����O���[�h�̎w��
	m_GraphicsManager->GetDevice()->CreateRasterizerState(&rd, &m_RS_Cull_CW);

	//�J�����O���[�h�̐ݒ�(CULL_BACK)
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;		//�J�����O���[�h�̎w��
	m_GraphicsManager->GetDevice()->CreateRasterizerState(&rd, &m_RS_Cull_CCW);

	//�����Ɏ��s
	if (!m_RS_Cull_Off)	return false;
	if (!m_RS_Cull_CW)	return false;
	if (!m_RS_Cull_CCW)	return false;

	std::cout << "Success to Create RasterizerState!" << std::endl;

	return true;
}

/*=============================================================================================
	���[�h�̐ݒ菈��
=============================================================================================*/
void RasterizerState::SetMode(CULL_MODE mode)
{
	ID3D11RasterizerState* setMode = nullptr;

	switch (mode)
	{
	case CULL_MODE::NONE	:	setMode = m_RS_Cull_Off;	break;
	case CULL_MODE::FRONT	:	setMode = m_RS_Cull_CW;		break;
	case CULL_MODE::BACK	:	setMode = m_RS_Cull_CCW;	break;
	default:
		break;
	}

	//�J�����O���[�h���w�肷��
	m_GraphicsManager->GetDeviceContext()->RSSetState(setMode);
}

/*=============================================================================================
	�������
=============================================================================================*/
void RasterizerState::Release()
{
	m_GraphicsManager = nullptr;
	if (m_RS_Cull_Off)	m_RS_Cull_Off->Release();
	if (m_RS_Cull_CW)	m_RS_Cull_CW->Release();
	if (m_RS_Cull_CCW)	m_RS_Cull_CCW->Release();
}
