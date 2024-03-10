/*===========================================================================
	Date : 2022/02/08(月)	BlendState.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "BlendState.h"


/*=============================================================================================
	コンストラクタ
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
	デストラクタ
=============================================================================================*/
BlendState::~BlendState()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool BlendState::Create()
{
	D3D11_BLEND_DESC bd = {};
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));

	//Alpha設定
	bd.AlphaToCoverageEnable					= false;													//アルファカバレッジの指定(正直よくわかってない)
	bd.IndependentBlendEnable					= false;													//独立したブレンドを有効にするかどうか
	bd.RenderTarget[0].BlendEnable				= true;														//ブレンド設定を有効にする
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;	
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND::D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha				= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE::D3D11_COLOR_WRITE_ENABLE_ALL;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendAlpha);

	//None設定
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendNone);

	//Add設定
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendAdd);

	//Sub設定
	bd.RenderTarget[0].SrcBlend					= D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend				= D3D11_BLEND::D3D11_BLEND_ONE;
	bd.RenderTarget[0].BlendOp					= D3D11_BLEND_OP::D3D11_BLEND_OP_REV_SUBTRACT;
	m_GraphicsManager->GetDevice()->CreateBlendState(&bd, &m_BlendSub);

	//生成に失敗
	if (!m_BlendNone)	return false;
	if (!m_BlendAlpha)	return false;
	if (!m_BlendAdd)	return false;
	if (!m_BlendSub)	return false;

	std::cout << "Success to Create Blend State!" << std::endl;
	return true;
}

/*=============================================================================================
	設定処理
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

	//ブレンドモードの設定処理
	m_GraphicsManager->GetDeviceContext()->OMSetBlendState(setMode, blendFactor, 0xffffffff);
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void BlendState::Release()
{
	m_GraphicsManager = nullptr;
	if (m_BlendNone)	m_BlendNone->Release();
	if (m_BlendAlpha)	m_BlendAlpha->Release();
	if (m_BlendAdd)		m_BlendAdd->Release();
	if (m_BlendSub)		m_BlendSub->Release();
}
