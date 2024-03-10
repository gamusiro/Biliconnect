/*===========================================================================
	Date : 2022/02/07(��)	DeviceManager.cpp
		Author	: ���ނ��邧
		Update	:
		Comment	: 
===========================================================================*/
#include "DeviceManager.h"


/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
DeviceManager::DeviceManager()
	:m_d3dDevice(nullptr),
	m_d3dDeviceContext(nullptr),
	m_d3dFactory(nullptr),
	m_d3dFeatureLevel()
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
DeviceManager::~DeviceManager()
{
}

/*=============================================================================================
	��������
=============================================================================================*/
bool DeviceManager::Create()
{
	D3D_FEATURE_LEVEL featureLevels[] = {
	   D3D_FEATURE_LEVEL_11_0,
	   D3D_FEATURE_LEVEL_10_1,
	   D3D_FEATURE_LEVEL_10_0,
	};

	//�t�@�N�g���[�̐���
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_d3dFactory));
	
	//�����Ɏ��s
	if (!m_d3dFactory)	return false;

	//�f�o�C�X�̐�������
	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
		0,
		0,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_d3dDevice,
		&m_d3dFeatureLevel,
		&m_d3dDeviceContext);

	//�����Ɏ��s
	if (!m_d3dDevice)			return false;
	if (!m_d3dDeviceContext)	return false;

	std::cout << "Success to Create Device Manager!" << std::endl;
	return true;
}

/*=============================================================================================
	�������
=============================================================================================*/
void DeviceManager::Release()
{
	if (m_d3dDeviceContext)	m_d3dDeviceContext->Release();
	if (m_d3dDevice)			m_d3dDevice->Release();
}
