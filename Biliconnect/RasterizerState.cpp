/*===========================================================================
	Date : 2022/02/08(月)	RasterizerState.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "RasterizerState.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
RasterizerState::RasterizerState(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_RS_Cull_Off(nullptr),
	m_RS_Cull_CW(nullptr),
	m_RS_Cull_CCW(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
RasterizerState::~RasterizerState()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool RasterizerState::Create()
{
	D3D11_RASTERIZER_DESC rd = {};
	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));

	//カリングモードの設定(CULL_NONE)
	rd.FillMode				= D3D11_FILL_MODE::D3D11_FILL_SOLID;	//塗りつぶしモード
	rd.CullMode				= D3D11_CULL_MODE::D3D11_CULL_NONE;		//カリングモードの指定
	rd.DepthClipEnable		= true;									//クリッピング処理を有効化
	rd.MultisampleEnable	= false;								//サンプルを利用しない
	m_GraphicsManager->GetDevice()->CreateRasterizerState(&rd, &m_RS_Cull_Off);

	//カリングモードの設定(CULL_FRONT)
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;	//カリングモードの指定
	m_GraphicsManager->GetDevice()->CreateRasterizerState(&rd, &m_RS_Cull_CW);

	//カリングモードの設定(CULL_BACK)
	rd.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;		//カリングモードの指定
	m_GraphicsManager->GetDevice()->CreateRasterizerState(&rd, &m_RS_Cull_CCW);

	//生成に失敗
	if (!m_RS_Cull_Off)	return false;
	if (!m_RS_Cull_CW)	return false;
	if (!m_RS_Cull_CCW)	return false;

	std::cout << "Success to Create RasterizerState!" << std::endl;

	return true;
}

/*=============================================================================================
	モードの設定処理
=============================================================================================*/
void RasterizerState::SetMode(CULL_MODE mode)
{
	ID3D11RasterizerState* setMode = nullptr;

	switch (mode)
	{
	case CULL_MODE::NONE	:	setMode = m_RS_Cull_Off;	break;
	case CULL_MODE::FRONT	:	setMode = m_RS_Cull_CW;		break;
	case CULL_MODE::BACK	:	setMode = m_RS_Cull_CCW;	break;
	default:
		break;
	}

	//カリングモードを指定する
	m_GraphicsManager->GetDeviceContext()->RSSetState(setMode);
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void RasterizerState::Release()
{
	m_GraphicsManager = nullptr;
	if (m_RS_Cull_Off)	m_RS_Cull_Off->Release();
	if (m_RS_Cull_CW)	m_RS_Cull_CW->Release();
	if (m_RS_Cull_CCW)	m_RS_Cull_CCW->Release();
}
