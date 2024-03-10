/*===========================================================================
	Date : 2022/02/08(��)	Sprite.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"
#include "Texture.h"
#include "TextureManager.h"
#include "MaterialBuffer.h"

#include "Sprite.h"
using namespace math;

GraphicsManager*	Sprite::m_GraphicsManager = nullptr;
ID3D11Buffer*		Sprite::m_VertexBuffer = nullptr;

/*===================================================================
	����������
===================================================================*/
bool Sprite::Init(GraphicsManager* gm)
{
	m_GraphicsManager = gm;

	//���_�o�b�t�@�̐���
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage			= D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	bd.ByteWidth		= sizeof(Vertex) * 4;
	bd.BindFlags		= D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags	= D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	m_GraphicsManager->GetDevice()->CreateBuffer(&bd, nullptr, &m_VertexBuffer);

	if (!m_VertexBuffer)
		return false;

	std::cout << "Success to Initialize Sprite!" << std::endl;
	return true;
}

/*===================================================================
	�e�N�X�`����UV�l���W�̎w��
===================================================================*/
void Sprite::Uninit()
{
	m_GraphicsManager = nullptr;
	if (m_VertexBuffer) m_VertexBuffer->Release();
}

/*===================================================================
	������W�𒆐S�ɂƂ��ĕ`��
===================================================================*/
void Sprite::DrawLeftTop(Float2 pos, Float2 size, const Texture* image, Float4 color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_GraphicsManager->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex* vertex = (Vertex*)msr.pData;

	// ���_���̐ݒ�
	vertex[0].Position = Float3(pos.x, pos.y, 0.0f);
	vertex[1].Position = Float3(pos.x + size.x, pos.y, 0.0f);
	vertex[2].Position = Float3(pos.x, pos.y + size.y, 0.0f);
	vertex[3].Position = Float3(pos.x + size.x, pos.y + size.y, 0.0f);
	// �J���[���̐ݒ�
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	if (image == nullptr)
	{
		vertex[0].TexCoord = Float2(0.0f, 0.0f);
		vertex[1].TexCoord = Float2(1.0f, 0.0f);
		vertex[2].TexCoord = Float2(0.0f, 1.0f);
		vertex[3].TexCoord = Float2(1.0f, 1.0f);
	}
	else
	{
		switch (image->m_Direction)
		{
		case DIRECTION_TEXTURE::LEFT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,  image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		case DIRECTION_TEXTURE::RIGHT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,  image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		default:
			break;
		}

	}

	m_GraphicsManager->GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	Material data = {};

	if (image)
	{//�e�N�X�`���ݒ�
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));
		data.noTexSampling = 1;
	}
	else
	{//�|���S���`��
		data.noTexSampling = 0;
	}
	//�f�[�^��ݒ肷��
	MaterialBuffer::SetData(data);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}

/*===================================================================
	�e�N�X�`����UV�l���W�̎w��
===================================================================*/
void Sprite::DrawCenter(Float2 pos, Float2 size, const Texture* image, Float4 color, float degree)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_GraphicsManager->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex* vertex = (Vertex*)msr.pData;

	Float2 halfSize = size * 0.5f;

	float radian = math::MathCommons::Radian(degree);
	float baseAngle = atan2f(halfSize.y, halfSize.x);
	float radius	= math::MathFloat::Length(halfSize);

	// ���_���̐ݒ�
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius, 0.0f);

	// �J���[���̐ݒ�
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	if (image == nullptr)
	{
		vertex[0].TexCoord = Float2(0.0f, 0.0f);
		vertex[1].TexCoord = Float2(1.0f, 0.0f);
		vertex[2].TexCoord = Float2(0.0f, 1.0f);
		vertex[3].TexCoord = Float2(1.0f, 1.0f);
	}
	else
	{
		switch (image->m_Direction)
		{
		case DIRECTION_TEXTURE::LEFT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
										image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		case DIRECTION_TEXTURE::RIGHT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
										image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
										image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		default:
			break;
		}
	}

	m_GraphicsManager->GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	Material data = {};

	if (image)
	{//�e�N�X�`���ݒ�
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));	//���̃e�N�X�`��
		data.noTexSampling = 1;
	}
	else
	{//�|���S���`��
		data.noTexSampling = 0;
	}
	//�f�[�^��ݒ肷��
	MaterialBuffer::SetData(data);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}

