/*===========================================================================
	Date : 2022/02/08(月)	DepthStencilView.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "DepthStencilView.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
DepthStencilView::DepthStencilView(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_d3dDSV(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
DepthStencilView::~DepthStencilView()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool DepthStencilView::Create(IDXGISwapChain* swapChain)
{
	//ステンシル用テクスチャの生成処理
	ID3D11Texture2D* depthTexture	= nullptr;
	D3D11_TEXTURE2D_DESC td			= {};
	DXGI_SWAP_CHAIN_DESC scd		= {};
	swapChain->GetDesc(&scd);

	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));

	td.Width			= scd.BufferDesc.Width;							//バッファのサイズ(幅)
	td.Height			= scd.BufferDesc.Height;						//バッファのサイズ(縦)
	td.MipLevels		= 1;											//ミップマップレベルの指定
	td.ArraySize		= 1;											//テクスチャ配列内のテクスチャの数
	td.Format			= DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;	//テクスチャの形式(深度 24ビット, ステンシル用に8ビット, Zバッファ形式)
	td.SampleDesc		= scd.SampleDesc;								//サンプル指定
	td.Usage			= D3D11_USAGE::D3D11_USAGE_DEFAULT;				//バッファの使用方法に指定
	td.BindFlags		= D3D11_BIND_DEPTH_STENCIL;						//パイプラインステージへのバインドに対するフラグ
	td.CPUAccessFlags	= 0;											//アクセス不要
	td.MiscFlags		= 0;								
	m_GraphicsManager->GetDevice()->CreateTexture2D(&td, nullptr, &depthTexture);

	//生成に失敗
	if (!depthTexture)
		return false;

	//ステンシルターゲットの設定
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	dsvd.Format			= td.Format;											//テクスチャの形式(深度 24ビット, ステンシル用に8ビット, Zバッファ形式)
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags			= 0;

	m_GraphicsManager->GetDevice()->CreateDepthStencilView(depthTexture, &dsvd, &m_d3dDSV);

	//生成に失敗
	if (!m_d3dDSV)
		return false;

	std::cout << "Success to Create Depth Stencil View!" << std::endl;
	return true;
}

/*=============================================================================================
	バッファのクリア処理
=============================================================================================*/
void DepthStencilView::Clear()
{
	m_GraphicsManager->GetDeviceContext()->ClearDepthStencilView(m_d3dDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void DepthStencilView::Release()
{
	m_GraphicsManager = nullptr;
	if (m_d3dDSV) m_d3dDSV->Release();
}
