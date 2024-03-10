/*=========================================================================
	Date : 2022/04/25(月)	BlockFactory.cpp
		Author : A.I.
		Update :
=========================================================================*/
#include "BlockFactory.h"

using namespace math;

//
// 通常ブロック
//
std::unique_ptr<Block> BlockFactory::MakeBlock(Int2 pos, int objecttype)
{
	_position = {};
	_size = SIZE;

	int type = objecttype / 10;
	int color = objecttype % 10;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	if (_type == BLOCKTYPE::ENEMY)
	{
		switch (color)
		{
		case 0:
			_size *= 1;
			break;
		case 1:
			_size *= MEDIUM;
			break;
		case 2:
			_size *= BIG;
			break;
		default: break;
		}
	}

	return std::make_unique<Block>(_type, _position, _size, type, color);
}

//
// 移動ブロック
//
#include "MoveBlock.h"
MBlockFactory::MBlockFactory(BLOCKTYPE type, DIRECTION dir) : Factory(type)
{
	switch (dir)
	{
	case DIRECTION::UP:
		direction.x = 0;
		direction.y = -1;
		break;
	case DIRECTION::DOWN:
		direction.x = 0;
		direction.y = 1;
		break;
	case DIRECTION::LEFT:
		direction.x = -1;
		direction.y = 0;
		break;
	case DIRECTION::RIGHT:
		direction.x = 1;
		direction.y = 0;
		break;
	default: direction = {}; break;
	}
}
std::unique_ptr<Block> MBlockFactory::MakeBlock(Int2 pos, int objecttype)
{
	_position = {};
	lenght = {};
	speed = 0;
	_size = SIZE;

	int sizespd = objecttype / 10;
	int directi = objecttype % 10;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	// サイズ・速さ指定
	switch (sizespd)
	{
	case 0:
		speed = SLOW;
		break;
	case 1:
		speed = FAST;
		break;
	case 2:
		_size *= MEDIUM;
		speed = SLOW;
		break;
	case 3:
		_size *= MEDIUM;
		speed = FAST;
		break;
	case 4:
		_size *= BIG;
		speed = SLOW;
		break;
	case 5:
		_size *= BIG;
		speed = FAST;
		break;
	default: break;
	}

	// 移動幅
	switch (directi)
	{
	case 0:
		lenght = Float2(GameObject::Chipsize * 3, GameObject::Chipsize * 3) * direction;
		break;
	case 1:
		lenght = Float2(GameObject::Chipsize * 4, GameObject::Chipsize * 4) * direction;
		break;
	case 2:
		lenght = Float2(GameObject::Chipsize * 5, GameObject::Chipsize * 5) * direction;
		break;
	case 3:
		lenght = Float2(GameObject::Chipsize * 6, GameObject::Chipsize * 6) * direction;
		break;
	case 4:
		lenght = Float2(GameObject::Chipsize * 7, GameObject::Chipsize * 7) * direction;
		break;
	case 5:
		lenght = Float2(GameObject::Chipsize * 8, GameObject::Chipsize * 8) * direction;
		break;
	case 6:
		lenght = Float2(GameObject::Chipsize * 9, GameObject::Chipsize * 9) * direction;
		break;
	case 7:
		lenght = Float2(GameObject::Chipsize * 12, GameObject::Chipsize * 12) * direction;
		break;
	case 8:
		lenght = Float2(GameObject::Chipsize * 16, GameObject::Chipsize * 16) * direction;
		break;
	case 9:
		lenght = Float2(GameObject::Chipsize * 14, GameObject::Chipsize * 14) * direction;
		break;
	default: break;
	}

	return std::make_unique<MoveBlock>(_type, speed, lenght, _position, _size);
}

//
// 円移動
//
#include "MoveCircle.h"
std::unique_ptr<Block> CBlockFactory::MakeBlock(Int2 pos, int objecttype)
{
	_position = {};
	lenght = {};
	speed = 0;
	_size = SIZE;

	int size = objecttype / 10;
	int spelen = objecttype % 10;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	switch (size)
	{
	case 1:
		_size *= MEDIUM;
		break;
	case 2:
		_size *= BIG;
		break;
	default:
		break;
	}

	switch (spelen)
	{
	case 0:
		lenght = 500;
		speed = 2.5;
		break;
	case 1:
		lenght = 800;
		speed = 2.5;
		break;
	case 2:
		lenght = 500;
		speed = -2.5;
		break;
	default:
		lenght = 800;
		speed = -2.5;
		break;
	}

	return std::make_unique<MoveCircle>(_type, speed, lenght, _position, _size);
}

