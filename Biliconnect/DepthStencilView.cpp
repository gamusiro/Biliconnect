/*===========================================================================
	Date : 2022/02/08(��)	DepthStencilView.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "DepthStencilView.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
DepthStencilView::DepthStencilView(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_d3dDSV(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
DepthStencilView::~DepthStencilView()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool DepthStencilView::Create(IDXGISwapChain* swapChain)
{
	//�X�e���V���p�e�N�X�`���̐�������
	ID3D11Texture2D* depthTexture	= nullptr;
	D3D11_TEXTURE2D_DESC td			= {};
	DXGI_SWAP_CHAIN_DESC scd		= {};
	swapChain->GetDesc(&scd);

	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));

	td.Width			= scd.BufferDesc.Width;							//�o�b�t�@�̃T�C�Y(��)
	td.Height			= scd.BufferDesc.Height;						//�o�b�t�@�̃T�C�Y(�c)
	td.MipLevels		= 1;											//�~�b�v�}�b�v���x���̎w��
	td.ArraySize		= 1;											//�e�N�X�`���z����̃e�N�X�`���̐�
	td.Format			= DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;	//�e�N�X�`���̌`��(�[�x 24�r�b�g, �X�e���V���p��8�r�b�g, Z�o�b�t�@�`��)
	td.SampleDesc		= scd.SampleDesc;								//�T���v���w��
	td.Usage			= D3D11_USAGE::D3D11_USAGE_DEFAULT;				//�o�b�t�@�̎g�p���@�Ɏw��
	td.BindFlags		= D3D11_BIND_DEPTH_STENCIL;						//�p�C�v���C���X�e�[�W�ւ̃o�C���h�ɑ΂���t���O
	td.CPUAccessFlags	= 0;											//�A�N�Z�X�s�v
	td.MiscFlags		= 0;								
	m_GraphicsManager->GetDevice()->CreateTexture2D(&td, nullptr, &depthTexture);

	//�����Ɏ��s
	if (!depthTexture)
		return false;

	//�X�e���V���^�[�Q�b�g�̐ݒ�
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	dsvd.Format			= td.Format;											//�e�N�X�`���̌`��(�[�x 24�r�b�g, �X�e���V���p��8�r�b�g, Z�o�b�t�@�`��)
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags			= 0;

	m_GraphicsManager->GetDevice()->CreateDepthStencilView(depthTexture, &dsvd, &m_d3dDSV);

	//�����Ɏ��s
	if (!m_d3dDSV)
		return false;

	std::cout << "Success to Create Depth Stencil View!" << std::endl;
	return true;
}

/*=============================================================================================
	�o�b�t�@�̃N���A����
=============================================================================================*/
void DepthStencilView::Clear()
{
	m_GraphicsManager->GetDeviceContext()->ClearDepthStencilView(m_d3dDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

/*=============================================================================================
	�������
=============================================================================================*/
void DepthStencilView::Release()
{
	m_GraphicsManager = nullptr;
	if (m_d3dDSV) m_d3dDSV->Release();
}
