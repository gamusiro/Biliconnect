/*
*	Date : 2022/05/11(��)
*		Author	: ���ނ��邧
*		Update	: ----/--/--()
*/
#pragma once


class SaveManager
{
public:
	struct SaveData
	{
		int coin;
		int life;
		int kill;
	};

public:
	/*
	* @ brief \
	*	����������
	*/
	static void		Load();
	
	/*
	* @ brief \
	*	�ݒ菈��
	*/
	static void		Set(int stageNum, SaveData& data);
	
	/*
	* @ brief \
	*	�擾����
	*/
	static SaveData Get(int stagerNum);
	
	/*
	* @ brief \
	*	�I������
	*/
	static void		Write();

private:
	constexpr static int SAVEDATA_MAX = 26;	// �Z�[�u�f�[�^�̊֐�

private:
	static SaveData m_Save[SAVEDATA_MAX];	// �Z�[�u�f�[�^�̊i�[�ϐ�
};

