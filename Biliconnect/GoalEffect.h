#pragma once
#include <memory>
#include "GameCreateSystem.h"

class GoalEffect
{
protected:
	enum {
		USING_TEX,
		TEX_1,
		TEX_2,
		TEX_3,
		TEX_MAX,
	};

	static const int RESET_SIZE = 80;

	static const int MAX = 600;//ëçÉOÉãÅ[Évêî
	Texture m_Tex[TEX_MAX];
	math::Float2 m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
	math::Float4 m_Col[MAX];
	bool m_Use[MAX];
	int m_Rot[MAX];
	int m_Frame, m_FrameSinceToSet[MAX];

	//
	static const int ROT_INDEX_MAX = 360;
	int m_RotIndex;

public:
	GoalEffect();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(math::Float2 pos);

private:
	float m_Rad;
	float m_Vol;
	bool trigger;
};

