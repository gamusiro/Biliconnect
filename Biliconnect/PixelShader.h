/*===========================================================================
	Date : 2022/02/08(��)	PixelShader.h
		Author	: ���ނ��邧
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
	bool Create();		//��������
	void SetShader();	//�ݒ菈��
	void Release();		//�������

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11PixelShader*	m_PixelShader;
};

#endif // !PIXELSHADER_H_
