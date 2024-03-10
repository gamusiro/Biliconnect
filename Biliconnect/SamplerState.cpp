/*===========================================================================
	Date : 2022/02/08(火)	SamplerState.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "SamplerState.h"
using namespace math;


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
SamplerState::SamplerState(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_BorderColor(Float4())
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
SamplerState::~SamplerState()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool SamplerState::Create()
{
	//サンプラーステートの設定
	D3D11_SAMPLER_DESC sd = {};
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));

	sd.Filter	= D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	//BORDER色の指定
	m_BorderColor.w = 1.0f;
	sd.BorderColor[0] = m_BorderColor.x;
	sd.BorderColor[1] = m_BorderColor.y;
	sd.BorderColor[2] = m_BorderColor.z;
	sd.BorderColor[3] = m_BorderColor.w;

	sd.MipLODBias		= 0;
	sd.MaxAnisotropy	= 16;
	sd.ComparisonFunc	= D3D11_COMPARISON_FUNC::D3D11_COMPARISON_ALWAYS;
	sd.MinLOD			= 0;
	sd.MaxLOD			= D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = nullptr;
	m_GraphicsManager->GetDevice()->CreateSamplerState(&sd, &samplerState);
	m_GraphicsManager->GetDeviceContext()->PSSetSamplers(0, 1, &samplerState);
	samplerState->Release();

	//生成に失敗
	if (!samplerState)	return false;

    std::cout << "Success to Create Sampler State!" << std::endl;
	return true;
}

/*=============================================================================================
	モード設定処理
=============================================================================================*/
void SamplerState::SetMode(ADDRESS_MODE am, FILTER_MODE fm)
{
    // サンプラーステート設定
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));

    switch (fm)
    {
    case FILTER_MODE::POINT      :  sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;     break;
    case FILTER_MODE::LINEAR     :  sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;    break;
    case FILTER_MODE::ANISOTROPIC:  sd.Filter = D3D11_FILTER_ANISOTROPIC;           break;
    }

    //テクスチャのアドレッシングモードの設定        
    switch (am)
    {
    case ADDRESS_MODE::WRAP:
        sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        break;
    case ADDRESS_MODE::MIRROR:
        sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
        break;
    case ADDRESS_MODE::CLAMP:
        sd.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        break;
    case ADDRESS_MODE::BORDER:
        sd.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
        sd.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
        sd.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
        break;
    }

    //ボーダーカラーの指定
    sd.BorderColor[0] = m_BorderColor.x;
    sd.BorderColor[1] = m_BorderColor.y;
    sd.BorderColor[2] = m_BorderColor.z;
    sd.BorderColor[3] = m_BorderColor.w;

    ID3D11SamplerState* samplerState = nullptr;
    m_GraphicsManager->GetDevice()->CreateSamplerState(&sd, &samplerState);
    m_GraphicsManager->GetDeviceContext()->PSSetSamplers(0, 1, &samplerState);
    samplerState->Release();
}

/*=============================================================================================
	ボーダーカラー設定処理
=============================================================================================*/
void SamplerState::SetColor(Float4 borderColor)
{
    m_BorderColor = borderColor;
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void SamplerState::Release()
{
    m_GraphicsManager = nullptr;
}
