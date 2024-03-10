/*===========================================================================
	Date : 2022/02/08(火)	Sprite.cpp
		Author	: がむしるぉ
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
	初期化処理
===================================================================*/
bool Sprite::Init(GraphicsManager* gm)
{
	m_GraphicsManager = gm;

	//頂点バッファの生成
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
	テクスチャのUV値座標の指定
===================================================================*/
void Sprite::Uninit()
{
	m_GraphicsManager = nullptr;
	if (m_VertexBuffer) m_VertexBuffer->Release();
}

/*===================================================================
	左上座標を中心にとして描画
===================================================================*/
void Sprite::DrawLeftTop(Float2 pos, Float2 size, const Texture* image, Float4 color)
{
	D3D11_MAPPED_SUBRESOURCE msr;
	m_GraphicsManager->GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	Vertex* vertex = (Vertex*)msr.pData;

	// 頂点情報の設定
	vertex[0].Position = Float3(pos.x, pos.y, 0.0f);
	vertex[1].Position = Float3(pos.x + size.x, pos.y, 0.0f);
	vertex[2].Position = Float3(pos.x, pos.y + size.y, 0.0f);
	vertex[3].Position = Float3(pos.x + size.x, pos.y + size.y, 0.0f);
	// カラー情報の設定
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
	{//テクスチャ設定
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));
		data.noTexSampling = 1;
	}
	else
	{//ポリゴン描画
		data.noTexSampling = 0;
	}
	//データを設定する
	MaterialBuffer::SetData(data);

	// 頂点バッファ設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}

/*===================================================================
	テクスチャのUV値座標の指定
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

	// 頂点情報の設定
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius, 0.0f);

	// カラー情報の設定
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
	{//テクスチャ設定
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));	//白のテクスチャ
		data.noTexSampling = 1;
	}
	else
	{//ポリゴン描画
		data.noTexSampling = 0;
	}
	//データを設定する
	MaterialBuffer::SetData(data);

	// 頂点バッファ設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}

/*===================================================================
	テクスチャのUV値座標の指定
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

	// 頂点情報の設定
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius * 0.5f - size.y * 1.0f, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius * 0.5f - size.y * 1.0f, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius * 0.5f - size.y * 0.5f, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius * 0.5f - size.y * 0.5f, 0.0f);

	// カラー情報の設定
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
	{//テクスチャ設定
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));	//白のテクスチャ
		data.noTexSampling = 1;
	}
	else
	{//ポリゴン描画
		data.noTexSampling = 0;
	}
	//データを設定する
	MaterialBuffer::SetData(data);

	// 頂点バッファ設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}


/*===================================================================
	テクスチャのUV値座標の指定
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

	// 頂点情報の設定
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius, 0.0f);

	// カラー情報の設定
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
	{//テクスチャ設定
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetTexture(image->m_Info.TextureID));	//白のテクスチャ
		data.noTexSampling = 1;
	}
	else
	{//ポリゴン描画
		data.noTexSampling = 0;
	}
	//データを設定する
	MaterialBuffer::SetData(data);

	// 頂点バッファ設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}

/*===================================================================
	テクスチャのUV値座標の指定
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

	// 頂点情報の設定
	vertex[0].Position = Float3(pos.x - cosf(baseAngle + radian) * radius, pos.y - sinf(baseAngle + radian) * radius, 0.0f);
	vertex[1].Position = Float3(pos.x + cosf(baseAngle - radian) * radius, pos.y - sinf(baseAngle - radian) * radius, 0.0f);
	vertex[2].Position = Float3(pos.x - cosf(baseAngle - radian) * radius, pos.y + sinf(baseAngle - radian) * radius, 0.0f);
	vertex[3].Position = Float3(pos.x + cosf(baseAngle + radian) * radius, pos.y + sinf(baseAngle + radian) * radius, 0.0f);

	// カラー情報の設定
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
	{//テクスチャ設定
		m_GraphicsManager->GetDeviceContext()->PSSetShaderResources(0, 1, TextureManager::GetMask());
		data.noTexSampling = 1;
	}
	else
	{//ポリゴン描画
		data.noTexSampling = 0;
	}
	//データを設定する
	MaterialBuffer::SetData(data);

	// 頂点バッファ設定
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_GraphicsManager->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// プリミティブトポロジ設定
	m_GraphicsManager->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	m_GraphicsManager->GetDeviceContext()->Draw(4, 0);
}