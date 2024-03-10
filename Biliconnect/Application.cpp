/*===========================================================================
	Date : 2022/02/05(土)	Application.cpp
		Author	: がむしるぉ
		Update	:
		Comment	:
===========================================================================*/
#include "SceneManager.h"
#include "Input.h"
#include "GraphicsManager.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "Controller.h"
#include "SceneManager.h"
#include "Fade.h"
#include "Movie.h"
#include "SaveManager.h"
#include "BGMOption.h"

#include "Application.h"


/*=============================================================================================
	コンストラクタ
=============================================================================================*/
Application::Application(HINSTANCE hInstance, int nCmdShow)
	:m_GraphicsManager(new GraphicsManager()),
	m_SceneManager(new SceneManager())
{
	Window* window = this->GetWindow();
	window->Init(hInstance, "ApplicationWindow");
	window->Create("ビリコネクト");
	window->Show(nCmdShow);

#ifndef _DEBUG
	ShowCursor(false);

#endif // _DEBUG


	Input::Init(hInstance, window);
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
Application::~Application()
{
	Input::Uninit();
	ShowCursor(true);
	delete m_SceneManager;
	delete m_GraphicsManager;
	this->GetWindow(true);
}

/*=============================================================================================
	初期化処理
=============================================================================================*/
bool Application::Init()
{
	//Comの初期化処理
	HRESULT ret = CoInitializeEx(nullptr, COINIT::COINIT_MULTITHREADED);
	if (FAILED(ret))								return false;

	if (!m_GraphicsManager->Init())					return false;
	if (!Sprite::Init(m_GraphicsManager))			return false;
	if (!TextureManager::Init(m_GraphicsManager))	return false;
	if (!SoundManager::Init())						return false;
	Controller::Init();
	Fade::Init(this);
	Movie::Init(this->GetWindow()->Get_HWND());
	SaveManager::Load();

#ifdef _DEBUG
	m_SceneManager->Init(SCENE_TYPE::STAGE_SELECT);
#else
	m_SceneManager->Init(SCENE_TYPE::OPENING);
#endif

	return true;
}


/*=============================================================================================
	終了処理
=============================================================================================*/
void Application::Uninit()
{
	m_SceneManager->Uninit();

	SaveManager::Write();
	Movie::Uninit();
	Fade::Uninit();
	Controller::Uninit();
	SoundManager::Uninit();
	TextureManager::Uninit();
	Sprite::Uninit();
	m_GraphicsManager->Uninit();
	this->GetWindow()->Uninit();

	//Comの終了処理
	CoUninitialize();
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void Application::Update()
{
	Input::Update();
	Controller::Update();

	m_SceneManager->Update();
	Fade::Update();
	Movie::Update();
}

/*=============================================================================================
	描画処理
=============================================================================================*/
void Application::Draw()
{
	if (Movie::GetState() != MOVIE_STATE::RUN)
	{
		m_GraphicsManager->Clear();			//描画のクリア処理
		m_GraphicsManager->Translate2D();
		m_GraphicsManager->SetDepthEnable(false);

		m_SceneManager->Draw();
		Fade::Draw();

		m_GraphicsManager->Present();	//バッファの切り替え処理
	}
}

/*=============================================================================================
	アプリケーションの状態取得
=============================================================================================*/
bool Application::Close()
{
	//アプリケーションを終了するか
	if (this->GetWindow()->Dispatcher())
		return false;

	//アプリケーションの終了
	return true;
}

/*=============================================================================================
	シーンの取得処理
=============================================================================================*/
SceneManager* Application::GetSceneManager()
{
	return m_SceneManager;
}

/*=============================================================================================
	ウィンドウハンドルの取得処理
=============================================================================================*/
HWND Application::GetWindowHandle()
{
	return GetWindow()->Get_HWND();
}

/*=============================================================================================
	ウィンドウの取得処理
=============================================================================================*/
Window* Application::GetWindow(bool Destroy)
{
	static Window* ret;

	if (!ret)
	{//メモリ確保
		ret = new Window();
	}

	if (Destroy)
	{//メモリ解放
		delete ret;
		ret = nullptr;
	}

	return ret;
}
