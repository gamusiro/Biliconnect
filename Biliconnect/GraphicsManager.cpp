/*===========================================================================
	Date : 2022/02/07(��)	GraphicsManager.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	: Alchemy!? ����ȏ��ՂŁI
===========================================================================*/
#include "Application.h"
#include "DeviceManager.h"
#include "SwapChain.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"
#include "RasterizerState.h"
#include "BlendState.h"
#include "DepthStencilState.h"
#include "SamplerState.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "MaterialBuffer.h"
#include "Movie.h"

#include "GraphicsManager.h"
using namespace math;


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
GraphicsManager::GraphicsManager()
	:m_DeviceManager(nullptr),
	m_SwapChain(nullptr),
	m_RenderTargetView(nullptr),
	m_DepthStencilView(nullptr),
	m_RasterizerState(nullptr),
	m_BlendState(nullptr),
	m_DepthStencilState(nullptr),
	m_SamplerState(nullptr),
	m_VertexShader(nullptr),
	m_PixelShader(nullptr),
	m_ConstantBuffer(nullptr)
{
	m_DeviceManager		= new DeviceManager();
	m_SwapChain			= new SwapChain(this);
	m_RenderTargetView	= new RenderTargetView(this);
	m_DepthStencilView	= new DepthStencilView(this);
	m_RasterizerState	= new RasterizerState(this);
	m_BlendState		= new BlendState(this);
	m_DepthStencilState = new DepthStencilState(this);
	m_SamplerState		= new SamplerState(this);
	m_VertexShader		= new VertexShader(this);
	m_PixelShader		= new PixelShader(this);
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
GraphicsManager::~GraphicsManager()
{
	delete m_PixelShader;
	delete m_VertexShader;
	delete m_SamplerState;
	delete m_DepthStencilState;
	delete m_BlendState;
	delete m_RasterizerState;
	delete m_DepthStencilView;
	delete m_RenderTargetView;
	delete m_SwapChain;
	delete m_DeviceManager;
}

/*=============================================================================================
	����������
=============================================================================================*/
bool GraphicsManager::Init()
{
	if (!m_DeviceManager->Create())								return false;	//�f�o�C�X�̐�������
	if (!m_SwapChain->Create(m_DeviceManager->m_d3dFactory))	return false;	//�X���b�v�`�F�C���̐�������
	if (!m_RenderTargetView->Create(m_SwapChain->m_dxgiSC))		return false;	//�����_�[�^�[�Q�b�g�̐�������
	if (!m_DepthStencilView->Create(m_SwapChain->m_dxgiSC))		return false;	//�X���b�v�`�F�C���̐�������

	//�����_�[�^�[�Q�b�g�ƃX�e���V���r���[�̓o�^����
	m_DeviceManager->
		m_d3dDeviceContext->OMSetRenderTargets(1, &m_RenderTargetView->m_d3dRTV, m_DepthStencilView->m_d3dDSV);

	//�r���[�|�[�g�̐ݒ菈��
	this->SetViewport();

	if (!m_RasterizerState->Create())	return false;	//���X�^���C�U�X�e�[�g�̐�������
	if (!m_BlendState->Create())		return false;	//�u�����h�X�e�[�g�̐�������
	if (!m_DepthStencilState->Create())	return false;	//�f�v�X�X�e���V���X�e�[�g�̐�������
	if (!m_SamplerState->Create())		return false;	//�T���v���[�X�e�[�g
	if (!m_VertexShader->Create())		return false;	//���_�V�F�[�_�̐�������
	if (!m_PixelShader->Create())		return false;	//�s�N�Z���V�F�[�_�̐�������
	this->CreateConstantBuffer();						//�R���X�^���g�o�b�t�@�̐�������

	m_RasterizerState->SetMode(CULL_MODE::BACK);
	m_BlendState->SetMode(BLEND_MODE::ALPHA);
	m_DepthStencilState->SetEnable(false);
	m_VertexShader->SetLayout();

	m_VertexShader->SetShader();
	m_PixelShader->SetShader();

	if (!MaterialBuffer::Init(this))			return false;	//�}�e���A���o�b�t�@�̏���������

	std::cout << "Completed to Initialize Graphics!" << std::endl;
	return true;
}

/*=============================================================================================
	�I������
=============================================================================================*/
void GraphicsManager::Uninit()
{
	Movie::Uninit();
	MaterialBuffer::Uninit();
	if (m_ConstantBuffer) m_ConstantBuffer->Release();
	m_PixelShader->Release();
	m_VertexShader->Release();
	m_SamplerState->Release();
	m_DepthStencilState->Release();
	m_BlendState->Release();
	m_DepthStencilView->Release();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceManager->Release();
}

/*=============================================================================================
	��ʂ̃N���A����
=============================================================================================*/
void GraphicsManager::Clear()
{
	m_RenderTargetView->Clear(1.0f, 1.0f, 1.0f);
	m_DepthStencilView->Clear();
}

/*=============================================================================================
	�o�b�t�@�̐؂�ւ�����
=============================================================================================*/
void GraphicsManager::Present()
{
	m_SwapChain->Present();
}

/*=============================================================================================
	2D�̍��W�ϊ�
=============================================================================================*/
void GraphicsManager::Translate2D()
{
	Matrix4x4 mat;
	MathMatrix::OrthoOffCenterLH(mat, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
	MathMatrix::Transpose(mat);

	m_DeviceManager->m_d3dDeviceContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &mat, 0, 0);
}

/*=============================================================================================
	�[�x�L���̐ݒ菈��
=============================================================================================*/
void GraphicsManager::SetDepthEnable(bool use)
{
	m_DepthStencilState->SetEnable(use);
}

/*=============================================================================================
	�r���[�|�[�g�̐ݒ菈��
=============================================================================================*/
void GraphicsManager::SetViewport()
{
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width	= SCREEN_WIDTH;
	vp.Height	= SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DeviceManager->m_d3dDeviceContext->RSSetViewports(1, &vp);

	std::cout << "Success to Set Viewport!" << std::endl;
}

/*=============================================================================================
	�萔�o�b�t�@�̐�������
=============================================================================================*/
void GraphicsManager::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth			= sizeof(Matrix4x4);
	bd.Usage				= D3D11_USAGE::D3D11_USAGE_DEFAULT;
	bd.BindFlags			= D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags		= 0;
	bd.MiscFlags			= 0;
	bd.StructureByteStride	= sizeof(float);

	m_DeviceManager->m_d3dDevice->CreateBuffer(&bd, nullptr, &m_ConstantBuffer);
	m_DeviceManager->m_d3dDeviceContext->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
}

/*=============================================================================================
	�\�����[�h�ؑ�
=============================================================================================*/
void GraphicsManager::SetScreenMode(bool full)
{
	m_SwapChain->ScreenChanger(full);
}

/*=============================================================================================
	�f�o�C�X�̎擾����
=============================================================================================*/
ID3D11Device* GraphicsManager::GetDevice()
{
	return m_DeviceManager->m_d3dDevice;
}

/*=============================================================================================
	�f�o�C�X�R���e�L�X�g�̎擾����
=============================================================================================*/
ID3D11DeviceContext* GraphicsManager::GetDeviceContext()
{
	return m_DeviceManager->m_d3dDeviceContext;
}
