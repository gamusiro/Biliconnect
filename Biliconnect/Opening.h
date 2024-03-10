/*=========================================================================
	Date : 2022/05/30(月)	Opening.h
		Author : がむしるぉ
		Update :
=========================================================================*/
#ifndef OPENING_H_
#define OPENING_H_

#include "GameCreateSystem.h"
#include "SceneInterface.h"

class Opening : public SceneInterface
{
public:
	void Init();	//初期化処理
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Draw();	//描画処理
};

#endif // !OPENING_H_