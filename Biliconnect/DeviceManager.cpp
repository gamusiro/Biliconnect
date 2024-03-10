/*===========================================================================
	Date : 2022/02/07(日)	DeviceManager.cpp
		Author	: がむしるぉ
		Update	:
		Comment	: 
===========================================================================*/
#include "DeviceManager.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
DeviceManager::DeviceManager()
	:m_d3dDevice(nullptr),
	m_d3dDeviceContext(nullptr),
	m_d3dFactory(nullptr),
	m_d3dFeatureLevel()
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
DeviceManager::~DeviceManager()
{
}

/*=============================================================================================
	生成処理
=============================================================================================*/
bool DeviceManager::Create()
{
	D3D_FEATURE_LEVEL featureLevels[] = {
	   D3D_FEATURE_LEVEL_11_0,
	   D3D_FEATURE_LEVEL_10_1,
	   D3D_FEATURE_LEVEL_10_0,
	};

	//ファクトリーの生成
	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&m_d3dFactory));
	
	//生成に失敗
	if (!m_d3dFactory)	return false;

	//デバイスの生成処理
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

	//生成に失敗
	if (!m_d3dDevice)			return false;
	if (!m_d3dDeviceContext)	return false;

	std::cout << "Success to Create Device Manager!" << std::endl;
	return true;
}

/*=============================================================================================
	解放処理
=============================================================================================*/
void DeviceManager::Release()
{
	if (m_d3dDeviceContext)	m_d3dDeviceContext->Release();
	if (m_d3dDevice)			m_d3dDevice->Release();
}
