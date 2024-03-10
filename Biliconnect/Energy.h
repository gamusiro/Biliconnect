/*=========================================================================
	Date : 2021/05/03(��)	Energy.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef ENERGY_H_
#define ENERGY_H_

#include "GameCreateSystem.h"

class Energy
{
private:
	constexpr static float SIZE = 100;

	constexpr static float COLOR_MAX = 1;
	constexpr static float COLOR_MIN = 0;
	constexpr static float COLOR_RATE = 0.025f;

private:
	math::Float2 m_Pos;
	math::Float4 m_Color;

	bool m_Active;	// �����t���O

	Texture m_Tex;
	Texture m_Texout;

public:
	Energy() = delete;
	// �`����W�w��-����
	Energy(math::Float2 pos, int num = 0);

	void Update();
	void Draw();

	// �������؂�ւ�
	void ActivateChange();

	bool GetActive() { return m_Active; }
};

#endif
