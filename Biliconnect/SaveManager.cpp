/*
*	Date : 2022/05/11(水)
*		Author	: がむしるぉ
*		Update	: ----/--/--()
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "SaveManager.h"


SaveManager::SaveData SaveManager::m_Save[SaveManager::SAVEDATA_MAX]{};

// 読み込み処理
void SaveManager::Load()
{
	// ファイル読み込み
	FILE* pFile = nullptr;
	pFile = std::fopen("SaveData.sev", "rb");
	if (!pFile)
		return;
	
	// データの読み取り
	std::fread(m_Save, sizeof(SaveData), SAVEDATA_MAX, pFile);

	// ファイルを閉じる
	std::fclose(pFile);
}

// セーブデータを設定する
void SaveManager::Set(int stageNum, SaveData& data)
{
	m_Save[stageNum] = data;
}

// データの取得処理
SaveManager::SaveData SaveManager::Get(int stagerNum)
{
	return m_Save[stagerNum];
}

// 書き出し
void SaveManager::Write()
{
	// ファイル読み込み
	FILE* pFile = nullptr;
	pFile = std::fopen("SaveData.sev", "wb");
	if (!pFile)
		return;

	// データの読み取り
	std::fwrite(m_Save, sizeof(SaveData), SAVEDATA_MAX, pFile);

	// ファイルを閉じる
	std::fclose(pFile);
}
