/*===========================================================================
	Date : 2022/02/08(��)	SamplerState.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "SamplerState.h"
using namespace math;


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
SamplerState::SamplerState(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_BorderColor(Float4())
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
SamplerState::~SamplerState()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool SamplerState::Create()
{
	//�T���v���[�X�e�[�g�̐ݒ�
	D3D11_SAMPLER_DESC sd = {};
	ZeroMemory(&sd, sizeof(D3D11_SAMPLER_DESC));

	sd.Filter	= D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	//BORDER�F�̎w��
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

	//�����Ɏ��s
	if (!samplerState)	return false;

    std::cout << "Success to Create Sampler State!" << std::endl;
	return true;
}

/*=============================================================================================
	���[�h�ݒ菈��
=============================================================================================*/
void SamplerState::SetMode(ADDRESS_MODE am, FILTER_MODE fm)
{
    // �T���v���[�X�e�[�g�ݒ�
    D3D11_SAMPLER_DESC sd;
    ZeroMemory(&sd, sizeof(sd));

    switch (fm)
    {
    case FILTER_MODE::POINT      :  sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;     break;
    case FILTER_MODE::LINEAR     :  sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;    break;
    case FILTER_MODE::ANISOTROPIC:  sd.Filter = D3D11_FILTER_ANISOTROPIC;           break;
    }

    //�e�N�X�`���̃A�h���b�V���O���[�h�̐ݒ�        
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

    //�{�[�_�[�J���[�̎w��
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
	�{�[�_�[�J���[�ݒ菈��
=============================================================================================*/
void SamplerState::SetColor(Float4 borderColor)
{
    m_BorderColor = borderColor;
}

/*=============================================================================================
	�������
=============================================================================================*/
void SamplerState::Release()
{
    m_GraphicsManager = nullptr;
}
