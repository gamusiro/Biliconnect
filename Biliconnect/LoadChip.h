/*=========================================================================
	Date : 2021/04/30(ã‡)	LoadChip.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef LOAD_H_
#define LOAD_H_

#include <vector>
#include <memory>
#include "GameCreateSystem.h"

class Block;
class MoveChan;

class LoadChip
{
public:
	std::vector<std::unique_ptr<Block>> LoadChips(int num, MoveChan& mc);
	float GetStageY(void);

private:
	constexpr static int CHIP_NUMX = 16; // â°É`ÉbÉvêî
	constexpr static int FACTORY_NUM = 17;

	std::vector<int> stacker;
};

#endif
