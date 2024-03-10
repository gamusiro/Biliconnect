/*=========================================================================
	Date : 2021/04/30(金)	LoadChip.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "LoadChip.h"

#include <iostream>
#include <vector>
#include "FileIO.h"

#include "Stage.h"
#include "BlockFactory.h"

std::vector<std::unique_ptr<Block>> LoadChip::LoadChips(int num, MoveChan& mc)
{
	// 計算結果を格納する
	{
		std::string buffer;
		std::string filename = "Material/Data/" + std::to_string(StageNum::Get()) + ".csv";
		FileIO file(buffer, filename);

		int currentData = 0;
		for (size_t i = 0; i < buffer.size(); i++)
		{
			if (buffer[i] == ',')
			{// カンマがあるときデータを確定する
				stacker.push_back(currentData);
				currentData = 0;
			}
			else if (buffer[i] == '\r')
			{// \rは行の最後の文字の後ろにあるのでこれを基準に使う
				stacker.push_back(currentData);
				currentData = 0;
			}
			else if (buffer[i] == '\n')
			{// 改行文字は無視する(これをカウントすれば行数がわかる)
			}
			else
			{// 数値データの場合は数値に変換していく(自力)
				currentData *= 10;
				currentData += buffer[i] - '0';
			}
		}
		stacker.shrink_to_fit();
	}

	std::vector<std::unique_ptr<Block>> block;
	block.reserve(100);
	std::unique_ptr<Factory> NBFac[FACTORY_NUM] = {
		std::make_unique< BlockFactory>(BLOCKTYPE::BLOCK),											//  1.動かない
		std::make_unique< BlockFactory>(BLOCKTYPE::ENEMY),											//  2.動かない敵
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::UP),			//  3.移動敵上
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::DOWN),			//  4.移動敵下
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::LEFT),			//  5.移動敵左
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::RIGHT),			//  6.移動敵右
		std::make_unique<CBlockFactory>(BLOCKTYPE::ENEMY),											//  7.移動敵円
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::UP),			//  8.移動上
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::DOWN),			//  9.移動下
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::LEFT),			// 10.移動左
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::RIGHT),			// 11.移動右
		std::make_unique<DBlockFactory>(BLOCKTYPE::BLOCK, DBlockFactory::DIRECTION::VERTICAL, mc),	// 12.ドッス縦
		std::make_unique<DBlockFactory>(BLOCKTYPE::BLOCK, DBlockFactory::DIRECTION::HORIZON, mc),	// 13.ドッス横
		std::make_unique<BBlockFactory>(BLOCKTYPE::BLOCK),											// 14.点滅
		std::make_unique<FBlockFactory>(BLOCKTYPE::ENEMY, mc),										// 15.弾打敵
		std::make_unique<RBlockFactory>(BLOCKTYPE::ENEMY, mc),										// 16.突進
		std::make_unique<CoinFactory>()																// 17.コイン
	};
	
	int type = 0;
	int objtype = 0;
	for (int i = 0; i < stacker.size(); i++)
	{
		type = stacker[i] / 100 - 1;
		objtype = stacker[i] % 100;

		if (type < 0 || type >= FACTORY_NUM) continue;

		int amari = i % CHIP_NUMX;
		int waru = i / CHIP_NUMX;

		block.push_back(NBFac[type]->MakeBlock(math::Int2(amari, waru), objtype));
	}
	block.shrink_to_fit();

	return block;
}

float LoadChip::GetStageY(void)
{

	return stacker.size() / CHIP_NUMX * GameObject::Chipsize;
}
