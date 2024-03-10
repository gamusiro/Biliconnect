/*=========================================================================
	Date : 2021/12/19(日)	BGM.h
		Author : がむしるぉ
		Update : 2021/12/19(日)
=========================================================================*/
#ifndef BGM_H_
#define BGM_H_

#include "SoundInterface.h"

class BGM : public SoundInterface
{
public:
	BGM();
	~BGM();

public:
	/*
	* @ brief
	*		音楽データをロードする
	* @ param 
	*		fileName : ファイルの名前
	* @ comment
	*		内部でMaterial/Sound/BGM/fileNameのパスに変換される
	*/
	void Load(const char* fileName) override;

	/*
	* @ brief
	*		音楽データを再生する
	* @ param
	*		loopCount : ループ回数
	*/
	void Play(int loopCount = -1) override;

	/*
	* @ brief
	*		音楽データを一時停止する
	*/
	void Pause() override;

	/*
	* @ brief
	*		音楽データを停止する
	*/
	void Stop() override;

	/*
	* @ brief
	*		音楽データの音量設定
	* @ param
	*		volume : 音量の設定(0 ~ 100)
	*/
	void SetVolume(int volume) override;

	/*
	* @ brief
	*		出力デバイスのの音量設定
	* @ param
	*		left  : 音量の設定(0 ~ 100)
	*		right : 音量の設定(0 ~ 100)
	*		degree: 角度
	* @ comment
	*		対応スタイルは5.1chのみ
	*/
	void SetPanning(int left, int right, float degree = 45.0f) override;
};

#endif // !BGM_H_



