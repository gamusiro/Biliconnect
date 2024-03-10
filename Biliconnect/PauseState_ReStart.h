/*=========================================================================
	Date : 2021/04/29(‹à)	PauseState_ReStart.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef PAUSESTATE_RESTART_H_
#define PAUSESTATE_RESTART_H_

#include "PauseState.h"

class Pause;
class Game;

class PauseState_ReStart : public PauseState
{
public:
	PauseState_ReStart(Pause& pause, Game* game);

	void Update() override;
	void Draw() override;
	void Set() override;

	Texture		m_Tex;
	Texture		m_Tex2;
	Texture		m_Return;
	Texture		m_Mouse;
};

#endif

