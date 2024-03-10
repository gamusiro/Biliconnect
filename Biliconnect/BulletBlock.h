#ifndef BULLETBLOCK_H_
#define BULLETBLOCK_H_

#include "Block.h"

class MoveChan;

struct Bullet
{
	math::Float2 Pos;
	math::Float2 Vel;
	math::Float2 Size;
};

class BulletBlock : public Block
{
public:
	BulletBlock() = delete;
	BulletBlock(BLOCKTYPE type, MoveChan& movechan, float vel, math::Float2 length, math::Float2 pos, math::Float2 size = { 120, 120 });// ���x�ƒ��������

	void Update() override;
	void Draw() override;
	void SetBullet();

private:
	void CollisionAction() override;

	float  m_Vel;   // ���x
	math::Float2 m_PosA;	// �n�_		
	math::Float2 m_PosB;	// �炷�Ƃ��ā[�����
	bool trigger;
	bool RE_B;
	int timer;
	Bullet m_Bullet;

	Texture m_BulletTex;

	MoveChan& m_MoveChan;

	constexpr static float VELOCITY = 5;
	constexpr static float SIZE_X = 1000;
	constexpr static float SIZE_Y = 600;
};
#endif

