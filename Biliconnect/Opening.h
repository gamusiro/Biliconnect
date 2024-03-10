/*=========================================================================
	Date : 2022/05/30(Œ)	Opening.h
		Author : ‚ª‚Ş‚µ‚é‚§
		Update :
=========================================================================*/
#ifndef OPENING_H_
#define OPENING_H_

#include "GameCreateSystem.h"
#include "SceneInterface.h"

class Opening : public SceneInterface
{
public:
	void Init();	//‰Šú‰»ˆ—
	void Uninit();	//I—¹ˆ—
	void Update();	//XVˆ—
	void Draw();	//•`‰æˆ—
};

#endif // !OPENING_H_