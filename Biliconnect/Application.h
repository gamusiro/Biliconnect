/*===========================================================================
	Date : 2022/02/05(�y)	Application.h
		Author	: ���ނ��邧
		Update	: 2022/02/11(��)
		Comment	: ���������ł������Ă邩�킩��Ȃ����x��wwww
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
	Application(HINSTANCE hInstance, int nCmdShow);	//�R���X�g���N�^
	~Application();									//�f�X�g���N�^

public:
	bool Init();			//����������
	void Uninit();			//�I������
	void Update();			//�X�V����
	void Draw();			//�`�揈��

public:
	bool		Close();			//�A�v���P�[�V�����̏I��

public:
	SceneManager* GetSceneManager();
	static HWND GetWindowHandle();	//�E�B���h�E�n���h���̎擾

public:
	static Window* GetWindow(bool Destroy = false);	//�A�v���P�[�V�����E�B���h�E�̐���

private:
	GraphicsManager*	m_GraphicsManager;
	SceneManager*		m_SceneManager;

private:
	friend GraphicsManager;
};

#endif // !APPLICATION_H_

