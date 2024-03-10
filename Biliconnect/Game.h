/*=========================================================================
	Date : 2021/12/21(火)	Game.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef GAME_H_
#define GAME_H_

#include <memory>
#include "GameCreateSystem.h"
#include "SceneInterface.h"

class Stage;
class Pause;

class Game : public SceneInterface
{
public:
	enum class GAMESTATE
	{
		PLAY,
		PAUSE
	};

public:
	Game();
	~Game();

	void Init();	//初期化処理
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Draw();	//描画処理

	static void SetGameState(int state) { m_GameState = state; }
	static int GetGameState() { return m_GameState; }

private:
	std::unique_ptr<Stage>  m_Stage;
	std::unique_ptr<Pause>	m_Pause;
	static int		m_GameState;

private:
	Texture* m_Texture;
	BGM* m_BGM;

	constexpr static int MASTER_VOLUME = 6;	// マスターボリューム
};
__declspec(selectany) int Game::m_GameState(0);

#endif // !GAME_H_

