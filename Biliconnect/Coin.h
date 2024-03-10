#ifndef COIN_H_
#define COIN_H_

#include "Block.h"


class Coin : public Block
{
public:
	Coin() = delete;
	Coin(BLOCKTYPE type, math::Float2 pos, int number);

	void Update() override;

	static int	Get() { return coinnum; }
	static void	Reset() { coinnum = 0; }

private:
	void CollisionAction() override;

	bool trigger;
	int m_Number;// 何枚目か
	static int coinnum;// コインの取得枚数
};
__declspec(selectany) int Coin::coinnum(0);

#endif

