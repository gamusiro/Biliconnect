/*=========================================================================
	Date : 2022/03/11(金)	PlayerManager.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "PlayerManager.h"
#include <vector>

#include "PlayerLeft.h"
#include "PlayerRight.h"

using namespace math;
using std::vector;

PlayerManager::PlayerManager()
{
	m_Player[static_cast<int>(PLAYERS::LEFT)].reset(new PlayerLeft());
	m_Player[static_cast<int>(PLAYERS::RIGHT)].reset(new PlayerRight());
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::Update()
{
	for (auto& it : m_Player)
	{
		it->Update();
	}
}

void PlayerManager::Draw()
{
	for (auto& it : m_Player)
	{
		it->Draw();
	}
}

math::Float2& PlayerManager::GetLeftPos()
{
	return m_Player[static_cast<int>(PLAYERS::LEFT)]->GetPos();
}

math::Float2& PlayerManager::GetRightPos()
{
	return m_Player[static_cast<int>(PLAYERS::RIGHT)]->GetPos();
}

math::Float2 PlayerManager::GetCenter()
{
	// 現在中心座標取得
	math::Float2 pos = (GetLeftPos() + GetRightPos()) * 0.5f;
	// 初期画面中心からの差分
	pos = pos - math::Float2(SCREEN_CENTER_X, SCREEN_SCROOL_Y);

	return pos;
}
