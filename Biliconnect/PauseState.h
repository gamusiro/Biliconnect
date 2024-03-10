/*=========================================================================
	Date : 2021/04/08(‹à)	PauseState.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef PAUSESTATE_H_
#define PAUSESTATE_H_

#include "GameCreateSystem.h"

class Pause;
class Game;

class PauseState
{
public:
	PauseState(Pause& pause, Game* game) : m_Pause(pause), m_Game(game){}

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Set() = 0;

protected:
	Pause&				m_Pause;
	Game*				m_Game;
	Texture				m_Tex;
	float				m_Pos;
	int					timer;
	bool				trigger;

	constexpr static int WAIT = 15;

	typedef enum {
		UP,
		DOWN,
		LEFT,
		RIGHT,
	}INPUT_DIRECTION;

	float m_DrawPos;
	INPUT_DIRECTION m_InputDirection;
};

#endif
