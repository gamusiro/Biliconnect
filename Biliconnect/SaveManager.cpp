/*
*	Date : 2022/05/11(��)
*		Author	: ���ނ��邧
*		Update	: ----/--/--()
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "SaveManager.h"


SaveManager::SaveData SaveManager::m_Save[SaveManager::SAVEDATA_MAX]{};

// �ǂݍ��ݏ���
void SaveManager::Load()
{
	// �t�@�C���ǂݍ���
	FILE* pFile = nullptr;
	pFile = std::fopen("SaveData.sev", "rb");
	if (!pFile)
		return;
	
	// �f�[�^�̓ǂݎ��
	std::fread(m_Save, sizeof(SaveData), SAVEDATA_MAX, pFile);

	// �t�@�C�������
	std::fclose(pFile);
}

// �Z�[�u�f�[�^��ݒ肷��
void SaveManager::Set(int stageNum, SaveData& data)
{
	m_Save[stageNum] = data;
}

// �f�[�^�̎擾����
SaveManager::SaveData SaveManager::Get(int stagerNum)
{
	return m_Save[stagerNum];
}

// �����o��
void SaveManager::Write()
{
	// �t�@�C���ǂݍ���
	FILE* pFile = nullptr;
	pFile = std::fopen("SaveData.sev", "wb");
	if (!pFile)
		return;

	// �f�[�^�̓ǂݎ��
	std::fwrite(m_Save, sizeof(SaveData), SAVEDATA_MAX, pFile);

	// �t�@�C�������
	std::fclose(pFile);
}
