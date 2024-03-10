/*===========================================================================
	Date : 2022/02/08(月)	DepthStencilState.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "DepthStencilState.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
DepthStencilState::DepthStencilState(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_Enable(nullptr),
	m_Disable(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
DepthStencilState::~DepthStencilState()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool DepthStencilState::Create()
{
	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));

	dsd.DepthEnable		= true;
	dsd.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc		= D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	dsd.StencilEnable	= false;
	m_GraphicsManager->GetDevice()->CreateDepthStencilState(&dsd, &m_Enable);	//深度有効

	dsd.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
	dsd.DepthFunc		= D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
	m_GraphicsManager->GetDevice()->CreateDepthStencilState(&dsd, &m_Disable);	//深度無効

	//生成に失敗
	if (!m_Enable)	return false;
	if (!m_Disable)	return false;

	std::cout << "Success to Create Depth Stencil State!" << std::endl;
	return true;
}

/*=============================================================================================
	設定処理
=============================================================================================*/
void DepthStencilState::SetEnable(bool use)
{
	if (use)
		m_GraphicsManager->GetDeviceContext()->OMSetDepthStencilState(m_Enable, 0);
	else
		m_GraphicsManager->GetDeviceContext()->OMSetDepthStencilState(m_Disable, 0);
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void DepthStencilState::Release()
{
	m_GraphicsManager = nullptr;
	if (m_Enable)	m_Enable->Release();
	if (m_Disable)	m_Disable->Release();
}
