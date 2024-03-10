#ifndef BLINKBLOCK_H_
#define BLINKBLOCK_H_

#include "Block.h"


class BlinkBlock : public Block
{
public:
	BlinkBlock() = delete;
	BlinkBlock(BLOCKTYPE type, float interval, math::Float2 pos, int num, int color);

	void Update() override;

private:
	void CollisionAction() override;

private:
	int timer;
	float m_Interval;
	float m_Rad;
	Texture		EffectTex;

	constexpr static int INTERVAL = 60;
	constexpr static float ADDRAD = 0.005f;
	constexpr static float LIMIT = 1;
};
#endif

