/*===========================================================================
	Date : 2022/02/08(月)	SamplerState.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef SAMPLERSTATE_H_
#define SAMPLERSTATE_H_

#include "main.h"

class GraphicsManager;

/**********************************************************
	@brief アドレスモードの指定
	WRAP	: テクスチャを繰り返す(向きは同じ)
	MIRROR	: テクスチャをミラーリングする(向きが反転する)
	CLAMP	: テクスチャをクランプする
	BORDER	: テクスチャをボーダーする(境界線の色が適用される)
**********************************************************/
enum class ADDRESS_MODE
{
	WRAP,
	MIRROR,
	CLAMP,
	BORDER
};

/**********************************************************
	@brief フィルターモードの指定
	POINT		: ポイントフィルタリング(低画質、低コスト)
	LINEAR		: バイリニアフィルタリング(2次元)
	ANISOTOROPIC: アニソトロピックフィルタリング(高画質、高コスト)
**********************************************************/
enum class FILTER_MODE
{
	POINT,
	LINEAR,
	ANISOTROPIC
};

class SamplerState
{
public:
	SamplerState(GraphicsManager* gm);
	~SamplerState();

public:
	bool Create();									//生成処理
	void SetMode(ADDRESS_MODE am, FILTER_MODE fm);	//モード設定処理
	void SetColor(math::Float4 boaderColor);		//ボーダーカラーの指定				
	void Release();									//解放処理

private:
	GraphicsManager*	m_GraphicsManager;
	math::Float4		m_BorderColor;
};

#endif // !SAMPLERSTATE_H_
