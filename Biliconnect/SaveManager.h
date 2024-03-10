/*
*	Date : 2022/05/11(水)
*		Author	: がむしるぉ
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
	*	初期化処理
	*/
	static void		Load();
	
	/*
	* @ brief \
	*	設定処理
	*/
	static void		Set(int stageNum, SaveData& data);
	
	/*
	* @ brief \
	*	取得処理
	*/
	static SaveData Get(int stagerNum);
	
	/*
	* @ brief \
	*	終了処理
	*/
	static void		Write();

private:
	constexpr static int SAVEDATA_MAX = 26;	// セーブデータの関数

private:
	static SaveData m_Save[SAVEDATA_MAX];	// セーブデータの格納変数
};

