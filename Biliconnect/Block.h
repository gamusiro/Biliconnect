/*=========================================================================
	Date : 2021/03/05(�y)	Block.h
		Author : A.I.
		Update :
=========================================================================*/
#ifndef BLOCK_H_
#define BLOCK_H_

#include "GameCreateSystem.h"
#include "GameObject.h"
#include "GoalEffect.h"
class Line;
class MoveChan;
class DefeatEffect;
class DefeatEffect2;
class DefeatEffect3;
class CharacterEffect;
class GoalEffect;

enum class BLOCKTYPE
{
	BLOCK = 0,
	ENEMY,
	ITEM,
	MAX
};

class Block : public GameObject
{
public:
	Block() = delete;
	Block(BLOCKTYPE type, math::Float2 pos, math::Float2 size = { Chipsize,Chipsize }, int num = 5, int color = 0);

	void Update() override;
	void Draw() override;

	void CheckCollision(MoveChan& movechan, DefeatEffect& df, DefeatEffect2& df2, DefeatEffect3& df3, CharacterEffect& ch);		// �Փ˔���

protected:
	virtual void CollisionAction();							// �Փˎ�����

	BLOCKTYPE	m_Type;
	Texture		EffectTex;

	int m_Frame = 0;
	int m_Num;// �u���b�N�e�N�X�`���̔ԍ�
	int m_color;


	bool isBlink;
	bool isDoss;
	bool isCoin;
};

#endif