/*===================================================================
	�e�N�X�`����UV�l���W�̎w��
===================================================================*/
void Sprite::DrawBottom(Float2 pos, Float2 size, const Texture* image, Float4 color, float degree)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_GraphicsManager->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex* vertex = (Vertex*)msr.pData;

	Float2 halfSize = size * 0.5f;

	float radian = math::MathCommons::Radian(degree);
	float baseAngle = atan2f(halfSize.y, halfSize.x);
	float radius = math::MathFloat::Length(halfSize);

	// ���_���̐ݒ�
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius * 0.5f - size.y * 1.0f, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius * 0.5f - size.y * 1.0f, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius * 0.5f - size.y * 0.5f, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius * 0.5f - size.y * 0.5f, 0.0f);

	// �J���[���̐ݒ�
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	if (image == nullptr)
	{
		vertex[0].TexCoord = Float2(0.0f, 0.0f);
		vertex[1].TexCoord = Float2(1.0f, 0.0f);
		vertex[2].TexCoord = Float2(0.0f, 1.0f);
		vertex[3].TexCoord = Float2(1.0f, 1.0f);
	}
	else
	{
		switch (image->m_Direction)
		{
		case DIRECTION_TEXTURE::LEFT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		case DIRECTION_TEXTURE::RIGHT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		default:
			break;
		}
	}

	m_GraphicsManager->GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	Material data = {};

	if (image)
	{//�e�N�X�`���ݒ�
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));	//���̃e�N�X�`��
		data.noTexSampling = 1;
	}
	else
	{//�|���S���`��
		data.noTexSampling = 0;
	}
	//�f�[�^��ݒ肷��
	MaterialBuffer::SetData(data);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}


/*===================================================================
	�e�N�X�`����UV�l���W�̎w��
===================================================================*/
void Sprite::DrawCenterK(Float2 pos, Float2 size, const Texture* image, Float4 color, float degree)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_GraphicsManager->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex* vertex = (Vertex*)msr.pData;

	Float2 halfSize = size * 0.5f;

	float radian = degree;
	float baseAngle = atan2f(halfSize.y, halfSize.x);
	float radius = math::MathFloat::Length(halfSize);

	// ���_���̐ݒ�
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius, 0.0f);

	// �J���[���̐ݒ�
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	if (image == nullptr)
	{
		vertex[0].TexCoord = Float2(0.0f, 0.0f);
		vertex[1].TexCoord = Float2(1.0f, 0.0f);
		vertex[2].TexCoord = Float2(0.0f, 1.0f);
		vertex[3].TexCoord = Float2(1.0f, 1.0f);
	}
	else
	{
		switch (image->m_Direction)
		{
		case DIRECTION_TEXTURE::LEFT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		case DIRECTION_TEXTURE::RIGHT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		default:
			break;
		}
	}

	m_GraphicsManager->GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	Material data = {};

	if (image)
	{//�e�N�X�`���ݒ�
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));	//���̃e�N�X�`��
		data.noTexSampling = 1;
	}
	else
	{//�|���S���`��
		data.noTexSampling = 0;
	}
	//�f�[�^��ݒ肷��
	MaterialBuffer::SetData(data);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}

/*===================================================================
	�e�N�X�`����UV�l���W�̎w��
===================================================================*/
void Sprite::DrawMask(Float2 pos, Float2 size, const Texture* image, Float4 color, float degree)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_GraphicsManager->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex* vertex = (Vertex*)msr.pData;

	Float2 halfSize = size * 0.5f;

	float radian = math::MathCommons::Radian(degree);
	float baseAngle = atan2f(halfSize.y, halfSize.x);
	float radius = math::MathFloat::Length(halfSize);

	// ���_���̐ݒ�
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius, 0.0f);

	// �J���[���̐ݒ�
	vertex[0].Color = color;
	vertex[1].Color = color;
	vertex[2].Color = color;
	vertex[3].Color = color;

	if (image->m_Info.TextureID <= -1)
	{
		vertex[0].TexCoord = Float2(0.0f, 0.0f);
		vertex[1].TexCoord = Float2(1.0f, 0.0f);
		vertex[2].TexCoord = Float2(0.0f, 1.0f);
		vertex[3].TexCoord = Float2(1.0f, 1.0f);
	}
	else
	{
		switch (image->m_Direction)
		{
		case DIRECTION_TEXTURE::LEFT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x + image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		case DIRECTION_TEXTURE::RIGHT:
			vertex[0].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y);
			vertex[1].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y);
			vertex[2].TexCoord = Float2(image->m_Info.StartUVPosition.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			vertex[3].TexCoord = Float2(image->m_Info.StartUVPosition.x - image->m_Info.SizeUV.x,
				image->m_Info.StartUVPosition.y + image->m_Info.SizeUV.y);
			break;
		default:
			break;
		}
	}

	m_GraphicsManager->GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	Material data = {};

	if (image->m_Info.TextureID >= 0)
	{//�e�N�X�`���ݒ�
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetMask());
		data.noTexSampling = 1;
	}
	else
	{//�|���S���`��
		data.noTexSampling = 0;
	}
	//�f�[�^��ݒ肷��
	MaterialBuffer::SetData(data);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}