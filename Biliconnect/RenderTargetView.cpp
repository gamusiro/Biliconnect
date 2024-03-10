/*===========================================================================
	Date : 2022/02/08(月)	RenderTargetView.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "RenderTargetView.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
RenderTargetView::RenderTargetView(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_d3dRTV(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
RenderTargetView::~RenderTargetView()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool RenderTargetView::Create(IDXGISwapChain* swapChain)
{
	ID3D11Texture2D* buffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)(&buffer));				//スワップチェインのバッファを取得
	m_GraphicsManager->GetDevice()->CreateRenderTargetView(buffer, nullptr, &m_d3dRTV);	//レンダーターゲットを生成する
	buffer->Release();

	//生成に失敗
	if (!m_d3dRTV)
		return false;

	std::cout << "Success to Create Render Target View!" << std::endl;
	return true;
}

/*=============================================================================================
	描画のクリア処理
=============================================================================================*/
void RenderTargetView::Clear(float r, float g, float b)
{
	float color[4] = { r, g, b, 1.0f };
	m_GraphicsManager->GetDeviceContext()->ClearRenderTargetView(m_d3dRTV, color);
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void RenderTargetView::Release()
{
	m_GraphicsManager = nullptr;
	if (m_d3dRTV) m_d3dRTV->Release();
}
