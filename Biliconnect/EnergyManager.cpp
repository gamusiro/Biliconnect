/*=========================================================================
	Date : 2021/05/03(‰Î)	EnergyManager.h
		Author : Mr.
		Update :
=========================================================================*/
#include "EnergyManager.h"

using namespace math;

EnergyManager::EnergyManager(math::Float2 pos)
	: m_Energy{ pos, {pos, 1}, {pos, 2} }
{
}

void EnergyManager::Update()
{
	for (int i = 0; i < m_Energy.size(); i++)
	{
		m_Energy[i].Update();
	}
}

void EnergyManager::Draw()
{
	for (int i = 0; i < m_Energy.size(); i++)
	{
		m_Energy[i].Draw();
	}
}

bool EnergyManager::Minus()
{
	int i;
	for (i = 0; i < m_Energy.size(); i++)
	{
		if (m_Energy[i].GetActive())
		{
			num -= 1;
			m_Energy[i].ActivateChange();
			if (i == m_Energy.size() - 1) return true;
			else break;
		}
	}
	return false;
}

void EnergyManager::Plus()
{
	num = ENERGY_NUM;

	if (!m_Energy[0].GetActive())	m_Energy[0].ActivateChange();
	if (!m_Energy[1].GetActive())	m_Energy[1].ActivateChange();
	if (!m_Energy[2].GetActive())	m_Energy[2].ActivateChange();
}
