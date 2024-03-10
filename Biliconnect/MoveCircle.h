#ifndef MOVECIRCLE_H_
#define MOVECIRCLE_H_

#include "Block.h"

class MoveCircle : public Block
{
public:
	MoveCircle() = delete;
	MoveCircle(BLOCKTYPE type, float Rot, float length, math::Float2 pos, math::Float2 size = { 120, 120 });// ���x�ƃ^�C�v�ƒ��������

	void Update() override;

private:
	void CollisionAction() override;

	float  m_Vel;   // ���x
	math::Float2 m_Radius;	// ���a
	math::Float2 m_Origin;	// ���_	
	float  m_Angle; //
};
#endif

