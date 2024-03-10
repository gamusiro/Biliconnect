#pragma once
#include "GameCreateSystem.h"

class Tutorial
{
public:
	enum
	{
		TUTO_1,
		TUTO_2,
		TUTO_3,
		TUTO_4,
		TUTO_5,
		TUTO_6,
		TUTO_7,
		TUTO_8,
		TUTO_9,
		TUTO_10,
		TUTO_MAX
	};

	Tutorial();
	~Tutorial();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static bool Get() { return trigger; }

private:
	Texture m_Tuto[TUTO_MAX];
	math::Float2 m_Pos[TUTO_MAX];
	math::Float2 m_Vel[TUTO_MAX];
	math::Float2 m_Size[TUTO_MAX];
	math::Float4 m_Color[TUTO_MAX];
	int m_timer;
	int num;
	static bool trigger;
};
__declspec(selectany) bool Tutorial::trigger(false);

