/*=========================================================================
	Date : 2021/12/20(月)	SE.h
		Author : がむしるぉ
		Update : 
=========================================================================*/
#ifndef SE_H_
#define SE_H_

#include "SoundInterface.h"

class SE : public SoundInterface
{
public:
	SE();
	~SE();

public:
	/*
	* @ brief
	*		音楽データをロードする
	* @ param
	*		fileName : ファイルの名前
	* @ comment
	*		内部でMaterial/Sound/SE/fileNameのパスに変換される
	*/
	void Load(const char* fileName) override;

	/*
	* @ brief \
	*		リバーブの設定処理
	* @ param \
	*		
	*/
	void SetReverb(const char* fileName);

	/*
	* @ brief
	*		音楽データを再生する
	* @ param
	*		loopCount : ループ回数
	*/
	void Play(int loopCount) override;
	
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
	void SetPanning(int left, int right, float degree = 45.0f);
};

#endif // !SE_H_
