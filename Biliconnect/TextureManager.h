/*=========================================================================
	Date : 2021/12/25(土)	TextureManager.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include "main.h"

#define MAX_TEXTURE_NUM	100
#define MAX_TEXTURE_ALPHABET 26

class GraphicsManager;

class TextureManager
{
public:
	static bool Init(GraphicsManager* gm);
	static void Uninit();
	/********************************************************************************
		@ brief テクスチャデータの読み込み処理
		@ param
			fileName	: テクスチャのファイル名
	********************************************************************************/
	static int  Load(const char* fileName);

	/********************************************************************************
		@ brief テクスチャデータの解放処理
		@ comment
			読み込まれているデータを全て開放する
			※シーンごとにテクスチャデータを破棄することで、パフォーマンス向上につながる?
	********************************************************************************/
	static void Unload();

	/********************************************************************************
		@ brief テクスチャデータの取得処理
		@ param 
			index	: テクスチャの管理番号
		@ return 
			テクスチャリソースデータ
	********************************************************************************/
	static ID3D11ShaderResourceView** GetTexture(int index);

	static ID3D11ShaderResourceView** GetMask();

private:
	static GraphicsManager*			 m_GraphicsManager;
	static ID3D11ShaderResourceView* m_TextureArray[MAX_TEXTURE_NUM];
	static ID3D11ShaderResourceView* m_TextureMask;
	static char						 m_TextureName[MAX_TEXTURE_NUM][256];
	static int						 m_Index;
};

#endif // !TEXTUREMANAGER_H_



