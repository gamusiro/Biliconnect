/*===========================================================================
	Date : 2022/02/08(‰Î)	PixelShader.h
		Author	: ‚ª‚Ş‚µ‚é‚§
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
	bool Create();		//¶¬ˆ—
	void SetShader();	//İ’èˆ—
	void Release();		//‰ğ•úˆ—

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11PixelShader*	m_PixelShader;
};

#endif // !PIXELSHADER_H_
