/*
*	Date : 2022/05/31(火)
*		Author : がむしろ
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
	NONE,	// 再生していない
	RUN,	// 再生中
	END		// 再生終了
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
	*	初期化処理
	* @ comment \
	*	描画ウィンドウの登録を行う
	*/
	static bool Init(HWND hWnd);
	
	/*
	* @	brief \
	*	更新処理
	* @ comment \
	*	再生状態の更新を行う
	*/
	static void Update();
	
	/*
	* @	brief \
	*	終了処理
	* @ comment \
	*	ウィンドウの解除を行う
	*/
	static void Uninit();

	/*
	* @ brief \
	*	画面がリサイズされた場合に呼ぶ
	*/
	static void Resize();

public:
	/*
	* @ brief /
	*	動画データの読み込み処理
	* @ param \
	*	fileName : 動画のファイル名(相対パス)
	*/
	static void Load(LPCWSTR fileName);

	/*
	* @ brief /
	*	動画の再生処理
	*/
	static void Play();
	
	/*
	* @ brief /
	*	動画音量の調節処理
	*/
	static void SetVolume(int val);
	
	/*
	* @ brief /
	*	動画の停止処理
	*/
	static void Stop();
	
	/*
	* @ brief /
	*	動画の解放処理
	*/
	static void Unload();

public:
	static MOVIE_STATE GetState();
};

