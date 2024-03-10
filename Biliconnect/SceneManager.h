/*=========================================================================
	Date : 2021/12/21(火)	SceneManager.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef SCENEMANAGER_H_
#define SCENEMANAGER_H_

//シーンの名前
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
