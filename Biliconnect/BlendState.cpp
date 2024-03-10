/*===========================================================================
	Date : 2022/02/08(��)	BlendState.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "BlendState.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
BlendState::BlendState(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_BlendNone(nullptr),
	m_BlendAlpha(nullptr),
	m_BlendAdd(nullptr),
	m_BlendSub(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
BlendState::~BlendState()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool BlendState::Create()
{
	D3D11_BLEND_DESC bd = {};
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//Alpha�ݒ�
	bd.AlphaToCoverageEnable					= false;													//�A���t�@�J�o���b�W�̎w��(�����悭�킩���ĂȂ�)
	bd.IndependentBlendEnable					= false;													//�Ɨ������u�����h��L���ɂ��邩�ǂ���
	bd.RenderTarget[0].BlendEnable				= true;														//�u�����h�ݒ��L���ɂ���
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;	
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND::D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha				= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendAlpha);

	//None�ݒ�
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendNone);

	//Add�ݒ�
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendAdd);

	//Sub�ݒ�
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_REV_SUBTRACT;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendSub);

	//�����Ɏ��s
	if (!m_BlendNone)	return false;
	if (!m_BlendAlpha)	return false;
	if (!m_BlendAdd)	return false;
	if (!m_BlendSub)	return false;

	std::cout << "Success to Create Blend State!" << std::endl;
	return true;
}

/*=============================================================================================
	�ݒ菈��
=============================================================================================*/
void BlendState::SetMode(BLEND_MODE mode)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* setMode = nullptr;

	switch (mode)
	{
	case BLEND_MODE::NONE		:	setMode = m_BlendNone;	break;
	case BLEND_MODE::ALPHA		:	setMode = m_BlendAlpha;	break;
	case BLEND_MODE::ADD		:	setMode = m_BlendAdd;	break;
	case BLEND_MODE::SUBTRACT	:	setMode = m_BlendSub;	break;
	default:
		break;
	}

	//�u�����h���[�h�̐ݒ菈��
	m_GraphicsManager->GetDeviceContext()->OMSetBlendState(setMode, blendFactor, 0xffffffff);
}

/*=============================================================================================
	�������
=============================================================================================*/
void BlendState::Release()
{
	m_GraphicsManager = nullptr;
	if (m_BlendNone)	m_BlendNone->Release();
	if (m_BlendAlpha)	m_BlendAlpha->Release();
	if (m_BlendAdd)		m_BlendAdd->Release();
	if (m_BlendSub)		m_BlendSub->Release();
}
