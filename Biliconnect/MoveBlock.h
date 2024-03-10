#ifndef MOVEBLOCK_H_
#define MOVEBLOCK_H_

#include "Block.h"


class MoveBlock : public Block
{
public:
	MoveBlock() = delete;
	MoveBlock(BLOCKTYPE type, float vel, math::Float2 length, math::Float2 pos, math::Float2 size = { 120, 120 });// ���x�ƒ��������

	void Update() override;

private:
	void CollisionAction() override;

	float  m_Vel;   // ���x
	math::Float2 m_PosA;	// �n�_		
	math::Float2 m_PosB;	// �炷�Ƃ��ā[�����
};
#endif

