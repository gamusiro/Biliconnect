/*===========================================================================
	Date : 2022/02/08(��)	RenderTargetView.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "RenderTargetView.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
RenderTargetView::RenderTargetView(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_d3dRTV(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
RenderTargetView::~RenderTargetView()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool RenderTargetView::Create(IDXGISwapChain* swapChain)
{
	ID3D11Texture2D* buffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)(&buffer));				//�X���b�v�`�F�C���̃o�b�t�@���擾
	m_GraphicsManager->GetDevice()->CreateRenderTargetView(buffer, nullptr, &m_d3dRTV);	//�����_�[�^�[�Q�b�g�𐶐�����
	buffer->Release();

	//�����Ɏ��s
	if (!m_d3dRTV)
		return false;

	std::cout << "Success to Create Render Target View!" << std::endl;
	return true;
}

/*=============================================================================================
	�`��̃N���A����
=============================================================================================*/
void RenderTargetView::Clear(float r, float g, float b)
{
	float color[4] = { r, g, b, 1.0f };
	m_GraphicsManager->GetDeviceContext()->ClearRenderTargetView(m_d3dRTV, color);
}

/*=============================================================================================
	�������
=============================================================================================*/
void RenderTargetView::Release()
{
	m_GraphicsManager = nullptr;
	if (m_d3dRTV) m_d3dRTV->Release();
}
