/*=========================================================================
	Date : 2021/11/28(日)	Window.h
		Author	: がむしるぉ
		Update	: 2022/02/05(土)
		Comment	:
		※ウィンドウ画面のクラス
=========================================================================*/
#ifndef WINDOW_H_
#define WINDOW_H_


#define WINDOW_SIZE_WIDTH  960
#define WINDOW_SIZE_HEIGHT 540

#include <Windows.h>

class Window
{
public:
	Window();
	~Window();

public:
	//ウィンドウの登録を行う
	int  Init	(HINSTANCE hInstance, const LPCSTR& class_name);	
	//ウィンドウの終了処理
	void Uninit	();													

public:
	//画面の生成処理
	//ウィンドウ名前を表示しない場合は空白
	void Create	(const LPCSTR& window_name);		
	//画面の表示処理
	void Show	(int nCmdShow);
	//画面の管理を行う
	bool Dispatcher();

	// ウィンドウをゲーム母田んえ閉じる
	void Exit();
public:
	HWND	Get_HWND()	{ return m_hwnd; }
	LPCSTR	Get_Title() { return m_windowTitle; }

private:
	HINSTANCE	m_instance;			//登録時のウィンドウのインスタンスを登録しておく
	LPCSTR		m_className;		//ウィンドウクラスの名前を登録しておく
	LPCSTR		m_windowTitle;		//バーに表示する名前を保持しておく
	HWND		m_hwnd;				//ウィンドウハンドルのデータを保持しておく
	MSG			m_message;			//メッセージを保持しておく
};

#endif // !WINDOW_H_
