/*===========================================================================
	Date : 2022/02/08(��)	PixelShader.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"
#include "FileIO.h"

#include "PixelShader.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
PixelShader::PixelShader(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_PixelShader(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
PixelShader::~PixelShader()
{
}

/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
bool PixelShader::Create()
{
	std::string buffer;
	FileIO().Load(buffer, "PixelShader.cso");
	
	m_GraphicsManager->GetDevice()->CreatePixelShader(buffer.c_str(), buffer.size(), nullptr, &m_PixelShader);

	if (!m_PixelShader) return false;

	std::cout << "Success to Load Pixel Shader.hlsl!" << std::endl;
	return true;
}

/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
void PixelShader::SetShader()
{
	m_GraphicsManager->GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
}

/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
void PixelShader::Release()
{
	m_GraphicsManager = nullptr;
	if (m_PixelShader) m_PixelShader->Release();
}
