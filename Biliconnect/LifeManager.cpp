/*=========================================================================
	Date : 2021/04/04(ŒŽ)	LifeManager.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "LifeManager.h"

using namespace math;

LifeManager::LifeManager(math::Float2 pos)
	: m_Life{ pos, {pos, 1}, {pos, 2} }
{
}

void LifeManager::Update()
{
	for (int i = 0; i < m_Life.size(); i++)
	{
		m_Life[i].Update();
	}
}

void LifeManager::Draw()
{
	for (int i = 0; i < m_Life.size(); i++)
	{
		m_Life[i].Draw();
	}
}

bool LifeManager::Damage()
{
	int i;
	for (i = 0; i < m_Life.size(); i++)
	{
		if (m_Life[i].GetActive())
		{
			num -= 1;
			m_Life[i].ActivateChange();
			if (i == m_Life.size() - 1) return true;
			else break;
		}
	}
	return false;
}

void LifeManager::Heal()
{
	/*for (int i = 0; i < m_Life.size(); i++)
	{
		if (m_Life[i].GetActive())
		{
			m_Life[i].ActivateChange();
			break;
		}
	}*/

	if(num < 3)
	num = num + 1;

	if (!m_Life[0].GetActive() && m_Life[1].GetActive())	m_Life[0].ActivateChange();
	if (!m_Life[1].GetActive() && m_Life[2].GetActive())	m_Life[1].ActivateChange();
	/*if (!m_Life[2].GetActive())	m_Life[2].ActivateChange();*/
}
