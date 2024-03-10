/*=========================================================================
	Date : 2021/12/21(火)	SceneManager.cpp
		Author : がむしるぉ
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
	コンストラクタ
=============================================================================================*/
SceneManager::SceneManager()
	:currently(SCENE_TYPE::NONE),
	next(SCENE_TYPE::NONE),
	m_Scene(nullptr)
{
}

/*=============================================================================================
	デストラクタ
=============================================================================================*/
SceneManager::~SceneManager()
{
}

/*=============================================================================================
	初期化処理
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
	終了処理
=============================================================================================*/
void SceneManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
}

/*=============================================================================================
	更新処理
=============================================================================================*/
void SceneManager::Update()
{
	m_Scene->Update();
	this->Check();
}

/*=============================================================================================
	描画処理
=============================================================================================*/
void SceneManager::Draw()
{
	m_Scene->Draw();
}

/*=============================================================================================
	次にシーンの設定処理
=============================================================================================*/
void SceneManager::Set(SCENE_TYPE type)
{
	//シーン先を設定する
	next = type;
}

/*=============================================================================================
	シーンチェック
=============================================================================================*/
void SceneManager::Check()
{
	//リスタート
	if (currently != SCENE_TYPE::RESTART && next == SCENE_TYPE::RESTART)
	{
		this->Uninit();
		this->Init(SCENE_TYPE::GAME);
	}
	//現在のシーンと遷移先が異なっていたら
	else if (currently != next)
	{
		this->Uninit();
		this->Init(next);
	}
}
	
