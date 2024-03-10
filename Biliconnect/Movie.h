/*
*	Date : 2022/05/31(��)
*		Author : ���ނ���
*		Update : ----/--/--()
*/
#pragma once
#include <Windows.h>
#include <wrl.h>

 #include <atlbase.h>
 #include <atlwin.h>
 #include <atlstr.h>

#include <d3d9.h>
#include <dshow.h>
#include <evr.h>
#include <evr9.h>

#pragma comment(lib, "strmiids.lib")


enum class MOVIE_STATE
{
	NONE,	// �Đ����Ă��Ȃ�
	RUN,	// �Đ���
	END		// �Đ��I��
};

class Movie
{
private:
	static CComPtr<IGraphBuilder>			m_GraphBuilder;
	static CComPtr<IBaseFilter>				m_BaseFilter;
	static CComPtr<IMFVideoDisplayControl>	m_DisplayControl;
	static CComPtr<IMediaControl>			m_MediaControl;
	static CComPtr<IMediaEventEx>			m_MediaEvent;
	static CComPtr<IBasicAudio>				m_BasicAudio;
	static MOVIE_STATE						m_State;
	static HWND m_WindowHandle;

public:
	/*
	* @	brief \
	*	����������
	* @ comment \
	*	�`��E�B���h�E�̓o�^���s��
	*/
	static bool Init(HWND hWnd);
	
	/*
	* @	brief \
	*	�X�V����
	* @ comment \
	*	�Đ���Ԃ̍X�V���s��
	*/
	static void Update();
	
	/*
	* @	brief \
	*	�I������
	* @ comment \
	*	�E�B���h�E�̉������s��
	*/
	static void Uninit();

	/*
	* @ brief \
	*	��ʂ����T�C�Y���ꂽ�ꍇ�ɌĂ�
	*/
	static void Resize();

public:
	/*
	* @ brief /
	*	����f�[�^�̓ǂݍ��ݏ���
	* @ param \
	*	fileName : ����̃t�@�C����(���΃p�X)
	*/
	static void Load(LPCWSTR fileName);

	/*
	* @ brief /
	*	����̍Đ�����
	*/
	static void Play();
	
	/*
	* @ brief /
	*	���批�ʂ̒��ߏ���
	*/
	static void SetVolume(int val);
	
	/*
	* @ brief /
	*	����̒�~����
	*/
	static void Stop();
	
	/*
	* @ brief /
	*	����̉������
	*/
	static void Unload();

public:
	static MOVIE_STATE GetState();
};

