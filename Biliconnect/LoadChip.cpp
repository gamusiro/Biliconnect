/*=========================================================================
	Date : 2021/04/30(��)	LoadChip.cpp
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
	// �v�Z���ʂ��i�[����
	{
		std::string buffer;
		std::string filename = "Material/Data/" + std::to_string(StageNum::Get()) + ".csv";
		FileIO file(buffer, filename);

		int currentData = 0;
		for (size_t i = 0; i < buffer.size(); i++)
		{
			if (buffer[i] == ',')
			{// �J���}������Ƃ��f�[�^���m�肷��
				stacker.push_back(currentData);
				currentData = 0;
			}
			else if (buffer[i] == '\r')
			{// \r�͍s�̍Ō�̕����̌��ɂ���̂ł������Ɏg��
				stacker.push_back(currentData);
				currentData = 0;
			}
			else if (buffer[i] == '\n')
			{// ���s�����͖�������(������J�E���g����΍s�����킩��)
			}
			else
			{// ���l�f�[�^�̏ꍇ�͐��l�ɕϊ����Ă���(����)
				currentData *= 10;
				currentData += buffer[i] - '0';
			}
		}
		stacker.shrink_to_fit();
	}

	std::vector<std::unique_ptr<Block>> block;
	block.reserve(100);
	std::unique_ptr<Factory> NBFac[FACTORY_NUM] = {
		std::make_unique< BlockFactory>(BLOCKTYPE::BLOCK),											//  1.�����Ȃ�
		std::make_unique< BlockFactory>(BLOCKTYPE::ENEMY),											//  2.�����Ȃ��G
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::UP),			//  3.�ړ��G��
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::DOWN),			//  4.�ړ��G��
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::LEFT),			//  5.�ړ��G��
		std::make_unique<MBlockFactory>(BLOCKTYPE::ENEMY, MBlockFactory::DIRECTION::RIGHT),			//  6.�ړ��G�E
		std::make_unique<CBlockFactory>(BLOCKTYPE::ENEMY),											//  7.�ړ��G�~
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::UP),			//  8.�ړ���
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::DOWN),			//  9.�ړ���
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::LEFT),			// 10.�ړ���
		std::make_unique<MBlockFactory>(BLOCKTYPE::BLOCK, MBlockFactory::DIRECTION::RIGHT),			// 11.�ړ��E
		std::make_unique<DBlockFactory>(BLOCKTYPE::BLOCK, DBlockFactory::DIRECTION::VERTICAL, mc),	// 12.�h�b�X�c
		std::make_unique<DBlockFactory>(BLOCKTYPE::BLOCK, DBlockFactory::DIRECTION::HORIZON, mc),	// 13.�h�b�X��
		std::make_unique<BBlockFactory>(BLOCKTYPE::BLOCK),											// 14.�_��
		std::make_unique<FBlockFactory>(BLOCKTYPE::ENEMY, mc),										// 15.�e�œG
		std::make_unique<RBlockFactory>(BLOCKTYPE::ENEMY, mc),										// 16.�ːi
		std::make_unique<CoinFactory>()																// 17.�R�C��
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
