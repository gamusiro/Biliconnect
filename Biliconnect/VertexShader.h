/*===========================================================================
	Date : 2022/02/08(火)	VertexShader.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef VERTEXSHADER_H_
#define VERTEXSHADER_H_

#include "main.h"

class GraphicsManager;

class VertexShader
{
public:
	VertexShader(GraphicsManager* gm);
	~VertexShader();

public:
	bool Create();		//生成処理
	void SetLayout();	//入力レイアウト設定処理
	void SetShader();	//シェーダ―の設定処理
	void Release();		//解放処理

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11VertexShader* m_VertexShader;
	ID3D11InputLayout*	m_VertexLayout;
};

#endif // !VERTEXSHADER_H_
