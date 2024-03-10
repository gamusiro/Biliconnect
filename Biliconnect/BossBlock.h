/*=========================================================================
	Date : 2021/05/26(��)	BossBlock.h
		Author : ��
		Update :
=========================================================================*/
#ifndef BOSSBLOCK_H_
#define BOSSBLOCK_H_

#include "GameCreateSystem.h"
#include "Stage.h"

class MoveChan;
class Bug;

class BossBlock
{
public:
	BossBlock() = delete;
	BossBlock(MoveChan& movechan);

	void Update();
	void Draw();

	void CheckCollision(MoveChan& movechan, Bug& bug);		// �Փ˔���

	int GetTimer() { return timer; }
	static math::Float2 Get() { return m_Pos; }
private:
	void CollisionAction();							// �Փˎ�����

	MoveChan& m_Movechan;

	static math::Float2	m_Pos;
	math::Float2	m_Size;
	math::Float2	m_ColSize;

	Texture			m_Tex;
	math::Float4	m_Color;
	float m_Rot;

	bool trigger;
	int  timer;
};
__declspec(selectany) math::Float2 BossBlock::m_Pos({ SCREEN_WIDTH / 2 , Stage::m_MoveMax - SCREEN_HEIGHT / 2 });
#endif
