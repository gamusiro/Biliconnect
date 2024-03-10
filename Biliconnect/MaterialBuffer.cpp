/*===========================================================================
	Date : 2022/02/11(��)	MaterialBuffer.h
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"

#include "MaterialBuffer.h"

GraphicsManager* MaterialBuffer::m_GraphicsManager;
ID3D11Buffer* MaterialBuffer::m_MaterialBuffer;

/*=============================================================================================
	����������
=============================================================================================*/
bool MaterialBuffer::Init(GraphicsManager* gm)
{
	m_GraphicsManager = gm;

	D3D11_BUFFER_DESC bd = {};
	bd.ByteWidth			= sizeof(Material);
	bd.Usage				= D3D11_USAGE::D3D11_USAGE_DEFAULT;
	bd.BindFlags			= D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags		= 0;
	bd.MiscFlags			= 0;
	bd.StructureByteStride	= sizeof(float);

	m_GraphicsManager->GetDevice()->CreateBuffer(&bd, nullptr, &m_MaterialBuffer);
	m_GraphicsManager->GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_MaterialBuffer);

	//�����Ɏ��s
	if (!m_MaterialBuffer)
		return false;

	return true;
}

/*=============================================================================================
	�ݒ菈��
=============================================================================================*/
void MaterialBuffer::SetData(const Material& data)
{
	Material setData;
	setData.noTexSampling = data.noTexSampling;

	m_GraphicsManager->GetDeviceContext()->UpdateSubresource(m_MaterialBuffer, 0, nullptr, &setData, 0, 0);
}

/*=============================================================================================
	�I������
=============================================================================================*/
void MaterialBuffer::Uninit()
{
	m_GraphicsManager = nullptr;
	if (m_MaterialBuffer)	m_MaterialBuffer->Release();
}
