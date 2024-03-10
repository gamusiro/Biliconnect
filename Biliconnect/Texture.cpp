/*=========================================================================
	Date : 2021/12/26(土)	GameCreateSystem.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#include "TextureManager.h"

#include "Texture.h"
using namespace math;

/*===================================================================
	コンストラクタ
===================================================================*/
Texture::Texture()
	:m_Frame(),
	m_Info(),
	m_Direction(DIRECTION_TEXTURE::LEFT)
{
}

/*===================================================================
	デストラクタ
===================================================================*/
Texture::~Texture()
{
}

/*===================================================================
	画像データの生成
===================================================================*/
void Texture::Create(const char* fileName, int column, int row, int frame)
{
	//ファイル名がnullptrでなければ
	if (fileName != nullptr)
		this->m_Info.TextureID = TextureManager::Load(fileName);
	else
		this->m_Info.TextureID = -1;

	//カットサイズが不適切でなければ
	if (column > 0 && row > 0)
	{
		this->m_Info.TotalTexture = column * row;
		this->m_Info.CutNum = Int2(column, row);
		this->m_Info.SizeUV = Float2(1.0f / column, 1.0f / row);
	}
	else
	{
		this->m_Info.TotalTexture = 1 * 1;
		this->m_Info.CutNum = Int2(1, 1);
		this->m_Info.SizeUV = Float2(1.0f, 1.0f);
	}

	this->m_Frame.Criteria = frame;
	
}

/*===================================================================
	テクスチャの更新
===================================================================*/
void Texture::Update()
{
	//フレームの更新
	this->m_Frame.Counter++;

	if (this->m_Frame.Counter > this->m_Frame.Criteria)
	{
		//フレームカウンタを０に戻す
		this->m_Frame.Counter = 0;

		//テクスチャアニメーションを一つ進める
		this->m_Info.CurrentTexture++;
		this->m_Info.CurrentTexture %= this->m_Info.TotalTexture;

		//UV値を更新する
		this->m_Info.StartUVPosition.x
			= this->m_Info.SizeUV.x * (this->m_Info.CurrentTexture % this->m_Info.CutNum.x);
		this->m_Info.StartUVPosition.y
			= this->m_Info.SizeUV.y * (this->m_Info.CurrentTexture / this->m_Info.CutNum.x);
	}
}
void Texture::Update(int index)
{
	//フレームの更新
	this->m_Frame.Counter++;

	if (this->m_Frame.Counter > this->m_Frame.Criteria)
	{
		//フレームカウンタを０に戻す
		this->m_Frame.Counter = 0;

		//テクスチャアニメーションを一つ進める
		this->m_Info.CurrentTexture++;
		this->m_Info.CurrentTexture %= this->m_Info.TotalTexture;

		//UV値を更新する
		this->m_Info.StartUVPosition.x
			= this->m_Info.SizeUV.x * (this->m_Info.CurrentTexture % this->m_Info.CutNum.x);
		this->m_Info.StartUVPosition.y
			= this->m_Info.SizeUV.y * (this->m_Info.CutNum.y * (index % this->m_Info.CutNum.y));
	}
}

/*===================================================================
	テクスチャ番号を指定
===================================================================*/
void Texture::SetCurrentTexture(int frame)
{
	m_Info.CurrentTexture = frame - 1;
	this->m_Frame.Counter = m_Frame.Criteria + 1;
}

/*===================================================================
	テクスチャのID変更
===================================================================*/
void Texture::SetImageID(int num)
{
	//データが指定されていない状態であれば
	if (!this->AlreadyLoaded())
	{
		this->m_Info.TextureID = num;
	}
}

/*===================================================================
	テクスチャのUV値座標の指定
===================================================================*/
void Texture::SetStartUVPosition(Float2 pos)
{
	this->m_Info.StartUVPosition = pos;
}

/*===================================================================
	テクスチャの方向指定
===================================================================*/
void Texture::SetTextureDirection(DIRECTION_TEXTURE dir)
{
	this->m_Direction = dir;
}

/*===================================================================
	データをリセットする
===================================================================*/
void Texture::Reset()
{
	*this = Texture();
}

/*===================================================================
	テクスチャを取得しているか
===================================================================*/
bool Texture::AlreadyLoaded()
{
	if (this->m_Info.TextureID == -1)
		return false;

	return true;
}
