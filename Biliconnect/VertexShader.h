/*===========================================================================
	Date : 2022/02/08(��)	VertexShader.h
		Author	: ���ނ��邧
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
	bool Create();		//��������
	void SetLayout();	//���̓��C�A�E�g�ݒ菈��
	void SetShader();	//�V�F�[�_�\�̐ݒ菈��
	void Release();		//�������

private:
	GraphicsManager*	m_GraphicsManager;
	ID3D11VertexShader* m_VertexShader;
	ID3D11InputLayout*	m_VertexLayout;
};

#endif // !VERTEXSHADER_H_
