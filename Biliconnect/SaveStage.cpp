/*
*	Date : 2022/05/12(木)
*		Author	: Mr.
*		Update	: ----/--/--()
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "SaveStage.h"


SaveStage::NowData SaveStage::m_Data[SaveStage::SAVEDATA_MAX]{};

// セーブデータを設定する
void SaveStage::Set(int stageNum, NowData& data)
{
	m_Data[stageNum] = data;
}

// データの取得処理
SaveStage::NowData SaveStage::Get(int stagerNum)
{
	return m_Data[stagerNum];
}