/*===========================================================================
	Date : 2022/02/11(金)	GameCreateSystem.h
		Author	: がむしるぉ
		Update	:
		Comment	: Baseデータの塊 Game制作のベース部分ヘッダー
===========================================================================*/
#ifndef GAMECREATESYSTEM_H_
#define GAMECREATESYSTEM_H_


// おこらないで
#pragma warning(disable : 4244)

//入力処理
#include "Input.h"
#include "Controller.h"

//描画処理
#include "Fade.h"
#include "Sprite.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Movie.h"

//サウンド処理
#include "BGM.h"
#include "SE.h"
#include "SoundManager.h"

//MyClass
#include "Original/MathManager.h"

#endif // !GAMECREATESYSTEM_H_

