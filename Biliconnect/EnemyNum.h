/*=========================================================================
	Date : 2022/05/13(‹à)	EnemyNum.h
		Author : Mr.
		Update :
=========================================================================*/
#ifndef ENEMYNUM_H_
#define ENEMYNUM_H_

#include "GameCreateSystem.h"

class EnemyNum
{
public:

	static void Add() { Num += 1; }
	static void Reset() { Num = 0; KillNum = 0; }
	static int	Get(void) { return Num; }

	static void Kill() { KillNum += 1; }
	static int	GetKill(void) { return KillNum; }

private:
	static int Num;// “G‚Ì”
	static int KillNum;// “|‚µ‚½“G‚Ì”

};
__declspec(selectany) int EnemyNum::Num(0);
__declspec(selectany) int EnemyNum::KillNum(0);

#endif
