#ifndef RUSHBLOCK_H_
#define RUSHBLOCK_H_

#include "Block.h"

class MoveChan;

class RushBlock : public Block
{
public:
	RushBlock() = delete;
	RushBlock(BLOCKTYPE type, MoveChan& movechan, math::Float2 pos, math::Float2 size = { 120, 120 });// 速度と長さを入力

	void Update() override;
	void Draw() override;

private:
	void Set();
	void CollisionAction() override;

	math::Float2  m_Vel;   // 速度
	bool	trigger;

	MoveChan& m_MoveChan;

	constexpr static float VELOCITY = 60;
	constexpr static float SIZE_X = SCREEN_WIDTH * 2;
	constexpr static float SIZE_Y = SCREEN_HEIGHT - 200;
};
#endif

