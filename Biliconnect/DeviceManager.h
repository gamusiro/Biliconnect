/*===========================================================================
	Date : 2022/02/07(“ú)	DeviceManager.h
		Author	: ‚ª‚Ş‚µ‚é‚§
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
	bool Create();		//¶¬ˆ—
	void Release();		//‰ğ•úˆ—

private:
	ID3D11Device*			m_d3dDevice;
	ID3D11DeviceContext*	m_d3dDeviceContext;
	IDXGIFactory*			m_d3dFactory;
	D3D_FEATURE_LEVEL		m_d3dFeatureLevel;

private:
	friend class GraphicsManager;
};

#endif // !DEVICEMANAGER_H_
