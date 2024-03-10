/*===========================================================================
	Date : 2022/02/05(�y)	Application.cpp
		Author	: ���ނ��邧
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
	�R���X�g���N�^
=============================================================================================*/
Application::Application(HINSTANCE hInstance, int nCmdShow)
	:m_GraphicsManager(new GraphicsManager()),
	m_SceneManager(new SceneManager())
{
	Window* window = this->GetWindow();
	window->Init(hInstance, "ApplicationWindow");
	window->Create("�r���R�l�N�g");
	window->Show(nCmdShow);

#ifndef _DEBUG
	ShowCursor(false);

#endif // _DEBUG


	Input::Init(hInstance, window);
}

/*=============================================================================================
	�f�X�g���N�^
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
	����������
=============================================================================================*/
bool Application::Init()
{
	//Com�̏���������
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
	�I������
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

	//Com�̏I������
	CoUninitialize();
}

/*=============================================================================================
	�X�V����
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
	�`�揈��
=============================================================================================*/
void Application::Draw()
{
	if (Movie::GetState() != MOVIE_STATE::RUN)
	{
		m_GraphicsManager->Clear();			//�`��̃N���A����
		m_GraphicsManager->Translate2D();
		m_GraphicsManager->SetDepthEnable(false);

		m_SceneManager->Draw();
		Fade::Draw();

		m_GraphicsManager->Present();	//�o�b�t�@�̐؂�ւ�����
	}
}

/*=============================================================================================
	�A�v���P�[�V�����̏�Ԏ擾
=============================================================================================*/
bool Application::Close()
{
	//�A�v���P�[�V�������I�����邩
	if (this->GetWindow()->Dispatcher())
		return false;

	//�A�v���P�[�V�����̏I��
	return true;
}

/*=============================================================================================
	�V�[���̎擾����
=============================================================================================*/
SceneManager* Application::GetSceneManager()
{
	return m_SceneManager;
}

/*=============================================================================================
	�E�B���h�E�n���h���̎擾����
=============================================================================================*/
HWND Application::GetWindowHandle()
{
	return GetWindow()->Get_HWND();
}

/*=============================================================================================
	�E�B���h�E�̎擾����
=============================================================================================*/
Window* Application::GetWindow(bool Destroy)
{
	static Window* ret;

	if (!ret)
	{//�������m��
		ret = new Window();
	}

	if (Destroy)
	{//���������
		delete ret;
		ret = nullptr;
	}

	return ret;
}
