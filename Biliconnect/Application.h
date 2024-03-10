/*===========================================================================
	Date : 2022/02/05(土)	Application.h
		Author	: がむしるぉ
		Update	: 2022/02/11(金)
		Comment	: もう自分でも何してるかわからないレベルwwww
===========================================================================*/
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Window.h"
#include "BGMOption.h"

class GraphicsManager;
class SceneManager;
class BGMOption;

class Application
{
public:
	Application(HINSTANCE hInstance, int nCmdShow);	//コンストラクタ
	~Application();									//デストラクタ

public:
	bool Init();			//初期化処理
	void Uninit();			//終了処理
	void Update();			//更新処理
	void Draw();			//描画処理

public:
	bool		Close();			//アプリケーションの終了

public:
	SceneManager* GetSceneManager();
	static HWND GetWindowHandle();	//ウィンドウハンドルの取得

public:
	static Window* GetWindow(bool Destroy = false);	//アプリケーションウィンドウの生成

private:
	GraphicsManager*	m_GraphicsManager;
	SceneManager*		m_SceneManager;

private:
	friend GraphicsManager;
};

#endif // !APPLICATION_H_

