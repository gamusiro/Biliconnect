#pragma once

#include <memory>
#include "GameCreateSystem.h"

class DefeatEffect
{
protected:
	static const int GROUP = 20;//総グループ数
	static const int DEBRIS = 400;//1グループごとの破片の数
	static const int RESET_SIZE = 100;//リセットサイズ

	Texture m_Tex[GROUP][DEBRIS];
	math::Float2 m_Pos[GROUP][DEBRIS], m_Vel[GROUP][DEBRIS], m_Size[GROUP][DEBRIS];
	math::Float4 m_Col[GROUP][DEBRIS];
	bool m_GroupUse[GROUP], m_Use[GROUP][DEBRIS], m_SecondGroupFlag[GROUP][DEBRIS];//二陣を呼ぶフラグ
	int m_Degree[GROUP][DEBRIS];
	int m_FrameToSet[GROUP][DEBRIS], m_FrameToBeFalse[GROUP][DEBRIS];
	bool m_Flag;



public:
	DefeatEffect();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(math::Float2 pos);


};

class DefeatEffect2
{
private:
	static const int GROUP = 20;

	Texture      m_Tex[GROUP];
	math::Float2 m_Pos[GROUP], m_Size[GROUP];
	math::Float4 m_Col[GROUP];
	bool         isUsing[GROUP];
	int          m_FrameSinceToSet[GROUP];
	int          m_Rot[GROUP];

public:
	DefeatEffect2();
	void Update();
	void Draw();
	void Set(math::Float2 pos);
};



class DefeatEffect3
{
private:

	Texture             m_Tex;
	math::Float4	    m_Color;
	math::Float2	    m_Pos = { SCREEN_WIDTH * 1.0f,SCREEN_HEIGHT * 1.0f };
	math::Float2	    m_Size = { SCREEN_WIDTH,SCREEN_HEIGHT };
	const float         m_AlphaMax = 0.4f;
	int                 m_Frame = 0;
	bool                trigger;
public:
	DefeatEffect3();
	~DefeatEffect3();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set();
};




class CharacterEffect
{
private:

#define   PI  3.14159265358f

	enum {
		GOOD_1,
		GOOD_2,
		EXCELLENT_1,
		EXCELLENT_2,
		AMAZING_1,
		AMAZING_2,
		MAX,
	};

	typedef enum {
		NONE,
		GOOD,
		EXCELLENT,
		AMAZING,
	}CHARACTER;



	Texture             m_Tex[MAX];
	math::Float4	    m_Color[MAX];
	math::Float2	    m_Pos[MAX], m_Vel[MAX], m_Size[MAX];
	const float         m_AlphaMax = 0.5f;
	int                 m_Frame[MAX];
	bool                m_Use[MAX];
	int                 m_Cnt;

	
	CHARACTER AppearingCharacter;

public:
	CharacterEffect();
	~CharacterEffect();
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Set(math::Float2 pos);
};

