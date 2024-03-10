/*=========================================================================
	Date : 2022/05/11(êÖ)	EffectManager.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef EFFECTMANAGER_H_
#define EFFECTMANAGER_H_

#include "GameCreateSystem.h"
#include <memory>
#include <vector>

class MoveChanEffect;

class EffectManager
{
public:
	EffectManager() = delete;
	EffectManager(math::Float2& movechan);
	~EffectManager();

	void Update();
	void Draw();

private:
	std::vector<std::unique_ptr<MoveChanEffect>> m_Effects;
};

#endif
