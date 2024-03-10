/*=========================================================================
	Date : 2022/03/11(金)	PlayerManager.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef PLAYERMANAGAR_H_
#define PLAYERMANAGAR_H_

#include <array>
#include <memory>
#include "GameCreateSystem.h"
class Player;

class PlayerManager
{
private:
	enum class PLAYERS
	{
		LEFT = 0,
		RIGHT,
		MAX
	};

private:
	std::array< std::unique_ptr<Player>, static_cast<int>(PLAYERS::MAX)> m_Player;
	
	constexpr static float SCREEN_CENTER_X = SCREEN_WIDTH  / 2;	// 初期画面中心X座標
	constexpr static float SCREEN_CENTER_Y = SCREEN_HEIGHT / 2;	// 初期画面中心Y座標 

	constexpr static float SCREEN_SCROOL_Y = SCREEN_HEIGHT / 3;	// 手前スクロールY座標 
		
public:
	PlayerManager();
	~PlayerManager();

	void Update();
	void Draw();

	math::Float2& GetLeftPos();
	math::Float2& GetRightPos();

	math::Float2 GetCenter();
};

#endif
