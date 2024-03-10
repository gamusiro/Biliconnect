/*=========================================================================
	Date : 2021/12/21(��)	SceneManager.h
		Author : ���ނ��邧
		Update :
=========================================================================*/
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

//�V�[���̖��O
enum class SCENE_TYPE
{
	NONE,
	OPENING,
	TITLE,
	STAGE_SELECT,
	GAME,
	GAMEOVER,
	RESTART,
	RESULT
};

class SceneInterface;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	void Init(SCENE_TYPE type);
	void Uninit();
	void Update();
	void Draw();

public:
	void Set(SCENE_TYPE type);
	void Check();

private:
	SCENE_TYPE currently;
	SCENE_TYPE next;

private:
	SceneInterface* m_Scene;
};

#endif // !SCENEMANAGER_H_
