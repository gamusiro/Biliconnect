#ifndef RUSHBLOCK_H_
#define RUSHBLOCK_H_

#include "Block.h"

class MoveChan;

class RushBlock : public Block
{
public:
	RushBlock() = delete;
	RushBlock(BLOCKTYPE type, MoveChan& movechan, math::Float2 pos, math::Float2 size = { 120, 120 });// ‘¬“x‚Æ’·‚³‚ð“ü—Í

	void Update() override;
	void Draw() override;

private:
	void Set();
	void CollisionAction() override;

	math::Float2  m_Vel;   // ‘¬“x
	bool	trigger;

	MoveChan& m_MoveChan;

	constexpr static float VELOCITY = 60;
	constexpr static float SIZE_X = SCREEN_WIDTH * 2;
	constexpr static float SIZE_Y = SCREEN_HEIGHT - 200;
};
#endif

