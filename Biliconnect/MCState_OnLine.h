/*=========================================================================
	Date : 2021/04/05(火)	MCState_OnLine.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef MCSTATE_O_H_
#define MCSTATE_O_H_

#include "MCState.h"
class MoveChan;
class Line;

class MCState_OnLine : public MCState
{
public:
	MCState_OnLine(MoveChan& movechan, Line& line);

	void Update() override;
	void ChangeState() override;
	void Set() override;

	static bool GetL() { return left; }
	static bool GetR() { return right; }

private:
	math::Float2&	m_TargetPosA;			// 線形補完始点
	math::Float2&	m_TargetPosB;			// 線形補完終点
	math::Float2	m_DistanceAB;			// 2点間X/Y距離

	float			m_Place = 0;			// 媒介変数
	int				DIRECTION = 1;			// 移動方向
	float			m_AddSpeed = 0;			// ダッシュ

	static bool right;
	static bool left;

	float m_Addvel = 0;

	bool m_Left;
	bool m_Right;

	bool trigger;// 動けるかどうかのフラグ

private:
	constexpr static float BASE_SPEED = 10.f;	// 基準速度
	constexpr static float DASH_SPEED = .075f;	// ダッシュ速度
	constexpr static float BACK_SPEED = .5f;	// 戻る速度
	constexpr static float VIB_POW = 14000.0f;	// 振動の強さ
};
__declspec(selectany) bool MCState_OnLine::right(false);
__declspec(selectany) bool MCState_OnLine::left(false);
#endif
