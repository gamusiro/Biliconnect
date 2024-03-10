#ifndef MOVEBLOCK_H_
#define MOVEBLOCK_H_

#include "Block.h"


class MoveBlock : public Block
{
public:
	MoveBlock() = delete;
	MoveBlock(BLOCKTYPE type, float vel, math::Float2 length, math::Float2 pos, math::Float2 size = { 120, 120 });// 速度と長さを入力

	void Update() override;

private:
	void CollisionAction() override;

	float  m_Vel;   // 速度
	math::Float2 m_PosA;	// 始点		
	math::Float2 m_PosB;	// らすとすてーしょん
};
#endif

