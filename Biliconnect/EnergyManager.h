/*=========================================================================
	Date : 2021/05/03(��)	EnergyManager.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef ENERGYM_H_
#define ENERGYM_H_

#include <array>
#include "GameCreateSystem.h"
#include "Energy.h"

class EnergyManager
{
private:
	constexpr static int ENERGY_NUM = 3;
private:
	std::array<Energy, ENERGY_NUM> m_Energy;

public:
	EnergyManager() = delete;
	// �G�l���M�[�`��ʒu(��ԍ���)
	EnergyManager(math::Float2 pos);

	void Update();
	void Draw();

	// �߂�l�F�G�l���M�[�c�ʂȂ� = true
	bool Minus();
	void Plus();
	int num = ENERGY_NUM;
	int Get() { return num; };
};

#endif
