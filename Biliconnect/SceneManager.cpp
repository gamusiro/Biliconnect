/*=========================================================================
	Date : 2021/12/21(��)	SceneManager.cpp
		Author : ���ނ��邧
		Update :
=========================================================================*/
#include "Opening.h"
#include "Title.h"
#include "StageSelect.h"
#include "Game.h"
#include "GameOver.h"
#include "Result.h"
#include "Fade.h"

#include "SceneManager.h"

/*=============================================================================================
	�R���X�g���N�^
=============================================================================================*/
SceneManager::SceneManager()
	:currently(SCENE_TYPE::NONE),
	next(SCENE_TYPE::NONE),
	m_Scene(nullptr)
{
}

/*=============================================================================================
	�f�X�g���N�^
=============================================================================================*/
SceneManager::~SceneManager()
{
}

/*=============================================================================================
	����������
=============================================================================================*/
void SceneManager::Init(SCENE_TYPE type)
{
	currently = next = type;

	switch (currently)
	{
	case SCENE_TYPE::OPENING		:	m_Scene = new Opening();		break;
	case SCENE_TYPE::TITLE			:	m_Scene = new Title();			break;
	case SCENE_TYPE::STAGE_SELECT	:	m_Scene = new StageSelect();	break;
	case SCENE_TYPE::GAME			:	m_Scene = new Game();			break;
	case SCENE_TYPE::GAMEOVER		:	m_Scene = new GameOver();		break;
	case SCENE_TYPE::RESTART		:	m_Scene = new Game();			break;
	case SCENE_TYPE::RESULT			:	m_Scene = new Result();			break;
	default:
		break;
	}
	m_Scene->Init();
}

/*=============================================================================================
	�I������
=============================================================================================*/
void SceneManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
}

/*=============================================================================================
	�X�V����
=============================================================================================*/
void SceneManager::Update()
{
	m_Scene->Update();
	this->Check();
}

/*=============================================================================================
	�`�揈��
=============================================================================================*/
void SceneManager::Draw()
{
	m_Scene->Draw();
}

/*=============================================================================================
	���ɃV�[���̐ݒ菈��
=============================================================================================*/
void SceneManager::Set(SCENE_TYPE type)
{
	//�V�[�����ݒ肷��
	next = type;
}

/*=============================================================================================
	�V�[���`�F�b�N
=============================================================================================*/
void SceneManager::Check()
{
	//���X�^�[�g
	if (currently != SCENE_TYPE::RESTART && next == SCENE_TYPE::RESTART)
	{
		this->Uninit();
		this->Init(SCENE_TYPE::GAME);
	}
	//���݂̃V�[���ƑJ�ڐ悪�قȂ��Ă�����
	else if (currently != next)
	{
		this->Uninit();
		this->Init(next);
	}
}
	