//
// doss
//
#include "MoveDossun.h"
#include "MoveChan.h"
DBlockFactory::DBlockFactory(BLOCKTYPE type, DIRECTION dir, MoveChan& mc) : Factory(type), _mc(mc)
{
	switch (dir)
	{
	case DIRECTION::VERTICAL:
		default_dir.x = 0;
		default_dir.y = 1;
		break;
	case DIRECTION::HORIZON:
		default_dir.x = 1;
		default_dir.y = 0;
		break;
	default: default_dir = {}; break;
	}
}
std::unique_ptr<Block> DBlockFactory::MakeBlock(math::Int2 pos, int objecttype)
{
	_position = {};
	lenght = {};
	_size = Float2(SIZE.x, SIZE.y);
	direction = default_dir;

	int sizespd = objecttype / 10;
	int directi = objecttype % 10;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	// サイズ・速さ指定
	switch (sizespd)
	{
	case 1:
		direction *= -1;
		break;
	case 2:
		_size *= MEDIUM;
		break;
	case 3:
		_size *= MEDIUM;
		direction *= -1;
		break;
	case 4:
		_size *= BIG;
		break;
	case 5:
		_size *= BIG;
		direction *= -1;
		break;
	default: break;
	}

	// 移動幅
	switch (directi)
	{
	case 0:
		lenght = Float2(GameObject::Chipsize * 3, GameObject::Chipsize * 3) * direction;
		break;
	case 1:
		lenght = Float2(GameObject::Chipsize * 4, GameObject::Chipsize * 4) * direction;
		break;
	case 2:
		lenght = Float2(GameObject::Chipsize * 5, GameObject::Chipsize * 5) * direction;
		break;
	case 3:
		lenght = Float2(GameObject::Chipsize * 6, GameObject::Chipsize * 6) * direction;
		break;
	case 4:
		lenght = Float2(GameObject::Chipsize * 7, GameObject::Chipsize * 7) * direction;
		break;
	case 5:
		lenght = Float2(GameObject::Chipsize * 8, GameObject::Chipsize * 8) * direction;
		break;
	case 6:
		lenght = Float2(GameObject::Chipsize * 9, GameObject::Chipsize * 9) * direction;
		break;
	case 7:
		lenght = Float2(GameObject::Chipsize * 12, GameObject::Chipsize * 12) * direction;
		break;
	case 8:
		lenght = Float2(GameObject::Chipsize * 16, GameObject::Chipsize * 16) * direction;
		break;
	case 9:
		lenght = Float2(GameObject::Chipsize * 14, GameObject::Chipsize * 14) * direction;
		break;
	default: break;
	}

	return std::make_unique<MoveDossun>(_type, _mc.GetPos(), _mc.GetSize(), lenght, _position, _size);
}

//
// 点滅
//
#include "BlinkBlock.h"
std::unique_ptr<Block> BBlockFactory::MakeBlock(math::Int2 pos, int objecttype)
{
	int type = objecttype / 10;
	int color = objecttype % 10;

	_position = {};
	_size = SIZE;
	interval = INTERVAL_DEFAULT;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	switch (objecttype)
	{
	case 1:
		_size *= MEDIUM;
		break;
	case 2:
		_size *= BIG;
		break;
	default:
		break;
	}

	return std::make_unique<BlinkBlock>(_type, interval, _position, type, color);
}

//
// たまうち
//
#include "BulletBlock.h"
std::unique_ptr<Block> FBlockFactory::MakeBlock(math::Int2 pos, int objecttype)
{
	_position = {};
	_size = SIZE;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	switch (objecttype)
	{
	case 1:
		_size *= MEDIUM;
		break;
	case 2:
		_size *= BIG;
		break;
	default:
		break;
	}

	return std::make_unique<BulletBlock>(_type, _mc, 0.f, Float2(0, 0), _position, _size);
}

//
// とっしん
//
#include "RushBlock.h"
std::unique_ptr<Block> RBlockFactory::MakeBlock(math::Int2 pos, int objecttype)
{
	_position = {};
	_size = SIZE;

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	switch (objecttype)
	{
	case 1:
		_size *= MEDIUM;
		break;
	case 2:
		_size *= BIG;
		break;
	default:
		break;
	}

	return std::make_unique<RushBlock>(_type, _mc, _position, _size);
}

//
// coin
//
#include "Coin.h"
CoinFactory::CoinFactory() : Factory(BLOCKTYPE::ITEM)
{
}

std::unique_ptr<Block> CoinFactory::MakeBlock(Int2 pos, int objecttype)
{
	int num = objecttype % 10;

	_position = {};

	_position.x = pos.x * GameObject::Chipsize + GameObject::Offset;
	_position.y = pos.y * GameObject::Chipsize + GameObject::Offset;

	return std::make_unique<Coin>(_type, _position, num);
}
