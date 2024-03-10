/*=========================================================================
	Date : 2022/04/25(月)	BlockFactory.h
		Author : A.I.
		Update :
		Comment: 禁忌を犯します
=========================================================================*/
#ifndef BFACTORY_H_
#define BFACTORY_H_

#include <memory>
#include "GameCreateSystem.h"
#include "GameObject.h"

#include "Block.h"
#include "MoveChan.h"

class Factory
{
public:
	Factory(BLOCKTYPE type) : _type(type)
	{
		if (type == BLOCKTYPE::ENEMY)	SIZE = { SMALL_E, SMALL_E };
		else							SIZE = { SMALL_B, SMALL_B };
	}

	virtual std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype) = 0;

protected:
	constexpr static float SMALL_B = GameObject::Chipsize;
	constexpr static float SMALL_E = 100;
	constexpr static float MEDIUM = 2;
	constexpr static float BIG = 3;
protected:
	BLOCKTYPE		_type;		// ブロックor敵
	math::Float2	_position;	// 位置
	math::Float2	_size = {};	// サイズ
	math::Float2	SIZE;		// サイズ(デフォルト)
};

// 移動しない
class BlockFactory : public Factory
{
public:
	BlockFactory(BLOCKTYPE type) : Factory(type) {}
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;
};

// 移動する
class MoveBlock;
class MBlockFactory : public Factory
{
public:
	enum DIRECTION
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
		MAX
	};

	// DIRECTION：移動方向
	MBlockFactory(BLOCKTYPE type, DIRECTION dir);
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;

private:
	constexpr static float SLOW = 5;
	constexpr static float FAST = SLOW * 3;

private:
	math::Float2	lenght = {};
	float			speed = 0;
	math::Float2	direction;
};

// 円
class MoveCircle;
class CBlockFactory : public Factory
{
public:
	CBlockFactory(BLOCKTYPE type) : Factory(type) {}
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;

private:
	constexpr static float SLOW = 3;
	constexpr static float FAST = SLOW * 3;

private:
	float	lenght = {};
	float	speed = 0;
};

// doss
class MoveDossun;
class MoveChan;
class DBlockFactory : public Factory
{
public:
	enum DIRECTION
	{
		VERTICAL = 0,	// Y移動
		HORIZON,		// X移動
		MAX
	};

public:
	DBlockFactory(BLOCKTYPE type, DIRECTION dir, MoveChan& mc);
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;

private:
	math::Float2	lenght = {};
	math::Float2	default_dir;
	math::Float2	direction;
	MoveChan& _mc;
};

// 点滅
class BlinkBlock;
class BBlockFactory : public Factory
{
public:
	BBlockFactory(BLOCKTYPE type) : Factory(type) {}
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;

private:
	constexpr static float INTERVAL_DEFAULT = 1;
private:
	float interval = INTERVAL_DEFAULT;
};

// たまうち
class BulletBlock;
class FBlockFactory : public Factory
{
public:
	FBlockFactory(BLOCKTYPE type, MoveChan& mc) : Factory(type), _mc(mc) {}
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;

private:
	MoveChan& _mc;
};

// とっしｎ
class BulletBlock;
class RBlockFactory : public Factory
{
public:
	RBlockFactory(BLOCKTYPE type, MoveChan& mc) : Factory(type), _mc(mc) {}
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;

private:
	MoveChan& _mc;

};


// coin
class CoinFactory : public Factory
{
public:
	CoinFactory();
	std::unique_ptr<Block> MakeBlock(math::Int2 pos, int objecttype = 0) override;
};

#endif
