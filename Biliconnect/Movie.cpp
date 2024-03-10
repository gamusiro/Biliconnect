/*
*	Date : 2022/05/31(火)
*		Author : がむしろ
*		Update : ----/--/--()
*/
#include "Monitor.h"

#include "Movie.h"
using namespace Microsoft::WRL;

#define SAFE_RELEASE(x) if(x){x.Release();}

CComPtr<IGraphBuilder>			Movie::m_GraphBuilder = nullptr;
CComPtr<IBaseFilter>			Movie::m_BaseFilter = nullptr;
CComPtr<IMFVideoDisplayControl> Movie::m_DisplayControl = nullptr;
CComPtr<IMediaControl>			Movie::m_MediaControl = nullptr;
CComPtr<IMediaEventEx>			Movie::m_MediaEvent = nullptr;
CComPtr<IBasicAudio>			Movie::m_BasicAudio = nullptr;
MOVIE_STATE						Movie::m_State = MOVIE_STATE::NONE;
HWND							Movie::m_WindowHandle = nullptr;

// 初期化処理
bool Movie::Init(HWND hWnd)
{
	m_WindowHandle = hWnd;
	return true;
}

// 更新処理
void Movie::Update()
{
	if (m_State != MOVIE_STATE::NONE)
	{
		long state;
		LONG_PTR ptr1, ptr2;
		m_MediaEvent->GetEvent(&state, &ptr1, &ptr2, 0);

		if (state == EC_COMPLETE)
		{// 動画が終了したら
			m_State = MOVIE_STATE::END;
		}
	}
}

// 終了処理
void Movie::Uninit()
{
	m_WindowHandle = nullptr;
}

// 画面のリサイズ
void Movie::Resize()
{
	if (m_DisplayControl)
	{
		MFVideoNormalizedRect mvnr{ 0, 0, 1, 1 };
		RECT rect{};
#ifdef DEBUG
		GetClientRect(m_WindowHandle, &rect);
#else
		rect = Monitor::GetMonitorRect();
#endif // DEBUG
		m_DisplayControl->SetVideoPosition(&mvnr, &rect);
	}
}

// データの読み込み処理
void Movie::Load(LPCWSTR fileName)
{
	HRESULT ret;
	ret = m_GraphBuilder.CoCreateInstance(CLSID_FilterGraph);
	ret = m_BaseFilter.CoCreateInstance(CLSID_EnhancedVideoRenderer);

	CComQIPtr<IMFGetService> service(m_BaseFilter);
	ret = service->GetService(
		MR_VIDEO_RENDER_SERVICE,
		IID_IMFVideoDisplayControl,
		(void**)&m_DisplayControl
	);
	ret = m_DisplayControl->SetVideoWindow(m_WindowHandle);
	
	Resize();

	ret = m_GraphBuilder->AddFilter(m_BaseFilter, L"EVR");
	ret = m_GraphBuilder->RenderFile(fileName, nullptr);

	m_MediaControl	= CComQIPtr<IMediaControl>(m_GraphBuilder);
	m_MediaEvent	= CComQIPtr<IMediaEventEx>(m_GraphBuilder);
	m_BasicAudio	= CComQIPtr<IBasicAudio>(m_GraphBuilder);
}

// 再生処理
void Movie::Play()
{
	if (m_MediaControl)
	{
		m_State = MOVIE_STATE::RUN;
		m_MediaControl->Run();
	}
		
}

// 停止処理
void Movie::Stop()
{
	if (m_MediaControl)
	{
		m_State = MOVIE_STATE::END;
		m_MediaControl->Stop();
	}
}

// 音量調整
void Movie::SetVolume(int val)
{
	if (m_BasicAudio)
	{
		val = min(100, val);
		val = max(val, 0);
		long volume = -10000 + (100 * val);
		m_BasicAudio->put_Volume(volume);
	}
}

// 解放処理
void Movie::Unload()
{
	SAFE_RELEASE(m_GraphBuilder);
	SAFE_RELEASE(m_BaseFilter);
	SAFE_RELEASE(m_DisplayControl);
	SAFE_RELEASE(m_MediaControl);
	SAFE_RELEASE(m_MediaEvent);
	m_State = MOVIE_STATE::NONE;
}

// 動画状態の取得処理
MOVIE_STATE Movie::GetState()
{
	return m_State;
}
