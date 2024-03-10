/*===========================================================================
	Date : 2022/02/08(火)	PixelShader.h
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#ifndef PIXELSHADER_H_
#define PIXELSHADER_H_

#include "main.h"

class GraphicsManager;

class PixelShader
{
public:
	PixelShader(GraphicsManager* gm);
	~PixelShader();

public:
	bool Create();		//生成処理
	void SetShader();	//設定処理
	void Release();		//解放処理

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11PixelShader*	m_PixelShader;
};

#endif // !PIXELSHADER_H_
