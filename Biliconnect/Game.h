/*=========================================================================
	Date : 2021/12/21(��)	Game.h
		Author : ���ނ��邧
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

	void Init();	//����������
	void Uninit();	//�I������
	void Update();	//�X�V����
	void Draw();	//�`�揈��

	static void SetGameState(int state) { m_GameState = state; }
	static int GetGameState() { return m_GameState; }

private:
	std::unique_ptr<Stage>  m_Stage;
	std::unique_ptr<Pause>	m_Pause;
	static int		m_GameState;

private:
	Texture* m_Texture;
	BGM* m_BGM;

	constexpr static int MASTER_VOLUME = 6;	// �}�X�^�[�{�����[��
};
__declspec(selectany) int Game::m_GameState(0);

#endif // !GAME_H_

