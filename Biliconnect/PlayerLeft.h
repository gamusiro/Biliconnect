/*=========================================================================
	Date : 2021/03/05(“y)	PlayerLeft.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef PLAYER_LEFT_H_
#define PLAYER_LEFT_H_

#include "Player.h"


class PlayerLeft : public Player
{
public:
	PlayerLeft();
	~PlayerLeft(){}

	void Update()	override;
	void Draw()		override;

private:
	Texture			m_Tex2;
	int             m_Frame;
	math::Float4    m_Col;

};

#endif
