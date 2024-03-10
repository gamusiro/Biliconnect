/*=========================================================================
	Date : 2022/04/26(‰Î)	ObjectManager.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef OBJMANAGER_H_
#define OBJMANAGER_H_

#include <vector>
#include <memory>
#include "GameCreateSystem.h"

class Block;
class MoveChan;
class DefeatEffect;
class DefeatEffect2;
class DefeatEffect3;
class CharacterEffect;

class ObjectManager
{
public:
	ObjectManager(std::vector<std::unique_ptr<Block>> blocks, MoveChan& movechan, DefeatEffect& df, DefeatEffect2& df2, DefeatEffect3& df3, CharacterEffect& cf);
	~ObjectManager();

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::vector<std::unique_ptr<Block>> m_Blocks;
	MoveChan& m_MoveChan;
	DefeatEffect&  m_DEffect;
	DefeatEffect2& m_DEffect2;
	DefeatEffect3& m_DEffect3;
	CharacterEffect& m_CharcterEffect;
	
};

#endif
