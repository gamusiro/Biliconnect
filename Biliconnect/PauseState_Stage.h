/*=========================================================================
	Date : 2021/04/08(‹à)	PauseState_Stage.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef PAUSESTATE_STAGE_H_
#define PAUSESTATE_STAGE_H_

#include "PauseState.h"

class Pause;
class Game;

class PauseState_Stage : public PauseState
{
public:
	PauseState_Stage(Pause& pause, Game* game);

	void Update() override;
	void Draw() override;
	void Set() override;

	Texture		m_Tex;
	Texture		m_Tex2;
	Texture		m_Return;
	Texture		m_Mouse;
};

#endif

