/*=========================================================================
	Date : 2022/04/26(‰Î)	ObjectManager.h
		Author : A.I.
		Update :
=========================================================================*/
#include "ObjectManager.h"
#include "Block.h"

ObjectManager::ObjectManager(std::vector<std::unique_ptr<Block>> blocks,MoveChan& movechan, DefeatEffect& df, DefeatEffect2& df2, DefeatEffect3& df3, CharacterEffect& cf)
	: m_MoveChan(movechan), m_DEffect(df), m_DEffect2(df2), m_DEffect3(df3), m_CharcterEffect(cf)
{
	m_Blocks.insert(m_Blocks.end(), std::make_move_iterator(blocks.begin()), std::make_move_iterator(blocks.end()));
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
}

void ObjectManager::Uninit()
{
}

void ObjectManager::Update()
{
	for (auto& it : m_Blocks)
	{
		it->Update();
		it->CheckCollision(m_MoveChan, m_DEffect, m_DEffect2, m_DEffect3, m_CharcterEffect);
	}
}

void ObjectManager::Draw()
{
	for (auto& it : m_Blocks)
	{
		it->Draw();
	}
}
