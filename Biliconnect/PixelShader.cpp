/*===========================================================================
	Date : 2022/02/08(火)	PixelShader.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"
#include "FileIO.h"

#include "PixelShader.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
PixelShader::PixelShader(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_PixelShader(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
PixelShader::~PixelShader()
{
}

/*=============================================================================================
	コンストラクタ
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
	コンストラクタ
=============================================================================================*/
void PixelShader::SetShader()
{
	m_GraphicsManager->GetDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);
}

/*=============================================================================================
	コンストラクタ
=============================================================================================*/
void PixelShader::Release()
{
	m_GraphicsManager = nullptr;
	if (m_PixelShader) m_PixelShader->Release();
}
