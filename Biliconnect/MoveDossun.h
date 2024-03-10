#ifndef MOVEDOSSUN_H_
#define MOVEDOSSUN_H_

#include "Block.h"

class MoveChan;

class MoveDossun : public Block
{
public:
	MoveDossun() = delete;
	MoveDossun(BLOCKTYPE type, math::Float2& movechanpos, float movechansize, math::Float2 length, math::Float2 pos, math::Float2 size = { 120, 120 });// 速度と長さを入力

	void Update() override;

private:
	void CollisionAction() override;

	float  m_Vel;   // 速度
	math::Float2 m_PosA;	// 始点		
	math::Float2 m_PosB;	// らすとすてーしょん
	bool trigger;
	
	math::Float2& m_MoveChanPos;
	float  m_MoveChanSize;

	constexpr static float BACKSPD = 5.0f;
};
#endif

