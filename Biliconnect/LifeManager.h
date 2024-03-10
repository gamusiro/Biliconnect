/*=========================================================================
	Date : 2021/04/04(��)	LifeManager.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef LIFEM_H_
#define LIFEM_H_

#include <array>
#include "GameCreateSystem.h"
#include "Life.h"

class LifeManager
{
private:
	constexpr static int LIFE_NUM = 3;
private:
	std::array<Life, LIFE_NUM> m_Life;

public:
	LifeManager() = delete;
	// ���C�t�`��ʒu(��ԍ���)
	LifeManager(math::Float2 pos);

	void Update();
	void Draw();

	// �߂�l�F���C�t�c�ʂȂ� = true
	bool Damage();
	void Heal();
	int num = LIFE_NUM;
	int Get() { return num; }
};

#endif
