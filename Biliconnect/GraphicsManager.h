/*===========================================================================
	Date : 2022/02/07(月)	GraphicsManager.h
		Author	: がむしるぉ
		Update	:
		Comment	: 
===========================================================================*/
#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_

#include "main.h"

//頂点の構造体
struct Vertex
{
	math::Float3 Position;
	math::Float3 Normal;
	math::Float4 Color;
	math::Float2 TexCoord;
};


class DeviceManager;
class SwapChain;
class RenderTargetView;
class DepthStencilView;
class RasterizerState;
class BlendState;
class DepthStencilState;
class SamplerState;
class VertexShader;
class PixelShader;
class MaterialBuffer;

class GraphicsManager
{
public:
	GraphicsManager();
	~GraphicsManager();

public:
	bool Init();		//初期化処理
	void Uninit();		//終了処理
	void Clear();		//画面のクリア
	void Present();		//バッファの切り替え処理

public:
	/********************************************************************************
		行列のデータをここで生成し、登録をしてVertexShader.hlslに転送する
		あくまでデータを生成し、Shader側で変換を行う
	********************************************************************************/
	void Translate2D();

	/********************************************************************************
		深度の有効設定処理(2Dの場合は深度無効でよい)
	********************************************************************************/
	void SetDepthEnable(bool use);

	void SetScreenMode(bool full);	//true であれば フルスクリーン

private:
	void SetViewport();				//ビューポートの設定処理
	void CreateConstantBuffer();	//定数バッファの生成処理

public:
	ID3D11Device*			GetDevice();		//デバイスの取得処理
	ID3D11DeviceContext*	GetDeviceContext();	//デバイスコンテキストの取得処理

private:
	DeviceManager*		m_DeviceManager;
	SwapChain*			m_SwapChain;
	RenderTargetView*	m_RenderTargetView;
	DepthStencilView*	m_DepthStencilView;
	RasterizerState*	m_RasterizerState;
	BlendState*			m_BlendState;
	DepthStencilState*	m_DepthStencilState;
	SamplerState*		m_SamplerState;
	VertexShader*		m_VertexShader;
	PixelShader*		m_PixelShader;
	ID3D11Buffer*		m_ConstantBuffer;
};


#endif // !GRAPHICSMANAGER_H_
