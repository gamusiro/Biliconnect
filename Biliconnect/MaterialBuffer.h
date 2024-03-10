/*===========================================================================
	Date : 2022/02/11(金)	MaterialBuffer.h
		Author	: がむしるぉ
		Update	:
		Comment	: 今回利用したいのはテクスチャを利用するか、
				　ポリゴンを描画するかの二択なので boolでよいのだが、
				  バッファの都合上16バイトは最低でも必要らしいので、
				  適当な構造体を作ってしまいましょうという訳です。
===========================================================================*/
#ifndef MATERIALBUFFER_H_
#define MATERIALBUFFER_H_

#include "main.h"

//構造体は16の倍数でなければならない
struct Material
{
	int		noTexSampling;	//テクスチャの利用フラグ(1: 利用する, 0: 利用しない)
	float	Dummy[3];		//16byte境界用
};

class GraphicsManager;

class MaterialBuffer
{
public:
	static bool Init(GraphicsManager* gm);		//初期化処理
	static void SetData(const Material& data);	//データの設定処理
	static void Uninit();						//終了処理

private:
	static GraphicsManager*	m_GraphicsManager;
	static ID3D11Buffer*	m_MaterialBuffer;
};

#endif // !MATERIALBUFFER_H_
