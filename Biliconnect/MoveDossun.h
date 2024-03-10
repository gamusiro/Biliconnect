#ifndef MOVEDOSSUN_H_
#define MOVEDOSSUN_H_

#include "Block.h"

class MoveChan;

class MoveDossun : public Block
{
public:
	MoveDossun() = delete;
	MoveDossun(BLOCKTYPE type, math::Float2& movechanpos, float movechansize, math::Float2 length, math::Float2 pos, math::Float2 size = { 120, 120 });// ���x�ƒ��������

	void Update() override;

private:
	void CollisionAction() override;

	float  m_Vel;   // ���x
	math::Float2 m_PosA;	// �n�_		
	math::Float2 m_PosB;	// �炷�Ƃ��ā[�����
	bool trigger;
	
	math::Float2& m_MoveChanPos;
	float  m_MoveChanSize;

	constexpr static float BACKSPD = 5.0f;
};
#endif

