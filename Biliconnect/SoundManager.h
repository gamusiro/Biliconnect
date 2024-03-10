/*=========================================================================
	Date : 2021/12/18(土)	SoundManager.h
		Author : がむしるぉ
		Update : 2021/12/19(日)
=========================================================================*/
#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <Windows.h>
#include "XAudio2.h"
#include <xaudio2fx.h>

#pragma comment(lib, "xaudio2.lib")

#define SOUNDMANAGER_INOUTPUT_CAHNNELS	2
#define SOUNDMANAGER_SAMPLING_RATE		44100

#define MAX_SOUND_NUM	100

class SoundManager
{
public:
	static bool Init();		//初期化処理
	static void Unload();	//全解放処理
	static void Uninit();	//終了処理

private:
	//メンバ関数
	static int  Load(const char* folderName, const char* fileName);			//読み込み処理
	static void Play(int index, int loopCnt);								//再生処理
	static void Pause(int index);											//一時停止処理
	static void Stop(int index);											//停止処理
	static void SetVolume(int index, int value);							//音量調節処理
	static void SetPanning(int index, int left, int right, float degree);	//パンニングの設定処理
	static void SetReverb(int index, const char* fileName);					//リバーブの設定処理

private:
	static IXAudio2*				m_XA2;
	static IXAudio2MasteringVoice*	m_XA2MV;
	static IXAudio2SourceVoice*		m_XA2SV[MAX_SOUND_NUM];
	static IXAudio2SubmixVoice*		m_XA2SubV[MAX_SOUND_NUM];
	static BYTE*					m_AudioData[MAX_SOUND_NUM];
	static DWORD					m_AudioSize[MAX_SOUND_NUM];
	static DWORD					m_AudioIndex;

private:
	friend class BGM;
	friend class SE;
};

#endif // !SOUNDMANAGER_H_



