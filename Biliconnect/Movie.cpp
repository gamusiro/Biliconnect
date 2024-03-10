/*
*	Date : 2022/05/31(��)
*		Author : ���ނ���
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

// ����������
bool Movie::Init(HWND hWnd)
{
	m_WindowHandle = hWnd;
	return true;
}

// �X�V����
void Movie::Update()
{
	if (m_State != MOVIE_STATE::NONE)
	{
		long state;
		LONG_PTR ptr1, ptr2;
		m_MediaEvent->GetEvent(&state, &ptr1, &ptr2, 0);

		if (state == EC_COMPLETE)
		{// ���悪�I��������
			m_State = MOVIE_STATE::END;
		}
	}
}

// �I������
void Movie::Uninit()
{
	m_WindowHandle = nullptr;
}

// ��ʂ̃��T�C�Y
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

// �f�[�^�̓ǂݍ��ݏ���
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

// �Đ�����
void Movie::Play()
{
	if (m_MediaControl)
	{
		m_State = MOVIE_STATE::RUN;
		m_MediaControl->Run();
	}
		
}

// ��~����
void Movie::Stop()
{
	if (m_MediaControl)
	{
		m_State = MOVIE_STATE::END;
		m_MediaControl->Stop();
	}
}

// ���ʒ���
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

// �������
void Movie::Unload()
{
	SAFE_RELEASE(m_GraphBuilder);
	SAFE_RELEASE(m_BaseFilter);
	SAFE_RELEASE(m_DisplayControl);
	SAFE_RELEASE(m_MediaControl);
	SAFE_RELEASE(m_MediaEvent);
	m_State = MOVIE_STATE::NONE;
}

// �����Ԃ̎擾����
MOVIE_STATE Movie::GetState()
{
	return m_State;
}
