/*===========================================================================
	Date : 2022/02/07(��)	GraphicsManager.h
		Author	: ���ނ��邧
		Update	:
		Comment	: 
===========================================================================*/
#ifndef GRAPHICSMANAGER_H_
#define GRAPHICSMANAGER_H_

#include "main.h"

//���_�̍\����
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
	bool Init();		//����������
	void Uninit();		//�I������
	void Clear();		//��ʂ̃N���A
	void Present();		//�o�b�t�@�̐؂�ւ�����

public:
	/********************************************************************************
		�s��̃f�[�^�������Ő������A�o�^������VertexShader.hlsl�ɓ]������
		�����܂Ńf�[�^�𐶐����AShader���ŕϊ����s��
	********************************************************************************/
	void Translate2D();

	/********************************************************************************
		�[�x�̗L���ݒ菈��(2D�̏ꍇ�͐[�x�����ł悢)
	********************************************************************************/
	void SetDepthEnable(bool use);

	void SetScreenMode(bool full);	//true �ł���� �t���X�N���[��

private:
	void SetViewport();				//�r���[�|�[�g�̐ݒ菈��
	void CreateConstantBuffer();	//�萔�o�b�t�@�̐�������

public:
	ID3D11Device*			GetDevice();		//�f�o�C�X�̎擾����
	ID3D11DeviceContext*	GetDeviceContext();	//�f�o�C�X�R���e�L�X�g�̎擾����

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
