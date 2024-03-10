#ifndef DANGERBLOCK_H_
#define DANGERBLOCK_H_

#include "Block.h"


class DangerBlock : public Block
{
public:
	DangerBlock() = delete;
	DangerBlock(BLOCKTYPE type, math::Float2 pos, math::Float2 size = { 100, 100 }, float vel = BASE_SPEED);

	void Update() override;

private:
	void CollisionAction() override;

private:
	float m_Vel;
	constexpr static float BASE_SPEED = 2.3f;	// äÓèÄë¨ìx // ÇSÅCÇT
};
#endif

