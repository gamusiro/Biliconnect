/*
*	Date : 2022/05/12(��)
*		Author	: Mr.
*		Update	: ----/--/--()
*/
#pragma once


class SaveStage
{
public:
	struct NowData
	{
		int coin;
		int life;
		int kill;
		int enemymax;
	};

public:
	/*
	* @ brief \
	*	�ݒ菈��
	*/
	static void		Set(int stageNum, NowData& data);

	/*
	* @ brief \
	*	�擾����
	*/
	static NowData Get(int stagerNum);

private:
	constexpr static int SAVEDATA_MAX = 26;	// �Z�[�u�f�[�^�̊֐�

private:
	static NowData m_Data[SAVEDATA_MAX];	// ���݂̃X�e�[�W�̃f�[�^�ϐ�
};

