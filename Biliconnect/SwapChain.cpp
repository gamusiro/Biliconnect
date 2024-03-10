/*===========================================================================
	Date : 2022/02/07(��)	SwapChain.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "Application.h"
#include "GraphicsManager.h"

#include "SwapChain.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
SwapChain::SwapChain(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_dxgiSC(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
SwapChain::~SwapChain()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool SwapChain::Create(IDXGIFactory* fact)
{
	//�X���b�v�`�F�C���̐ݒ菈��
	DXGI_SWAP_CHAIN_DESC scd = {};
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount							= 1;										//�p�ӂ���o�b�t�@�̐�
	scd.BufferDesc.Width					= SCREEN_WIDTH;								//�s�N�Z���𑜓x(��)
	scd.BufferDesc.Height					= SCREEN_HEIGHT;							//�s�N�Z���𑜓x(�c)
	scd.BufferDesc.Format					= DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;	//RGBA�J���[�t�H�[�}�b�g
	scd.BufferDesc.RefreshRate.Numerator	= 60;										//���t���b�V�����[�g�̐ݒ�(���q)
	scd.BufferDesc.RefreshRate.Denominator	= 1;										//���t���b�V�����[�g�̐ݒ�(����)
	scd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;			//�o�b�t�@�̗��p���@�̎w��
	scd.OutputWindow						= Application::GetWindowHandle();			//����E�B���h�E�̓o�^
	scd.SampleDesc.Count					= 1;										//�T���v�����̎w��
	scd.SampleDesc.Quality					= 0;										//�T���v���N�I���e�B�̎w��(�Œ�)
	scd.Windowed							= TRUE;										//�E�B���h�E���[�h�̎w��(true �E�B���h�E���[�h, false �t���X�N���[��)
	
	//�X���b�v�`�F�C���̐�������
	fact->CreateSwapChain(m_GraphicsManager->GetDevice(), &scd, &m_dxgiSC);

	//�����Ɏ��s
	if (!m_dxgiSC)	return false;

	std::cout << "Success to Create SwapChain!" << std::endl;
	return true;
}

/*=============================================================================================
	�������
=============================================================================================*/
void SwapChain::Release()
{
	m_GraphicsManager = nullptr;
	if (m_dxgiSC)	m_dxgiSC->Release();
}

/*=============================================================================================
	�o�b�t�@�̐؂�ւ�����
=============================================================================================*/
void SwapChain::Present()
{
	m_dxgiSC->Present(1, 0);
}

/*=============================================================================================
	�\�����[�h�ؑ�
=============================================================================================*/
void SwapChain::ScreenChanger(bool full)
{
	m_dxgiSC->SetFullscreenState(full, nullptr);
}
