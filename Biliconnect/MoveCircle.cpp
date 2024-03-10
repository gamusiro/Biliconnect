#include "MoveCircle.h"
#include "Stage.h"
#include "Block.h"
#include "MoveBlock.h"

using namespace math;

MoveCircle::MoveCircle(BLOCKTYPE type, float Rot, float length, math::Float2 pos, math::Float2 size)
	: Block(type, pos, size)
{
	// ������
	m_Type = type;

	if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Create("enemy_green.png", 5, 2, 10);
	m_Vel = Rot;
	m_Color = { 1,1,1,1 };
	m_Angle = 0;

	m_Radius = Float2(length * 0.5f, length * 0.5f);
	m_Origin = Float2(pos.x, pos.y);
}

void MoveCircle::Update()
{
	if (m_Type == BLOCKTYPE::ENEMY)
	m_Tex.Update();

	// �p�x����ړ��p�̃x�N�g�������߂ĕ`����W�ɉ��Z����
	// �x���@�̊p�x���ʓx�@�ɕϊ�
	float radius = m_Angle * 3.14f / 180.0f;
	//radius *= -1;

	// �O�p�֐����g�p���A�~�̈ʒu������o���B
	float add_x = cos(radius) * m_Radius.x;
	float add_y = sin(radius) * m_Radius.y;

	// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
	m_Pos.x = m_Origin.x + add_x;
	m_Pos.y = m_Origin.y + add_y;

	// ������ς���
	m_Angle += m_Vel;
}

void MoveCircle::CollisionAction()
{
	//m_Color = { 0,0,0,1 };
}

