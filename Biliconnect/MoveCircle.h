#ifndef MOVECIRCLE_H_
#define MOVECIRCLE_H_

#include "Block.h"

class MoveCircle : public Block
{
public:
	MoveCircle() = delete;
	MoveCircle(BLOCKTYPE type, float Rot, float length, math::Float2 pos, math::Float2 size = { 120, 120 });// 速度とタイプと長さを入力

	void Update() override;

private:
	void CollisionAction() override;

	float  m_Vel;   // 速度
	math::Float2 m_Radius;	// 半径
	math::Float2 m_Origin;	// 原点	
	float  m_Angle; //
};
#endif

