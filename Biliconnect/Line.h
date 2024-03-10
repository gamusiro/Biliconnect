/*=========================================================================
	Date : 2021/03/05(�y)	Line.h
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

	math::Float2& GetPointPosA() { return m_Start; }		// ��_A���W�擾
	math::Float2& GetPointPosB() { return m_End; }			// ��_B���W�擾

private:
	math::Float2&	m_StartPos;								// �n�_
	math::Float2	m_Start;								// �n�_
	math::Float2&	m_EndPos;								// �I�_
	math::Float2	m_End;									// �I�_
	math::Float2	m_DistanceSE;							// 2�_��X/Y����

	math::Float2	m_Pos = {};
	math::Float2	m_Size = { 5,5 };

	Texture			m_Tex;
	math::Float4	m_Color = { 1,1,0,1 };
	int m_Frame = 0;

};

#endif
