/*=========================================================================
	Date : 2021/12/25(土)	TextureManager.cpp
		Author : がむしるぉ
		Update :
=========================================================================*/
#include "GraphicsManager.h"
#include "StringConverter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_library/stb_image.h"

#include <wrl.h>
#include <iostream>
using namespace Microsoft::WRL;


#include "TextureManager.h"

GraphicsManager*			TextureManager::m_GraphicsManager = nullptr;
ID3D11ShaderResourceView*	TextureManager::m_TextureArray[MAX_TEXTURE_NUM] = {};
ID3D11ShaderResourceView*	TextureManager::m_TextureMask;
char						TextureManager::m_TextureName[MAX_TEXTURE_NUM][256];
int							TextureManager::m_Index = 0;

/*=============================================================================================
	初期化処理
=============================================================================================*/
bool TextureManager::Init(GraphicsManager* gm)
{
	m_GraphicsManager = gm;

	//ファイルからテクスチャを読み込む
	HRESULT ret{};

	// load image

	int image_width;
	int image_height;
	int image_channels;
	int image_desired_channels = 4;

	unsigned char* image_data = stbi_load(
		"Material/Texture/chan2.png",
		&image_width,
		&image_height,
		&image_channels, image_desired_channels);

	int image_pitch = image_width * 4;

	// texture
	D3D11_TEXTURE2D_DESC image_texture_desc = {};

	image_texture_desc.Width				= image_width;
	image_texture_desc.Height				= image_height;
	image_texture_desc.MipLevels			= 1;
	image_texture_desc.ArraySize			= 1;
	image_texture_desc.Format				= DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	image_texture_desc.SampleDesc.Count		= 1;
	image_texture_desc.SampleDesc.Quality	= 0;
	image_texture_desc.Usage				= D3D11_USAGE_DEFAULT;
	image_texture_desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA image_subresource_data = {};
	image_subresource_data.pSysMem = image_data;
	image_subresource_data.SysMemPitch = image_pitch;

	ComPtr<ID3D11Texture2D> image_texture;

	ret = m_GraphicsManager->GetDevice()->CreateTexture2D(
		&image_texture_desc,
		&image_subresource_data,
		image_texture.GetAddressOf()
	);

	ret = m_GraphicsManager->GetDevice()->CreateShaderResourceView(
		image_texture.Get(),
		nullptr,
		&m_TextureMask
	);

	free(image_data);

	return true;
}

/*=============================================================================================
	終了処理
=============================================================================================*/
void TextureManager::Uninit()
{
	m_GraphicsManager = nullptr;
	Unload();

	if (m_TextureMask != nullptr)
	{
		m_TextureMask->Release();
		m_TextureMask = nullptr;
	}
}

/*=============================================================================================
	テクスチャの読み込み処理
=============================================================================================*/
int TextureManager::Load(const char* file_name)
{
	//読み込み最大数を超えていたら負の値を返す
	if (m_Index == MAX_TEXTURE_NUM)
	{
		return -1;
	}

	//ファイルパスの生成
	char file_path[256] = "Material/Texture/";
	strcat_s(file_path, file_name);

	//同じファイル名のものがあれば
	for (int i = 0; i < m_Index; i++)
	{
		if (strcmp(m_TextureName[i], file_path) == 0)
		{
			return i;
		}
	}
	
	//ファイルからテクスチャを読み込む
	HRESULT ret{};
	// load image

	int image_width;
	int image_height;
	int image_channels;
	int image_desired_channels = 4;

	unsigned char* image_data = stbi_load(
		file_path,
		&image_width,
		&image_height,
		&image_channels,
		image_desired_channels
	);

	int image_pitch = image_width * 4;

	// texture
	D3D11_TEXTURE2D_DESC image_texture_desc = {};

	image_texture_desc.Width = image_width;
	image_texture_desc.Height = image_height;
	image_texture_desc.MipLevels = 1;
	image_texture_desc.ArraySize = 1;
	image_texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	image_texture_desc.SampleDesc.Count = 1;
	image_texture_desc.SampleDesc.Quality = 0;
	image_texture_desc.Usage = D3D11_USAGE_DEFAULT;
	image_texture_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA image_subresource_data = {};

	image_subresource_data.pSysMem = image_data;
	image_subresource_data.SysMemPitch = image_pitch;

	ComPtr<ID3D11Texture2D> image_texture;

	ret = m_GraphicsManager->GetDevice()->CreateTexture2D(
		&image_texture_desc,
		&image_subresource_data,
		&image_texture
	);

	ret = m_GraphicsManager->GetDevice()->CreateShaderResourceView(
		image_texture.Get(),
		nullptr,
		&m_TextureArray[m_Index]
	);

	free(image_data);

	//ファイル名を保存する
	strcpy_s(m_TextureName[m_Index], file_path);

	int index = m_Index;

	//インデックスを一つ進める
	m_Index++;

	return index;
}

/*=============================================================================================
	テクスチャの解放処理(自分で読み込んだものだけ)
=============================================================================================*/
void TextureManager::Unload()
{
	//テクスチャを全て開放
	for (int i = 0; i < m_Index; i++)
	{
		if (m_TextureArray[i] != nullptr)
		{
			m_TextureArray[i]->Release();
			m_TextureArray[i] = nullptr;
		}
		ZeroMemory(m_TextureName[i], sizeof(char) * 256);
	}

	//初期値に戻す
	m_Index = 0;
}

/*=============================================================================================
	テクスチャの取得処理
=============================================================================================*/
ID3D11ShaderResourceView** TextureManager::GetTexture(int index)
{
	if (index < 0) return nullptr;
	if (index >= MAX_TEXTURE_NUM) return nullptr;

	return &m_TextureArray[index];
}

/*=============================================================================================
	マスクの取得処理
=============================================================================================*/
ID3D11ShaderResourceView** TextureManager::GetMask()
{
	return &m_TextureMask;
}