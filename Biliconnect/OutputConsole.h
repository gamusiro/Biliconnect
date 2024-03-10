/*=========================================================================
	Date : 2021/01/21(金)	OutputConsole.h
		Author	: がむしるぉ
		Update	:
		Comment	:
		※古本氏の資料データを簡易的に利用する暮らす(Living)
=========================================================================*/
#ifndef OUTPUTCONSOLE_H_
#define OUTPUTCONSOLE_H_

#include <stdio.h>
#include <Windows.h>

class OutputConsole
{
public:
	void Init();	//初期化処理
	void Uninit();	//終了処理
	void Update();	//更新処理
	void Clear();	//コンソールウィンドウのクリア処理

private:
	FILE*	m_Output;		
	HANDLE	m_Console;		//コンソールのハンドル
	COORD	m_CurosrPos;	//コンソール内のカーソルポジション
};

#endif // !OUTPUTCONSOLE_H_

