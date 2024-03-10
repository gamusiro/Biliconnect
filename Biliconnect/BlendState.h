/*===========================================================================
	Date : 2022/02/08(月)	BlendState.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef BLENDSTATE_H_
#define BLENDSTATE_H_

#include "main.h"

class GraphicsManager;

/**********************************************************
	@brief ブレンドモードの指定
	None		: ブレンドなし
	ALPHA		: アルファブレンド
	ADD			: 加算ブレンド
	SUBTRACT	: 減算ブレンド
**********************************************************/
enum class BLEND_MODE
{
	NONE, 
	ALPHA,
	ADD,
	SUBTRACT
};

class BlendState
{
public:
	BlendState(GraphicsManager* gm);
	~BlendState();

public:
	bool Create();					//生成処理
	void SetMode(BLEND_MODE mode);	//設定処理
	void Release();					//解放処理

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11BlendState*	m_BlendNone;
	ID3D11BlendState*	m_BlendAlpha;
	ID3D11BlendState*	m_BlendAdd;
	ID3D11BlendState*	m_BlendSub;
};

#endif // !BLENDSTATE_H_
