/*=========================================================================
	Date : 2021/03/17(–Ø)	GameObject.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef GAMAOBJECT_H_
#define GAMAOBJECT_H_

#include "GameCreateSystem.h"

class GameObject
{
public:
	GameObject() = delete;
	GameObject(math::Float2 pos, math::Float2 size, math::Float4 color = { 1,1,1,1 })
	: m_Pos(pos), m_Size(size), m_Color(color) {}
	~GameObject(){}

	virtual void Update() = 0;
	virtual void Draw() = 0;

	math::Float2 GetPos()  { return m_Pos; }
	math::Float2 GetSize() { return m_Size; }


public:
	constexpr static float Chipsize = 120;
	constexpr static float Offset	= Chipsize / 2;

protected:
	math::Float2	m_Pos;
	math::Float2	m_Size;

	Texture			m_Tex;
	math::Float4	m_Color;
	float m_Rot;
};

#endif
