/*=========================================================================
	Date : 2022/05/11(êÖ)	EffectManager.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "EffectManager.h"
#include "MoveChanEffect.h"

EffectManager::EffectManager(math::Float2& movechan)
{
	m_Effects.push_back(std::make_unique<MoveChanEffectTail>(movechan));
	m_Effects.push_back(std::make_unique<MoveChanEffectBall>(movechan));
	m_Effects.push_back(std::make_unique<MoveChanEffectCircle>(movechan));
	m_Effects.push_back(std::make_unique<MoveChanEffectSpark>(movechan));
}

EffectManager::~EffectManager()
{
}

void EffectManager::Update()
{
	for (auto& it : m_Effects)
	{
		it->Update();
	}
}

void EffectManager::Draw()
{
	for (auto& it : m_Effects)
	{
		it->Draw();
	}
}
