#include "MoveCircle.h"
#include "Stage.h"
#include "Block.h"
#include "MoveBlock.h"

using namespace math;

MoveCircle::MoveCircle(BLOCKTYPE type, float Rot, float length, math::Float2 pos, math::Float2 size)
	: Block(type, pos, size)
{
	// 初期化
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

	// 角度から移動用のベクトルを求めて描画座標に加算する
	// 度数法の角度を弧度法に変換
	float radius = m_Angle * 3.14f / 180.0f;
	//radius *= -1;

	// 三角関数を使用し、円の位置を割り出す。
	float add_x = cos(radius) * m_Radius.x;
	float add_y = sin(radius) * m_Radius.y;

	// 結果ででた位置を中心位置に加算し、それを描画位置とする
	m_Pos.x = m_Origin.x + add_x;
	m_Pos.y = m_Origin.y + add_y;

	// 向きを変える
	m_Angle += m_Vel;
}

void MoveCircle::CollisionAction()
{
	//m_Color = { 0,0,0,1 };
}

