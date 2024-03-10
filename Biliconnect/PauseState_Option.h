/*=========================================================================
	Date : 2021/04/08(‹à)	PauseState_Option.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef PAUSESTATE_OPTION_H_
#define PAUSESTATE_OPTION_H_

#include "PauseState.h"

class Pause;
class Game;
class BGMOption;

class PauseState_Option : public PauseState
{
public:
	PauseState_Option(Pause& pause, Game* game);

	void Update() override;
	void Draw() override;
	void Set() override;

	Texture		m_Tex;
	Texture		m_Tex2;
	Texture		m_Tex3;
	Texture		m_Mouse;

	BGMOption*	m_BGMOption;
};

#endif

