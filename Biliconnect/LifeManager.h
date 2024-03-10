/*=========================================================================
	Date : 2021/04/04(月)	LifeManager.h
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
	// ライフ描画位置(一番左側)
	LifeManager(math::Float2 pos);

	void Update();
	void Draw();

	// 戻り値：ライフ残量なし = true
	bool Damage();
	void Heal();
	int num = LIFE_NUM;
	int Get() { return num; }
};

#endif
