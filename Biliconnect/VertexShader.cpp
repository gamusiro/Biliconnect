/*===========================================================================
	Date : 2022/02/08(��)	VertexShader.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	:
===========================================================================*/
#include "GraphicsManager.h"
#include "FileIO.h"

#include "VertexShader.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
VertexShader::VertexShader(GraphicsManager* gm)
	:m_GraphicsManager(gm),
	m_VertexLayout(nullptr),
	m_VertexShader(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
VertexShader::~VertexShader()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool VertexShader::Create()
{
	std::string buffer;
	FileIO().Load(buffer, "VertexShader.cso");

	//�V�F�[�_�\�̐ݒ菈��
	m_GraphicsManager->GetDevice()->CreateVertexShader(buffer.c_str(), buffer.size(), nullptr, &m_VertexShader);

	//�����Ɏ��s
	if (!m_VertexShader)	return false;

	//���̓��C�A�E�g�̐�������
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",	 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,	 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",	 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,		 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	//���̓��C�A�E�g�̐�������
	m_GraphicsManager->GetDevice()->CreateInputLayout(
		layout,
		_countof(layout),
		buffer.c_str(),
		buffer.size(),
		&m_VertexLayout);

	//���������Ɏ��s
	if (!m_VertexLayout)	return false;

	std::cout << "Success to Load Vertex Shader.hlsl!" << std::endl;
	return true;
}

/*=============================================================================================
	���C�A�E�g�ݒ菈��
=============================================================================================*/
void VertexShader::SetLayout()
{
	m_GraphicsManager->GetDeviceContext()->IASetInputLayout(m_VertexLayout);
}

/*=============================================================================================
	�V�F�[�_�\�̐ݒ菈��
=============================================================================================*/
void VertexShader::SetShader()
{
	m_GraphicsManager->GetDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
}

/*=============================================================================================
	�������
=============================================================================================*/
void VertexShader::Release()
{
	m_GraphicsManager = nullptr;
	if (m_VertexLayout) m_VertexLayout->Release();
	if (m_VertexShader) m_VertexShader->Release();
}
