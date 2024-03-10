/*===========================================================================
	Date : 2022/02/07(日)	GraphicsManager.cpp
		Author	: がむしるぉ
		Update	:
		Comment	: Alchemy!? こんな序盤で！
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
	コンストラクタ
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
	デストラクタ
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
	初期化処理
=============================================================================================*/
bool GraphicsManager::Init()
{
	if (!m_DeviceManager->Create())								return false;	//デバイスの生成処理
	if (!m_SwapChain->Create(m_DeviceManager->m_d3dFactory))	return false;	//スワップチェインの生成処理
	if (!m_RenderTargetView->Create(m_SwapChain->m_dxgiSC))		return false;	//レンダーターゲットの生成処理
	if (!m_DepthStencilView->Create(m_SwapChain->m_dxgiSC))		return false;	//スワップチェインの生成処理

	//レンダーターゲットとステンシルビューの登録処理
	m_DeviceManager->
		m_d3dDeviceContext->OMSetRenderTargets(1, &m_RenderTargetView->m_d3dRTV, m_DepthStencilView->m_d3dDSV);

	//ビューポートの設定処理
	this->SetViewport();

	if (!m_RasterizerState->Create())	return false;	//ラスタライザステートの生成処理
	if (!m_BlendState->Create())		return false;	//ブレンドステートの生成処理
	if (!m_DepthStencilState->Create())	return false;	//デプスステンシルステートの生成処理
	if (!m_SamplerState->Create())		return false;	//サンプラーステート
	if (!m_VertexShader->Create())		return false;	//頂点シェーダの生成処理
	if (!m_PixelShader->Create())		return false;	//ピクセルシェーダの生成処理
	this->CreateConstantBuffer();						//コンスタントバッファの生成処理

	m_RasterizerState->SetMode(CULL_MODE::BACK);
	m_BlendState->SetMode(BLEND_MODE::ALPHA);
	m_DepthStencilState->SetEnable(false);
	m_VertexShader->SetLayout();

	m_VertexShader->SetShader();
	m_PixelShader->SetShader();

	if (!MaterialBuffer::Init(this))			return false;	//マテリアルバッファの初期化処理

	std::cout << "Completed to Initialize Graphics!" << std::endl;
	return true;
}

/*=============================================================================================
	終了処理
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
	画面のクリア処理
=============================================================================================*/
void GraphicsManager::Clear()
{
	m_RenderTargetView->Clear(1.0f, 1.0f, 1.0f);
	m_DepthStencilView->Clear();
}

/*=============================================================================================
	バッファの切り替え処理
=============================================================================================*/
void GraphicsManager::Present()
{
	m_SwapChain->Present();
}

/*=============================================================================================
	2Dの座標変換
=============================================================================================*/
void GraphicsManager::Translate2D()
{
	Matrix4x4 mat;
	MathMatrix::OrthoOffCenterLH(mat, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1);
	MathMatrix::Transpose(mat);

	m_DeviceManager->m_d3dDeviceContext->UpdateSubresource(m_ConstantBuffer, 0, nullptr, &mat, 0, 0);
}

/*=============================================================================================
	深度有効の設定処理
=============================================================================================*/
void GraphicsManager::SetDepthEnable(bool use)
{
	m_DepthStencilState->SetEnable(use);
}

/*=============================================================================================
	ビューポートの設定処理
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
	定数バッファの生成処理
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
	表示モード切替
=============================================================================================*/
void GraphicsManager::SetScreenMode(bool full)
{
	m_SwapChain->ScreenChanger(full);
}

/*=============================================================================================
	デバイスの取得処理
=============================================================================================*/
ID3D11Device* GraphicsManager::GetDevice()
{
	return m_DeviceManager->m_d3dDevice;
}

/*=============================================================================================
	デバイスコンテキストの取得処理
=============================================================================================*/
ID3D11DeviceContext* GraphicsManager::GetDeviceContext()
{
	return m_DeviceManager->m_d3dDeviceContext;
}
