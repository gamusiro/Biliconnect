/*
*	Date : 2022/05/12(木)
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
	*	設定処理
	*/
	static void		Set(int stageNum, NowData& data);

	/*
	* @ brief \
	*	取得処理
	*/
	static NowData Get(int stagerNum);

private:
	constexpr static int SAVEDATA_MAX = 26;	// セーブデータの関数

private:
	static NowData m_Data[SAVEDATA_MAX];	// 現在のステージのデータ変数
};

