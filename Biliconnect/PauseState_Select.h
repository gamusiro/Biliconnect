/*=========================================================================
	Date : 2021/04/08(‹à)	PauseState_Select.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef PAUSESTATE_SELECT_H_
#define PAUSESTATE_SELECT_H_

#include "GameCreateSystem.h"
#include "PauseState.h"

class Pause;
class Game;

class PauseState_Select : public PauseState
{
public:
	PauseState_Select(Pause& pause, Game* game);

	void Update() override;
	void Draw() override;
	void Set() override;

	Texture		m_Tex;
	Texture		m_Tex2;
	Texture		m_Tex3;
	Texture		m_Tex4;
	Texture		m_Mouse;


};

#endif

