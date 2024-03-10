/*=========================================================================
	Date : 2021/03/05(“y)	PlayerRight.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef PLAYER_RIGHT_H_
#define PLAYER_RIGHT_H_

#include "Player.h"


class PlayerRight : public Player
{
public:
	PlayerRight();
	~PlayerRight() {}

	void Update()	override;
	void Draw()		override;

private:
	Texture			m_Tex2;
	int             m_Frame;
	math::Float4    m_Col;
};

#endif
