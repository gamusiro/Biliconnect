/*=========================================================================
	Date : 2021/04/08(‹à)	Pause.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef PAUSE_H_
#define PAUSE_H_

#include "GameCreateSystem.h"
#include <memory>

class PauseState;
class Game;

class Pause
{
public:
	enum class PAUSESTATE
	{
		SELECT,
		OPTION,
		STAGE,
		RESTART,
		MAX
	};

public:
	Pause(Game* game);
	~Pause();

	void Update();
	void Draw();

	void ChangeState(PAUSESTATE state);
	void ResetState();

private:
	Texture		Waku;
	PAUSESTATE m_State;
	std::unique_ptr<PauseState>	m_States[static_cast<int>(PAUSESTATE::MAX)];
};

#endif

