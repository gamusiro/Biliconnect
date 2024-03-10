/*=========================================================================
	Date : 2021/03/05(土)	Line.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef LINE_H_
#define LINE_H_

#include "GameCreateSystem.h"

class Line
{
public:
	Line(math::Float2& startpos, math::Float2& endpos);

	void Update();
	void Draw();

	math::Float2& GetPointPosA() { return m_Start; }		// 基準点A座標取得
	math::Float2& GetPointPosB() { return m_End; }			// 基準点B座標取得

private:
	math::Float2&	m_StartPos;								// 始点
	math::Float2	m_Start;								// 始点
	math::Float2&	m_EndPos;								// 終点
	math::Float2	m_End;									// 終点
	math::Float2	m_DistanceSE;							// 2点間X/Y距離

	math::Float2	m_Pos = {};
	math::Float2	m_Size = { 5,5 };

	Texture			m_Tex;
	math::Float4	m_Color = { 1,1,0,1 };
	int m_Frame = 0;

};

#endif
