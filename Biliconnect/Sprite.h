/*===========================================================================
	Date : 2022/02/08(火)	Sprite.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef SPRITE_H_
#define SPRITE_H_

#include "main.h"

class GraphicsManager;
class Texture;

class Sprite
{
public:
	static bool Init(GraphicsManager* gm);
	static void Uninit();
	/*
	*	@ brief
	*		左上基準の矩形の描画
	*	@ param
	*		pos		: 左上頂点座標
	*		_size	: 矩形のサイズ
	*		color	: カラー
	*/
	static void DrawLeftTop(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = {1, 1, 1, 1});

	/*
	*	@ brief
	*		中心基準の矩形の描画
	*	@ param
	*		pos		: 中心座標
	*		_size	: 矩形のサイズ
	*		color	: カラー
	*/
	static void DrawCenter(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = {1, 1, 1, 1},
		float degree = 0.0f);

	static void DrawBottom(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = { 1, 1, 1, 1 },
		float degree = 0.0f);

	static void DrawCenterK(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = { 1, 1, 1, 1 },
		float degree = 0.0f);

	/*
	*	@ brief
	*		マスク用
	*	@ param
	*		pos		: 中心座標
	*		_size	: 矩形のサイズ
	*		color	: カラー
	* @ comment	
	*		シーンをまたぐ描画の場合はTextureクラスのメンバ関数 Create(でファイルを読み込んではいけない) 利用不可。
	*		(例)テクスチャのアニメーションがある場合のCreateの使用法:
	*				texture->Create(nullptr, 2, 2, 10);
	*				texture->SetImageID(0);
	* 
	*		マスク画像の管理方法は検討中・・・
	*/
	static void DrawMask(
		math::Float2 pos,
		math::Float2 size,
		const Texture* image,
		math::Float4 color = { 1, 1, 1, 1 },
		float degree = 0.0f);

private:
	static GraphicsManager* m_GraphicsManager;
	static ID3D11Buffer*	m_VertexBuffer;
};

#endif // !SPRITE_H_
