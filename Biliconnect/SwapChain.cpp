/*===========================================================================
	Date : 2022/02/07(日)	SwapChain.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "Application.h"
#include "GraphicsManager.h"

#include "SwapChain.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
SwapChain::SwapChain(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_dxgiSC(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
SwapChain::~SwapChain()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool SwapChain::Create(IDXGIFactory* fact)
{
	//スワップチェインの設定処理
	DXGI_SWAP_CHAIN_DESC scd = {};
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	scd.BufferCount							= 1;										//用意するバッファの数
	scd.BufferDesc.Width					= SCREEN_WIDTH;								//ピクセル解像度(幅)
	scd.BufferDesc.Height					= SCREEN_HEIGHT;							//ピクセル解像度(縦)
	scd.BufferDesc.Format					= DXGI_FORMAT::DXGI_FORMAT_B8G8R8A8_UNORM;	//RGBAカラーフォーマット
	scd.BufferDesc.RefreshRate.Numerator	= 60;										//リフレッシュレートの設定(分子)
	scd.BufferDesc.RefreshRate.Denominator	= 1;										//リフレッシュレートの設定(分母)
	scd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;			//バッファの利用方法の指定
	scd.OutputWindow						= Application::GetWindowHandle();			//制御ウィンドウの登録
	scd.SampleDesc.Count					= 1;										//サンプル数の指定
	scd.SampleDesc.Quality					= 0;										//サンプルクオリティの指定(最低)
	scd.Windowed							= TRUE;										//ウィンドウモードの指定(true ウィンドウモード, false フルスクリーン)
	
	//スワップチェインの生成処理
	fact->CreateSwapChain(m_GraphicsManager->GetDevice(), &scd, &m_dxgiSC);

	//生成に失敗
	if (!m_dxgiSC)	return false;

	std::cout << "Success to Create SwapChain!" << std::endl;
	return true;
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void SwapChain::Release()
{
	m_GraphicsManager = nullptr;
	if (m_dxgiSC)	m_dxgiSC->Release();
}

/*=============================================================================================
	バッファの切り替え処理
=============================================================================================*/
void SwapChain::Present()
{
	m_dxgiSC->Present(1, 0);
}

/*=============================================================================================
	表示モード切替
=============================================================================================*/
void SwapChain::ScreenChanger(bool full)
{
	m_dxgiSC->SetFullscreenState(full, nullptr);
}
