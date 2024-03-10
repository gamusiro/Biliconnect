/*===========================================================================
	Date : 2022/02/07(日)	DeviceManager.h
		Author	: がむしるぉ
		Update	:
		Comment	: 
===========================================================================*/
#ifndef DEVICEMANAGER_H_
#define DEVICEMANAGER_H_

#include "main.h"

class DeviceManager
{
public:
	DeviceManager();
	~DeviceManager();

public:
	bool Create();		//生成処理
	void Release();		//解放処理

private:
	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_d3dDeviceContext;
	IDXGIFactory*			m_d3dFactory;
	D3D_FEATURE_LEVEL		m_d3dFeatureLevel;

private:
	friend class GraphicsManager;
};

#endif // !DEVICEMANAGER_H_
